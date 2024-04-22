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

static ciot_err_t ciot_iface_process_request_result(ciot_iface_t *self, ciot_iface_t *sender, ciot_msg_t *msg, ciot_err_t err);

ciot_err_t ciot_iface_start(ciot_iface_t *self, ciot_msg_data_u *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);
    CIOT_NULL_CHECK(self->base.ptr);
    CIOT_NULL_CHECK(self->base.start);
    self->base.req.response_size = CIOT_MSG_HEADER_SIZE;
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
    #ifdef  CIOT_LOG_HEX_ENABLED
    CIOT_LOG_BUFFER_HEX(TAG, data, size);
    #endif  //CIOT_LOG_HEX_ENABLED
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
        msg->id = ciot_iface_get_msg_id();
        
        CIOT_LOG_MSG_P("ciot", CIOT_LOGV, "TX RSP <- ", self, msg);
        #if CIOT_CONFIG_FEATURE_SERIALIZER
        if(self->serializer != NULL)
        {
            ciot_msg_t data = *msg;
            size = ciot_serializer_to_bytes(self->serializer, (uint8_t*)msg, &data);
        }
        #endif  //

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
        CIOT_LOG_MSG_P("ciot", CIOT_LOGV, "TX RSP <- ", self, rsp);
        #if CIOT_CONFIG_FEATURE_SERIALIZER
        if(self->serializer != NULL)
        {
            ciot_msg_t data = *rsp;
            size = ciot_serializer_to_bytes(self->serializer, (uint8_t*)rsp, &data);
        }
        #endif  //

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
        req->id = ciot_iface_get_msg_id();
        ciot_iface_register_request(self, &req->iface, req, CIOT_IFACE_REQ_STATUS_SENDED);

        CIOT_LOG_MSG_P("ciot", CIOT_LOGV, "TX REQ <- ", self, req);
        #if CIOT_CONFIG_FEATURE_SERIALIZER
        if(self->serializer != NULL)
        {
            ciot_msg_t data = *req;
            size = ciot_serializer_to_bytes(self->serializer, (uint8_t*)req, &data);
        }
        #endif  //
        
        ciot_err_t err = ciot_iface_send_data(self, req, size);
        if(err != CIOT_OK)
        {
            self->base.req.status = CIOT_IFACE_REQ_STATUS_IDLE;
        }
        return err;
    }
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
            ciot_iface_register_request(self, &sender_iface->info, msg, CIOT_IFACE_REQ_STATUS_RECEIVED);
            err = ciot_iface_start(self, &msg->data);
            err = ciot_iface_process_request_result(self, sender_iface, msg, err);
            break;
        case CIOT_MSG_TYPE_STOP:
            self->base.req.response_size = CIOT_MSG_HEADER_SIZE;
            ciot_iface_register_request(self, &sender_iface->info, msg, CIOT_IFACE_REQ_STATUS_RECEIVED);
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
            ciot_iface_register_request(self, &sender_iface->info, msg, CIOT_IFACE_REQ_STATUS_RECEIVED);
            err = ciot_iface_process_req(self, &msg->data, sender);
            err = ciot_iface_process_request_result(self, sender_iface, msg, err);
            break;
        case CIOT_MSG_TYPE_EVENT:
            err = CIOT_ERR_NOT_IMPLEMENTED;
            break;
        case CIOT_MSG_TYPE_ERROR:
            CIOT_LOG_MSG_P(TAG, CIOT_LOGE, "RX ERR <- ", sender_iface, msg);
            break;
        case CIOT_MSG_TYPE_CUSTOM:
            ciot_iface_register_request(self, &sender_iface->info, msg, CIOT_IFACE_REQ_STATUS_RECEIVED);
            // register event to main applcation
            break;
        }
    }

    if(err != CIOT_OK)
    {
        msg->data.error.msg_type = msg->type;
        // if(self != NULL)
        // {
        //     msg->data.error.iface = self->info;
        // }
        // else
        // {
        //     msg->data.error.iface.id = -1;
        //     msg->data.error.iface.type = CIOT_IFACE_TYPE_UNKNOWN;
        // }
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
            return "IFACE_UNKNOWN";
        case CIOT_IFACE_TYPE_CIOT:
            return "IFACE_CIOT";
        case CIOT_IFACE_TYPE_STORAGE:
            return "IFACE_STORAGE";
        case CIOT_IFACE_TYPE_SYSTEM:
            return "IFACE_SYSTEM";
        case CIOT_IFACE_TYPE_UART:
            return "IFACE_UART";
        case CIOT_IFACE_TYPE_USB:
            return "IFACE_USB";
        case CIOT_IFACE_TYPE_TCP:
            return "IFACE_TCP";
        case CIOT_IFACE_TYPE_ETH:
            return "IFACE_ETH";
        case CIOT_IFACE_TYPE_WIFI:
            return "IFACE_WIFI";
        case CIOT_IFACE_TYPE_BLE:
            return "IFACE_BLE";
        case CIOT_IFACE_TYPE_BLE_SCN:
            return "IFACE_BLE_SCN";
        case CIOT_IFACE_TYPE_NTP:
            return "IFACE_NTP";
        case CIOT_IFACE_TYPE_OTA:
            return "IFACE_OTA";
        case CIOT_IFACE_TYPE_HTTP_CLIENT:
            return "IFACE_HTTP_CLIENT";
        case CIOT_IFACE_TYPE_HTTP_SERVER:
            return "IFACE_HTTP_SERVER";
        case CIOT_IFACE_TYPE_MQTT:
            return "IFACE_MQTT";
        case CIOT_IFACE_TYPE_BRIDGE:
            return "IFACE_MQTT";
        case CIOT_IFACE_TYPE_CUSTOM:
            return "IFACE_CUSTOM";
    default:
            return "IFACE_CUSTOM";
    }
}

const char *ciot_iface_event_to_str(ciot_iface_event_t *event)
{
    if(event == NULL)
    {
        return "NULL";
    }

    switch (event->type)
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

ciot_err_t ciot_iface_register_request(ciot_iface_t *self, ciot_msg_iface_info_t *iface, ciot_msg_t *msg, ciot_iface_req_status_t status)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(iface);
    CIOT_NULL_CHECK(msg);
    self->base.req.status = status;
    self->base.req.id = msg->id;
    self->base.req.type = msg->type;
    self->base.req.iface = *iface;
    return CIOT_OK;
}

ciot_err_t ciot_iface_set_serializer(ciot_iface_t *self, ciot_serializer_t serializer)
{
    CIOT_NULL_CHECK(self);
    self->serializer = serializer;
    return CIOT_OK;
}

uint8_t ciot_iface_get_msg_id(void)
{
    uint8_t ret = msg_id;
    msg_id++;
    return ret;
}

static ciot_err_t ciot_iface_process_request_result(ciot_iface_t *self, ciot_iface_t *sender, ciot_msg_t *msg, ciot_err_t err)
{
    if(self->base.req.status == CIOT_IFACE_REQ_STATUS_IDLE && err == CIOT_OK)
    {
        int size = self->base.req.response_size;
        self->base.req.response_size = CIOT_MSG_HEADER_SIZE;
        return ciot_iface_send_rsp(sender, msg, size);
    }
    return err;
}