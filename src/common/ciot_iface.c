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

ciot_err_t ciot_iface_send_msg(ciot_iface_t *self, ciot_msg_t *msg, int size)
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

    ciot_err_t err = CIOT_OK;

    if (msg->iface.id != self->info.id)
    {
        err = CIOT_ERR_INVALID_ID;
    }

    if (msg->iface.type != self->info.type)
    {
        err = CIOT_ERR_INVALID_TYPE;
    }

    if(err == CIOT_OK)
    {
        switch (msg->type)
        {
        case CIOT_MSG_TYPE_UNKNOWN:
            err = CIOT_ERR_INVALID_TYPE;
            break;
        case CIOT_MSG_TYPE_START:
            err = ciot_iface_start(self, &msg->data);
            break;
        case CIOT_MSG_TYPE_STOP:
            err = ciot_iface_stop(self);
            break;
        case CIOT_MSG_TYPE_GET_CONFIG:
            err = ciot_iface_get_cfg(self, &msg->data);
            if(err == CIOT_OK)
            {
                err = ciot_iface_send_data(sender, msg, self->base.cfg.size + CIOT_MSG_HEADER_SIZE);
            }
            break;
        case CIOT_MSG_TYPE_GET_STATUS:
            err = ciot_iface_get_status(self, &msg->data);
            if(err == CIOT_OK)
            {
                err = ciot_iface_send_data(sender, msg, self->base.status.size + CIOT_MSG_HEADER_SIZE);
            }
            break;
        case CIOT_MSG_TYPE_REQUEST:
            err = ciot_iface_process_req(self, &msg->data, sender);
            break;
        case CIOT_MSG_TYPE_EVENT:
            err = CIOT_ERR_NOT_IMPLEMENTED;
            break;
        case CIOT_MSG_TYPE_ERROR:
            err = CIOT_ERR_INVALID_TYPE;
            break;
        }
    }

    if(err != CIOT_OK)
    {
        msg->data.error.msg_type = msg->type;
        msg->data.error.iface = self->info;
        msg->data.error.code = err;
        msg->type = CIOT_MSG_TYPE_ERROR;
        ciot_iface_send_data(sender, msg, CIOT_MSG_GET_SIZE(msg->data.error));
    }

    return err;
}

ciot_err_t ciot_iface_register_event(ciot_iface_t *self, ciot_iface_event_handler_t event_handler, void *event_args)
{
    CIOT_NULL_CHECK(self);
    self->event_handler = event_handler;
    self->event_args = event_args;
    return CIOT_OK;
}
