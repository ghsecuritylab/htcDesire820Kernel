/***********************************************************************
*
* radius.c
*
* RADIUS plugin for pppd.  Performs PAP, CHAP, MS-CHAP, MS-CHAPv2
* authentication using RADIUS.
*
* Copyright (C) 2002 Roaring Penguin Software Inc.
*
* Based on a patch for ipppd, which is:
*    Copyright (C) 1996, Matjaz Godec <gody@elgo.si>
*    Copyright (C) 1996, Lars Fenneberg <in5y050@public.uni-hamburg.de>
*    Copyright (C) 1997, Miguel A.L. Paraz <map@iphil.net>
*
* Uses radiusclient library, which is:
*    Copyright (C) 1995,1996,1997,1998 Lars Fenneberg <lf@elemental.net>
*    Copyright (C) 2002 Roaring Penguin Software Inc.
*
* MPPE support is by Ralf Hofmann, <ralf.hofmann@elvido.net>, with
* modification from Frank Cusack, <frank@google.com>.
*
* This plugin may be distributed according to the terms of the GNU
* General Public License, version 2 or (at your option) any later version.
*
***********************************************************************/
static char const RCSID[] =
"$Id: radius.c,v 1.28 2004/11/14 10:27:57 paulus Exp $";

#include "pppd.h"
#include "chap-new.h"
#ifdef CHAPMS
#include "chap_ms.h"
#ifdef MPPE
#include "md5.h"
#endif
#endif
#include "radiusclient.h"
#include "fsm.h"
#include "ipcp.h"
#include <syslog.h>
#include <sys/types.h>
#include <sys/time.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>

#define BUF_LEN 1024

#define MD5_HASH_SIZE	16

static char *config_file = NULL;
static int add_avp(char **);
static struct avpopt {
    char *vpstr;
    struct avpopt *next;
} *avpopt = NULL;
static bool portnummap = 0;

static option_t Options[] = {
    { "radius-config-file", o_string, &config_file },
    { "avpair", o_special, add_avp },
    { "map-to-ttyname", o_bool, &portnummap,
	"Set Radius NAS-Port attribute value via libradiusclient library", OPT_PRIO | 1 },
    { "map-to-ifname", o_bool, &portnummap,
	"Set Radius NAS-Port attribute to number as in interface name (Default)", OPT_PRIOSUB | 0 },
    { NULL }
};

static int radius_secret_check(void);
static int radius_pap_auth(char *user,
			   char *passwd,
			   char **msgp,
			   struct wordlist **paddrs,
			   struct wordlist **popts);
static int radius_chap_verify(char *user, char *ourname, int id,
			      struct chap_digest_type *digest,
			      unsigned char *challenge,
			      unsigned char *response,
			      char *message, int message_space);

static void radius_ip_up(void *opaque, int arg);
static void radius_ip_down(void *opaque, int arg);
static void make_username_realm(char *user);
static int radius_setparams(VALUE_PAIR *vp, char *msg, REQUEST_INFO *req_info,
			    struct chap_digest_type *digest,
			    unsigned char *challenge,
			    char *message, int message_space);
static void radius_choose_ip(u_int32_t *addrp);
static int radius_init(char *msg);
static int get_client_port(char *ifname);
static int radius_allowed_address(u_int32_t addr);
static void radius_acct_interim(void *);
#ifdef MPPE
static int radius_setmppekeys(VALUE_PAIR *vp, REQUEST_INFO *req_info,
			      unsigned char *);
static int radius_setmppekeys2(VALUE_PAIR *vp, REQUEST_INFO *req_info);
#endif

#ifndef MAXSESSIONID
#define MAXSESSIONID 32
#endif

#ifndef MAXCLASSLEN
#define MAXCLASSLEN 500
#endif

struct radius_state {
    int accounting_started;
    int initialized;
    int client_port;
    int choose_ip;
    int any_ip_addr_ok;
    int done_chap_once;
    u_int32_t ip_addr;
    char user[MAXNAMELEN];
    char config_file[MAXPATHLEN];
    char session_id[MAXSESSIONID + 1];
    time_t start_time;
    int acct_interim_interval;
    SERVER *authserver;		
    SERVER *acctserver;		
    int class_len;
    char class[MAXCLASSLEN];
    VALUE_PAIR *avp;	
};

void (*radius_attributes_hook)(VALUE_PAIR *) = NULL;

void (*radius_pre_auth_hook)(char const *user,
			     SERVER **authserver,
			     SERVER **acctserver) = NULL;

static struct radius_state rstate;

