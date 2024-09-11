/**
 * @file ciot_viface_base.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-06-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "ciot_viface.h"
#include "ciot_config.h"

// static const char *TAG = "ciot_viface";

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);

ciot_err_t ciot_viface_init(ciot_viface_t self, ciot_iface_type_t type)
{
    ciot_viface_base_t *base = (ciot_viface_base_t *)self;

    ciot_iface_init(&base->iface);

    base->iface.ptr = self;
    base->iface.process_req = ciot_iface_process_req;
    base->iface.get_data = ciot_iface_get_data;
    base->iface.send_data = ciot_iface_send_data;
    base->iface.info.type = type;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
{
    ciot_viface_t self = iface->ptr;

    switch (req->type)
    {
    case CIOT__MSG_TYPE__MSG_TYPE_START:
        return ciot_viface_start(self, NULL);
    case CIOT__MSG_TYPE__MSG_TYPE_STOP:
        return ciot_viface_stop(self);
    case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
        return ciot_viface_process_req(self, NULL);
    default:
        break;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_viface_base_t *self = iface->ptr;

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

    // self->iface.data.viface = &self->data;
    msg->data = &self->iface.data;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    uint8_t *u8ptr = data;
    printf("Virtual interface send data:\n");
    for (size_t i = 0; i < size; i++)
    {
        printf("%02X", u8ptr[i]);
    }
    printf("\n");
    return CIOT_ERR__OK;
}

ciot_err_t ciot_viface_process_req(ciot_viface_t self, ciot_viface_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_viface_get_cfg(ciot_viface_t self, ciot_viface_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    ciot_viface_base_t *base = (ciot_viface_base_t *)self;
    *cfg = base->cfg;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_viface_get_status(ciot_viface_t self, ciot_viface_status_t *status)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    ciot_viface_base_t *base = (ciot_viface_base_t *)self;
    *status = base->status;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_viface_get_info(ciot_viface_t self, ciot_viface_info_t *info)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(info);
    ciot_viface_base_t *base = (ciot_viface_base_t *)self;
    *info = base->info;
    return CIOT_ERR__OK;
}
