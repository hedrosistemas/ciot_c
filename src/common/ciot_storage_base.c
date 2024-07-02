/**
 * @file ciot_storage_base.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "ciot_storage.h"
#include "ciot_config.h"

// static const char *TAG = "ciot_storage";

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);

ciot_err_t ciot_storage_init(ciot_storage_t self)
{
    ciot_storage_base_t *base = (ciot_storage_base_t*)self;

    ciot_iface_init(&base->iface);
    ciot__storage_data__init(&base->data);
    ciot__storage_cfg__init(&base->cfg);
    ciot__storage_status__init(&base->status);
    ciot__storage_info__init(&base->info);

    base->iface.ptr = self;
    base->iface.process_req = ciot_iface_process_req;
    base->iface.get_data = ciot_iface_get_data;
    base->iface.send_data = ciot_iface_send_data;
    base->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_STORAGE;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
{
    ciot_storage_t self = iface->ptr;

    switch (req->type)
    {
        case CIOT__MSG_TYPE__MSG_TYPE_START:
            return ciot_storage_start(self, req->data->storage->config);
        case CIOT__MSG_TYPE__MSG_TYPE_STOP:
            return ciot_storage_stop(self);
        case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
            return ciot_storage_process_req(self, req->data->storage->request);
    default:
        break;
    }
    
    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_storage_base_t *self = iface->ptr;

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

    self->iface.data.storage = &self->data;
    msg->data = &self->iface.data;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_storage_process_req(ciot_storage_t self, ciot_storage_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);

    switch (req->type)
    {
        case CIOT__STORAGE_REQ_TYPE__STORAGE_REQ_TYPE_UNKOWN:
            return CIOT_ERR__INVALID_TYPE;
        case CIOT__STORAGE_REQ_TYPE__STORAGE_REQ_TYPE_REQ_SAVE:
            return ciot_storage_save(self, req->data->path, req->data->data.data, req->data->data.len);
        case CIOT__STORAGE_REQ_TYPE__STORAGE_REQ_TYPE_REQ_LOAD:
            return ciot_storage_load(self, req->data->path, req->data->data.data, req->data->data.len);
        case CIOT__STORAGE_REQ_TYPE__STORAGE_REQ_TYPE_REQ_DELETE:
            return ciot_storage_delete(self, req->data->path);
        case CIOT__STORAGE_REQ_TYPE__STORAGE_REQ_TYPE_REQ_FORMAT:
            return ciot_storage_format(self);
        default:
            break;
    }

    return CIOT_ERR__INVALID_TYPE;
}

ciot_err_t ciot_storage_get_cfg(ciot_storage_t self, ciot_storage_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    ciot_storage_base_t *base = (ciot_storage_base_t*)self;
    *cfg = base->cfg;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_storage_get_status(ciot_storage_t self, ciot_storage_status_t *status)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    ciot_storage_base_t *base = (ciot_storage_base_t*)self;
    *status = base->status;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_storage_get_info(ciot_storage_t self, ciot_storage_info_t *info)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(info);
    ciot_storage_base_t *base = (ciot_storage_base_t*)self;
    *info = base->info;
    return CIOT_ERR__OK;
}