char pppd_version[] = VERSION;

void
plugin_init(void)
{
    pap_check_hook = radius_secret_check;
    pap_auth_hook = radius_pap_auth;

    chap_check_hook = radius_secret_check;
    chap_verify_hook = radius_chap_verify;

    ip_choose_hook = radius_choose_ip;
    allowed_address_hook = radius_allowed_address;

    add_notifier(&ip_up_notifier, radius_ip_up, NULL);
    add_notifier(&ip_down_notifier, radius_ip_down, NULL);

    memset(&rstate, 0, sizeof(rstate));

    strlcpy(rstate.config_file, "/etc/radiusclient/radiusclient.conf",
	    sizeof(rstate.config_file));

    add_options(Options);

    info("RADIUS plugin initialized.");
}

static int
add_avp(char **argv)
{
    struct avpopt *p = malloc(sizeof(struct avpopt));

    
    p->vpstr = strdup(*argv);
    p->next = avpopt;
    avpopt = p;

    return 1;
}

static int
radius_secret_check(void)
{
    return 1;
}

static void
radius_choose_ip(u_int32_t *addrp)
{
    if (rstate.choose_ip) {
	*addrp = rstate.ip_addr;
    }
}

static int
radius_pap_auth(char *user,
		char *passwd,
		char **msgp,
		struct wordlist **paddrs,
		struct wordlist **popts)
{
    VALUE_PAIR *send, *received;
    UINT4 av_type;
    int result;
    static char radius_msg[BUF_LEN];

    radius_msg[0] = 0;
    *msgp = radius_msg;

    if (radius_init(radius_msg) < 0) {
	return 0;
    }

    
    make_username_realm(user);

    if (radius_pre_auth_hook) {
	radius_pre_auth_hook(rstate.user,
			     &rstate.authserver,
			     &rstate.acctserver);
    }

    send = NULL;
    received = NULL;

    rstate.client_port = get_client_port(portnummap ? devnam : ifname);

    av_type = PW_FRAMED;
    rc_avpair_add(&send, PW_SERVICE_TYPE, &av_type, 0, VENDOR_NONE);

    av_type = PW_PPP;
    rc_avpair_add(&send, PW_FRAMED_PROTOCOL, &av_type, 0, VENDOR_NONE);

    rc_avpair_add(&send, PW_USER_NAME, rstate.user , 0, VENDOR_NONE);
    rc_avpair_add(&send, PW_USER_PASSWORD, passwd, 0, VENDOR_NONE);
    if (*remote_number) {
	rc_avpair_add(&send, PW_CALLING_STATION_ID, remote_number, 0,
		       VENDOR_NONE);
    } else if (ipparam)
	rc_avpair_add(&send, PW_CALLING_STATION_ID, ipparam, 0, VENDOR_NONE);

    
    if (rstate.avp)
	rc_avpair_insert(&send, NULL, rc_avpair_copy(rstate.avp));

    if (rstate.authserver) {
	result = rc_auth_using_server(rstate.authserver,
				      rstate.client_port, send,
				      &received, radius_msg, NULL);
    } else {
	result = rc_auth(rstate.client_port, send, &received, radius_msg, NULL);
    }

    if (result == OK_RC) {
	if (radius_setparams(received, radius_msg, NULL, NULL, NULL, NULL, 0) < 0) {
	    result = ERROR_RC;
	}
    }

    
    rc_avpair_free(received);
    rc_avpair_free(send);

    return (result == OK_RC) ? 1 : 0;
}

