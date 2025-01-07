/**
 * @file ciot_tcp_base.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include <string.h>
#include "ciot_tcp.h"
#include "ciot_config.h"

// static const char *TAG = "ciot_tcp_base";

ciot_err_t ciot_tcp_init(ciot_tcp_t self)
{
    ciot_tcp_base_t *base = (ciot_tcp_base_t*)self;

    // ciot__tcp_data__init(&base->data);
    // ciot__tcp_cfg__init(&base->cfg);
    // ciot__tcp_status__init(&base->status);
    // ciot__tcp_dhcp_status__init(&base->dhcp_status);
    // ciot__tcp_info__init(&base->info);

    // base->iface.ptr = self;
    // base->iface.process_req = ciot_iface_process_req;
    // base->iface.get_data = ciot_iface_get_data;
    // base->iface.send_data = ciot_iface_send_data;
    // base->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_TCP;

    // base->status.dhcp = &base->dhcp_status;
    // base->cfg.ip.data = base->cfg_ip;
    // base->cfg.ip.len = sizeof(base->cfg_ip);
    // base->cfg.gateway.data = base->cfg_gateway;
    // base->cfg.gateway.len = sizeof(base->cfg_gateway);
    // base->cfg.dns.data = base->cfg_dns;
    // base->cfg.dns.len = sizeof(base->cfg_dns);
    // base->cfg.mask.data = base->cfg_mask;
    // base->cfg.mask.len = sizeof(base->cfg_mask);

    // base->info.ip.data = base->info_ip;
    // base->info.ip.len = sizeof(base->info_ip);
    // base->info.mac.data = base->info_mac;
    // base->info.mac.len = sizeof(base->info_mac);

    // base->iface.ptr = self;
    // base->iface.process_data = ciot_tcp_process_req;
    // base->iface.get_data = ciot_tcp_get_data;
    // base->iface.send_data = ciot_tcp_send_data;
    // base->iface.info.type = CIOT_IFACE_TYPE_TCP;

    return CIOT_ERR_OK;
}

// static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
// {
//     ciot_tcp_t self = iface->ptr;

//     switch (req->type)
//     {
//         case CIOT__MSG_TYPE__MSG_TYPE_START:
//             return ciot_tcp_start(self, req->data->tcp->config);
//         case CIOT__MSG_TYPE__MSG_TYPE_STOP:
//             return ciot_tcp_stop(self);
//         case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
//             return ciot_tcp_process_req(self, req->data->tcp->request);
//     default:
//         break;
//     }
    
//     return CIOT_ERR_OK;
// }

// static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
// {
//     ciot_tcp_base_t *self = iface->ptr;

//     self->data.config = NULL;
//     self->data.status = NULL;
//     self->data.info = NULL;
//     self->data.request = NULL;

//     switch (msg->type)
//     {
//     case CIOT__MSG_TYPE__MSG_TYPE_CONFIG:
//         self->data.config = &self->cfg;
//         break;
//     case CIOT__MSG_TYPE__MSG_TYPE_STATUS:
//         self->data.status = &self->status;
//         break;
//     case CIOT__MSG_TYPE__MSG_TYPE_INFO:
//         self->data.info = &self->info;
//         break;
//     default:
//         break;
//     }

//     self->iface.data.tcp = &self->data;
//     msg->data = &self->iface.data;

//     return CIOT_ERR_OK;
// }

// static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
// {
//     return CIOT__ERR__NOT_IMPLEMENTED;
// }

// ciot_err_t ciot_tcp_process_req(ciot_tcp_t self, ciot_tcp_req_t *req)
// {
//     CIOT_ERR_NULL_CHECK(self);
//     CIOT_ERR_NULL_CHECK(req);
//     return CIOT__ERR__NOT_IMPLEMENTED;
// }

ciot_err_t ciot_tcp_get_cfg(ciot_tcp_t self, ciot_tcp_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    ciot_tcp_base_t *base = (ciot_tcp_base_t*)self;
    *cfg = base->cfg;
    return CIOT_ERR_OK;
}

ciot_err_t ciot_tcp_set_cfg(ciot_tcp_t self, ciot_tcp_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    ciot_tcp_base_t *base = (ciot_tcp_base_t*)self;
    base->cfg = *cfg;
    return CIOT_ERR_OK;
}

ciot_err_t ciot_tcp_get_status(ciot_tcp_t self, ciot_tcp_status_t *status)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    ciot_tcp_base_t *base = (ciot_tcp_base_t*)self;
    *status = base->status;
    return CIOT_ERR_OK;
}

ciot_err_t ciot_tcp_get_info(ciot_tcp_t self, ciot_tcp_info_t *info)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(info);
    ciot_tcp_base_t *base = (ciot_tcp_base_t*)self;
    *info = base->info;
    return CIOT_ERR_OK;
}
