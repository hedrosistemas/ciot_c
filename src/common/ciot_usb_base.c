/**
 * @file ciot_usb_base.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "ciot_usb.h"
#include "ciot_config.h"

// static const char *TAG = "ciot_usb";

#if CIOT_CONFIG_FEATURE_USB == 0

struct ciot_usb
{
    ciot_usb_base_t base;
};

ciot_usb_t ciot_usb_new(void *handle)
{
    ciot_usb_t self = calloc(1, sizeof(struct ciot_usb));
    ciot_usb_init(self);
    return self;
}

ciot_err_t ciot_usb_start(ciot_usb_t self, ciot_usb_cfg_t *cfg)
{
    return CIOT_ERR__NOT_SUPPORTED;
}

ciot_err_t ciot_usb_stop(ciot_usb_t self)
{
    return CIOT_ERR__NOT_SUPPORTED;
}

ciot_err_t ciot_usb_task(ciot_usb_t self)
{
    return CIOT_ERR__NOT_SUPPORTED;
}

ciot_err_t ciot_usb_send_bytes(ciot_iface_t *iface, uint8_t *bytes, int size)
{
    return CIOT_ERR__NOT_SUPPORTED;
}

#endif

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);

ciot_err_t ciot_usb_init(ciot_usb_t self)
{
    ciot_usb_base_t *base = (ciot_usb_base_t*)self;

    ciot_iface_init(&base->iface);
    ciot__usb_data__init(&base->data);
    ciot__usb_cfg__init(&base->cfg);
    ciot__usb_status__init(&base->status);
    // ciot__usb_info__init(&base->info);

    base->iface.ptr = self;
    base->iface.process_req = ciot_iface_process_req;
    base->iface.get_data = ciot_iface_get_data;
    base->iface.send_data = ciot_iface_send_data;
    base->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_USB;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
{
    ciot_usb_t self = iface->ptr;

    switch (req->type)
    {
        case CIOT__MSG_TYPE__MSG_TYPE_START:
            return ciot_usb_start(self, req->data->usb->config);
        case CIOT__MSG_TYPE__MSG_TYPE_STOP:
            return ciot_usb_stop(self);
        case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
            return ciot_usb_process_req(self, req->data->usb->request);
    default:
        break;
    }
    
    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_usb_base_t *self = iface->ptr;

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

    self->iface.data.usb = &self->data;
    msg->data = &self->iface.data;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    return ciot_usb_send_bytes(iface, data, size);
}

ciot_err_t ciot_usb_process_req(ciot_usb_t self, ciot_usb_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_usb_get_cfg(ciot_usb_t self, ciot_usb_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    ciot_usb_base_t *base = (ciot_usb_base_t*)self;
    *cfg = base->cfg;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_usb_get_status(ciot_usb_t self, ciot_usb_status_t *status)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    ciot_usb_base_t *base = (ciot_usb_base_t*)self;
    *status = base->status;
    return CIOT_ERR__OK;
}