static int
radius_chap_verify(char *user, char *ourname, int id,
		   struct chap_digest_type *digest,
		   unsigned char *challenge, unsigned char *response,
		   char *message, int message_space)
{
    VALUE_PAIR *send, *received;
    UINT4 av_type;
    static char radius_msg[BUF_LEN];
    int result;
    int challenge_len, response_len;
    u_char cpassword[MAX_RESPONSE_LEN + 1];
#ifdef MPPE
    
    REQUEST_INFO request_info, *req_info = &request_info;
#else
    REQUEST_INFO *req_info = NULL;
#endif

    challenge_len = *challenge++;
    response_len = *response++;

    radius_msg[0] = 0;

    if (radius_init(radius_msg) < 0) {
	error("%s", radius_msg);
	return 0;
    }

    
    if ((digest->code != CHAP_MD5)
#ifdef CHAPMS
	&& (digest->code != CHAP_MICROSOFT)
	&& (digest->code != CHAP_MICROSOFT_V2)
#endif
	) {
	error("RADIUS: Challenge type %u unsupported", digest->code);
	return 0;
    }

    
    if (!rstate.done_chap_once) {
	make_username_realm(user);
	rstate.client_port = get_client_port (portnummap ? devnam : ifname);
	if (radius_pre_auth_hook) {
	    radius_pre_auth_hook(rstate.user,
				 &rstate.authserver,
				 &rstate.acctserver);
	}
    }

    send = received = NULL;

    av_type = PW_FRAMED;
    rc_avpair_add (&send, PW_SERVICE_TYPE, &av_type, 0, VENDOR_NONE);

    av_type = PW_PPP;
    rc_avpair_add (&send, PW_FRAMED_PROTOCOL, &av_type, 0, VENDOR_NONE);

    rc_avpair_add (&send, PW_USER_NAME, rstate.user , 0, VENDOR_NONE);

    switch (digest->code) {
    case CHAP_MD5:
	
	if (response_len != MD5_HASH_SIZE)
	    return 0;
	cpassword[0] = id;
	memcpy(&cpassword[1], response, MD5_HASH_SIZE);

	rc_avpair_add(&send, PW_CHAP_CHALLENGE,
		      challenge, challenge_len, VENDOR_NONE);
	rc_avpair_add(&send, PW_CHAP_PASSWORD,
		      cpassword, MD5_HASH_SIZE + 1, VENDOR_NONE);
	break;

#ifdef CHAPMS
    case CHAP_MICROSOFT:
    {
	
	MS_ChapResponse *rmd = (MS_ChapResponse *) response;
	u_char *p = cpassword;

	if (response_len != MS_CHAP_RESPONSE_LEN)
	    return 0;
	*p++ = id;
	
	memcpy(p, rmd->UseNT, sizeof(rmd->UseNT));
	p += sizeof(rmd->UseNT);
	memcpy(p, rmd->LANManResp, sizeof(rmd->LANManResp));
	p += sizeof(rmd->LANManResp);
	memcpy(p, rmd->NTResp, sizeof(rmd->NTResp));

	rc_avpair_add(&send, PW_MS_CHAP_CHALLENGE,
		      challenge, challenge_len, VENDOR_MICROSOFT);
	rc_avpair_add(&send, PW_MS_CHAP_RESPONSE,
		      cpassword, MS_CHAP_RESPONSE_LEN + 1, VENDOR_MICROSOFT);
	break;
    }

    case CHAP_MICROSOFT_V2:
    {
	
	MS_Chap2Response *rmd = (MS_Chap2Response *) response;
	u_char *p = cpassword;

	if (response_len != MS_CHAP2_RESPONSE_LEN)
	    return 0;
	*p++ = id;
	
	memcpy(p, rmd->Flags, sizeof(rmd->Flags));
	p += sizeof(rmd->Flags);
	memcpy(p, rmd->PeerChallenge, sizeof(rmd->PeerChallenge));
	p += sizeof(rmd->PeerChallenge);
	memcpy(p, rmd->Reserved, sizeof(rmd->Reserved));
	p += sizeof(rmd->Reserved);
	memcpy(p, rmd->NTResp, sizeof(rmd->NTResp));

	rc_avpair_add(&send, PW_MS_CHAP_CHALLENGE,
		      challenge, challenge_len, VENDOR_MICROSOFT);
	rc_avpair_add(&send, PW_MS_CHAP2_RESPONSE,
		      cpassword, MS_CHAP2_RESPONSE_LEN + 1, VENDOR_MICROSOFT);
	break;
    }
#endif
    }

    if (*remote_number) {
	rc_avpair_add(&send, PW_CALLING_STATION_ID, remote_number, 0,
		       VENDOR_NONE);
    } else if (ipparam)
	rc_avpair_add(&send, PW_CALLING_STATION_ID, ipparam, 0, VENDOR_NONE);

    
    if (rstate.avp)
	rc_avpair_insert(&send, NULL, rc_avpair_copy(rstate.avp));


    if (rstate.authserver) {
	result = rc_auth_using_server(rstate.authserver,
				      rstate.client_port, send,
				      &received, radius_msg, req_info);
    } else {
	result = rc_auth(rstate.client_port, send, &received, radius_msg,
			 req_info);
    }

    if (result == OK_RC) {
	if (!rstate.done_chap_once) {
	    if (radius_setparams(received, radius_msg, req_info, digest,
				 challenge, message, message_space) < 0) {
		error("%s", radius_msg);
		result = ERROR_RC;
	    } else {
		rstate.done_chap_once = 1;
	    }
	}
    }

    rc_avpair_free(received);
    rc_avpair_free (send);
    return (result == OK_RC);
}

