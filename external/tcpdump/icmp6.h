
/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)ip_icmp.h	8.1 (Berkeley) 6/10/93
 */

#ifndef _NETINET_ICMP6_H_
#define _NETINET_ICMP6_H_

struct icmp6_hdr {
	u_int8_t	icmp6_type;	
	u_int8_t	icmp6_code;	
	u_int16_t	icmp6_cksum;	
	union {
		u_int32_t	icmp6_un_data32[1]; 
		u_int16_t	icmp6_un_data16[2]; 
		u_int8_t	icmp6_un_data8[4];  
	} icmp6_dataun;
};

#define icmp6_data32	icmp6_dataun.icmp6_un_data32
#define icmp6_data16	icmp6_dataun.icmp6_un_data16
#define icmp6_data8	icmp6_dataun.icmp6_un_data8
#define icmp6_pptr	icmp6_data32[0]		
#define icmp6_mtu	icmp6_data32[0]		
#define icmp6_id	icmp6_data16[0]		
#define icmp6_seq	icmp6_data16[1]		
#define icmp6_maxdelay	icmp6_data16[0]		

#define ICMP6_DST_UNREACH		1	
#define ICMP6_PACKET_TOO_BIG		2	
#define ICMP6_TIME_EXCEEDED		3	
#define ICMP6_PARAM_PROB		4	

#define ICMP6_ECHO_REQUEST		128	
#define ICMP6_ECHO_REPLY		129	
#define ICMP6_MEMBERSHIP_QUERY		130	
#define MLD6_LISTENER_QUERY		130 	
#define ICMP6_MEMBERSHIP_REPORT		131	
#define MLD6_LISTENER_REPORT		131	
#define ICMP6_MEMBERSHIP_REDUCTION	132	
#define MLD6_LISTENER_DONE		132	

#define ND_ROUTER_SOLICIT		133	
#define ND_ROUTER_ADVERT		134	
#define ND_NEIGHBOR_SOLICIT		135	
#define ND_NEIGHBOR_ADVERT		136	
#define ND_REDIRECT			137	

#define ICMP6_ROUTER_RENUMBERING	138	

#define ICMP6_WRUREQUEST		139	
#define ICMP6_WRUREPLY			140	
#define ICMP6_FQDN_QUERY		139	
#define ICMP6_FQDN_REPLY		140	
#define ICMP6_NI_QUERY			139	
#define ICMP6_NI_REPLY			140	
#define IND_SOLICIT			141	
#define IND_ADVERT			142	

#define ICMP6_V2_MEMBERSHIP_REPORT	143	
#define MLDV2_LISTENER_REPORT		143	
#define ICMP6_HADISCOV_REQUEST		144
#define ICMP6_HADISCOV_REPLY		145
#define ICMP6_MOBILEPREFIX_SOLICIT	146
#define ICMP6_MOBILEPREFIX_ADVERT	147

#define MLD6_MTRACE_RESP		200	
#define MLD6_MTRACE			201	

#define ICMP6_MAXTYPE			201

#define ICMP6_DST_UNREACH_NOROUTE	0	
#define ICMP6_DST_UNREACH_ADMIN	 	1	
#define ICMP6_DST_UNREACH_NOTNEIGHBOR	2	
#define ICMP6_DST_UNREACH_BEYONDSCOPE	2	
#define ICMP6_DST_UNREACH_ADDR		3	
#define ICMP6_DST_UNREACH_NOPORT	4	

#define ICMP6_TIME_EXCEED_TRANSIT 	0	
#define ICMP6_TIME_EXCEED_REASSEMBLY	1	

#define ICMP6_PARAMPROB_HEADER 	 	0	
#define ICMP6_PARAMPROB_NEXTHEADER	1	
#define ICMP6_PARAMPROB_OPTION		2	

#define ICMP6_INFOMSG_MASK		0x80	

#define ICMP6_NI_SUBJ_IPV6	0	
#define ICMP6_NI_SUBJ_FQDN	1	
#define ICMP6_NI_SUBJ_IPV4	2	

