/**
 * @file ciot_ntp_base.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "ciot_ntp.h"
#include "ciot_config.h"
#include "ciot_str.h"

// static const char *TAG = "ciot_ntp";

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);

ciot_err_t ciot_ntp_init(ciot_ntp_t self)
{
    ciot_ntp_base_t *base = (ciot_ntp_base_t*)self;

    ciot_iface_init(&base->iface);
    ciot__ntp_data__init(&base->data);
    ciot__ntp_cfg__init(&base->cfg);
    ciot__ntp_status__init(&base->status);
    // ciot__ntp_info__init(&base->info);

    base->iface.ptr = self;
    base->iface.process_req = ciot_iface_process_req;
    base->iface.get_data = ciot_iface_get_data;
    base->iface.send_data = ciot_iface_send_data;
    base->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_NTP;

    base->cfg.timezone = base->timezone;
    base->cfg.server1 = base->server1;
    base->cfg.server2 = base->server2;
    base->cfg.server3 = base->server3;

    return CIOT__ERR__OK;
}

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
{
    ciot_ntp_t self = iface->ptr;

    switch (req->type)
    {
        case CIOT__MSG_TYPE__MSG_TYPE_START:
            return ciot_ntp_start(self, req->data->ntp->config);
        case CIOT__MSG_TYPE__MSG_TYPE_STOP:
            return ciot_ntp_stop(self);
        case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
            return ciot_ntp_process_req(self, req->data->ntp->request);
    default:
        break;
    }
    
    return CIOT__ERR__OK;
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_ntp_base_t *self = iface->ptr;

    self->data.config = NULL;
    self->data.status = NULL;
    // self->data.info = NULL;
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
        // self->data.info = &self->info;
        break;
    default:
        break;
    }

    self->iface.data.ntp = &self->data;
    msg->data = &self->iface.data;

    return CIOT__ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    return CIOT__ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_ntp_process_req(ciot_ntp_t self, ciot_ntp_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);
    return CIOT__ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_ntp_get_cfg(ciot_ntp_t self, ciot_ntp_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    ciot_ntp_base_t *base = (ciot_ntp_base_t*)self;
    *cfg = base->cfg;
    return CIOT__ERR__OK;
}

ciot_err_t ciot_ntp_set_cfg(ciot_ntp_t self, ciot_ntp_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    ciot_ntp_base_t *base = (ciot_ntp_base_t*)self;
    base->cfg.op_mode = cfg->op_mode;
    base->cfg.sync_interval = cfg->sync_interval;
    base->cfg.sync_mode = cfg->sync_mode;
    base->cfg.timezone = cfg->timezone;
    ciot_strncpy(base->timezone, cfg->timezone, CIOT_CONFIG_NTP_TIMEZONE_LEN);
    ciot_strncpy(base->server1, cfg->server1, CIOT_CONFIG_NTP_SERVER_URL_LEN);
    ciot_strncpy(base->server2, cfg->server2, CIOT_CONFIG_NTP_SERVER_URL_LEN);
    ciot_strncpy(base->server3, cfg->server3, CIOT_CONFIG_NTP_SERVER_URL_LEN);
    return CIOT__ERR__OK;
}

ciot_err_t ciot_ntp_get_status(ciot_ntp_t self, ciot_ntp_status_t *status)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    ciot_ntp_base_t *base = (ciot_ntp_base_t*)self;
    *status = base->status;
    return CIOT__ERR__OK;
}

// ciot_err_t ciot_ntp_get_info(ciot_ntp_t self, ciot_ntp_info_t *info)
// {
//     CIOT_ERR_NULL_CHECK(self);
//     CIOT_ERR_NULL_CHECK(info);
//     ciot_ntp_base_t *base = (ciot_ntp_base_t*)self;
//     *info = base->info;
//     return CIOT__ERR__OK;
// }