static void
make_username_realm(char *user)
{
    char *default_realm;

    if ( user != NULL ) {
	strlcpy(rstate.user, user, sizeof(rstate.user));
    }  else {
	rstate.user[0] = 0;
    }

    default_realm = rc_conf_str("default_realm");

    if (!strchr(rstate.user, '@') &&
	default_realm &&
	(*default_realm != '\0')) {
	strlcat(rstate.user, "@", sizeof(rstate.user));
	strlcat(rstate.user, default_realm, sizeof(rstate.user));
    }
}

static int
radius_setparams(VALUE_PAIR *vp, char *msg, REQUEST_INFO *req_info,
		 struct chap_digest_type *digest, unsigned char *challenge,
		 char *message, int message_space)
{
    u_int32_t remote;
    int ms_chap2_success = 0;
#ifdef MPPE
    int mppe_enc_keys = 0;	
    int mppe_enc_policy = 0;
    int mppe_enc_types = 0;
#endif

    
    if (radius_attributes_hook) {
	(*radius_attributes_hook)(vp);
    }


    while (vp) {
	if (vp->vendorcode == VENDOR_NONE) {
	    switch (vp->attribute) {
	    case PW_SERVICE_TYPE:
		
		
		if (vp->lvalue != PW_FRAMED) {
		    slprintf(msg, BUF_LEN, "RADIUS: wrong service type %ld for %s",
			     vp->lvalue, rstate.user);
		    return -1;
		}
		break;

	    case PW_FRAMED_PROTOCOL:
		
		
		if (vp->lvalue != PW_PPP) {
		    slprintf(msg, BUF_LEN, "RADIUS: wrong framed protocol %ld for %s",
			     vp->lvalue, rstate.user);
		    return -1;
		}
		break;

	    case PW_SESSION_TIMEOUT:
		
		maxconnect = vp->lvalue;
		break;
#ifdef MAXOCTETS
	    case PW_SESSION_OCTETS_LIMIT:
		
		maxoctets = vp->lvalue;
		break;
	    case PW_OCTETS_DIRECTION:
		
		maxoctets_dir = ( vp->lvalue > 4 ) ? 0 : vp->lvalue ;
		break;
#endif
	    case PW_ACCT_INTERIM_INTERVAL:
		
		rstate.acct_interim_interval = vp->lvalue;
		
		
		if (rstate.acct_interim_interval &&
		    rstate.acct_interim_interval < 60) {
		    rstate.acct_interim_interval = 60;
		}
		break;
	    case PW_FRAMED_IP_ADDRESS:
		
		remote = vp->lvalue;
		if (remote == 0xffffffff) {
		    
		    rstate.any_ip_addr_ok = 1;
		} else if (remote != 0xfffffffe) {
		    
		    remote = htonl(vp->lvalue);
		    if (bad_ip_adrs (remote)) {
			slprintf(msg, BUF_LEN, "RADIUS: bad remote IP address %I for %s",
				 remote, rstate.user);
			return -1;
		    }
		    rstate.choose_ip = 1;
		    rstate.ip_addr = remote;
		}
		break;
	    case PW_CLASS:
		
		if (vp->lvalue <= MAXCLASSLEN) {
		    rstate.class_len=vp->lvalue;
		    memcpy(rstate.class, vp->strvalue, rstate.class_len);
		} 
		break;
	    }


#ifdef CHAPMS
	} else if (vp->vendorcode == VENDOR_MICROSOFT) {
	    switch (vp->attribute) {
	    case PW_MS_CHAP2_SUCCESS:
		if ((vp->lvalue != 43) || strncmp(vp->strvalue + 1, "S=", 2)) {
		    slprintf(msg,BUF_LEN,"RADIUS: bad MS-CHAP2-Success packet");
		    return -1;
		}
		if (message != NULL)
		    strlcpy(message, vp->strvalue + 1, message_space);
		ms_chap2_success = 1;
		break;

#ifdef MPPE
	    case PW_MS_CHAP_MPPE_KEYS:
		if (radius_setmppekeys(vp, req_info, challenge) < 0) {
		    slprintf(msg, BUF_LEN,
			     "RADIUS: bad MS-CHAP-MPPE-Keys attribute");
		    return -1;
		}
		mppe_enc_keys = 1;
		break;

	    case PW_MS_MPPE_SEND_KEY:
	    case PW_MS_MPPE_RECV_KEY:
		if (radius_setmppekeys2(vp, req_info) < 0) {
		    slprintf(msg, BUF_LEN,
			     "RADIUS: bad MS-MPPE-%s-Key attribute",
			     (vp->attribute == PW_MS_MPPE_SEND_KEY)?
			     "Send": "Recv");
		    return -1;
		}
		mppe_enc_keys = 1;
		break;

	    case PW_MS_MPPE_ENCRYPTION_POLICY:
		mppe_enc_policy = vp->lvalue;	
		break;

	    case PW_MS_MPPE_ENCRYPTION_TYPES:
		mppe_enc_types = vp->lvalue;	
		break;

#endif 
#if 0
	    case PW_MS_PRIMARY_DNS_SERVER:
	    case PW_MS_SECONDARY_DNS_SERVER:
	    case PW_MS_PRIMARY_NBNS_SERVER:
	    case PW_MS_SECONDARY_NBNS_SERVER:
		break;
#endif
	    }
#endif 
	}
	vp = vp->next;
    }

    
    if (digest && (digest->code == CHAP_MICROSOFT_V2) && !ms_chap2_success)
	return -1;

#ifdef MPPE
    if (mppe_enc_policy && mppe_enc_keys) {
	mppe_keys_set = 1;
	
	if (mppe_enc_types)
	    set_mppe_enc_types(mppe_enc_policy, mppe_enc_types);
    }
#endif

    return 0;
}

