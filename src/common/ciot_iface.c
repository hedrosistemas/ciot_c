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

static const char *TAG = "ciot_iface";

static uint8_t msg_id = 0;

ciot_err_t ciot_iface_start(ciot_iface_t *self, ciot_msg_data_u *cfg)
{
    CIOT_NULL_CHECK(self);
    self->base.req.response_size = CIOT_MSG_HEADER_SIZE;
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

        CIOT_LOGV("ciot", "TX MSG -> id:%d sender:%s msgt:%s iface:%s", 
                msg->id,
                ciot_iface_to_str(self),
                ciot_msg_type_to_str(msg),
                ciot_iface_type_to_str(msg->iface.type));

        return ciot_iface_send_data(self, msg, size);
    }
}

ciot_err_t ciot_iface_send_rsp(ciot_iface_t *self, ciot_msg_t *rsp, int size)
{
    if (self->base.req.status != CIOT_IFACE_REQ_STATUS_IDLE)
    {
        return CIOT_ERR_BUSY;
    }
    else
    {
        CIOT_LOGV("ciot", "TX RSP -> id:%d sender:%s msgt:%s iface:%s", 
                rsp->id,
                ciot_iface_to_str(self),
                ciot_msg_type_to_str(rsp),
                ciot_iface_type_to_str(rsp->iface.type));

        return ciot_iface_send_data(self, rsp, size);
    }
}

ciot_err_t ciot_iface_send_req(ciot_iface_t *self, ciot_msg_t *req, int size)
{
    if (self->base.req.status != CIOT_IFACE_REQ_STATUS_IDLE)
    {
        CIOT_LOGE(TAG, "Iface %s (%d) is busy", ciot_iface_to_str(self), self->info.id);
        return CIOT_ERR_BUSY;
    }
    else
    {
        req->id = msg_id;
        msg_id++;

        self->base.req.status = CIOT_IFACE_REQ_STATUS_SENDED;
        self->base.req.type = req->type;
        self->base.req.iface = req->iface;
        self->base.req.id = req->id;

        CIOT_LOGV("ciot", "TX REQ -> id:%d sender:%s msgt:%s iface:%s", 
                req->id,
                ciot_iface_to_str(self),
                ciot_msg_type_to_str(req),
                ciot_iface_type_to_str(req->iface.type));

        return ciot_iface_send_data(self, req, size);
    }
}

static void ciot_iface_register_request(ciot_iface_t *self, ciot_iface_t *sender, ciot_msg_t *msg)
{
    self->base.req.status = CIOT_IFACE_REQ_STATUS_RECEIVED;
    self->base.req.type = msg->id;
    self->base.req.type = msg->type;
    self->base.req.iface = sender->info;
}

static ciot_err_t ciot_iface_process_request_result(ciot_iface_t *self, ciot_iface_t *sender, ciot_msg_t *msg, ciot_err_t err)
{
    if(self->base.req.status == CIOT_IFACE_REQ_STATUS_IDLE && err == CIOT_OK)
    {
        return ciot_iface_send_rsp(sender, msg, self->base.req.response_size);
    }
    return err;
}

