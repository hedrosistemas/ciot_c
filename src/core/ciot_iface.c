/**
 * @file ciot_iface.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <string.h> 
#include "ciot_err.h"
#include "ciot_iface.h"
#include "ciot_log.h"
#include "ciot_msg.h"

static const char *TAG = "ciot_iface";

static uint8_t msg_id = 0;

static uint8_t buf[256];

static ciot_msg_error_t error;

static ciot_err_t ciot_iface_process_request_result(ciot_iface_t *self, ciot_iface_t *sender, ciot_msg_t *msg, ciot_err_t err);

ciot_err_t ciot_iface_send_msg(ciot_iface_t *self, ciot_msg_t *msg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(msg);

    if (self->req_status.state != CIOT_IFACE_REQ_STATE_IDLE)
    {
        CIOT_LOGE(TAG, "Iface %s (%lu) is busy", ciot_iface_to_str(self), self->info.id);
        return CIOT_ERR__BUSY;
    }
    else
    {
        msg->id = ciot_iface_get_msg_id();
        
        // CIOT_LOG_MSG_P(TAG, CIOT_LOGV, "TX RSP <- ", self, msg);

        if(self->serializer != NULL)
        {
            int size = self->serializer->to_bytes(buf, msg);
            return self->send_data(self, buf, size);
        }
        else
        {
            int size = ciot__msg__pack(msg, buf);
            return self->send_data(self, buf, size);
        }
    }
}

ciot_err_t ciot_iface_send_rsp(ciot_iface_t *self, ciot_msg_t *rsp)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(rsp);

    if (self->req_status.state != CIOT_IFACE_REQ_STATE_IDLE)
    {
        CIOT_LOGE(TAG, "Iface %s (%lu) is busy", ciot_iface_to_str(self), self->info.id);
        return CIOT_ERR__BUSY;
    }
    else
    {
        // CIOT_LOG_MSG_P("ciot", CIOT_LOGV, "TX RSP <- ", self, rsp);

        if(self->serializer != NULL)
        {
            int size = self->serializer->to_bytes(buf, rsp);
            return self->send_data(self, buf, size);
        }
        else
        {
            int size = ciot__msg__pack(rsp, buf);
            return self->send_data(self, buf, size);
        }
    }
}

ciot_err_t ciot_iface_send_req(ciot_iface_t *self, ciot_msg_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);

    if (self->req_status.state != CIOT_IFACE_REQ_STATE_IDLE)
    {
        CIOT_LOGE(TAG, "Iface %s (%lu) is busy", ciot_iface_to_str(self), self->info.id);
        return CIOT_ERR__BUSY;
    }
    else
    {
        req->id = ciot_iface_get_msg_id();
        ciot_iface_register_req(self, req->iface, req, CIOT_IFACE_REQ_STATE_SENDED);

        CIOT_LOG_MSG_P("ciot", CIOT_LOGV, "TX REQ <- ", self, req);
        
        if(self->serializer != NULL)
        {
            int size = self->serializer->to_bytes(buf, req);
            return self->send_data(self, buf, size);
        }
        else
        {
            int size = ciot__msg__pack(req, buf);
            ciot_err_t err = self->send_data(self, buf, size);
            if(err != CIOT_ERR__OK)
            {
                self->req_status.state = CIOT_IFACE_REQ_STATE_IDLE;
            }
            return err;
        }
    }
}

ciot_err_t ciot_iface_process_msg(ciot_iface_t *self, ciot_msg_t *msg, ciot_iface_t *sender)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(msg);

    ciot_iface_t *sender_iface = (ciot_iface_t*)sender;
    ciot_err_t err = CIOT_ERR__OK;

    if(self != NULL && msg != NULL)
    {
        if (msg->iface->id != self->info.id)
        {
            err = CIOT_ERR__INVALID_ID;
        }
        if (msg->iface->type != self->info.type)
        {
            err = CIOT_ERR__INVALID_TYPE;
        }
    }
    else
    {
        err = CIOT_ERR__NULL_ARG;
    }

    if(err == CIOT_ERR__OK)
    {
        switch (msg->type)
        {
        case CIOT__MSG_TYPE__MSG_TYPE_UNKNOWN:
            err = CIOT_ERR__INVALID_TYPE;
            break;
        case CIOT__MSG_TYPE__MSG_TYPE_START:
        case CIOT__MSG_TYPE__MSG_TYPE_STOP:
        case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
            ciot_iface_register_req(self, &sender_iface->info, msg, CIOT_IFACE_REQ_STATE_RECEIVED);
            err = self->process_req(self, msg);
            err = ciot_iface_process_request_result(self, sender_iface, msg, err);
            break;
        case CIOT__MSG_TYPE__MSG_TYPE_CONFIG:
        case CIOT__MSG_TYPE__MSG_TYPE_STATUS:
        case CIOT__MSG_TYPE__MSG_TYPE_INFO:
            err = self->get_data(self, msg);
            err = ciot_iface_process_request_result(self, sender_iface, msg, err);
            break;
        case CIOT__MSG_TYPE__MSG_TYPE_EVENT:
            err = CIOT_ERR__NOT_IMPLEMENTED;
            break;
        case CIOT__MSG_TYPE__MSG_TYPE_ERROR:
            CIOT_LOG_MSG_P(TAG, CIOT_LOGE, "RX ERR <- ", sender_iface, msg);
            break;
        default:
            break;
        // case CIOT__MSG_TYPE__MSG_TYPE_CUSTOM:
        //     ciot_iface_register_request(self, &sender_iface->info, msg, CIOT_IFACE_REQ_STATE_RECEIVED);
        //     // register event to main applcation
        //     break;
        }
    }

    if(err != CIOT_ERR__OK)
    {
        error.msg->id = msg->id;
        error.msg->type = msg->type;
        error.iface->id = self->info.id;
        error.iface->type = self->info.type;
        error.code = err;
        msg->data->error = &error;
        msg->type = CIOT__MSG_TYPE__MSG_TYPE_ERROR;
        ciot_iface_send_rsp(sender, msg);
    }

    return err;
}

ciot_err_t ciot_iface_register_req(ciot_iface_t *self, ciot_iface_info_t *iface, ciot_msg_t *req, ciot_iface_req_state_t state)
{
    CIOT_ERR_NULL_CHECK(self);
    self->req_status.state = state;
    self->req_status.id = req->id;
    self->req_status.type = req->type;
    self->req_status.iface = *iface;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_iface_set_event_handler(ciot_iface_t *self, ciot_iface_event_handler_fn event_handler, void *event_args)
{
    CIOT_ERR_NULL_CHECK(self);
    self->event_handler = event_handler;
    self->event_args = event_args;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_iface_set_serializer(ciot_iface_t *self, ciot_serializer_t serializer)
{
    CIOT_ERR_NULL_CHECK(self);
    self->serializer = serializer;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_iface_send_event(ciot_iface_t *self, ciot_iface_event_t *event)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(event);
    CIOT_ERR_NULL_CHECK(self->event_handler);
    return self->event_handler(self, event, self->event_args);
}

ciot_err_t ciot_iface_send_event_type(ciot_iface_t *self, ciot_iface_event_type_t event_type)
{
    ciot_iface_event_t iface_event = { .type = event_type };
    return ciot_iface_send_event(self, &iface_event);
}

ciot_err_t ciot_iface_get_msg_id(void)
{
    uint8_t ret = msg_id;
    msg_id++;
    return ret;
}

const char* ciot_iface_to_str(ciot_iface_t *iface)
{
    if(iface == NULL)
    {
        return "NULL";
    }

    return ciot_iface_type_to_str(iface->info.type);
}

const char* ciot_iface_type_to_str(ciot_iface_type_t iface_type)
{
    switch (iface_type)
    {
        case CIOT__IFACE_TYPE__IFACE_TYPE_UNKNOWN:
            return "IFACE_UNKNOWN";
        case CIOT__IFACE_TYPE__IFACE_TYPE_CIOT:
            return "IFACE_CIOT";
        case CIOT__IFACE_TYPE__IFACE_TYPE_STORAGE:
            return "IFACE_STORAGE";
        case CIOT__IFACE_TYPE__IFACE_TYPE_SYS:
            return "IFACE_SYSTEM";
        case CIOT__IFACE_TYPE__IFACE_TYPE_UART:
            return "IFACE_UART";
        case CIOT__IFACE_TYPE__IFACE_TYPE_USB:
            return "IFACE_USB";
        case CIOT__IFACE_TYPE__IFACE_TYPE_TCP:
            return "IFACE_TCP";
        case CIOT__IFACE_TYPE__IFACE_TYPE_ETH:
            return "IFACE_ETH";
        case CIOT__IFACE_TYPE__IFACE_TYPE_WIFI:
            return "IFACE_WIFI";
        case CIOT__IFACE_TYPE__IFACE_TYPE_BLE:
            return "IFACE_BLE";
        case CIOT__IFACE_TYPE__IFACE_TYPE_BLE_SCN:
            return "IFACE_BLE_SCN";
        case CIOT__IFACE_TYPE__IFACE_TYPE_NTP:
            return "IFACE_NTP";
        case CIOT__IFACE_TYPE__IFACE_TYPE_OTA:
            return "IFACE_OTA";
        case CIOT__IFACE_TYPE__IFACE_TYPE_HTTP_CLIENT:
            return "IFACE_HTTP_CLIENT";
        case CIOT__IFACE_TYPE__IFACE_TYPE_HTTP_SERVER:
            return "IFACE_HTTP_SERVER";
        case CIOT__IFACE_TYPE__IFACE_TYPE_MQTT:
            return "IFACE_MQTT";
        case CIOT__IFACE_TYPE__IFACE_TYPE_BRIDGE:
            return "IFACE_MQTT";
        case CIOT__IFACE_TYPE__IFACE_TYPE_CUSTOM:
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

bool ciot_iface_is_equal(ciot_iface_info_t *iface, ciot_iface_info_t *other)
{
    return (iface->id == other->id &&
            iface->type == other->type);
}

bool ciot_iface_event_is_ack(ciot_iface_event_t *event)
{
    return (event->type >= CIOT_IFACE_EVENT_STARTED &&
            event->type <= CIOT_IFACE_EVENT_ERROR);
}

static ciot_err_t ciot_iface_process_request_result(ciot_iface_t *self, ciot_iface_t *sender, ciot_msg_t *msg, ciot_err_t err)
{
    if(self->req_status.state == CIOT_IFACE_REQ_STATE_IDLE && err == CIOT_ERR__OK)
    {
        return ciot_iface_send_rsp(sender, msg);
    }
    return err;
}
