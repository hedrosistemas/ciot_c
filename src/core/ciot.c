/**
 * @file ciot.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-06-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "ciot.h"
#include "ciot_err.h"
#include "ciot_timer.h"
#include "ciot_log.h"
#include "ciot_logger.h"
#include "ciot_sys.h"

#define CIOT_IFACE_START_TIMEOUT_SECS 5

static const char *TAG = "ciot";

static ciot_err_t ciot_starting_task(ciot_t self);
static ciot_err_t ciot_busy_task(ciot_t self);
static ciot_err_t ciot_start_iface(ciot_t self, ciot_iface_t *iface, ciot_msg_data_t *cfg);
static ciot_err_t ciot_set_iface_list(ciot_t self, ciot_iface_t *ifaces[], int count);
static ciot_err_t ciot_bytes_received(ciot_t self, ciot_iface_t *sender, uint8_t *bytes, int size);
static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *event_args);
static ciot_err_t ciot_free_recv(ciot_t self);

ciot_t ciot_new(void)
{
    ciot_t self = calloc(1, sizeof(struct ciot));
    self->iface.ptr = self;
    ciot_init(self);
    #ifdef CIOT_MG_ENABLED
    mg_mgr_init(CIOT_HANDLE);
    #endif
    return self;
}

ciot_err_t ciot_start(ciot_t self, ciot_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    if (self->status.state != CIOT__CIOT_STATE__CIOT_STATE_IDLE &&
        self->status.state != CIOT__CIOT_STATE__CIOT_STATE_STARTED)
    {
        CIOT_LOGE(TAG, "ciot core incorrect state");
        return CIOT_ERR__INVALID_STATE;
    }
    self->ifaces.cfgs = cfg->cfgs;
    self->storage = cfg->storage;
    ciot_set_iface_list(self, cfg->ifaces, cfg->count);
    self->starting.timer = 0;
    self->starting.iface_id = 0;
    self->starting.waiting_result = false;
    self->status.state = CIOT__CIOT_STATE__CIOT_STATE_STARTING;
    CIOT_LOGI(TAG, "CIOT_STATE_STARTING");
    return CIOT_ERR__OK;
}

ciot_err_t ciot_stop(ciot_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    self->status.state = CIOT__CIOT_STATE__CIOT_STATE_IDLE;
    CIOT_LOGV(TAG, "CIOT_STATE_IDLE");
    return CIOT_ERR__OK;
}

ciot_err_t ciot_task(ciot_t self)
{
    CIOT_ERR_NULL_CHECK(self);

    #ifdef CIOT_MG_ENABLED
    mg_mgr_poll(CIOT_HANDLE, CIOT_CONFIG_MG_POOL_INTERVAL_MS);
    #endif

    switch (self->status.state)
    {
    case CIOT__CIOT_STATE__CIOT_STATE_STARTING:
        ciot_starting_task(self);
        break;
    case CIOT__CIOT_STATE__CIOT_STATE_BUSY:
        ciot_busy_task(self);
        break;
    default:
        break;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_starting_task(ciot_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(self->ifaces.list);

    if (self->ifaces.count == 1)
    {
        return CIOT_ERR__OK;
    }

    if (self->starting.waiting_result)
    {
        if (self->recv.sender != NULL &&
            self->recv.event.type == CIOT_IFACE_EVENT_STARTED &&
            self->starting.iface_id == self->recv.sender->info.id)
        {
            CIOT_LOGI(TAG, "Interface [%lu]:%s Started", self->recv.sender->info.id, ciot_iface_to_str(self->recv.sender));
            if(self->iface.event_handler != NULL)
            {
                self->iface.event_handler(self->recv.sender, &self->recv.event, self->iface.event_args);
            }
            self->starting.iface_id++;
            self->starting.waiting_result = false;
        }
        else if (ciot_timer_compare(&self->starting.timer, CIOT_IFACE_START_TIMEOUT_SECS))
        {
            CIOT_LOGE(TAG, "Interface [%lu]:%s Timeout", self->starting.iface_id, ciot_iface_to_str(self->ifaces.list[self->starting.iface_id]));
            self->starting.iface_id++;
            self->starting.waiting_result = false;
        }
    }
    else
    {
        uint8_t id = self->starting.iface_id;
        if(self->iface.info.id == id)
        {
            self->starting.iface_id++;
            id++;
        }

        ciot_iface_t *iface = self->ifaces.list[id];
        ciot_msg_data_t *cfg = NULL;

        if(self->storage != NULL)
        {
            cfg = ciot_load_cfg(self, id);
            if(cfg != NULL)
            {
                CIOT_LOGI(TAG, "Loading cfg into interface %s", ciot_iface_to_str(iface));
            }
        }

        if(cfg == NULL)
        {
            CIOT_LOGI(TAG, "Loading static configuration into interface %s", ciot_iface_to_str(iface));
            cfg = self->ifaces.cfgs[id];
        }

        if(cfg != NULL)
        {
            ciot_err_t err = ciot_start_iface(self, iface, cfg);
            if (err == CIOT_ERR__OK)
            {
                ciot_timer_init(&self->starting.timer, CIOT_IFACE_START_TIMEOUT_SECS);
                self->starting.waiting_result = true;
            }
            else
            {
                CIOT_LOGE(TAG, "Interface [%u]:%s cannot start. Error: %s[%u]", id, ciot_iface_to_str(iface), ciot_err_to_message(err), err);
                self->starting.iface_id++;
            }
        }
        else
        {
            CIOT_LOGI(TAG, "Interface [%u]:%s with null configuration not started.", id, ciot_iface_to_str(iface));
            self->starting.iface_id++;
        }
    }

    if (self->starting.iface_id == self->ifaces.count)
    {
        self->status.state = CIOT__CIOT_STATE__CIOT_STATE_STARTED;
        CIOT_LOGI(TAG, "CIOT_STATE_STARTED");
        ciot_iface_event_t event = { 0 };
        event.type = CIOT_IFACE_EVENT_STARTED;
        ciot_iface_send_event(&self->iface, &event);
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_busy_task(ciot_t self)
{       
    CIOT_LOGI(TAG, "ciot is busy...");

    if (self->recv.sender == NULL)
    {
        CIOT_LOGE(TAG, "Sender is null");
        self->status.state = CIOT__CIOT_STATE__CIOT_STATE_STARTED;
        return CIOT_ERR__NULL_ARG;
    }

    ciot_iface_event_t *event = &self->recv.event;
    ciot_iface_t *sender = self->recv.sender;

    if (sender->req_status.state != CIOT_IFACE_REQ_STATE_IDLE && event->msg != NULL)
    {
        CIOT_LOGI(TAG, "Processing event from %s", ciot_iface_to_str(sender));
        bool iface_is_equal = sender->req_status.state == CIOT_IFACE_REQ_STATE_SENDED 
            ? ciot_iface_is_equal(&sender->req_status.iface, event->msg->iface)
            : ciot_iface_is_equal(&sender->info, event->msg->iface);
        if ((ciot_iface_event_is_ack(event->type) || event->type == CIOT_IFACE_EVENT_REQUEST) &&
            iface_is_equal)
        {
            if (sender->req_status.state == CIOT_IFACE_REQ_STATE_SENDED &&
                sender->req_status.id == event->msg->id)
            {
                CIOT_LOGI(TAG, "Request done");
                event->type = CIOT_IFACE_EVENT_DONE;
            }
            else
            {
                CIOT_LOGI(TAG, "Response sended");
                event->msg->id = sender->req_status.id;
                ciot_iface_send_rsp(self->ifaces.list[sender->req_status.iface.id], event->msg);
            }
            sender->req_status.state = CIOT_IFACE_REQ_STATE_IDLE;
        }
        CIOT_LOGI(TAG, "Event processed");
    }

    if (event->type == CIOT_IFACE_EVENT_REQUEST)
    {
        CIOT_LOGI(TAG, "Processing request from %s", ciot_iface_to_str(sender));
        CIOT_LOG_MSG_P(TAG, CIOT_LOGV, "RX REQ <- ", sender, event->msg);
        uint8_t id = event->msg->iface->id;
        if (id < self->ifaces.count && event->msg->type <= CIOT__MSG_TYPE__MSG_TYPE_REQUEST)
        {
            ciot_iface_t *iface = self->ifaces.list[id];
            if (iface != NULL)
            {
                CIOT_LOGI(TAG, "Processing message");
                ciot_iface_process_msg(iface, event->msg, sender);
                if (iface->req_status.state == CIOT_IFACE_REQ_STATE_IDLE)
                {
                    event->type = CIOT_IFACE_EVENT_DONE;
                }
            }
            else if(event->msg->type != CIOT__MSG_TYPE__MSG_TYPE_CUSTOM)
            {
                CIOT_LOGE(TAG, "Error. %d iface is null.", id);
                event->type = CIOT_IFACE_EVENT_ERROR;
                ciot_iface_send_error(sender, CIOT__IFACE_TYPE__IFACE_TYPE_UNKNOWN, id, event->msg, CIOT_ERR__NULL_ARG);
            }
        }
        // else if(event->msg->type != CIOT__MSG_TYPE__MSG_TYPE_CUSTOM)
        // {
        //     CIOT_LOGE(TAG, "Error msg type %s from iface %d.", ciot__msg_type__descriptor.values[event->msg->type].name, id);
        //     event->type = CIOT_IFACE_EVENT_ERROR;
        //     ciot_iface_send_error(sender, CIOT__IFACE_TYPE__IFACE_TYPE_UNKNOWN, id, event->msg, CIOT_ERR__INVALID_HEADER);
        // }
    }

    self->recv.sender = NULL;
    self->status.state = CIOT__CIOT_STATE__CIOT_STATE_STARTED;

    if(self->iface.event_handler != NULL)
    {
        self->iface.event_handler(sender, event, self->iface.event_args);
    }

    CIOT_LOGI(TAG, "ciot done");

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_start_iface(ciot_t self, ciot_iface_t *iface, ciot_msg_data_t *cfg)
{
    CIOT_ERR_NULL_CHECK(iface);
    CIOT_ERR_NULL_CHECK(cfg);
    CIOT_LOGI(TAG, "Starting interface %s", ciot_iface_to_str(iface));
    ciot_msg_t msg;
    msg.type = CIOT__MSG_TYPE__MSG_TYPE_START;
    msg.iface = &self->iface.info;
    msg.data = cfg;
    return iface->process_req(iface, &msg);
}

static ciot_err_t ciot_set_iface_list(ciot_t self, ciot_iface_t *ifaces[], int count)
{
    ciot_err_t ret = CIOT_ERR__OK;

    self->ifaces.list = ifaces;
    self->ifaces.count = count;

    for (size_t i = 0; i < count; i++)
    {
        ciot_iface_t *iface = self->ifaces.list[i];
        if (iface != NULL)
        {
            iface->info.id = i;
            if(iface->info.id != self->iface.info.id)
            {
                ciot_err_t err = ciot_iface_set_event_handler(iface, ciot_iface_event_handler, self);
                if (err != CIOT_ERR__OK)
                {
                    CIOT_LOGE(TAG, "Interface id:%d type%d register event error: %d", i, iface->info.type, err);
                    ret = err;
                }
            }
        }
        else
        {
            CIOT_LOGI(TAG, "Interface %d is null.", i);
        }
    }

    return ret;
}

static ciot_err_t ciot_bytes_received(ciot_t self, ciot_iface_t *sender, uint8_t *bytes, int size)
{
    ciot_free_recv(self);
    if (sender->serializer != NULL)
    {
        self->recv.event.msg = sender->serializer->from_bytes(bytes, size);
    }
    else
    {
        CIOT_LOGD(TAG, "Deserializing %d bytes", size);
        self->recv.sender = sender;
        self->recv.event.msg = ciot__msg__unpack(NULL, size, bytes);
        self->recv.serialized = true;
        if(self->recv.event.msg == NULL)
        {
            CIOT_LOGE(TAG, "msg unpack error");
            return CIOT_ERR__DESERIALIZATION;
        }
    }
    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *event_args)
{
    ciot_t self = (ciot_t)event_args;

    CIOT_LOGD(TAG, "%s(%lu) evt type: %d", ciot_iface_to_str(sender), sender->info.id, event->type);

    if ((event->type == CIOT_IFACE_EVENT_DATA || 
         event->type == CIOT_IFACE_EVENT_INTERNAL ||
         event->type == CIOT_IFACE_EVENT_CUSTOM) && 
         self->iface.event_handler != NULL)
    {
        return self->iface.event_handler(sender, event, self->iface.event_args);
    }

    if (self->status.state == CIOT__CIOT_STATE__CIOT_STATE_BUSY)
    {
        CIOT_LOGE(TAG, "ciot busy. %s(%lu) evt type:%d ignored", ciot_iface_to_str(sender), sender->info.id, event->type);
        return CIOT_ERR__BUSY;
    }

    self->recv.event.type = event->type;
    self->recv.sender = sender;
    
    if (event->type == CIOT_IFACE_EVENT_REQUEST)
    {
        if (self->status.state != CIOT__CIOT_STATE__CIOT_STATE_STARTED)
        {
            CIOT_LOGE(TAG, "ciot core is not started");
            return CIOT_ERR__BUSY;
        }

        CIOT_ERR_RETURN(ciot_bytes_received(self, sender, event->data, event->size));

        if(self->recv.event.msg->type == CIOT__MSG_TYPE__MSG_TYPE_LOG)
        {
            ciot_log_t *log = self->recv.event.msg->data->log;
            if(log->level == CIOT__LOG_LEVEL__LOG_LEVEL_INFO) CIOT_LOGI(TAG, "[%s] %s", log->tag, log->message);
            if(log->level == CIOT__LOG_LEVEL__LOG_LEVEL_WARNING) CIOT_LOGW(TAG, "[%s] %s", log->tag, log->message);
            if(log->level == CIOT__LOG_LEVEL__LOG_LEVEL_ERROR) CIOT_LOGE(TAG, "[%s] %s", log->tag, log->message);
            return CIOT_ERR__OK;
        }

        if(self->recv.event.msg->type == CIOT__MSG_TYPE__MSG_TYPE_CUSTOM && self->iface.event_handler != NULL)
        {
            self->iface.event_handler(sender, &self->recv.event, self->iface.event_args);
        }
        else
        {
            CIOT_LOGI(TAG, "CIOT_STATE_BUSY");
            self->status.state = CIOT__CIOT_STATE__CIOT_STATE_BUSY;
        }
    }
    else if(self->status.state == CIOT__CIOT_STATE__CIOT_STATE_STARTED)
    {
        CIOT_LOGI(TAG, "Event received from %s", ciot_iface_to_str(sender));
        self->recv.serialized = false;
        self->recv.sender = sender;
        self->recv.event.type = event->type;
        self->recv.event.msg = event->msg;
        self->status.state = CIOT__CIOT_STATE__CIOT_STATE_BUSY;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_free_recv(ciot_t self)
{
    if(self->recv.serialized)
    {
        ciot__msg__free_unpacked(self->recv.event.msg, NULL);
        self->recv.serialized = false;
        self->recv.event.msg = NULL;
    }
    return CIOT_ERR__OK;
}