#ifdef MPPE
static int
radius_setmppekeys(VALUE_PAIR *vp, REQUEST_INFO *req_info,
		   unsigned char *challenge)
{
    int i;
    MD5_CTX Context;
    u_char  plain[32];
    u_char  buf[16];

    if (vp->lvalue != 32) {
	error("RADIUS: Incorrect attribute length (%d) for MS-CHAP-MPPE-Keys",
	      vp->lvalue);
	return -1;
    }

    memcpy(plain, vp->strvalue, sizeof(plain));

    MD5_Init(&Context);
    MD5_Update(&Context, req_info->secret, strlen(req_info->secret));
    MD5_Update(&Context, req_info->request_vector, AUTH_VECTOR_LEN);
    MD5_Final(buf, &Context);

    for (i = 0; i < 16; i++)
	plain[i] ^= buf[i];

    MD5_Init(&Context);
    MD5_Update(&Context, req_info->secret, strlen(req_info->secret));
    MD5_Update(&Context, vp->strvalue, 16);
    MD5_Final(buf, &Context);

    for(i = 0; i < 16; i++)
	plain[i + 16] ^= buf[i];

    mppe_set_keys(challenge, &plain[8]);

    return 0;    
}

static int
radius_setmppekeys2(VALUE_PAIR *vp, REQUEST_INFO *req_info)
{
    int i;
    MD5_CTX Context;
    u_char  *salt = vp->strvalue;
    u_char  *crypt = vp->strvalue + 2;
    u_char  plain[32];
    u_char  buf[MD5_HASH_SIZE];
    char    *type = "Send";

    if (vp->attribute == PW_MS_MPPE_RECV_KEY)
	type = "Recv";

    if (vp->lvalue != 34) {
	error("RADIUS: Incorrect attribute length (%d) for MS-MPPE-%s-Key",
	      vp->lvalue, type);
	return -1;
    }

    if ((salt[0] & 0x80) == 0) {
	error("RADIUS: Illegal salt value for MS-MPPE-%s-Key attribute", type);
	return -1;
    }

    memcpy(plain, crypt, 32);

    MD5_Init(&Context);
    MD5_Update(&Context, req_info->secret, strlen(req_info->secret));
    MD5_Update(&Context, req_info->request_vector, AUTH_VECTOR_LEN);
    MD5_Update(&Context, salt, 2);
    MD5_Final(buf, &Context);

    for (i = 0; i < 16; i++)
	plain[i] ^= buf[i];

    if (plain[0] != sizeof(mppe_send_key) ) {
	error("RADIUS: Incorrect key length (%d) for MS-MPPE-%s-Key attribute",
	      (int) plain[0], type);
	return -1;
    }

    MD5_Init(&Context);
    MD5_Update(&Context, req_info->secret, strlen(req_info->secret));
    MD5_Update(&Context, crypt, 16);
    MD5_Final(buf, &Context);

    plain[16] ^= buf[0]; 

    if (vp->attribute == PW_MS_MPPE_SEND_KEY)
	memcpy(mppe_send_key, plain + 1, 16);
    else
	memcpy(mppe_recv_key, plain + 1, 16);

    return 0;
}
#endif 

