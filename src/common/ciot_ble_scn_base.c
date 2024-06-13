/**
 * @file ciot_ble_scn_base.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "ciot_ble_scn.h"
#include "ciot_config.h"

// static const char *TAG = "ciot_ble_scn";

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);

ciot_err_t ciot_ble_scn_init(ciot_ble_scn_t self)
{
    ciot_ble_scn_base_t *base = (ciot_ble_scn_base_t*)self;

    base->iface.ptr = self;
    base->iface.process_req = ciot_iface_process_req;
    base->iface.get_data = ciot_iface_get_data;
    base->iface.send_data = ciot_iface_send_data;
    base->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_BLE_SCN;

    ciot__msg_data__init(&base->msg);
    ciot__ble_scn_data__init(&base->data);
    ciot__ble_scn_cfg__init(&base->cfg);
    ciot__ble_scn_status__init(&base->status);

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
{
    ciot_ble_scn_t self = iface->ptr;

    switch (req->type)
    {
        case CIOT__MSG_TYPE__MSG_TYPE_START:
            return ciot_ble_scn_start(self, req->data->ble_scn->config);
        case CIOT__MSG_TYPE__MSG_TYPE_STOP:
            return ciot_ble_scn_stop(self);
        case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
            return ciot_ble_scn_process_req(self, req->data->ble_scn->request);
    default:
        break;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_ble_scn_base_t *self = iface->ptr;

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

    self->msg.ble_scn = &self->data;
    msg->data = &self->msg;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_ble_scn_process_req(ciot_ble_scn_t self, ciot_ble_scn_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_ble_scn_get_cfg(ciot_ble_scn_t self, ciot_ble_scn_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_ble_scn_get_status(ciot_ble_scn_t self, ciot_ble_scn_status_t *status)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    return CIOT_ERR__NOT_IMPLEMENTED;
}