ciot_err_t ciot_iface_process_msg(ciot_iface_t *self, ciot_msg_t *msg, void *sender)
{
    ciot_iface_t *sender_iface = (ciot_iface_t*)sender;
    ciot_err_t err = CIOT_OK;

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
            self->base.req.response_size = CIOT_MSG_HEADER_SIZE;
            ciot_iface_register_request(self, sender_iface, msg);
            err = ciot_iface_start(self, &msg->data);
            err = ciot_iface_process_request_result(self, sender_iface, msg, err);
            break;
        case CIOT_MSG_TYPE_STOP:
            self->base.req.response_size = CIOT_MSG_HEADER_SIZE;
            ciot_iface_register_request(self, sender_iface, msg);
            err = ciot_iface_stop(self);
            err = ciot_iface_process_request_result(self, sender_iface, msg, err);
            break;
        case CIOT_MSG_TYPE_GET_CONFIG:
            self->base.req.response_size = self->base.cfg.size + CIOT_MSG_HEADER_SIZE;
            err = ciot_iface_get_cfg(self, &msg->data);
            err = ciot_iface_process_request_result(self, sender_iface, msg, err);
            break;
        case CIOT_MSG_TYPE_GET_STATUS:
            self->base.req.response_size = self->base.status.size + CIOT_MSG_HEADER_SIZE;
            err = ciot_iface_get_status(self, &msg->data);
            err = ciot_iface_process_request_result(self, sender_iface, msg, err);
            break;
        case CIOT_MSG_TYPE_REQUEST:
            ciot_iface_register_request(self, sender_iface, msg);
            err = ciot_iface_process_req(self, &msg->data, sender);
            err = ciot_iface_process_request_result(self, sender_iface, msg, err);
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
            msg->data.error.iface.type = CIOT_IFACE_TYPE_UNKNOWN;
        }
        msg->data.error.code = err;
        msg->type = CIOT_MSG_TYPE_ERROR;
        ciot_iface_send_rsp(sender, msg, CIOT_MSG_GET_SIZE(msg->data.error));
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

ciot_err_t ciot_iface_reset_request(ciot_iface_t *self)
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
        case CIOT_IFACE_TYPE_UNKNOWN:
            return "UNKNOWN";
        case CIOT_IFACE_TYPE_CIOT:
            return "CIOT";
        case CIOT_IFACE_TYPE_STORAGE:
            return "STORAGE";
        case CIOT_IFACE_TYPE_SYSTEM:
            return "SYSTEM";
        case CIOT_IFACE_TYPE_UART:
            return "UART";
        case CIOT_IFACE_TYPE_USB:
            return "USB";
        case CIOT_IFACE_TYPE_TCP:
            return "TCP";
        case CIOT_IFACE_TYPE_ETH:
            return "ETH";
        case CIOT_IFACE_TYPE_WIFI:
            return "WIFI";
        case CIOT_IFACE_TYPE_BLE:
            return "BLE";
        case CIOT_IFACE_TYPE_BLE_SCN:
            return "BLE_SCN";
        case CIOT_IFACE_TYPE_NTP:
            return "NTP";
        case CIOT_IFACE_TYPE_OTA:
            return "OTA";
        case CIOT_IFACE_TYPE_HTTP_CLIENT:
            return "HTTP_CLIENT";
        case CIOT_IFACE_TYPE_HTTP_SERVER:
            return "HTTP_SERVER";
        case CIOT_IFACE_TYPE_MQTT:
            return "MQTT";
        case CIOT_IFACE_TYPE_BRIDGE:
            return "MQTT";
        case CIOT_IFACE_TYPE_CUSTOM:
            return "CUSTOM";
    default:
            return "CUSTOM";
    }
}

const char *ciot_iface_event_to_str(ciot_iface_event_t *event)
{
    if(event == NULL)
    {
        return "NULL";
    }

    switch (event->id)
    {
        case CIOT_IFACE_EVENT_UNKNOWN:
            return "EVENT_UNKNOWN";
        case CIOT_IFACE_EVENT_STARTED:
            return "EVENT_STARTED";
        case CIOT_IFACE_EVENT_STOPPED:
            return "EVENT_STOPPED";
        case CIOT_IFACE_EVENT_ERROR:
            return "EVENT_ERROR";
        case CIOT_IFACE_EVENT_REQUEST:
            return "EVENT_REQUEST";
        case CIOT_IFACE_EVENT_DATA:
            return "EVENT_DATA";
        case CIOT_IFACE_EVENT_DONE:
            return "EVENT_DONE";
        case CIOT_IFACE_EVENT_CUSTOM:
            return "EVENT_CUSTOM";
    default:
            return "EVENT_CUSTOM";
    }
}