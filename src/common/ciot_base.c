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

    return CIOT__ERR__OK;
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
        return ciot_process_req(self, req);
    default:
        break;
    }

    return CIOT__ERR__OK;
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
        ciot_get_ifaces_info(self, &self->info.ifaces);
        self->data.info = &self->info;
        break;
    default:
        break;
    }

    self->iface.data.ciot = &self->data;
    msg->data = &self->iface.data;

    return CIOT__ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    return CIOT__ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_process_req(ciot_t self, ciot_msg_t *msg)
{
    CIOT_ERR_NULL_CHECK(self);
    ciot_req_t *req = msg->data->ciot->request;
    CIOT_ERR_NULL_CHECK(req);
    switch (req->type)
    {
    case CIOT__CIOT_REQ_TYPE__CIOT_REQ_TYPE_SAVE_CFG:
        self->iface.req_status.state = CIOT_IFACE_REQ_STATE_IDLE;
        return ciot_save_cfg(self, req->iface);
    case CIOT__CIOT_REQ_TYPE__CIOT_REQ_TYPE_CREATE_CFG:
        msg->data->ciot = NULL;
        self->iface.req_status.state = CIOT_IFACE_REQ_STATE_IDLE;
        return ciot_create_cfg(self, req->iface, msg->data);
    case CIOT__CIOT_REQ_TYPE__CIOT_REQ_TYPE_DELETE_CFG:
        self->iface.req_status.state = CIOT_IFACE_REQ_STATE_IDLE;
        return ciot_delete_cfg(self, req->iface);
    case CIOT__CIOT_REQ_TYPE__CIOT_REQ_TYPE_PROXY_MSG:
        return CIOT__ERR__NOT_IMPLEMENTED;
    default:
        return CIOT__ERR__INVALID_TYPE;
    }
    return CIOT__ERR__INVALID_TYPE;
}

ciot_err_t ciot_get_cfg(ciot_t self, ciot_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    *cfg = self->cfg;
    return CIOT__ERR__OK;
}

ciot_err_t ciot_get_status(ciot_t self, ciot_status_t *status)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    *status = self->status;
    return CIOT__ERR__OK;
}

ciot_err_t ciot_get_info(ciot_t self, ciot_info_t *info)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(info);
    *info = self->info;
    return CIOT__ERR__OK;
}

ciot_err_t ciot_delete_cfg(ciot_t self, ciot_iface_info_t *iface)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(self->storage);
    CIOT_ERR_VALUE_CHECK(iface->type, self->ifaces.list[iface->id]->info.type, CIOT__ERR__INVALID_TYPE);
    char filename[16];
    sprintf(filename, CIOT_IFACE_CFG_FILENAME, (int)iface->id);
    return self->storage->delete(filename);
}

ciot_err_t ciot_save_cfg(ciot_t self, ciot_iface_info_t *iface)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(self->storage);
    char filename[16];
    sprintf(filename, CIOT_IFACE_CFG_FILENAME, (int)iface->id);
    ciot_iface_t *iface_instance = self->ifaces.list[iface->id];
    ciot_msg_t msg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg__descriptor),
        .type = CIOT__MSG_TYPE__MSG_TYPE_CONFIG,
        .iface = &iface_instance->info,
    };
    CIOT_ERR_RETURN(iface_instance->get_data(iface_instance, &msg));
    return ciot_storage_set_data(self->storage, filename, msg.data);
}

ciot_err_t ciot_create_cfg(ciot_t self, ciot_iface_info_t *iface, ciot_msg_data_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(self->storage);
    CIOT_ERR_VALUE_CHECK(iface->type, self->ifaces.list[iface->id]->info.type, CIOT__ERR__INVALID_TYPE);
    char filename[16];
    sprintf(filename, CIOT_IFACE_CFG_FILENAME, (int)iface->id);
    cfg->ciot = NULL;
    return ciot_storage_set_data(self->storage, filename, cfg);
}

ciot_msg_data_t *ciot_load_cfg(ciot_t self, int iface_id)
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

ciot_err_t ciot_get_ifaces_info(ciot_t self, ProtobufCBinaryData *ifaces_info)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(ifaces_info);

    static uint8_t *iface_types = NULL;

    if(iface_types != NULL)
    {
        free(iface_types);
    }

    iface_types = calloc(1, self->ifaces.count);

    for (size_t i = 0; i < self->ifaces.count; i++)
    {
        if(self->ifaces.list[i] != NULL)
        {
            iface_types[i] = self->ifaces.list[i]->info.type;
        }
        else
        {
            iface_types[i] = 255;
        }
    }
    
    ifaces_info->data = iface_types;
    ifaces_info->len = self->ifaces.count;

    return CIOT__ERR__OK;
}