#define ICMP6_NI_SUCCESS	0	
#define ICMP6_NI_REFUSED	1	
#define ICMP6_NI_UNKNOWN	2	

#define ICMP6_ROUTER_RENUMBERING_COMMAND  0	
#define ICMP6_ROUTER_RENUMBERING_RESULT   1	
#define ICMP6_ROUTER_RENUMBERING_SEQNUM_RESET   255	

#define ND_REDIRECT_ONLINK	0	
#define ND_REDIRECT_ROUTER	1	

struct mld6_hdr {
	struct icmp6_hdr	mld6_hdr;
	struct in6_addr		mld6_addr; 
};

#define mld6_type	mld6_hdr.icmp6_type
#define mld6_code	mld6_hdr.icmp6_code
#define mld6_cksum	mld6_hdr.icmp6_cksum
#define mld6_maxdelay	mld6_hdr.icmp6_data16[0]
#define mld6_reserved	mld6_hdr.icmp6_data16[1]

#define MLD_MINLEN	24
#define MLDV2_MINLEN	28


struct nd_router_solicit {	
	struct icmp6_hdr 	nd_rs_hdr;
	
};

#define nd_rs_type	nd_rs_hdr.icmp6_type
#define nd_rs_code	nd_rs_hdr.icmp6_code
#define nd_rs_cksum	nd_rs_hdr.icmp6_cksum
#define nd_rs_reserved	nd_rs_hdr.icmp6_data32[0]

struct nd_router_advert {	
	struct icmp6_hdr	nd_ra_hdr;
	u_int32_t		nd_ra_reachable;	
	u_int32_t		nd_ra_retransmit;	
	
};

#define nd_ra_type		nd_ra_hdr.icmp6_type
#define nd_ra_code		nd_ra_hdr.icmp6_code
#define nd_ra_cksum		nd_ra_hdr.icmp6_cksum
#define nd_ra_curhoplimit	nd_ra_hdr.icmp6_data8[0]
#define nd_ra_flags_reserved	nd_ra_hdr.icmp6_data8[1]
#define ND_RA_FLAG_MANAGED	0x80
#define ND_RA_FLAG_OTHER	0x40
#define ND_RA_FLAG_HOME_AGENT	0x20

#define ND_RA_FLAG_RTPREF_MASK	0x18 

#define ND_RA_FLAG_RTPREF_HIGH	0x08 
#define ND_RA_FLAG_RTPREF_MEDIUM	0x00 
#define ND_RA_FLAG_RTPREF_LOW	0x18 
#define ND_RA_FLAG_RTPREF_RSV	0x10 

#define nd_ra_router_lifetime	nd_ra_hdr.icmp6_data16[1]

struct nd_neighbor_solicit {	
	struct icmp6_hdr	nd_ns_hdr;
	struct in6_addr		nd_ns_target;	
	
};

#define nd_ns_type		nd_ns_hdr.icmp6_type
#define nd_ns_code		nd_ns_hdr.icmp6_code
#define nd_ns_cksum		nd_ns_hdr.icmp6_cksum
#define nd_ns_reserved		nd_ns_hdr.icmp6_data32[0]

struct nd_neighbor_advert {	
	struct icmp6_hdr	nd_na_hdr;
	struct in6_addr		nd_na_target;	
	
};

#define nd_na_type		nd_na_hdr.icmp6_type
#define nd_na_code		nd_na_hdr.icmp6_code
#define nd_na_cksum		nd_na_hdr.icmp6_cksum
#define nd_na_flags_reserved	nd_na_hdr.icmp6_data32[0]

#define ND_NA_FLAG_ROUTER		0x80000000
#define ND_NA_FLAG_SOLICITED		0x40000000
#define ND_NA_FLAG_OVERRIDE		0x20000000

struct nd_redirect {		
	struct icmp6_hdr	nd_rd_hdr;
	struct in6_addr		nd_rd_target;	
	struct in6_addr		nd_rd_dst;	
	
};