static void
radius_acct_start(void)
{
    UINT4 av_type;
    int result;
    VALUE_PAIR *send = NULL;
    ipcp_options *ho = &ipcp_hisoptions[0];
    u_int32_t hisaddr;

    if (!rstate.initialized) {
	return;
    }

    rstate.start_time = time(NULL);

    strncpy(rstate.session_id, rc_mksid(), sizeof(rstate.session_id));

    rc_avpair_add(&send, PW_ACCT_SESSION_ID,
		   rstate.session_id, 0, VENDOR_NONE);
    rc_avpair_add(&send, PW_USER_NAME,
		   rstate.user, 0, VENDOR_NONE);

    if (rstate.class_len > 0)
	rc_avpair_add(&send, PW_CLASS,
		      rstate.class, rstate.class_len, VENDOR_NONE);

    av_type = PW_STATUS_START;
    rc_avpair_add(&send, PW_ACCT_STATUS_TYPE, &av_type, 0, VENDOR_NONE);

    av_type = PW_FRAMED;
    rc_avpair_add(&send, PW_SERVICE_TYPE, &av_type, 0, VENDOR_NONE);

    av_type = PW_PPP;
    rc_avpair_add(&send, PW_FRAMED_PROTOCOL, &av_type, 0, VENDOR_NONE);

    if (*remote_number) {
	rc_avpair_add(&send, PW_CALLING_STATION_ID,
		       remote_number, 0, VENDOR_NONE);
    } else if (ipparam)
	rc_avpair_add(&send, PW_CALLING_STATION_ID, ipparam, 0, VENDOR_NONE);

    av_type = PW_RADIUS;
    rc_avpair_add(&send, PW_ACCT_AUTHENTIC, &av_type, 0, VENDOR_NONE);


    av_type = ( using_pty ? PW_VIRTUAL : ( sync_serial ? PW_SYNC : PW_ASYNC ) );
    rc_avpair_add(&send, PW_NAS_PORT_TYPE, &av_type, 0, VENDOR_NONE);

    hisaddr = ho->hisaddr;
    av_type = htonl(hisaddr);
    rc_avpair_add(&send, PW_FRAMED_IP_ADDRESS , &av_type , 0, VENDOR_NONE);

    
    if (rstate.avp)
	rc_avpair_insert(&send, NULL, rc_avpair_copy(rstate.avp));

    if (rstate.acctserver) {
	result = rc_acct_using_server(rstate.acctserver,
				      rstate.client_port, send);
    } else {
	result = rc_acct(rstate.client_port, send);
    }

    rc_avpair_free(send);

    if (result != OK_RC) {
	
	syslog(LOG_WARNING,
		"Accounting START failed for %s", rstate.user);
    } else {
	rstate.accounting_started = 1;
	
	if (rstate.acct_interim_interval) {
	    TIMEOUT(radius_acct_interim, NULL, rstate.acct_interim_interval);
	}
    }
}

