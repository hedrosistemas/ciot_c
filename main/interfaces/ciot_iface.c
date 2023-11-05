/**
 * @file ciot_iface.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <string.h>

#include "ciot_err.h"
#include "ciot_iface.h"

ciot_err_t ciot_iface_start(ciot_iface_t *self, ciot_msg_data_u *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);
    CIOT_NULL_CHECK(self->base.ptr);
    ;
    CIOT_NULL_CHECK(self->base.start);
    return self->base.start(self->base.ptr, cfg);
}

ciot_err_t ciot_iface_stop(ciot_iface_t *self)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(self->base.ptr);
    CIOT_NULL_CHECK(self->base.stop);
    return self->base.stop(self->base.ptr);
}

ciot_err_t ciot_iface_get_cfg(ciot_iface_t *self, ciot_msg_data_u *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);
    CIOT_NULL_CHECK(self->base.ptr);
    memcpy(cfg, self->base.cfg.ptr, self->base.cfg.size);
    return CIOT_OK;
}

ciot_err_t ciot_iface_get_status(ciot_iface_t *self, ciot_msg_data_u *status)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(status);
    CIOT_NULL_CHECK(self->base.ptr);
    memcpy(status, self->base.status.ptr, self->base.status.size);
    return CIOT_OK;
}

ciot_err_t ciot_iface_process_req(ciot_iface_t *self, ciot_msg_data_u *req, void *sender)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(req);
    CIOT_NULL_CHECK(self->base.ptr);
    CIOT_NULL_CHECK(self->base.process_req);
    return self->base.process_req(self->base.ptr, req);
}

ciot_err_t ciot_iface_send_data(ciot_iface_t *self, void *data, int size)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(data);
    CIOT_NULL_CHECK(self->base.ptr);
    CIOT_NULL_CHECK(self->base.send_data);
    return self->base.send_data(self->base.ptr, data, size);
}

ciot_err_t ciot_iface_send_req(ciot_iface_t *self, ciot_msg_t *msg, int size)
{
    if (self->base.req.pending)
    {
        return CIOT_ERR_BUSY;
    }
    else
    {
        self->base.req.pending = true;
        self->base.req.type = msg->type;
        self->base.req.iface = msg->iface;
        return ciot_iface_send_data(self, msg, size);
    }
}

ciot_err_t ciot_iface_process_msg(ciot_iface_t *self, ciot_msg_t *msg, void *sender)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(msg);

    if (msg->iface.id != self->info.id)
    {
        return CIOT_ERR_INVALID_ID;
    }

    if (msg->iface.type != self->info.type)
    {
        return CIOT_ERR_INVALID_TYPE;
    }

    switch (msg->type)
    {
    case CIOT_MSG_TYPE_UNKNOWN:
        return CIOT_ERR_INVALID_TYPE;
    case CIOT_MSG_TYPE_START:
        return ciot_iface_start(self, &msg->data);
    case CIOT_MSG_TYPE_STOP:
        return ciot_iface_stop(self);
    case CIOT_MSG_TYPE_GET_CONFIG:
        msg->error = ciot_iface_get_cfg(self, &msg->data);
        return ciot_iface_send_data(sender, msg, self->base.cfg.size + CIOT_MSG_SIZE);
    case CIOT_MSG_TYPE_GET_STATUS:
        msg->error = ciot_iface_get_status(self, &msg->data);
        return ciot_iface_send_data(sender, msg, self->base.status.size + CIOT_MSG_SIZE);
    case CIOT_MSG_TYPE_REQUEST:
        ciot_iface_process_req(self, &msg->data, sender);
    case CIOT_MSG_TYPE_EVENT:
        return CIOT_ERR_NOT_IMPLEMENTED;
    }

    return CIOT_ERR_INVALID_TYPE;
}

ciot_err_t ciot_iface_register_event(ciot_iface_t *self, ciot_iface_event_handler_t event_handler, void *event_args)
{
    CIOT_NULL_CHECK(self);
    self->event_handler = event_handler;
    self->event_args = event_args;
    return CIOT_OK;
}
