/**
 * @file ciot_base.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <string.h>
#include <stdlib.h>
#include "ciot.h"
#include "ciot_config.h"

// static const char *TAG = "ciot_base";

static uint8_t ver[] = {CIOT_VER};

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);

ciot_err_t ciot_init(ciot_t self)
{
    self->iface.ptr = self;
    self->iface.process_req = ciot_iface_process_req;
    self->iface.get_data = ciot_iface_get_data;
    self->iface.send_data = ciot_iface_send_data;

    ciot_iface_init(&self->iface);
    ciot__ciot_data__init(&self->data);
    ciot__ciot_status__init(&self->status);
    ciot__ciot_info__init(&self->info);
    
    self->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_CIOT;

    self->info.version.data = ver;
    self->info.version.len = sizeof(ver);

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
{
    ciot_t self = iface->ptr;

    switch (req->type)
    {
    case CIOT__MSG_TYPE__MSG_TYPE_START:
        return ciot_iface_send_event_type(iface, CIOT_IFACE_EVENT_STARTED);
    case CIOT__MSG_TYPE__MSG_TYPE_STOP:
        return ciot_stop(self);
    case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
        return ciot_process_req(self, req->data->ciot->request);
    default:
        break;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_t self = iface->ptr;

    self->data.config = NULL;
    self->data.status = NULL;
    self->data.info = NULL;
    self->data.request = NULL;

    switch (msg->type)
    {
    case CIOT__MSG_TYPE__MSG_TYPE_CONFIG:
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

    self->iface.data.ciot = &self->data;
    msg->data = &self->iface.data;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_process_req(ciot_t self, ciot_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);
    switch (req->type)
    {
    case CIOT__CIOT_REQ_TYPE__CIOT_REQ_TYPE_SAVE_IFACE_CFG:
        self->iface.req_status.state = CIOT_IFACE_REQ_STATE_IDLE;
        return ciot_save_iface_cfg(self, req->data->iface_id);
    case CIOT__CIOT_REQ_TYPE__CIOT_REQ_TYPE_DELETE_IFACE_CFG:
        return CIOT_ERR__NOT_IMPLEMENTED;
    case CIOT__CIOT_REQ_TYPE__CIOT_REQ_TYPE_PROXY_MSG:
        return CIOT_ERR__NOT_IMPLEMENTED;
    default:
        return CIOT_ERR__INVALID_TYPE;
    }
    return CIOT_ERR__INVALID_TYPE;
}

ciot_err_t ciot_get_cfg(ciot_t self, ciot_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    *cfg = self->cfg;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_get_status(ciot_t self, ciot_status_t *status)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    *status = self->status;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_get_info(ciot_t self, ciot_info_t *info)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(info);
    *info = self->info;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_save_iface_cfg(ciot_t self, int iface_id)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(self->storage);

    char filename[16];
    sprintf(filename, CIOT_IFACE_CFG_FILENAME, iface_id);
    ciot_iface_t *iface = self->ifaces.list[iface_id];

    ciot_msg_t msg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg__descriptor),
        .type = CIOT__MSG_TYPE__MSG_TYPE_CONFIG,
        .iface = &iface->info,
    };

    CIOT_ERR_RETURN(iface->get_data(iface, &msg));
    return ciot_storage_set_data(self->storage, filename, msg.data);
}

ciot_msg_data_t *ciot_load_iface_cfg(ciot_t self, int iface_id)
{
    if(self == NULL || self->storage == NULL)
    {
        return NULL;
    }
    char filename[16];
    sprintf(filename, CIOT_IFACE_CFG_FILENAME, iface_id);
    return ciot_storage_get_data(self->storage, filename);
}

bool ciot_cfg_exits(ciot_t self, int iface_id)
{
    if(self == NULL || self->storage == NULL)
    {
        return false;
    }

    int size = 0;
    char filename[16];
    sprintf(filename, CIOT_IFACE_CFG_FILENAME, iface_id);
    self->storage->read_bytes(filename, NULL, &size);
    return size > 0;
}
