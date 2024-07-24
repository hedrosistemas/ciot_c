/**
 * @file ciot_ble_adv_base.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "ciot_ble_adv.h"
#include "ciot_config.h"

// static const char *TAG = "ciot_ble_adv";

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);

ciot_err_t ciot_ble_adv_init(ciot_ble_adv_t self)
{
    ciot_ble_adv_base_t *base = (ciot_ble_adv_base_t*)self;

    ciot_iface_init(&base->iface);
    ciot__ble_adv_data__init(&base->data);
    ciot__ble_adv_cfg__init(&base->cfg);
    ciot__ble_adv_status__init(&base->status);

    base->iface.ptr = self;
    base->iface.process_req = ciot_iface_process_req;
    base->iface.get_data = ciot_iface_get_data;
    base->iface.send_data = ciot_iface_send_data;
    base->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_BLE_ADV;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
{
    ciot_ble_adv_t self = iface->ptr;

    switch (req->type)
    {
        case CIOT__MSG_TYPE__MSG_TYPE_START:
            return ciot_ble_adv_start(self, req->data->ble_adv->config);
        case CIOT__MSG_TYPE__MSG_TYPE_STOP:
            return ciot_ble_adv_stop(self);
        case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
            return ciot_ble_adv_process_req(self, req->data->ble_adv->request);
    default:
        break;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_ble_adv_base_t *self = iface->ptr;

    self->data.config = NULL;
    self->data.status = NULL;
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
        break;
    default:
        break;
    }

    self->iface.data.ble_adv = &self->data;
    msg->data = &self->iface.data;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    ciot_ble_adv_t self = (ciot_ble_adv_t)iface;
    return ciot_ble_adv_send_data(self, data, size); 
}

ciot_err_t ciot_ble_adv_process_req(ciot_ble_adv_t self, ciot_ble_adv_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_ble_adv_get_cfg(ciot_ble_adv_t self, ciot_ble_adv_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    ciot_ble_adv_base_t *base = (ciot_ble_adv_base_t*)self;
    *cfg = base->cfg;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_ble_adv_get_status(ciot_ble_adv_t self, ciot_ble_adv_status_t *status)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    ciot_ble_adv_base_t *base = (ciot_ble_adv_base_t*)self;
    *status = base->status;
    return CIOT_ERR__OK;
}
