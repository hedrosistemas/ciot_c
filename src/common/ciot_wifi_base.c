/**
 * @file ciot_wifi_base.c
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

#include "ciot_wifi.h"
#include "ciot_config.h"

// static const char *TAG = "ciot_wifi";

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);

ciot_err_t ciot_wifi_init(ciot_wifi_t self)
{
    ciot_wifi_base_t *base = (ciot_wifi_base_t*)self;
    ciot_tcp_base_t *tcp =(ciot_tcp_base_t*)base->tcp;

    ciot_iface_init(&base->iface);
    ciot__wifi_data__init(&base->data);
    ciot__wifi_cfg__init(&base->cfg);
    ciot__wifi_status__init(&base->status);
    ciot__wifi_info__init(&base->info);
    ciot__wifi_ap_info__init(&base->ap_info);

    base->iface.ptr = self;
    base->iface.process_req = ciot_iface_process_req;
    base->iface.get_data = ciot_iface_get_data;
    base->iface.send_data = ciot_iface_send_data;
    base->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_WIFI;

    base->cfg.ssid = base->ssid;
    base->cfg.password = base->password;


    if(tcp->type == CIOT_TCP_TYPE_WIFI_STA)
    {
        base->info.ap = &base->ap_info;
        base->info.ap->bssid.data = base->ap_bssid;
        base->info.ap->bssid.len = sizeof(base->ap_bssid);
        base->info.ap->ssid = base->ap_ssid;
    }

    base->cfg.tcp = &tcp->cfg;
    base->status.tcp = &tcp->status;
    base->info.tcp = &tcp->info;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
{
    ciot_wifi_t self = iface->ptr;

    switch (req->type)
    {
        case CIOT__MSG_TYPE__MSG_TYPE_START:
            return ciot_wifi_start(self, req->data->wifi->config);
        case CIOT__MSG_TYPE__MSG_TYPE_STOP:
            return ciot_wifi_stop(self);
        case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
            return ciot_wifi_process_req(self, req->data->wifi->request);
    default:
        break;
    }
    
    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_wifi_base_t *self = iface->ptr;

    self->data.config = NULL;
    self->data.status = NULL;
    self->data.info = NULL;
    self->data.request = NULL;

    switch (msg->type)
    {
    case CIOT__MSG_TYPE__MSG_TYPE_CONFIG:
        self->data.config = &self->cfg;
        break;
    case CIOT__MSG_TYPE__MSG_TYPE_STATUS:
        self->data.status = &self->status;
        break;
    case CIOT__MSG_TYPE__MSG_TYPE_INFO:
        self->data.info = &self->info;
        break;
    default:
        break;
    }

    self->iface.data.wifi = &self->data;
    msg->data = &self->iface.data;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_wifi_process_req(ciot_wifi_t self, ciot_wifi_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_wifi_get_cfg(ciot_wifi_t self, ciot_wifi_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    ciot_wifi_base_t *base = (ciot_wifi_base_t*)self;
    *cfg = base->cfg;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_wifi_get_status(ciot_wifi_t self, ciot_wifi_status_t *status)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    ciot_wifi_base_t *base = (ciot_wifi_base_t*)self;
    *status = base->status;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_wifi_get_info(ciot_wifi_t self, ciot_wifi_info_t *info)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(info);
    ciot_wifi_base_t *base = (ciot_wifi_base_t*)self;
    *info = base->info;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_wifi_get_mac(ciot_wifi_t self, uint8_t mac[6])
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(mac);
    ciot_wifi_base_t *base = (ciot_wifi_base_t*)self;
    memcpy(mac, base->info.tcp->mac.data, 6);
    return CIOT_ERR__OK;
}