#define nd_rd_type		nd_rd_hdr.icmp6_type
#define nd_rd_code		nd_rd_hdr.icmp6_code
#define nd_rd_cksum		nd_rd_hdr.icmp6_cksum
#define nd_rd_reserved		nd_rd_hdr.icmp6_data32[0]

struct nd_opt_hdr {		
	u_int8_t	nd_opt_type;
	u_int8_t	nd_opt_len;
	
};

#define ND_OPT_SOURCE_LINKADDR		1
#define ND_OPT_TARGET_LINKADDR		2
#define ND_OPT_PREFIX_INFORMATION	3
#define ND_OPT_REDIRECTED_HEADER	4
#define ND_OPT_MTU			5
#define ND_OPT_ADVINTERVAL		7
#define ND_OPT_HOMEAGENT_INFO		8
#define ND_OPT_ROUTE_INFO		9	


struct nd_opt_prefix_info {	
	u_int8_t	nd_opt_pi_type;
	u_int8_t	nd_opt_pi_len;
	u_int8_t	nd_opt_pi_prefix_len;
	u_int8_t	nd_opt_pi_flags_reserved;
	u_int8_t	nd_opt_pi_valid_time[4];
	u_int8_t	nd_opt_pi_preferred_time[4];
	u_int8_t	nd_opt_pi_reserved2[4];
	struct in6_addr	nd_opt_pi_prefix;
};

#define ND_OPT_PI_FLAG_ONLINK		0x80
#define ND_OPT_PI_FLAG_AUTO		0x40
#define ND_OPT_PI_FLAG_ROUTER		0x20	

struct nd_opt_rd_hdr {         
	u_int8_t	nd_opt_rh_type;
	u_int8_t	nd_opt_rh_len;
	u_int16_t	nd_opt_rh_reserved1;
	u_int32_t	nd_opt_rh_reserved2;
	
};

struct nd_opt_mtu {		
	u_int8_t	nd_opt_mtu_type;
	u_int8_t	nd_opt_mtu_len;
	u_int16_t	nd_opt_mtu_reserved;
	u_int32_t	nd_opt_mtu_mtu;
};

struct nd_opt_advinterval {	
	u_int8_t	nd_opt_adv_type;
	u_int8_t	nd_opt_adv_len;
	u_int16_t	nd_opt_adv_reserved;
	u_int32_t	nd_opt_adv_interval;
};

struct nd_opt_homeagent_info {	
	u_int8_t	nd_opt_hai_type;
	u_int8_t	nd_opt_hai_len;
	u_int16_t	nd_opt_hai_reserved;
	int16_t		nd_opt_hai_preference;
	u_int16_t	nd_opt_hai_lifetime;
};

struct nd_opt_route_info {	
	u_int8_t	nd_opt_rti_type;
	u_int8_t	nd_opt_rti_len;
	u_int8_t	nd_opt_rti_prefixlen;
	u_int8_t	nd_opt_rti_flags;
	u_int32_t	nd_opt_rti_lifetime;
	
};


struct icmp6_namelookup {
	struct icmp6_hdr 	icmp6_nl_hdr;
	u_int8_t	icmp6_nl_nonce[8];
	int32_t		icmp6_nl_ttl;
#if 0
	u_int8_t	icmp6_nl_len;
	u_int8_t	icmp6_nl_name[3];
#endif
	
};

struct icmp6_nodeinfo {
	struct icmp6_hdr icmp6_ni_hdr;
	u_int8_t icmp6_ni_nonce[8];
	
};

#define ni_type		icmp6_ni_hdr.icmp6_type
#define ni_code		icmp6_ni_hdr.icmp6_code
#define ni_cksum	icmp6_ni_hdr.icmp6_cksum
#define ni_qtype	icmp6_ni_hdr.icmp6_data16[0]
#define ni_flags	icmp6_ni_hdr.icmp6_data16[1]