static void
radius_acct_stop(void)
{
    UINT4 av_type;
    VALUE_PAIR *send = NULL;
    ipcp_options *ho = &ipcp_hisoptions[0];
    u_int32_t hisaddr;
    int result;

    if (!rstate.initialized) {
	return;
    }

    if (!rstate.accounting_started) {
	return;
    }

    rstate.accounting_started = 0;
    rc_avpair_add(&send, PW_ACCT_SESSION_ID, rstate.session_id,
		   0, VENDOR_NONE);

    rc_avpair_add(&send, PW_USER_NAME, rstate.user, 0, VENDOR_NONE);

    av_type = PW_STATUS_STOP;
    rc_avpair_add(&send, PW_ACCT_STATUS_TYPE, &av_type, 0, VENDOR_NONE);

    av_type = PW_FRAMED;
    rc_avpair_add(&send, PW_SERVICE_TYPE, &av_type, 0, VENDOR_NONE);

    av_type = PW_PPP;
    rc_avpair_add(&send, PW_FRAMED_PROTOCOL, &av_type, 0, VENDOR_NONE);

    av_type = PW_RADIUS;
    rc_avpair_add(&send, PW_ACCT_AUTHENTIC, &av_type, 0, VENDOR_NONE);


    if (link_stats_valid) {
	av_type = link_connect_time;
	rc_avpair_add(&send, PW_ACCT_SESSION_TIME, &av_type, 0, VENDOR_NONE);

	av_type = link_stats.bytes_out;
	rc_avpair_add(&send, PW_ACCT_OUTPUT_OCTETS, &av_type, 0, VENDOR_NONE);

	av_type = link_stats.bytes_in;
	rc_avpair_add(&send, PW_ACCT_INPUT_OCTETS, &av_type, 0, VENDOR_NONE);

	av_type = link_stats.pkts_out;
	rc_avpair_add(&send, PW_ACCT_OUTPUT_PACKETS, &av_type, 0, VENDOR_NONE);

	av_type = link_stats.pkts_in;
	rc_avpair_add(&send, PW_ACCT_INPUT_PACKETS, &av_type, 0, VENDOR_NONE);
    }

    if (*remote_number) {
	rc_avpair_add(&send, PW_CALLING_STATION_ID,
		       remote_number, 0, VENDOR_NONE);
    } else if (ipparam)
	rc_avpair_add(&send, PW_CALLING_STATION_ID, ipparam, 0, VENDOR_NONE);

    av_type = ( using_pty ? PW_VIRTUAL : ( sync_serial ? PW_SYNC : PW_ASYNC ) );
    rc_avpair_add(&send, PW_NAS_PORT_TYPE, &av_type, 0, VENDOR_NONE);

    av_type = PW_NAS_ERROR;
    switch( status ) {
	case EXIT_OK:
	case EXIT_USER_REQUEST:
	    av_type = PW_USER_REQUEST;
	    break;

	case EXIT_HANGUP:
	case EXIT_PEER_DEAD:
	case EXIT_CONNECT_FAILED:
	    av_type = PW_LOST_CARRIER;
	    break;

	case EXIT_INIT_FAILED:
	case EXIT_OPEN_FAILED:
	case EXIT_LOCK_FAILED:
	case EXIT_PTYCMD_FAILED:
	    av_type = PW_PORT_ERROR;
	    break;

	case EXIT_PEER_AUTH_FAILED:
	case EXIT_AUTH_TOPEER_FAILED:
	case EXIT_NEGOTIATION_FAILED:
	case EXIT_CNID_AUTH_FAILED:
	    av_type = PW_SERVICE_UNAVAILABLE;
	    break;

	case EXIT_IDLE_TIMEOUT:
	    av_type = PW_ACCT_IDLE_TIMEOUT;
	    break;

	case EXIT_CONNECT_TIME:
	    av_type = PW_ACCT_SESSION_TIMEOUT;
	    break;
	    
#ifdef MAXOCTETS
	case EXIT_TRAFFIC_LIMIT:
	    av_type = PW_NAS_REQUEST;
	    break;
#endif

	default:
	    av_type = PW_NAS_ERROR;
	    break;
    }
    rc_avpair_add(&send, PW_ACCT_TERMINATE_CAUSE, &av_type, 0, VENDOR_NONE);

    hisaddr = ho->hisaddr;
    av_type = htonl(hisaddr);
    rc_avpair_add(&send, PW_FRAMED_IP_ADDRESS , &av_type , 0, VENDOR_NONE);

    
    if (rstate.avp)
	rc_avpair_insert(&send, NULL, rc_avpair_copy(rstate.avp));

    if (rstate.acctserver) {
	result = rc_acct_using_server(rstate.acctserver,
				      rstate.client_port, send);
    } else {
	result = rc_acct(rstate.client_port, send);
    }

    if (result != OK_RC) {
	
	syslog(LOG_WARNING,
		"Accounting STOP failed for %s", rstate.user);
    }
    rc_avpair_free(send);
}

