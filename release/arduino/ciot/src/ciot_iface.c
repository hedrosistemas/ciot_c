/**
 * @file ciot_iface.c
 * @author Wesley Santos (wesleypro37@gmail.com)
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

static const char *TAG = "ciot_iface";

static uint8_t msg_id = 0;

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

ciot_err_t ciot_iface_get_status(ciot_iface_t *self, void *status)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(status);
    CIOT_NULL_CHECK(self->base.ptr);
    memcpy(status, self->base.status.ptr, self->base.status.size);
    return CIOT_OK;
}

ciot_err_t ciot_iface_get_info(ciot_iface_t *iface, void *info, int size)
{
    CIOT_NULL_CHECK(iface);
    CIOT_NULL_CHECK(info);
    void *ptr = iface->base.status.ptr;
    ptr += iface->base.status.size;
    ptr -= size;
    memcpy(info, ptr, size);
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
    if (self->base.req.status != CIOT_IFACE_REQ_STATUS_IDLE)
    {
        return CIOT_ERR_BUSY;
    }
    else
    {
        msg->id = msg_id;
        msg_id++;
        
        CIOT_LOGV(TAG, "\n\n -- Message send -->");
        CIOT_LOGV(TAG, "Origin Id: %d", self ? self->info.id : -1);
        CIOT_LOGV(TAG, "Origin Type: %s", ciot_iface_to_str(self));
        CIOT_LOGV(TAG, "Msg Id: %d", msg->id);
        CIOT_LOGV(TAG, "Msg Type: %s", ciot_msg_type_to_str(msg));
        CIOT_LOGV(TAG, "Target Id: %d", msg ? msg->iface.id : -1);
        CIOT_LOGV(TAG, "Target Type: %s\n\n", ciot_iface_type_to_str(msg->iface.type));

        return ciot_iface_send_data(self, msg, size);
    }
}

ciot_err_t ciot_iface_send_req(ciot_iface_t *self, ciot_msg_t *msg, int size)
{
    if (self->base.req.status != CIOT_IFACE_REQ_STATUS_IDLE)
    {
        CIOT_LOGE(TAG, "Iface %s (%d) is busy", ciot_iface_to_str(self), self->info.id);
        return CIOT_ERR_BUSY;
    }
    else
    {
        msg->id = msg_id;
        msg_id++;

        self->base.req.status = CIOT_IFACE_REQ_STATUS_SENDED;
        self->base.req.type = msg->type;
        self->base.req.iface = msg->iface;
        
        CIOT_LOGV(TAG, "\n\n -- Request send -->");
        CIOT_LOGV(TAG, "Origin Id: %d", self ? self->info.id : -1);
        CIOT_LOGV(TAG, "Origin Type: %s", ciot_iface_to_str(self));
        CIOT_LOGV(TAG, "Msg Id: %d", msg->id);
        CIOT_LOGV(TAG, "Msg Type: %s", ciot_msg_type_to_str(msg));
        CIOT_LOGV(TAG, "Target Id: %d", msg ? msg->iface.id : -1);
        CIOT_LOGV(TAG, "Target Type: %s\n\n", ciot_iface_type_to_str(msg->iface.type));

        return ciot_iface_send_data(self, msg, size);
    }
}

ciot_err_t ciot_iface_process_msg(ciot_iface_t *self, ciot_msg_t *msg, void *sender)
{
    ciot_iface_t *sender_iface = (ciot_iface_t*)sender;
    ciot_err_t err = CIOT_OK;

    CIOT_LOGV(TAG, "\n\n <-- Request received -- ");
    CIOT_LOGV(TAG, "Iface Id: %d", self ? self->info.id : -1);
    CIOT_LOGV(TAG, "Iface Type: %s", ciot_iface_to_str(self));
    CIOT_LOGV(TAG, "Msg Id: %d", msg->id);
    CIOT_LOGV(TAG, "Msg Type: %s", ciot_msg_type_to_str(msg));
    CIOT_LOGV(TAG, "Target Id: %d", msg ? msg->iface.id : -1);
    CIOT_LOGV(TAG, "Target Type: %s\n\n", ciot_iface_type_to_str(msg->iface.type));

    if(self != NULL && msg != NULL)
    {
        if (msg->iface.id != self->info.id)
        {
            err = CIOT_ERR_INVALID_ID;
        }
        if (msg->iface.type != self->info.type)
        {
            err = CIOT_ERR_INVALID_TYPE;
        }
    }
    else
    {
        err = CIOT_ERR_NULL_ARG;
    }

    if(err == CIOT_OK)
    {
        switch (msg->type)
        {
        case CIOT_MSG_TYPE_UNKNOWN:
            err = CIOT_ERR_INVALID_TYPE;
            break;
        case CIOT_MSG_TYPE_START:
            self->base.req.status = CIOT_IFACE_REQ_STATUS_RECEIVED;
            self->base.req.type = msg->id;
            self->base.req.type = msg->type;
            self->base.req.iface = sender_iface->info;
            err = ciot_iface_start(self, &msg->data);
            if(self->base.req.status == CIOT_IFACE_REQ_STATUS_IDLE)
            {
                err = ciot_iface_send_msg(sender, msg, CIOT_MSG_GET_SIZE(msg->data.ciot.req));
            }
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
                err = ciot_iface_send_msg(sender, msg, self->base.status.size + CIOT_MSG_HEADER_SIZE);
            }
            break;
        case CIOT_MSG_TYPE_REQUEST:
            self->base.req.status = CIOT_IFACE_REQ_STATUS_RECEIVED;
            self->base.req.type = msg->id;
            self->base.req.type = msg->type;
            self->base.req.iface = sender_iface->info;
            err = ciot_iface_process_req(self, &msg->data, sender);
            if(self->base.req.status == CIOT_IFACE_REQ_STATUS_IDLE)
            {
                err = ciot_iface_send_msg(sender, msg, CIOT_MSG_GET_SIZE(msg->data.ciot.req));
            }
            break;
        case CIOT_MSG_TYPE_EVENT:
            err = CIOT_ERR_NOT_IMPLEMENTED;
            break;
        case CIOT_MSG_TYPE_ERROR:
            err = CIOT_ERR_INVALID_TYPE;
            break;
        case CIOT_MSG_TYPE_CUSTOM:
            // custom message type will be handle on main application
            break;
        }
    }

    if(err != CIOT_OK)
    {
        msg->data.error.msg_type = msg->type;
        if(self != NULL)
        {
            msg->data.error.iface = self->info;
        }
        else
        {
            msg->data.error.iface.id = -1;
            msg->data.error.iface.type = CIOT_IFACE_TYPE_NULL;
        }
        msg->data.error.code = err;
        msg->type = CIOT_MSG_TYPE_ERROR;
        ciot_iface_send_msg(sender, msg, CIOT_MSG_GET_SIZE(msg->data.error));
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

ciot_err_t coit_iface_reset_request(ciot_iface_t *self)
{
    CIOT_NULL_CHECK(self);
    self->base.req.status = CIOT_IFACE_REQ_STATUS_IDLE;
    return CIOT_OK;    
}

const char *ciot_iface_to_str(ciot_iface_t *iface)
{
    if(iface == NULL)
    {
        return "NULL";
    }

    return ciot_iface_type_to_str(iface->info.type);
}

const char *ciot_iface_type_to_str(ciot_msg_iface_type_t iface_type)
{
    switch (iface_type)
    {
        case CIOT_IFACE_TYPE_NULL:
            return "CIOT_IFACE_TYPE_NULL";
        case CIOT_IFACE_TYPE_UNKNOWN:
            return "CIOT_IFACE_TYPE_UNKNOWN";
        case CIOT_IFACE_TYPE_CIOT:
            return "CIOT_IFACE_TYPE_CIOT";
        case CIOT_IFACE_TYPE_STORAGE:
            return "CIOT_IFACE_TYPE_STORAGE";
        case CIOT_IFACE_TYPE_SYSTEM:
            return "CIOT_IFACE_TYPE_SYSTEM";
        case CIOT_IFACE_TYPE_UART:
            return "CIOT_IFACE_TYPE_UART";
        case CIOT_IFACE_TYPE_USB:
            return "CIOT_IFACE_TYPE_USB";
        case CIOT_IFACE_TYPE_TCP:
            return "CIOT_IFACE_TYPE_TCP";
        case CIOT_IFACE_TYPE_ETH:
            return "CIOT_IFACE_TYPE_ETH";
        case CIOT_IFACE_TYPE_WIFI:
            return "CIOT_IFACE_TYPE_WIFI";
        case CIOT_IFACE_TYPE_BLE:
            return "CIOT_IFACE_TYPE_BLE";
        case CIOT_IFACE_TYPE_BLE_SCN:
            return "CIOT_IFACE_TYPE_BLE_SCN";
        case CIOT_IFACE_TYPE_NTP:
            return "CIOT_IFACE_TYPE_NTP";
        case CIOT_IFACE_TYPE_OTA:
            return "CIOT_IFACE_TYPE_OTA";
        case CIOT_IFACE_TYPE_HTTP_CLIENT:
            return "CIOT_IFACE_TYPE_HTTP_CLIENT";
        case CIOT_IFACE_TYPE_HTTP_SERVER:
            return "CIOT_IFACE_TYPE_HTTP_SERVER";
        case CIOT_IFACE_TYPE_MQTT:
            return "CIOT_IFACE_TYPE_MQTT";
        case CIOT_IFACE_TYPE_BRIDGE:
            return "CIOT_IFACE_TYPE_MQTT";
        case CIOT_IFACE_TYPE_CUSTOM:
            return "CIOT_IFACE_TYPE_CUSTOM";
    default:
            return "Invalid iface type";
    }
}