#define NI_QTYPE_NOOP		0 
#define NI_QTYPE_SUPTYPES	1 
#define NI_QTYPE_FQDN		2 
#define NI_QTYPE_DNSNAME	2 
#define NI_QTYPE_NODEADDR	3 
#define NI_QTYPE_IPV4ADDR	4 

#define NI_SUPTYPE_FLAG_COMPRESS	((u_int16_t)htons(0x1))
#define NI_FQDN_FLAG_VALIDTTL		((u_int16_t)htons(0x1))

#define NI_NODEADDR_FLAG_TRUNCATE	((u_int16_t)htons(0x1))
#define NI_NODEADDR_FLAG_ALL		((u_int16_t)htons(0x2))
#define NI_NODEADDR_FLAG_COMPAT		((u_int16_t)htons(0x4))
#define NI_NODEADDR_FLAG_LINKLOCAL	((u_int16_t)htons(0x8))
#define NI_NODEADDR_FLAG_SITELOCAL	((u_int16_t)htons(0x10))
#define NI_NODEADDR_FLAG_GLOBAL		((u_int16_t)htons(0x20))
#define NI_NODEADDR_FLAG_ANYCAST	((u_int16_t)htons(0x40)) 

struct ni_reply_fqdn {
	u_int32_t ni_fqdn_ttl;	
	u_int8_t ni_fqdn_namelen; 
	u_int8_t ni_fqdn_name[3]; 
};

struct icmp6_router_renum {	
	struct icmp6_hdr	rr_hdr;
	u_int8_t	rr_segnum;
	u_int8_t	rr_flags;
	u_int16_t	rr_maxdelay;
	u_int32_t	rr_reserved;
};
#define ICMP6_RR_FLAGS_TEST		0x80
#define ICMP6_RR_FLAGS_REQRESULT	0x40
#define ICMP6_RR_FLAGS_FORCEAPPLY	0x20
#define ICMP6_RR_FLAGS_SPECSITE		0x10
#define ICMP6_RR_FLAGS_PREVDONE		0x08

#define rr_type		rr_hdr.icmp6_type
#define rr_code		rr_hdr.icmp6_code
#define rr_cksum	rr_hdr.icmp6_cksum
#define rr_seqnum 	rr_hdr.icmp6_data32[0]

struct rr_pco_match {		
	u_int8_t	rpm_code;
	u_int8_t	rpm_len;
	u_int8_t	rpm_ordinal;
	u_int8_t	rpm_matchlen;
	u_int8_t	rpm_minlen;
	u_int8_t	rpm_maxlen;
	u_int16_t	rpm_reserved;
	struct	in6_addr	rpm_prefix;
};

#define RPM_PCO_ADD		1
#define RPM_PCO_CHANGE		2
#define RPM_PCO_SETGLOBAL	3
#define RPM_PCO_MAX		4

struct rr_pco_use {		
	u_int8_t	rpu_uselen;
	u_int8_t	rpu_keeplen;
	u_int8_t	rpu_ramask;
	u_int8_t	rpu_raflags;
	u_int32_t	rpu_vltime;
	u_int32_t	rpu_pltime;
	u_int32_t	rpu_flags;
	struct	in6_addr rpu_prefix;
};
#define ICMP6_RR_PCOUSE_RAFLAGS_ONLINK	0x80
#define ICMP6_RR_PCOUSE_RAFLAGS_AUTO	0x40

#define ICMP6_RR_PCOUSE_FLAGS_DECRVLTIME     ((u_int32_t)htonl(0x80000000))
#define ICMP6_RR_PCOUSE_FLAGS_DECRPLTIME     ((u_int32_t)htonl(0x40000000))

struct rr_result {		
	u_int16_t	rrr_flags;
	u_int8_t	rrr_ordinal;
	u_int8_t	rrr_matchedlen;
	u_int32_t	rrr_ifid;
	struct	in6_addr rrr_prefix;
};
#define ICMP6_RR_RESULT_FLAGS_OOB		((u_int16_t)htons(0x0002))
#define ICMP6_RR_RESULT_FLAGS_FORBIDDEN		((u_int16_t)htons(0x0001))

#endif 
