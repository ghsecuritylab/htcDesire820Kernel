/*
 * QEMU Bluetooth HCI logic.
 *
 * Copyright (C) 2007 OpenMoko, Inc.
 * Copyright (C) 2008 Andrzej Zaborowski  <balrog@zabor.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "qemu-common.h"
#include "qemu-timer.h"
#include "usb.h"
#include "net.h"
#include "bt.h"

struct bt_hci_s {
    uint8_t *(*evt_packet)(void *opaque);
    void (*evt_submit)(void *opaque, int len);
    void *opaque;
    uint8_t evt_buf[256];

    uint8_t acl_buf[4096];
    int acl_len;

    uint16_t asb_handle;
    uint16_t psb_handle;

    int last_cmd;	

    struct bt_device_s *conn_req_host;

    struct {
        int inquire;
        int periodic;
        int responses_left;
        int responses;
        QEMUTimer *inquiry_done;
        QEMUTimer *inquiry_next;
        int inquiry_length;
        int inquiry_period;
        int inquiry_mode;

#define HCI_HANDLE_OFFSET	0x20
#define HCI_HANDLES_MAX		0x10
        struct bt_hci_master_link_s {
            struct bt_link_s *link;
            void (*lmp_acl_data)(struct bt_link_s *link,
                            const uint8_t *data, int start, int len);
            QEMUTimer *acl_mode_timer;
        } handle[HCI_HANDLES_MAX];
        uint32_t role_bmp;
        int last_handle;
        int connecting;
        bdaddr_t awaiting_bdaddr[HCI_HANDLES_MAX];
    } lm;

    uint8_t event_mask[8];
    uint16_t voice_setting;	
    uint16_t conn_accept_tout;
    QEMUTimer *conn_accept_timer;

    struct HCIInfo info;
    struct bt_device_s device;
};

#define DEFAULT_RSSI_DBM	20

#define hci_from_info(ptr)	container_of((ptr), struct bt_hci_s, info)
#define hci_from_device(ptr)	container_of((ptr), struct bt_hci_s, device)

struct bt_hci_link_s {
    struct bt_link_s btlink;
    uint16_t handle;	
};

#if 0
static void bt_submit_lmp(struct bt_device_s *bt, int length, uint8_t *data)
{
    int resp, resplen, error, op, tr;
    uint8_t respdata[17];

    if (length < 1)
        return;

    tr = *data & 1;
    op = *(data ++) >> 1;
    resp = LMP_ACCEPTED;
    resplen = 2;
    respdata[1] = op;
    error = 0;
    length --;

    if (op >= 0x7c) {	
        op |= *(data ++) << 8;
        resp = LMP_ACCEPTED_EXT;
        resplen = 4;
        respdata[0] = op >> 8;
        respdata[1] = op & 0xff;
        length --;
    }

    switch (op) {
    case LMP_ACCEPTED:
        if (length < 1) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        resp = 0;
        break;

    case LMP_ACCEPTED_EXT:
        if (length < 2) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        resp = 0;
        break;

    case LMP_NOT_ACCEPTED:
        if (length < 2) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        resp = 0;
        break;

    case LMP_NOT_ACCEPTED_EXT:
        if (length < 3) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        resp = 0;
        break;

    case LMP_HOST_CONNECTION_REQ:
        break;

    case LMP_SETUP_COMPLETE:
        resp = LMP_SETUP_COMPLETE;
        resplen = 1;
        bt->setup = 1;
        break;

    case LMP_DETACH:
        if (length < 1) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        bt->setup = 0;
        resp = 0;
        break;

    case LMP_SUPERVISION_TIMEOUT:
        if (length < 2) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        resp = 0;
        break;

    case LMP_QUALITY_OF_SERVICE:
        resp = 0;
        
    case LMP_QOS_REQ:
        if (length < 3) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        break;

    case LMP_MAX_SLOT:
        resp = 0;
        
    case LMP_MAX_SLOT_REQ:
        if (length < 1) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        break;

    case LMP_AU_RAND:
    case LMP_IN_RAND:
    case LMP_COMB_KEY:
        if (length < 16) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        if (op == LMP_AU_RAND) {
            if (bt->key_present) {
                resp = LMP_SRES;
                resplen = 5;
                
            } else {
                error = HCI_PIN_OR_KEY_MISSING;
                goto not_accepted;
            }
        } else if (op == LMP_IN_RAND) {
            error = HCI_PAIRING_NOT_ALLOWED;
            goto not_accepted;
        } else {
            
            resp = LMP_UNIT_KEY;
            resplen = 17;
            memcpy(respdata + 1, bt->key, 16);

            error = HCI_UNIT_LINK_KEY_USED;
            goto not_accepted;
        }
        break;

    case LMP_UNIT_KEY:
        if (length < 16) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        memcpy(bt->key, data, 16);
        bt->key_present = 1;
        break;

    case LMP_SRES:
        if (length < 4) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        break;

    case LMP_CLKOFFSET_REQ:
        resp = LMP_CLKOFFSET_RES;
        resplen = 3;
        respdata[1] = 0x33;
        respdata[2] = 0x33;
        break;

    case LMP_CLKOFFSET_RES:
        if (length < 2) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        break;

    case LMP_VERSION_REQ:
    case LMP_VERSION_RES:
        if (length < 5) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        if (op == LMP_VERSION_REQ) {
            resp = LMP_VERSION_RES;
            resplen = 6;
            respdata[1] = 0x20;
            respdata[2] = 0xff;
            respdata[3] = 0xff;
            respdata[4] = 0xff;
            respdata[5] = 0xff;
        } else
            resp = 0;
        break;

    case LMP_FEATURES_REQ:
    case LMP_FEATURES_RES:
        if (length < 8) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        if (op == LMP_FEATURES_REQ) {
            resp = LMP_FEATURES_RES;
            resplen = 9;
            respdata[1] = (bt->lmp_caps >> 0) & 0xff;
            respdata[2] = (bt->lmp_caps >> 8) & 0xff;
            respdata[3] = (bt->lmp_caps >> 16) & 0xff;
            respdata[4] = (bt->lmp_caps >> 24) & 0xff;
            respdata[5] = (bt->lmp_caps >> 32) & 0xff;
            respdata[6] = (bt->lmp_caps >> 40) & 0xff;
            respdata[7] = (bt->lmp_caps >> 48) & 0xff;
            respdata[8] = (bt->lmp_caps >> 56) & 0xff;
        } else
            resp = 0;
        break;

    case LMP_NAME_REQ:
        if (length < 1) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        resp = LMP_NAME_RES;
        resplen = 17;
        respdata[1] = data[0];
        respdata[2] = strlen(bt->lmp_name);
        memset(respdata + 3, 0x00, 14);
        if (respdata[2] > respdata[1])
            memcpy(respdata + 3, bt->lmp_name + respdata[1],
                            respdata[2] - respdata[1]);
        break;

    case LMP_NAME_RES:
        if (length < 16) {
            error = HCI_UNSUPPORTED_LMP_PARAMETER_VALUE;
            goto not_accepted;
        }
        resp = 0;
        break;

    default:
        error = HCI_UNKNOWN_LMP_PDU;
        
    not_accepted:
        if (op >> 8) {
            resp = LMP_NOT_ACCEPTED_EXT;
            resplen = 5;
            respdata[0] = op >> 8;
            respdata[1] = op & 0xff;
            respdata[2] = error;
        } else {
            resp = LMP_NOT_ACCEPTED;
            resplen = 3;
            respdata[0] = op & 0xff;
            respdata[1] = error;
        }
    }

    if (resp == 0)
        return;

    if (resp >> 8) {
        respdata[0] = resp >> 8;
        respdata[1] = resp & 0xff;
    } else
        respdata[0] = resp & 0xff;

    respdata[0] <<= 1;
    respdata[0] |= tr;
}

static void bt_submit_raw_acl(struct bt_piconet_s *net, int length, uint8_t *data)
{
    struct bt_device_s *slave;
    if (length < 1)
        return;

    slave = 0;
#if 0
    slave = net->slave;
#endif

    switch (data[0] & 3) {
    case LLID_ACLC:
        bt_submit_lmp(slave, length - 1, data + 1);
        break;
    case LLID_ACLU_START:
#if 0
        bt_sumbit_l2cap(slave, length - 1, data + 1, (data[0] >> 2) & 1);
        breka;
#endif
    default:
    case LLID_ACLU_CONT:
        break;
    }
}
#endif


#ifdef HOST_WORDS_BIGENDIAN
# define HNDL(raw)	bswap16(raw)
#else
# define HNDL(raw)	(raw)
#endif

static const uint8_t bt_event_reserved_mask[8] = {
    0xff, 0x9f, 0xfb, 0xff, 0x07, 0x18, 0x00, 0x00,
};

static inline uint8_t *bt_hci_event_start(struct bt_hci_s *hci,
                int evt, int len)
{
    uint8_t *packet, mask;
    int mask_byte;

    if (len > 255) {
        fprintf(stderr, "%s: HCI event params too long (%ib)\n",
                        __FUNCTION__, len);
        exit(-1);
    }

    mask_byte = (evt - 1) >> 3;
    mask = 1 << ((evt - 1) & 3);
    if (mask & bt_event_reserved_mask[mask_byte] & ~hci->event_mask[mask_byte])
        return NULL;

    packet = hci->evt_packet(hci->opaque);
    packet[0] = evt;
    packet[1] = len;

    return &packet[2];
}

static inline void bt_hci_event(struct bt_hci_s *hci, int evt,
                void *params, int len)
{
    uint8_t *packet = bt_hci_event_start(hci, evt, len);

    if (!packet)
        return;

    if (len)
        memcpy(packet, params, len);

    hci->evt_submit(hci->opaque, len + 2);
}

static inline void bt_hci_event_status(struct bt_hci_s *hci, int status)
{
    evt_cmd_status params = {
        .status	= status,
        .ncmd	= 1,
        .opcode	= hci->last_cmd,
    };

    bt_hci_event(hci, EVT_CMD_STATUS, &params, EVT_CMD_STATUS_SIZE);
}

static inline void bt_hci_event_complete(struct bt_hci_s *hci,
                void *ret, int len)
{
    uint8_t *packet = bt_hci_event_start(hci, EVT_CMD_COMPLETE,
                    len + EVT_CMD_COMPLETE_SIZE);
    evt_cmd_complete *params = (evt_cmd_complete *) packet;

    if (!packet)
        return;

    params->ncmd	= 1;
    params->opcode	= hci->last_cmd;
    if (len)
        memcpy(&packet[EVT_CMD_COMPLETE_SIZE], ret, len);

    hci->evt_submit(hci->opaque, len + EVT_CMD_COMPLETE_SIZE + 2);
}

static void bt_hci_inquiry_done(void *opaque)
{
    struct bt_hci_s *hci = (struct bt_hci_s *) opaque;
    uint8_t status = HCI_SUCCESS;

    if (!hci->lm.periodic)
        hci->lm.inquire = 0;

    bt_hci_event(hci, EVT_INQUIRY_COMPLETE, &status, 1);
}

static void bt_hci_inquiry_result_standard(struct bt_hci_s *hci,
                struct bt_device_s *slave)
{
    inquiry_info params = {
        .num_responses		= 1,
        .bdaddr			= BAINIT(&slave->bd_addr),
        .pscan_rep_mode		= 0x00,	
        .pscan_period_mode	= 0x00,	
        .pscan_mode		= 0x00,	
        .dev_class[0]		= slave->class[0],
        .dev_class[1]		= slave->class[1],
        .dev_class[2]		= slave->class[2],
        
        .clock_offset		= slave->clkoff,	
    };

    bt_hci_event(hci, EVT_INQUIRY_RESULT, &params, INQUIRY_INFO_SIZE);
}

static void bt_hci_inquiry_result_with_rssi(struct bt_hci_s *hci,
                struct bt_device_s *slave)
{
    inquiry_info_with_rssi params = {
        .num_responses		= 1,
        .bdaddr			= BAINIT(&slave->bd_addr),
        .pscan_rep_mode		= 0x00,	
        .pscan_period_mode	= 0x00,	
        .dev_class[0]		= slave->class[0],
        .dev_class[1]		= slave->class[1],
        .dev_class[2]		= slave->class[2],
        
        .clock_offset		= slave->clkoff,	
        .rssi			= DEFAULT_RSSI_DBM,
    };

    bt_hci_event(hci, EVT_INQUIRY_RESULT_WITH_RSSI,
                    &params, INQUIRY_INFO_WITH_RSSI_SIZE);
}

static void bt_hci_inquiry_result(struct bt_hci_s *hci,
                struct bt_device_s *slave)
{
    if (!slave->inquiry_scan || !hci->lm.responses_left)
        return;

    hci->lm.responses_left --;
    hci->lm.responses ++;

    switch (hci->lm.inquiry_mode) {
    case 0x00:
        bt_hci_inquiry_result_standard(hci, slave);
        return;
    case 0x01:
        bt_hci_inquiry_result_with_rssi(hci, slave);
        return;
    default:
        fprintf(stderr, "%s: bad inquiry mode %02x\n", __FUNCTION__,
                        hci->lm.inquiry_mode);
        exit(-1);
    }
}

static void bt_hci_mod_timer_1280ms(QEMUTimer *timer, int period)
{
    qemu_mod_timer(timer, qemu_get_clock_ns(vm_clock) +
                   muldiv64(period << 7, get_ticks_per_sec(), 100));
}

static void bt_hci_inquiry_start(struct bt_hci_s *hci, int length)
{
    struct bt_device_s *slave;

    hci->lm.inquiry_length = length;
    for (slave = hci->device.net->slave; slave; slave = slave->next)
        
        if (slave != &hci->device)
            bt_hci_inquiry_result(hci, slave);

    if (hci->lm.responses_left)
        bt_hci_mod_timer_1280ms(hci->lm.inquiry_done, hci->lm.inquiry_length);
    else
        bt_hci_inquiry_done(hci);

    if (hci->lm.periodic)
        bt_hci_mod_timer_1280ms(hci->lm.inquiry_next, hci->lm.inquiry_period);
}

static void bt_hci_inquiry_next(void *opaque)
{
    struct bt_hci_s *hci = (struct bt_hci_s *) opaque;

    hci->lm.responses_left += hci->lm.responses;
    hci->lm.responses = 0;
    bt_hci_inquiry_start(hci,  hci->lm.inquiry_length);
}

static inline int bt_hci_handle_bad(struct bt_hci_s *hci, uint16_t handle)
{
    return !(handle & HCI_HANDLE_OFFSET) ||
            handle >= (HCI_HANDLE_OFFSET | HCI_HANDLES_MAX) ||
            !hci->lm.handle[handle & ~HCI_HANDLE_OFFSET].link;
}

static inline int bt_hci_role_master(struct bt_hci_s *hci, uint16_t handle)
{
    return !!(hci->lm.role_bmp & (1 << (handle & ~HCI_HANDLE_OFFSET)));
}

static inline struct bt_device_s *bt_hci_remote_dev(struct bt_hci_s *hci,
                uint16_t handle)
{
    struct bt_link_s *link = hci->lm.handle[handle & ~HCI_HANDLE_OFFSET].link;

    return bt_hci_role_master(hci, handle) ? link->slave : link->host;
}

static void bt_hci_mode_tick(void *opaque);
static void bt_hci_lmp_link_establish(struct bt_hci_s *hci,
                struct bt_link_s *link, int master)
{
    hci->lm.handle[hci->lm.last_handle].link = link;

    if (master) {
        
        hci->lm.role_bmp |= 1 << hci->lm.last_handle;

        hci->lm.handle[hci->lm.last_handle].lmp_acl_data =
                link->slave->lmp_acl_data;
    } else {
        
        hci->lm.role_bmp &= ~(1 << hci->lm.last_handle);

        hci->lm.handle[hci->lm.last_handle].lmp_acl_data =
                link->host->lmp_acl_resp;
    }

    
    if (master) {
        link->acl_mode = acl_active;
        hci->lm.handle[hci->lm.last_handle].acl_mode_timer =
                qemu_new_timer_ns(vm_clock, bt_hci_mode_tick, link);
    }
}

static void bt_hci_lmp_link_teardown(struct bt_hci_s *hci, uint16_t handle)
{
    handle &= ~HCI_HANDLE_OFFSET;
    hci->lm.handle[handle].link = NULL;

    if (bt_hci_role_master(hci, handle)) {
        qemu_del_timer(hci->lm.handle[handle].acl_mode_timer);
        qemu_free_timer(hci->lm.handle[handle].acl_mode_timer);
    }
}

static int bt_hci_connect(struct bt_hci_s *hci, bdaddr_t *bdaddr)
{
    struct bt_device_s *slave;
    struct bt_link_s link;

    for (slave = hci->device.net->slave; slave; slave = slave->next)
        if (slave->page_scan && !bacmp(&slave->bd_addr, bdaddr))
            break;
    if (!slave || slave == &hci->device)
        return -ENODEV;

    bacpy(&hci->lm.awaiting_bdaddr[hci->lm.connecting ++], &slave->bd_addr);

    link.slave = slave;
    link.host = &hci->device;
    link.slave->lmp_connection_request(&link);	

    return 0;
}

static void bt_hci_connection_reject(struct bt_hci_s *hci,
                struct bt_device_s *host, uint8_t because)
{
    struct bt_link_s link = {
        .slave	= &hci->device,
        .host	= host,
        
    };

    host->reject_reason = because;
    host->lmp_connection_complete(&link);
}

static void bt_hci_connection_reject_event(struct bt_hci_s *hci,
                bdaddr_t *bdaddr)
{
    evt_conn_complete params;

    params.status	= HCI_NO_CONNECTION;
    params.handle	= 0;
    bacpy(&params.bdaddr, bdaddr);
    params.link_type	= ACL_LINK;
    params.encr_mode	= 0x00;		
    bt_hci_event(hci, EVT_CONN_COMPLETE, &params, EVT_CONN_COMPLETE_SIZE);
}

static void bt_hci_connection_accept(struct bt_hci_s *hci,
                struct bt_device_s *host)
{
    struct bt_hci_link_s *link = qemu_mallocz(sizeof(struct bt_hci_link_s));
    evt_conn_complete params;
    uint16_t handle;
    uint8_t status = HCI_SUCCESS;
    int tries = HCI_HANDLES_MAX;

    
    do {
        while (hci->lm.handle[++ hci->lm.last_handle].link && -- tries)
            hci->lm.last_handle &= HCI_HANDLES_MAX - 1;
        handle = hci->lm.last_handle | HCI_HANDLE_OFFSET;
    } while ((handle == hci->asb_handle || handle == hci->psb_handle) &&
            tries);

    if (!tries) {
        qemu_free(link);
        bt_hci_connection_reject(hci, host, HCI_REJECTED_LIMITED_RESOURCES);
        status = HCI_NO_CONNECTION;
        goto complete;
    }

    link->btlink.slave	= &hci->device;
    link->btlink.host	= host;
    link->handle = handle;

    
    bt_hci_lmp_link_establish(hci, &link->btlink, 0);

complete:
    params.status	= status;
    params.handle	= HNDL(handle);
    bacpy(&params.bdaddr, &host->bd_addr);
    params.link_type	= ACL_LINK;
    params.encr_mode	= 0x00;		
    bt_hci_event(hci, EVT_CONN_COMPLETE, &params, EVT_CONN_COMPLETE_SIZE);

    if (status == HCI_SUCCESS) {
        host->reject_reason = 0;
        host->lmp_connection_complete(&link->btlink);
    }
}

static void bt_hci_lmp_connection_request(struct bt_link_s *link)
{
    struct bt_hci_s *hci = hci_from_device(link->slave);
    evt_conn_request params;

    if (hci->conn_req_host) {
        bt_hci_connection_reject(hci, link->host,
                                 HCI_REJECTED_LIMITED_RESOURCES);
        return;
    }
    hci->conn_req_host = link->host;

    bacpy(&params.bdaddr, &link->host->bd_addr);
    memcpy(&params.dev_class, &link->host->class, sizeof(params.dev_class));
    params.link_type	= ACL_LINK;
    bt_hci_event(hci, EVT_CONN_REQUEST, &params, EVT_CONN_REQUEST_SIZE);
    return;
}

static void bt_hci_conn_accept_timeout(void *opaque)
{
    struct bt_hci_s *hci = (struct bt_hci_s *) opaque;

    if (!hci->conn_req_host)
        return;

    
}

static int bt_hci_lmp_connection_ready(struct bt_hci_s *hci,
                bdaddr_t *bdaddr)
{
    int i;

    for (i = 0; i < hci->lm.connecting; i ++)
        if (!bacmp(&hci->lm.awaiting_bdaddr[i], bdaddr)) {
            if (i < -- hci->lm.connecting)
                bacpy(&hci->lm.awaiting_bdaddr[i],
                                &hci->lm.awaiting_bdaddr[hci->lm.connecting]);
            return 0;
        }

    return 1;
}

static void bt_hci_lmp_connection_complete(struct bt_link_s *link)
{
    struct bt_hci_s *hci = hci_from_device(link->host);
    evt_conn_complete params;
    uint16_t handle;
    uint8_t status = HCI_SUCCESS;
    int tries = HCI_HANDLES_MAX;

    if (bt_hci_lmp_connection_ready(hci, &link->slave->bd_addr)) {
        if (!hci->device.reject_reason)
            link->slave->lmp_disconnect_slave(link);
        handle = 0;
        status = HCI_NO_CONNECTION;
        goto complete;
    }

    if (hci->device.reject_reason) {
        handle = 0;
        status = hci->device.reject_reason;
        goto complete;
    }

    
    do {
        while (hci->lm.handle[++ hci->lm.last_handle].link && -- tries)
            hci->lm.last_handle &= HCI_HANDLES_MAX - 1;
        handle = hci->lm.last_handle | HCI_HANDLE_OFFSET;
    } while ((handle == hci->asb_handle || handle == hci->psb_handle) &&
            tries);

    if (!tries) {
        link->slave->lmp_disconnect_slave(link);
        status = HCI_NO_CONNECTION;
        goto complete;
    }

    
    link->handle = handle;
    bt_hci_lmp_link_establish(hci, link, 1);

complete:
    params.status	= status;
    params.handle	= HNDL(handle);
    params.link_type	= ACL_LINK;
    bacpy(&params.bdaddr, &link->slave->bd_addr);
    params.encr_mode	= 0x00;		
    bt_hci_event(hci, EVT_CONN_COMPLETE, &params, EVT_CONN_COMPLETE_SIZE);
}

static void bt_hci_disconnect(struct bt_hci_s *hci,
                uint16_t handle, int reason)
{
    struct bt_link_s *btlink =
            hci->lm.handle[handle & ~HCI_HANDLE_OFFSET].link;
    struct bt_hci_link_s *link;
    evt_disconn_complete params;

    if (bt_hci_role_master(hci, handle)) {
        btlink->slave->reject_reason = reason;
        btlink->slave->lmp_disconnect_slave(btlink);
        

        goto complete;
    }

    btlink->host->reject_reason = reason;
    btlink->host->lmp_disconnect_master(btlink);

    
    link = (struct bt_hci_link_s *) btlink;
    qemu_free(link);

complete:
    bt_hci_lmp_link_teardown(hci, handle);

    params.status	= HCI_SUCCESS;
    params.handle	= HNDL(handle);
    params.reason	= HCI_CONNECTION_TERMINATED;
    bt_hci_event(hci, EVT_DISCONN_COMPLETE,
                    &params, EVT_DISCONN_COMPLETE_SIZE);
}

static void bt_hci_lmp_disconnect_host(struct bt_link_s *link)
{
    struct bt_hci_s *hci = hci_from_device(link->host);
    uint16_t handle = link->handle;
    evt_disconn_complete params;

    bt_hci_lmp_link_teardown(hci, handle);

    params.status	= HCI_SUCCESS;
    params.handle	= HNDL(handle);
    params.reason	= hci->device.reject_reason;
    bt_hci_event(hci, EVT_DISCONN_COMPLETE,
                    &params, EVT_DISCONN_COMPLETE_SIZE);
}

static void bt_hci_lmp_disconnect_slave(struct bt_link_s *btlink)
{
    struct bt_hci_link_s *link = (struct bt_hci_link_s *) btlink;
    struct bt_hci_s *hci = hci_from_device(btlink->slave);
    uint16_t handle = link->handle;
    evt_disconn_complete params;

    qemu_free(link);

    bt_hci_lmp_link_teardown(hci, handle);

    params.status	= HCI_SUCCESS;
    params.handle	= HNDL(handle);
    params.reason	= hci->device.reject_reason;
    bt_hci_event(hci, EVT_DISCONN_COMPLETE,
                    &params, EVT_DISCONN_COMPLETE_SIZE);
}

static int bt_hci_name_req(struct bt_hci_s *hci, bdaddr_t *bdaddr)
{
    struct bt_device_s *slave;
    evt_remote_name_req_complete params;
    int len;

    for (slave = hci->device.net->slave; slave; slave = slave->next)
        if (slave->page_scan && !bacmp(&slave->bd_addr, bdaddr))
            break;
    if (!slave)
        return -ENODEV;

    bt_hci_event_status(hci, HCI_SUCCESS);

    params.status       = HCI_SUCCESS;
    bacpy(&params.bdaddr, &slave->bd_addr);
    len = snprintf(params.name, sizeof(params.name),
                    "%s", slave->lmp_name ?: "");
    memset(params.name + len, 0, sizeof(params.name) - len);
    bt_hci_event(hci, EVT_REMOTE_NAME_REQ_COMPLETE,
                    &params, EVT_REMOTE_NAME_REQ_COMPLETE_SIZE);

    return 0;
}

static int bt_hci_features_req(struct bt_hci_s *hci, uint16_t handle)
{
    struct bt_device_s *slave;
    evt_read_remote_features_complete params;

    if (bt_hci_handle_bad(hci, handle))
        return -ENODEV;

    slave = bt_hci_remote_dev(hci, handle);

    bt_hci_event_status(hci, HCI_SUCCESS);

    params.status	= HCI_SUCCESS;
    params.handle	= HNDL(handle);
    params.features[0]	= (slave->lmp_caps >>  0) & 0xff;
    params.features[1]	= (slave->lmp_caps >>  8) & 0xff;
    params.features[2]	= (slave->lmp_caps >> 16) & 0xff;
    params.features[3]	= (slave->lmp_caps >> 24) & 0xff;
    params.features[4]	= (slave->lmp_caps >> 32) & 0xff;
    params.features[5]	= (slave->lmp_caps >> 40) & 0xff;
    params.features[6]	= (slave->lmp_caps >> 48) & 0xff;
    params.features[7]	= (slave->lmp_caps >> 56) & 0xff;
    bt_hci_event(hci, EVT_READ_REMOTE_FEATURES_COMPLETE,
                    &params, EVT_READ_REMOTE_FEATURES_COMPLETE_SIZE);

    return 0;
}

static int bt_hci_version_req(struct bt_hci_s *hci, uint16_t handle)
{
    evt_read_remote_version_complete params;

    if (bt_hci_handle_bad(hci, handle))
        return -ENODEV;

    bt_hci_remote_dev(hci, handle);

    bt_hci_event_status(hci, HCI_SUCCESS);

    params.status	= HCI_SUCCESS;
    params.handle	= HNDL(handle);
    params.lmp_ver	= 0x03;
    params.manufacturer	= cpu_to_le16(0xa000);
    params.lmp_subver	= cpu_to_le16(0xa607);
    bt_hci_event(hci, EVT_READ_REMOTE_VERSION_COMPLETE,
                    &params, EVT_READ_REMOTE_VERSION_COMPLETE_SIZE);

    return 0;
}

static int bt_hci_clkoffset_req(struct bt_hci_s *hci, uint16_t handle)
{
    struct bt_device_s *slave;
    evt_read_clock_offset_complete params;

    if (bt_hci_handle_bad(hci, handle))
        return -ENODEV;

    slave = bt_hci_remote_dev(hci, handle);

    bt_hci_event_status(hci, HCI_SUCCESS);

    params.status	= HCI_SUCCESS;
    params.handle	= HNDL(handle);
    
    params.clock_offset	= slave->clkoff;	
    bt_hci_event(hci, EVT_READ_CLOCK_OFFSET_COMPLETE,
                    &params, EVT_READ_CLOCK_OFFSET_COMPLETE_SIZE);

    return 0;
}

static void bt_hci_event_mode(struct bt_hci_s *hci, struct bt_link_s *link,
                uint16_t handle)
{
    evt_mode_change params = {
        .status		= HCI_SUCCESS,
        .handle		= HNDL(handle),
        .mode		= link->acl_mode,
        .interval	= cpu_to_le16(link->acl_interval),
    };

    bt_hci_event(hci, EVT_MODE_CHANGE, &params, EVT_MODE_CHANGE_SIZE);
}

static void bt_hci_lmp_mode_change_master(struct bt_hci_s *hci,
                struct bt_link_s *link, int mode, uint16_t interval)
{
    link->acl_mode = mode;
    link->acl_interval = interval;

    bt_hci_event_mode(hci, link, link->handle);

    link->slave->lmp_mode_change(link);
}

static void bt_hci_lmp_mode_change_slave(struct bt_link_s *btlink)
{
    struct bt_hci_link_s *link = (struct bt_hci_link_s *) btlink;
    struct bt_hci_s *hci = hci_from_device(btlink->slave);

    bt_hci_event_mode(hci, btlink, link->handle);
}

static int bt_hci_mode_change(struct bt_hci_s *hci, uint16_t handle,
                int interval, int mode)
{
    struct bt_hci_master_link_s *link;

    if (bt_hci_handle_bad(hci, handle) || !bt_hci_role_master(hci, handle))
        return -ENODEV;

    link = &hci->lm.handle[handle & ~HCI_HANDLE_OFFSET];
    if (link->link->acl_mode != acl_active) {
        bt_hci_event_status(hci, HCI_COMMAND_DISALLOWED);
        return 0;
    }

    bt_hci_event_status(hci, HCI_SUCCESS);

    qemu_mod_timer(link->acl_mode_timer, qemu_get_clock_ns(vm_clock) +
                   muldiv64(interval * 625, get_ticks_per_sec(), 1000000));
    bt_hci_lmp_mode_change_master(hci, link->link, mode, interval);

    return 0;
}

static int bt_hci_mode_cancel(struct bt_hci_s *hci, uint16_t handle, int mode)
{
    struct bt_hci_master_link_s *link;

    if (bt_hci_handle_bad(hci, handle) || !bt_hci_role_master(hci, handle))
        return -ENODEV;

    link = &hci->lm.handle[handle & ~HCI_HANDLE_OFFSET];
    if (link->link->acl_mode != mode) {
        bt_hci_event_status(hci, HCI_COMMAND_DISALLOWED);

        return 0;
    }

    bt_hci_event_status(hci, HCI_SUCCESS);

    qemu_del_timer(link->acl_mode_timer);
    bt_hci_lmp_mode_change_master(hci, link->link, acl_active, 0);

    return 0;
}

static void bt_hci_mode_tick(void *opaque)
{
    struct bt_link_s *link = opaque;
    struct bt_hci_s *hci = hci_from_device(link->host);

    bt_hci_lmp_mode_change_master(hci, link, acl_active, 0);
}

static void bt_hci_reset(struct bt_hci_s *hci)
{
    hci->acl_len = 0;
    hci->last_cmd = 0;
    hci->lm.connecting = 0;

    hci->event_mask[0] = 0xff;
    hci->event_mask[1] = 0xff;
    hci->event_mask[2] = 0xff;
    hci->event_mask[3] = 0xff;
    hci->event_mask[4] = 0xff;
    hci->event_mask[5] = 0x1f;
    hci->event_mask[6] = 0x00;
    hci->event_mask[7] = 0x00;
    hci->device.inquiry_scan = 0;
    hci->device.page_scan = 0;
    if (hci->device.lmp_name)
        qemu_free((void *) hci->device.lmp_name);
    hci->device.lmp_name = NULL;
    hci->device.class[0] = 0x00;
    hci->device.class[1] = 0x00;
    hci->device.class[2] = 0x00;
    hci->voice_setting = 0x0000;
    hci->conn_accept_tout = 0x1f40;
    hci->lm.inquiry_mode = 0x00;

    hci->psb_handle = 0x000;
    hci->asb_handle = 0x000;

    
    qemu_del_timer(hci->lm.inquiry_done);
    qemu_del_timer(hci->lm.inquiry_next);
    qemu_del_timer(hci->conn_accept_timer);
}

static void bt_hci_read_local_version_rp(struct bt_hci_s *hci)
{
    read_local_version_rp lv = {
        .status		= HCI_SUCCESS,
        .hci_ver	= 0x03,
        .hci_rev	= cpu_to_le16(0xa607),
        .lmp_ver	= 0x03,
        .manufacturer	= cpu_to_le16(0xa000),
        .lmp_subver	= cpu_to_le16(0xa607),
    };

    bt_hci_event_complete(hci, &lv, READ_LOCAL_VERSION_RP_SIZE);
}

static void bt_hci_read_local_commands_rp(struct bt_hci_s *hci)
{
    read_local_commands_rp lc = {
        .status		= HCI_SUCCESS,
        .commands	= {
            
            
            0xbf, 0x80, 0xf9, 0x03, 0xb2, 0xc0, 0x03, 0xc3,
            0x00, 0x0f, 0x80, 0x00, 0xc0, 0x00, 0xe8, 0x13,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
    };

    bt_hci_event_complete(hci, &lc, READ_LOCAL_COMMANDS_RP_SIZE);
}

static void bt_hci_read_local_features_rp(struct bt_hci_s *hci)
{
    read_local_features_rp lf = {
        .status		= HCI_SUCCESS,
        .features	= {
            (hci->device.lmp_caps >>  0) & 0xff,
            (hci->device.lmp_caps >>  8) & 0xff,
            (hci->device.lmp_caps >> 16) & 0xff,
            (hci->device.lmp_caps >> 24) & 0xff,
            (hci->device.lmp_caps >> 32) & 0xff,
            (hci->device.lmp_caps >> 40) & 0xff,
            (hci->device.lmp_caps >> 48) & 0xff,
            (hci->device.lmp_caps >> 56) & 0xff,
        },
    };

    bt_hci_event_complete(hci, &lf, READ_LOCAL_FEATURES_RP_SIZE);
}

static void bt_hci_read_local_ext_features_rp(struct bt_hci_s *hci, int page)
{
    read_local_ext_features_rp lef = {
        .status		= HCI_SUCCESS,
        .page_num	= page,
        .max_page_num	= 0x00,
        .features	= {
            
            0x5f, 0x35, 0x85, 0x7e, 0x9b, 0x19, 0x00, 0x80,
        },
    };
    if (page)
        memset(lef.features, 0, sizeof(lef.features));

    bt_hci_event_complete(hci, &lef, READ_LOCAL_EXT_FEATURES_RP_SIZE);
}

static void bt_hci_read_buffer_size_rp(struct bt_hci_s *hci)
{
    read_buffer_size_rp bs = {
        .status		= HCI_SUCCESS,
        .acl_mtu	= cpu_to_le16(0x0200),
        .sco_mtu	= 0,
        .acl_max_pkt	= cpu_to_le16(0x0001),
        .sco_max_pkt	= cpu_to_le16(0x0000),
    };

    bt_hci_event_complete(hci, &bs, READ_BUFFER_SIZE_RP_SIZE);
}

static void bt_hci_read_country_code_rp(struct bt_hci_s *hci)
{
    read_country_code_rp cc ={
        .status		= HCI_SUCCESS,
        .country_code	= 0x00,	
    };

    bt_hci_event_complete(hci, &cc, READ_COUNTRY_CODE_RP_SIZE);

    
}

static void bt_hci_read_bd_addr_rp(struct bt_hci_s *hci)
{
    read_bd_addr_rp ba = {
        .status = HCI_SUCCESS,
        .bdaddr = BAINIT(&hci->device.bd_addr),
    };

    bt_hci_event_complete(hci, &ba, READ_BD_ADDR_RP_SIZE);
}

static int bt_hci_link_quality_rp(struct bt_hci_s *hci, uint16_t handle)
{
    read_link_quality_rp lq = {
        .status		= HCI_SUCCESS,
        .handle		= HNDL(handle),
        .link_quality	= 0xff,
    };

    if (bt_hci_handle_bad(hci, handle))
        lq.status = HCI_NO_CONNECTION;

    bt_hci_event_complete(hci, &lq, READ_LINK_QUALITY_RP_SIZE);
    return 0;
}

static inline void bt_hci_event_complete_status(struct bt_hci_s *hci,
                uint8_t status)
{
    bt_hci_event_complete(hci, &status, 1);
}

static inline void bt_hci_event_complete_conn_cancel(struct bt_hci_s *hci,
                uint8_t status, bdaddr_t *bd_addr)
{
    create_conn_cancel_rp params = {
        .status = status,
        .bdaddr = BAINIT(bd_addr),
    };

    bt_hci_event_complete(hci, &params, CREATE_CONN_CANCEL_RP_SIZE);
}

static inline void bt_hci_event_auth_complete(struct bt_hci_s *hci,
                uint16_t handle)
{
    evt_auth_complete params = {
        .status = HCI_SUCCESS,
        .handle = HNDL(handle),
    };

    bt_hci_event(hci, EVT_AUTH_COMPLETE, &params, EVT_AUTH_COMPLETE_SIZE);
}

static inline void bt_hci_event_encrypt_change(struct bt_hci_s *hci,
                uint16_t handle, uint8_t mode)
{
    evt_encrypt_change params = {
        .status		= HCI_SUCCESS,
        .handle		= HNDL(handle),
        .encrypt	= mode,
    };

    bt_hci_event(hci, EVT_ENCRYPT_CHANGE, &params, EVT_ENCRYPT_CHANGE_SIZE);
}

static inline void bt_hci_event_complete_name_cancel(struct bt_hci_s *hci,
                bdaddr_t *bd_addr)
{
    remote_name_req_cancel_rp params = {
        .status = HCI_INVALID_PARAMETERS,
        .bdaddr = BAINIT(bd_addr),
    };

    bt_hci_event_complete(hci, &params, REMOTE_NAME_REQ_CANCEL_RP_SIZE);
}

static inline void bt_hci_event_read_remote_ext_features(struct bt_hci_s *hci,
                uint16_t handle)
{
    evt_read_remote_ext_features_complete params = {
        .status = HCI_UNSUPPORTED_FEATURE,
        .handle = HNDL(handle),
        
    };

    bt_hci_event(hci, EVT_READ_REMOTE_EXT_FEATURES_COMPLETE,
                    &params, EVT_READ_REMOTE_EXT_FEATURES_COMPLETE_SIZE);
}

static inline void bt_hci_event_complete_lmp_handle(struct bt_hci_s *hci,
                uint16_t handle)
{
    read_lmp_handle_rp params = {
        .status		= HCI_NO_CONNECTION,
        .handle		= HNDL(handle),
        .reserved	= 0,
        
    };

    bt_hci_event_complete(hci, &params, READ_LMP_HANDLE_RP_SIZE);
}

static inline void bt_hci_event_complete_role_discovery(struct bt_hci_s *hci,
                int status, uint16_t handle, int master)
{
    role_discovery_rp params = {
        .status		= status,
        .handle		= HNDL(handle),
        .role		= master ? 0x00 : 0x01,
    };

    bt_hci_event_complete(hci, &params, ROLE_DISCOVERY_RP_SIZE);
}

static inline void bt_hci_event_complete_flush(struct bt_hci_s *hci,
                int status, uint16_t handle)
{
    flush_rp params = {
        .status		= status,
        .handle		= HNDL(handle),
    };

    bt_hci_event_complete(hci, &params, FLUSH_RP_SIZE);
}

static inline void bt_hci_event_complete_read_local_name(struct bt_hci_s *hci)
{
    read_local_name_rp params;
    params.status = HCI_SUCCESS;
    memset(params.name, 0, sizeof(params.name));
    if (hci->device.lmp_name)
        strncpy(params.name, hci->device.lmp_name, sizeof(params.name));

    bt_hci_event_complete(hci, &params, READ_LOCAL_NAME_RP_SIZE);
}

static inline void bt_hci_event_complete_read_conn_accept_timeout(
                struct bt_hci_s *hci)
{
    read_conn_accept_timeout_rp params = {
        .status		= HCI_SUCCESS,
        .timeout	= cpu_to_le16(hci->conn_accept_tout),
    };

    bt_hci_event_complete(hci, &params, READ_CONN_ACCEPT_TIMEOUT_RP_SIZE);
}

static inline void bt_hci_event_complete_read_scan_enable(struct bt_hci_s *hci)
{
    read_scan_enable_rp params = {
        .status = HCI_SUCCESS,
        .enable =
                (hci->device.inquiry_scan ? SCAN_INQUIRY : 0) |
                (hci->device.page_scan ? SCAN_PAGE : 0),
    };

    bt_hci_event_complete(hci, &params, READ_SCAN_ENABLE_RP_SIZE);
}

static inline void bt_hci_event_complete_read_local_class(struct bt_hci_s *hci)
{
    read_class_of_dev_rp params;

    params.status = HCI_SUCCESS;
    memcpy(params.dev_class, hci->device.class, sizeof(params.dev_class));

    bt_hci_event_complete(hci, &params, READ_CLASS_OF_DEV_RP_SIZE);
}

static inline void bt_hci_event_complete_voice_setting(struct bt_hci_s *hci)
{
    read_voice_setting_rp params = {
        .status		= HCI_SUCCESS,
        .voice_setting	= hci->voice_setting,	
    };

    bt_hci_event_complete(hci, &params, READ_VOICE_SETTING_RP_SIZE);
}

static inline void bt_hci_event_complete_read_inquiry_mode(
                struct bt_hci_s *hci)
{
    read_inquiry_mode_rp params = {
        .status		= HCI_SUCCESS,
        .mode		= hci->lm.inquiry_mode,
    };

    bt_hci_event_complete(hci, &params, READ_INQUIRY_MODE_RP_SIZE);
}

static inline void bt_hci_event_num_comp_pkts(struct bt_hci_s *hci,
                uint16_t handle, int packets)
{
    uint16_t buf[EVT_NUM_COMP_PKTS_SIZE(1) / 2 + 1];
    evt_num_comp_pkts *params = (void *) ((uint8_t *) buf + 1);

    params->num_hndl			= 1;
    params->connection->handle		= HNDL(handle);
    params->connection->num_packets	= cpu_to_le16(packets);

    bt_hci_event(hci, EVT_NUM_COMP_PKTS, params, EVT_NUM_COMP_PKTS_SIZE(1));
}

static void bt_submit_hci(struct HCIInfo *info,
                const uint8_t *data, int length)
{
    struct bt_hci_s *hci = hci_from_info(info);
    uint16_t cmd;
    int paramlen, i;

    if (length < HCI_COMMAND_HDR_SIZE)
        goto short_hci;

    memcpy(&hci->last_cmd, data, 2);

    cmd = (data[1] << 8) | data[0];
    paramlen = data[2];
    if (cmd_opcode_ogf(cmd) == 0 || cmd_opcode_ocf(cmd) == 0)	
        return;

    data += HCI_COMMAND_HDR_SIZE;
    length -= HCI_COMMAND_HDR_SIZE;

    if (paramlen > length)
        return;

#define PARAM(cmd, param)	(((cmd##_cp *) data)->param)
#define PARAM16(cmd, param)	le16_to_cpup(&PARAM(cmd, param))
#define PARAMHANDLE(cmd)	HNDL(PARAM(cmd, handle))
#define LENGTH_CHECK(cmd)	if (length < sizeof(cmd##_cp)) goto short_hci
    switch (cmd) {
    case cmd_opcode_pack(OGF_LINK_CTL, OCF_INQUIRY):
        LENGTH_CHECK(inquiry);

        if (PARAM(inquiry, length) < 1) {
            bt_hci_event_complete_status(hci, HCI_INVALID_PARAMETERS);
            break;
        }

        hci->lm.inquire = 1;
        hci->lm.periodic = 0;
        hci->lm.responses_left = PARAM(inquiry, num_rsp) ?: INT_MAX;
        hci->lm.responses = 0;
        bt_hci_event_status(hci, HCI_SUCCESS);
        bt_hci_inquiry_start(hci, PARAM(inquiry, length));
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_INQUIRY_CANCEL):
        if (!hci->lm.inquire || hci->lm.periodic) {
            fprintf(stderr, "%s: Inquiry Cancel should only be issued after "
                            "the Inquiry command has been issued, a Command "
                            "Status event has been received for the Inquiry "
                            "command, and before the Inquiry Complete event "
                            "occurs", __FUNCTION__);
            bt_hci_event_complete_status(hci, HCI_COMMAND_DISALLOWED);
            break;
        }

        hci->lm.inquire = 0;
        qemu_del_timer(hci->lm.inquiry_done);
        bt_hci_event_complete_status(hci, HCI_SUCCESS);
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_PERIODIC_INQUIRY):
        LENGTH_CHECK(periodic_inquiry);

        if (!(PARAM(periodic_inquiry, length) <
                                PARAM16(periodic_inquiry, min_period) &&
                                PARAM16(periodic_inquiry, min_period) <
                                PARAM16(periodic_inquiry, max_period)) ||
                        PARAM(periodic_inquiry, length) < 1 ||
                        PARAM16(periodic_inquiry, min_period) < 2 ||
                        PARAM16(periodic_inquiry, max_period) < 3) {
            bt_hci_event_complete_status(hci, HCI_INVALID_PARAMETERS);
            break;
        }

        hci->lm.inquire = 1;
        hci->lm.periodic = 1;
        hci->lm.responses_left = PARAM(periodic_inquiry, num_rsp);
        hci->lm.responses = 0;
        hci->lm.inquiry_period = PARAM16(periodic_inquiry, max_period);
        bt_hci_event_complete_status(hci, HCI_SUCCESS);
        bt_hci_inquiry_start(hci, PARAM(periodic_inquiry, length));
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_EXIT_PERIODIC_INQUIRY):
        if (!hci->lm.inquire || !hci->lm.periodic) {
            fprintf(stderr, "%s: Inquiry Cancel should only be issued after "
                            "the Inquiry command has been issued, a Command "
                            "Status event has been received for the Inquiry "
                            "command, and before the Inquiry Complete event "
                            "occurs", __FUNCTION__);
            bt_hci_event_complete_status(hci, HCI_COMMAND_DISALLOWED);
            break;
        }
        hci->lm.inquire = 0;
        qemu_del_timer(hci->lm.inquiry_done);
        qemu_del_timer(hci->lm.inquiry_next);
        bt_hci_event_complete_status(hci, HCI_SUCCESS);
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_CREATE_CONN):
        LENGTH_CHECK(create_conn);

        if (hci->lm.connecting >= HCI_HANDLES_MAX) {
            bt_hci_event_status(hci, HCI_REJECTED_LIMITED_RESOURCES);
            break;
        }
        bt_hci_event_status(hci, HCI_SUCCESS);

        if (bt_hci_connect(hci, &PARAM(create_conn, bdaddr)))
            bt_hci_connection_reject_event(hci, &PARAM(create_conn, bdaddr));
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_DISCONNECT):
        LENGTH_CHECK(disconnect);

        if (bt_hci_handle_bad(hci, PARAMHANDLE(disconnect))) {
            bt_hci_event_status(hci, HCI_NO_CONNECTION);
            break;
        }

        bt_hci_event_status(hci, HCI_SUCCESS);
        bt_hci_disconnect(hci, PARAMHANDLE(disconnect),
                        PARAM(disconnect, reason));
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_CREATE_CONN_CANCEL):
        LENGTH_CHECK(create_conn_cancel);

        if (bt_hci_lmp_connection_ready(hci,
                                &PARAM(create_conn_cancel, bdaddr))) {
            for (i = 0; i < HCI_HANDLES_MAX; i ++)
                if (bt_hci_role_master(hci, i) && hci->lm.handle[i].link &&
                                !bacmp(&hci->lm.handle[i].link->slave->bd_addr,
                                        &PARAM(create_conn_cancel, bdaddr)))
                   break;

            bt_hci_event_complete_conn_cancel(hci, i < HCI_HANDLES_MAX ?
                            HCI_ACL_CONNECTION_EXISTS : HCI_NO_CONNECTION,
                            &PARAM(create_conn_cancel, bdaddr));
        } else
            bt_hci_event_complete_conn_cancel(hci, HCI_SUCCESS,
                            &PARAM(create_conn_cancel, bdaddr));
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_ACCEPT_CONN_REQ):
        LENGTH_CHECK(accept_conn_req);

        if (!hci->conn_req_host ||
                        bacmp(&PARAM(accept_conn_req, bdaddr),
                                &hci->conn_req_host->bd_addr)) {
            bt_hci_event_status(hci, HCI_INVALID_PARAMETERS);
            break;
        }

        bt_hci_event_status(hci, HCI_SUCCESS);
        bt_hci_connection_accept(hci, hci->conn_req_host);
        hci->conn_req_host = NULL;
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_REJECT_CONN_REQ):
        LENGTH_CHECK(reject_conn_req);

        if (!hci->conn_req_host ||
                        bacmp(&PARAM(reject_conn_req, bdaddr),
                                &hci->conn_req_host->bd_addr)) {
            bt_hci_event_status(hci, HCI_INVALID_PARAMETERS);
            break;
        }

        bt_hci_event_status(hci, HCI_SUCCESS);
        bt_hci_connection_reject(hci, hci->conn_req_host,
                        PARAM(reject_conn_req, reason));
        bt_hci_connection_reject_event(hci, &hci->conn_req_host->bd_addr);
        hci->conn_req_host = NULL;
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_AUTH_REQUESTED):
        LENGTH_CHECK(auth_requested);

        if (bt_hci_handle_bad(hci, PARAMHANDLE(auth_requested)))
            bt_hci_event_status(hci, HCI_NO_CONNECTION);
        else {
            bt_hci_event_status(hci, HCI_SUCCESS);
            bt_hci_event_auth_complete(hci, PARAMHANDLE(auth_requested));
        }
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_SET_CONN_ENCRYPT):
        LENGTH_CHECK(set_conn_encrypt);

        if (bt_hci_handle_bad(hci, PARAMHANDLE(set_conn_encrypt)))
            bt_hci_event_status(hci, HCI_NO_CONNECTION);
        else {
            bt_hci_event_status(hci, HCI_SUCCESS);
            bt_hci_event_encrypt_change(hci,
                            PARAMHANDLE(set_conn_encrypt),
                            PARAM(set_conn_encrypt, encrypt));
        }
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_REMOTE_NAME_REQ):
        LENGTH_CHECK(remote_name_req);

        if (bt_hci_name_req(hci, &PARAM(remote_name_req, bdaddr)))
            bt_hci_event_status(hci, HCI_NO_CONNECTION);
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_REMOTE_NAME_REQ_CANCEL):
        LENGTH_CHECK(remote_name_req_cancel);

        bt_hci_event_complete_name_cancel(hci,
                        &PARAM(remote_name_req_cancel, bdaddr));
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_READ_REMOTE_FEATURES):
        LENGTH_CHECK(read_remote_features);

        if (bt_hci_features_req(hci, PARAMHANDLE(read_remote_features)))
            bt_hci_event_status(hci, HCI_NO_CONNECTION);
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_READ_REMOTE_EXT_FEATURES):
        LENGTH_CHECK(read_remote_ext_features);

        if (bt_hci_handle_bad(hci, PARAMHANDLE(read_remote_ext_features)))
            bt_hci_event_status(hci, HCI_NO_CONNECTION);
        else {
            bt_hci_event_status(hci, HCI_SUCCESS);
            bt_hci_event_read_remote_ext_features(hci,
                            PARAMHANDLE(read_remote_ext_features));
        }
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_READ_REMOTE_VERSION):
        LENGTH_CHECK(read_remote_version);

        if (bt_hci_version_req(hci, PARAMHANDLE(read_remote_version)))
            bt_hci_event_status(hci, HCI_NO_CONNECTION);
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_READ_CLOCK_OFFSET):
        LENGTH_CHECK(read_clock_offset);

        if (bt_hci_clkoffset_req(hci, PARAMHANDLE(read_clock_offset)))
            bt_hci_event_status(hci, HCI_NO_CONNECTION);
        break;

    case cmd_opcode_pack(OGF_LINK_CTL, OCF_READ_LMP_HANDLE):
        LENGTH_CHECK(read_lmp_handle);

        
        bt_hci_event_complete_lmp_handle(hci, PARAMHANDLE(read_lmp_handle));
        break;

    case cmd_opcode_pack(OGF_LINK_POLICY, OCF_HOLD_MODE):
        LENGTH_CHECK(hold_mode);

        if (PARAM16(hold_mode, min_interval) >
                        PARAM16(hold_mode, max_interval) ||
                        PARAM16(hold_mode, min_interval) < 0x0002 ||
                        PARAM16(hold_mode, max_interval) > 0xff00 ||
                        (PARAM16(hold_mode, min_interval) & 1) ||
                        (PARAM16(hold_mode, max_interval) & 1)) {
            bt_hci_event_status(hci, HCI_INVALID_PARAMETERS);
            break;
        }

        if (bt_hci_mode_change(hci, PARAMHANDLE(hold_mode),
                                PARAM16(hold_mode, max_interval),
                                acl_hold))
            bt_hci_event_status(hci, HCI_NO_CONNECTION);
        break;

    case cmd_opcode_pack(OGF_LINK_POLICY, OCF_PARK_MODE):
        LENGTH_CHECK(park_mode);

        if (PARAM16(park_mode, min_interval) >
                        PARAM16(park_mode, max_interval) ||
                        PARAM16(park_mode, min_interval) < 0x000e ||
                        (PARAM16(park_mode, min_interval) & 1) ||
                        (PARAM16(park_mode, max_interval) & 1)) {
            bt_hci_event_status(hci, HCI_INVALID_PARAMETERS);
            break;
        }

        if (bt_hci_mode_change(hci, PARAMHANDLE(park_mode),
                                PARAM16(park_mode, max_interval),
                                acl_parked))
            bt_hci_event_status(hci, HCI_NO_CONNECTION);
        break;

    case cmd_opcode_pack(OGF_LINK_POLICY, OCF_EXIT_PARK_MODE):
        LENGTH_CHECK(exit_park_mode);

        if (bt_hci_mode_cancel(hci, PARAMHANDLE(exit_park_mode),
                                acl_parked))
            bt_hci_event_status(hci, HCI_NO_CONNECTION);
        break;

    case cmd_opcode_pack(OGF_LINK_POLICY, OCF_ROLE_DISCOVERY):
        LENGTH_CHECK(role_discovery);

        if (bt_hci_handle_bad(hci, PARAMHANDLE(role_discovery)))
            bt_hci_event_complete_role_discovery(hci,
                            HCI_NO_CONNECTION, PARAMHANDLE(role_discovery), 0);
        else
            bt_hci_event_complete_role_discovery(hci,
                            HCI_SUCCESS, PARAMHANDLE(role_discovery),
                            bt_hci_role_master(hci,
                                    PARAMHANDLE(role_discovery)));
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_SET_EVENT_MASK):
        LENGTH_CHECK(set_event_mask);

        memcpy(hci->event_mask, PARAM(set_event_mask, mask), 8);
        bt_hci_event_complete_status(hci, HCI_SUCCESS);
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_RESET):
        bt_hci_reset(hci);
        bt_hci_event_status(hci, HCI_SUCCESS);
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_SET_EVENT_FLT):
        if (length >= 1 && PARAM(set_event_flt, flt_type) == FLT_CLEAR_ALL)
            ;
        else
            LENGTH_CHECK(set_event_flt);

        
        bt_hci_event_complete_status(hci, HCI_SUCCESS);
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_FLUSH):
        LENGTH_CHECK(flush);

        if (bt_hci_handle_bad(hci, PARAMHANDLE(flush)))
            bt_hci_event_complete_flush(hci,
                            HCI_NO_CONNECTION, PARAMHANDLE(flush));
        else {
            
            bt_hci_event(hci, EVT_FLUSH_OCCURRED,
                            &PARAM(flush, handle),
                            EVT_FLUSH_OCCURRED_SIZE);
            bt_hci_event_complete_flush(hci,
                            HCI_SUCCESS, PARAMHANDLE(flush));
        }
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_CHANGE_LOCAL_NAME):
        LENGTH_CHECK(change_local_name);

        if (hci->device.lmp_name)
            qemu_free((void *) hci->device.lmp_name);
        hci->device.lmp_name = qemu_strndup(PARAM(change_local_name, name),
                        sizeof(PARAM(change_local_name, name)));
        bt_hci_event_complete_status(hci, HCI_SUCCESS);
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_READ_LOCAL_NAME):
        bt_hci_event_complete_read_local_name(hci);
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_READ_CONN_ACCEPT_TIMEOUT):
        bt_hci_event_complete_read_conn_accept_timeout(hci);
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_WRITE_CONN_ACCEPT_TIMEOUT):
        
        LENGTH_CHECK(write_conn_accept_timeout);

        if (PARAM16(write_conn_accept_timeout, timeout) < 0x0001 ||
                        PARAM16(write_conn_accept_timeout, timeout) > 0xb540) {
            bt_hci_event_complete_status(hci, HCI_INVALID_PARAMETERS);
            break;
        }

        hci->conn_accept_tout = PARAM16(write_conn_accept_timeout, timeout);
        bt_hci_event_complete_status(hci, HCI_SUCCESS);
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_READ_SCAN_ENABLE):
        bt_hci_event_complete_read_scan_enable(hci);
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_WRITE_SCAN_ENABLE):
        LENGTH_CHECK(write_scan_enable);

        
        hci->device.inquiry_scan =
                !!(PARAM(write_scan_enable, scan_enable) & SCAN_INQUIRY);
        hci->device.page_scan =
                !!(PARAM(write_scan_enable, scan_enable) & SCAN_PAGE);
        bt_hci_event_complete_status(hci, HCI_SUCCESS);
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_READ_CLASS_OF_DEV):
        bt_hci_event_complete_read_local_class(hci);
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_WRITE_CLASS_OF_DEV):
        LENGTH_CHECK(write_class_of_dev);

        memcpy(hci->device.class, PARAM(write_class_of_dev, dev_class),
                        sizeof(PARAM(write_class_of_dev, dev_class)));
        bt_hci_event_complete_status(hci, HCI_SUCCESS);
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_READ_VOICE_SETTING):
        bt_hci_event_complete_voice_setting(hci);
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_WRITE_VOICE_SETTING):
        LENGTH_CHECK(write_voice_setting);

        hci->voice_setting = PARAM(write_voice_setting, voice_setting);
        bt_hci_event_complete_status(hci, HCI_SUCCESS);
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_HOST_NUMBER_OF_COMPLETED_PACKETS):
        if (length < data[0] * 2 + 1)
            goto short_hci;

        for (i = 0; i < data[0]; i ++)
            if (bt_hci_handle_bad(hci,
                                    data[i * 2 + 1] | (data[i * 2 + 2] << 8)))
                bt_hci_event_complete_status(hci, HCI_INVALID_PARAMETERS);
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_READ_INQUIRY_MODE):
        bt_hci_event_complete_read_inquiry_mode(hci);
        break;

    case cmd_opcode_pack(OGF_HOST_CTL, OCF_WRITE_INQUIRY_MODE):
        LENGTH_CHECK(write_inquiry_mode);

        if (PARAM(write_inquiry_mode, mode) > 0x01) {
            bt_hci_event_complete_status(hci, HCI_INVALID_PARAMETERS);
            break;
        }

        hci->lm.inquiry_mode = PARAM(write_inquiry_mode, mode);
        bt_hci_event_complete_status(hci, HCI_SUCCESS);
        break;

    case cmd_opcode_pack(OGF_INFO_PARAM, OCF_READ_LOCAL_VERSION):
        bt_hci_read_local_version_rp(hci);
        break;

    case cmd_opcode_pack(OGF_INFO_PARAM, OCF_READ_LOCAL_COMMANDS):
        bt_hci_read_local_commands_rp(hci);
        break;

    case cmd_opcode_pack(OGF_INFO_PARAM, OCF_READ_LOCAL_FEATURES):
        bt_hci_read_local_features_rp(hci);
        break;

    case cmd_opcode_pack(OGF_INFO_PARAM, OCF_READ_LOCAL_EXT_FEATURES):
        LENGTH_CHECK(read_local_ext_features);

        bt_hci_read_local_ext_features_rp(hci,
                        PARAM(read_local_ext_features, page_num));
        break;

    case cmd_opcode_pack(OGF_INFO_PARAM, OCF_READ_BUFFER_SIZE):
        bt_hci_read_buffer_size_rp(hci);
        break;

    case cmd_opcode_pack(OGF_INFO_PARAM, OCF_READ_COUNTRY_CODE):
        bt_hci_read_country_code_rp(hci);
        break;

    case cmd_opcode_pack(OGF_INFO_PARAM, OCF_READ_BD_ADDR):
        bt_hci_read_bd_addr_rp(hci);
        break;

    case cmd_opcode_pack(OGF_STATUS_PARAM, OCF_READ_LINK_QUALITY):
        LENGTH_CHECK(read_link_quality);

        bt_hci_link_quality_rp(hci, PARAMHANDLE(read_link_quality));
        break;

    default:
        bt_hci_event_status(hci, HCI_UNKNOWN_COMMAND);
        break;

    short_hci:
        fprintf(stderr, "%s: HCI packet too short (%iB)\n",
                        __FUNCTION__, length);
        bt_hci_event_status(hci, HCI_INVALID_PARAMETERS);
        break;
    }
}

static inline void bt_hci_lmp_acl_data(struct bt_hci_s *hci, uint16_t handle,
                const uint8_t *data, int start, int len)
{
    struct hci_acl_hdr *pkt = (void *) hci->acl_buf;

    
    

    if (len + HCI_ACL_HDR_SIZE > sizeof(hci->acl_buf)) {
        fprintf(stderr, "%s: can't take ACL packets %i bytes long\n",
                        __FUNCTION__, len);
        return;
    }
    memcpy(hci->acl_buf + HCI_ACL_HDR_SIZE, data, len);

    pkt->handle = cpu_to_le16(
                    acl_handle_pack(handle, start ? ACL_START : ACL_CONT));
    pkt->dlen = cpu_to_le16(len);
    hci->info.acl_recv(hci->info.opaque,
                    hci->acl_buf, len + HCI_ACL_HDR_SIZE);
}

static void bt_hci_lmp_acl_data_slave(struct bt_link_s *btlink,
                const uint8_t *data, int start, int len)
{
    struct bt_hci_link_s *link = (struct bt_hci_link_s *) btlink;

    bt_hci_lmp_acl_data(hci_from_device(btlink->slave),
                    link->handle, data, start, len);
}

static void bt_hci_lmp_acl_data_host(struct bt_link_s *link,
                const uint8_t *data, int start, int len)
{
    bt_hci_lmp_acl_data(hci_from_device(link->host),
                    link->handle, data, start, len);
}

static void bt_submit_acl(struct HCIInfo *info,
                const uint8_t *data, int length)
{
    struct bt_hci_s *hci = hci_from_info(info);
    uint16_t handle;
    int datalen, flags;
    struct bt_link_s *link;

    if (length < HCI_ACL_HDR_SIZE) {
        fprintf(stderr, "%s: ACL packet too short (%iB)\n",
                        __FUNCTION__, length);
        return;
    }

    handle = acl_handle((data[1] << 8) | data[0]);
    flags = acl_flags((data[1] << 8) | data[0]);
    datalen = (data[3] << 8) | data[2];
    data += HCI_ACL_HDR_SIZE;
    length -= HCI_ACL_HDR_SIZE;

    if (bt_hci_handle_bad(hci, handle)) {
        fprintf(stderr, "%s: invalid ACL handle %03x\n",
                        __FUNCTION__, handle);
        
        return;
    }
    handle &= ~HCI_HANDLE_OFFSET;

    if (datalen > length) {
        fprintf(stderr, "%s: ACL packet too short (%iB < %iB)\n",
                        __FUNCTION__, length, datalen);
        return;
    }

    link = hci->lm.handle[handle].link;

    if ((flags & ~3) == ACL_ACTIVE_BCAST) {
        if (!hci->asb_handle)
            hci->asb_handle = handle;
        else if (handle != hci->asb_handle) {
            fprintf(stderr, "%s: Bad handle %03x in Active Slave Broadcast\n",
                            __FUNCTION__, handle);
            
            return;
        }

        
    }

    if ((flags & ~3) == ACL_PICO_BCAST) {
        if (!hci->psb_handle)
            hci->psb_handle = handle;
        else if (handle != hci->psb_handle) {
            fprintf(stderr, "%s: Bad handle %03x in Parked Slave Broadcast\n",
                            __FUNCTION__, handle);
            
            return;
        }

        
    }

    
    bt_hci_event_num_comp_pkts(hci, handle | HCI_HANDLE_OFFSET, 1);

    
    hci->lm.handle[handle].lmp_acl_data(link, data,
                    (flags & 3) == ACL_START, length);
}

static void bt_submit_sco(struct HCIInfo *info,
                const uint8_t *data, int length)
{
    struct bt_hci_s *hci = hci_from_info(info);
    uint16_t handle;
    int datalen;

    if (length < 3)
        return;

    handle = acl_handle((data[1] << 8) | data[0]);
    datalen = data[2];
    length -= 3;

    if (bt_hci_handle_bad(hci, handle)) {
        fprintf(stderr, "%s: invalid SCO handle %03x\n",
                        __FUNCTION__, handle);
        return;
    }

    if (datalen > length) {
        fprintf(stderr, "%s: SCO packet too short (%iB < %iB)\n",
                        __FUNCTION__, length, datalen);
        return;
    }

    

}

static uint8_t *bt_hci_evt_packet(void *opaque)
{
    
    struct bt_hci_s *s = opaque;

    return s->evt_buf;
}

static void bt_hci_evt_submit(void *opaque, int len)
{
    
    struct bt_hci_s *s = opaque;

    s->info.evt_recv(s->info.opaque, s->evt_buf, len);
}

static int bt_hci_bdaddr_set(struct HCIInfo *info, const uint8_t *bd_addr)
{
    struct bt_hci_s *hci = hci_from_info(info);

    bacpy(&hci->device.bd_addr, (const bdaddr_t *) bd_addr);
    return 0;
}

static void bt_hci_done(struct HCIInfo *info);
static void bt_hci_destroy(struct bt_device_s *dev)
{
    struct bt_hci_s *hci = hci_from_device(dev);

    bt_hci_done(&hci->info);
}

struct HCIInfo *bt_new_hci(struct bt_scatternet_s *net)
{
    struct bt_hci_s *s = qemu_mallocz(sizeof(struct bt_hci_s));

    s->lm.inquiry_done = qemu_new_timer_ns(vm_clock, bt_hci_inquiry_done, s);
    s->lm.inquiry_next = qemu_new_timer_ns(vm_clock, bt_hci_inquiry_next, s);
    s->conn_accept_timer =
            qemu_new_timer_ns(vm_clock, bt_hci_conn_accept_timeout, s);

    s->evt_packet = bt_hci_evt_packet;
    s->evt_submit = bt_hci_evt_submit;
    s->opaque = s;

    bt_device_init(&s->device, net);
    s->device.lmp_connection_request = bt_hci_lmp_connection_request;
    s->device.lmp_connection_complete = bt_hci_lmp_connection_complete;
    s->device.lmp_disconnect_master = bt_hci_lmp_disconnect_host;
    s->device.lmp_disconnect_slave = bt_hci_lmp_disconnect_slave;
    s->device.lmp_acl_data = bt_hci_lmp_acl_data_slave;
    s->device.lmp_acl_resp = bt_hci_lmp_acl_data_host;
    s->device.lmp_mode_change = bt_hci_lmp_mode_change_slave;

    
    s->device.lmp_caps = 0x8000199b7e85355fll;

    bt_hci_reset(s);

    s->info.cmd_send = bt_submit_hci;
    s->info.sco_send = bt_submit_sco;
    s->info.acl_send = bt_submit_acl;
    s->info.bdaddr_set = bt_hci_bdaddr_set;

    s->device.handle_destroy = bt_hci_destroy;

    return &s->info;
}

static void bt_hci_done(struct HCIInfo *info)
{
    struct bt_hci_s *hci = hci_from_info(info);
    int handle;

    bt_device_done(&hci->device);

    if (hci->device.lmp_name)
        qemu_free((void *) hci->device.lmp_name);

    if (hci->conn_req_host) {
        bt_hci_connection_reject(hci,
                                 hci->conn_req_host, HCI_OE_POWER_OFF);
        return;
    }

    for (handle = HCI_HANDLE_OFFSET;
                    handle < (HCI_HANDLE_OFFSET | HCI_HANDLES_MAX); handle ++)
        if (!bt_hci_handle_bad(hci, handle))
            bt_hci_disconnect(hci, handle, HCI_OE_POWER_OFF);


    qemu_free_timer(hci->lm.inquiry_done);
    qemu_free_timer(hci->lm.inquiry_next);
    qemu_free_timer(hci->conn_accept_timer);

    qemu_free(hci);
}