static void
radius_acct_interim(void *ignored)
{
    UINT4 av_type;
    VALUE_PAIR *send = NULL;
    ipcp_options *ho = &ipcp_hisoptions[0];
    u_int32_t hisaddr;
    int result;

    if (!rstate.initialized) {
	return;
    }

    if (!rstate.accounting_started) {
	return;
    }

    rc_avpair_add(&send, PW_ACCT_SESSION_ID, rstate.session_id,
		   0, VENDOR_NONE);

    rc_avpair_add(&send, PW_USER_NAME, rstate.user, 0, VENDOR_NONE);

    av_type = PW_STATUS_ALIVE;
    rc_avpair_add(&send, PW_ACCT_STATUS_TYPE, &av_type, 0, VENDOR_NONE);

    av_type = PW_FRAMED;
    rc_avpair_add(&send, PW_SERVICE_TYPE, &av_type, 0, VENDOR_NONE);

    av_type = PW_PPP;
    rc_avpair_add(&send, PW_FRAMED_PROTOCOL, &av_type, 0, VENDOR_NONE);

    av_type = PW_RADIUS;
    rc_avpair_add(&send, PW_ACCT_AUTHENTIC, &av_type, 0, VENDOR_NONE);

    
    update_link_stats(0);

    if (link_stats_valid) {
	link_stats_valid = 0; 

	av_type = link_connect_time;
	rc_avpair_add(&send, PW_ACCT_SESSION_TIME, &av_type, 0, VENDOR_NONE);

	av_type = link_stats.bytes_out;
	rc_avpair_add(&send, PW_ACCT_OUTPUT_OCTETS, &av_type, 0, VENDOR_NONE);

	av_type = link_stats.bytes_in;
	rc_avpair_add(&send, PW_ACCT_INPUT_OCTETS, &av_type, 0, VENDOR_NONE);

	av_type = link_stats.pkts_out;
	rc_avpair_add(&send, PW_ACCT_OUTPUT_PACKETS, &av_type, 0, VENDOR_NONE);

	av_type = link_stats.pkts_in;
	rc_avpair_add(&send, PW_ACCT_INPUT_PACKETS, &av_type, 0, VENDOR_NONE);
    }

    if (*remote_number) {
	rc_avpair_add(&send, PW_CALLING_STATION_ID,
		       remote_number, 0, VENDOR_NONE);
    } else if (ipparam)
	rc_avpair_add(&send, PW_CALLING_STATION_ID, ipparam, 0, VENDOR_NONE);

    av_type = ( using_pty ? PW_VIRTUAL : ( sync_serial ? PW_SYNC : PW_ASYNC ) );
    rc_avpair_add(&send, PW_NAS_PORT_TYPE, &av_type, 0, VENDOR_NONE);

    hisaddr = ho->hisaddr;
    av_type = htonl(hisaddr);
    rc_avpair_add(&send, PW_FRAMED_IP_ADDRESS , &av_type , 0, VENDOR_NONE);

    
    if (rstate.avp)
	rc_avpair_insert(&send, NULL, rc_avpair_copy(rstate.avp));

    if (rstate.acctserver) {
	result = rc_acct_using_server(rstate.acctserver,
				      rstate.client_port, send);
    } else {
	result = rc_acct(rstate.client_port, send);
    }

    if (result != OK_RC) {
	
	syslog(LOG_WARNING,
		"Interim accounting failed for %s", rstate.user);
    }
    rc_avpair_free(send);

    
    TIMEOUT(radius_acct_interim, NULL, rstate.acct_interim_interval);
}

static void
radius_ip_up(void *opaque, int arg)
{
    radius_acct_start();
}

static void
radius_ip_down(void *opaque, int arg)
{
    radius_acct_stop();
}

static int
radius_init(char *msg)
{
    if (rstate.initialized) {
	return 0;
    }

    if (config_file && *config_file) {
	strlcpy(rstate.config_file, config_file, MAXPATHLEN-1);
    }

    rstate.initialized = 1;

    if (rc_read_config(rstate.config_file) != 0) {
	slprintf(msg, BUF_LEN, "RADIUS: Can't read config file %s",
		 rstate.config_file);
	return -1;
    }

    if (rc_read_dictionary(rc_conf_str("dictionary")) != 0) {
	slprintf(msg, BUF_LEN, "RADIUS: Can't read dictionary file %s",
		 rc_conf_str("dictionary"));
	return -1;
    }

    if (rc_read_mapfile(rc_conf_str("mapfile")) != 0)	{
	slprintf(msg, BUF_LEN, "RADIUS: Can't read map file %s",
		 rc_conf_str("mapfile"));
	return -1;
    }

    
    while (avpopt) {
	struct avpopt *n = avpopt->next;

	rc_avpair_parse(avpopt->vpstr, &rstate.avp);
	free(avpopt->vpstr);
	free(avpopt);
	avpopt = n;
    }
    return 0;
}

static int
get_client_port(char *ifname)
{
    int port;
    if (sscanf(ifname, "ppp%d", &port) == 1) {
	return port;
    }
    return rc_map2id(ifname);
}

static int
radius_allowed_address(u_int32_t addr)
{
    ipcp_options *wo = &ipcp_wantoptions[0];

    if (!rstate.choose_ip) {
	
	if (rstate.any_ip_addr_ok) {
	    return 1;
	}

	if (wo->hisaddr != 0 && wo->hisaddr == addr) {
	    return 1;
	}

	return 0;
    }
    if (addr == rstate.ip_addr) return 1;
    return 0;
}

char *radius_logged_in_user(void)
{
    return rstate.user;
}
