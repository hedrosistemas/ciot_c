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

#define CIOT_IFACE_START_TIMEOUT_SECS 5
#define CIOT_IFACE_CFG_FILENAME "cfg%d.dat"

static const char *TAG = "ciot";

static ciot_err_t ciot_starting_task(ciot_t self);
static ciot_err_t ciot_busy_task(ciot_t self);
static ciot_err_t ciot_start_iface(ciot_t self, ciot_iface_t *iface, ciot_msg_data_t *cfg);
static ciot_err_t ciot_set_iface_list(ciot_t self, ciot_iface_t *ifaces[], int count);
static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *event_args);

ciot_t ciot_new(void)
{
    ciot_t self = calloc(1, sizeof(struct ciot));
    self->iface.ptr = self;
    self->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_CIOT;
    ciot_init(self);
    return self;
}

ciot_err_t ciot_start(ciot_t self, ciot_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    if (self->status.state != CIOT__CIOT_STATE__CIOT_STATE_IDLE)
    {
        CIOT_LOGE(TAG, "CIoT core incorrect state");
        return CIOT_ERR__INVALID_STATE;
    }
    self->ifaces.cfgs = cfg->cfgs;
    ciot_set_iface_list(self, cfg->ifaces, cfg->count);
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

    if (self->ifaces.count == 0)
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
            char filename[16];
            sprintf(filename, CIOT_IFACE_CFG_FILENAME, id);
            cfg = ciot_storage_get_data(self->storage, filename);
            if(cfg != NULL)
            {
                CIOT_LOGI(TAG, "Loading file %s into interface %s", filename, ciot_iface_to_str(iface));
            }
        }

        if(cfg == NULL)
        {
            CIOT_LOGI(TAG, "Loading static configuration into interface %s", ciot_iface_to_str(iface));
            cfg = self->ifaces.cfgs[id];
        }

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

    if (self->starting.iface_id == self->ifaces.count)
    {
        self->status.state = CIOT__CIOT_STATE__CIOT_STATE_STARTED;
        CIOT_LOGI(TAG, "CIOT_STATE_STARTED");
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_busy_task(ciot_t self)
{
    if (self->recv.sender == NULL)
    {
        CIOT_LOGE(TAG, "Sender is null");
        self->status.state = CIOT__CIOT_STATE__CIOT_STATE_STARTED;
        return CIOT_ERR__NULL_ARG;
    }

    ciot_iface_event_t *event = &self->recv.event;
    ciot_iface_t *sender = self->recv.sender;

    if (sender->req_status.state != CIOT_IFACE_REQ_STATE_IDLE)
    {
        if (ciot_iface_event_is_ack(event) &&
            ciot_iface_is_equal(&sender->info, event->msg->iface) &&
            sender->req_status.id == event->msg->id)
        {
            sender->req_status.state = CIOT_IFACE_REQ_STATE_IDLE;
            if (sender->req_status.state == CIOT_IFACE_REQ_STATE_SENDED)
            {
                event->type = CIOT_IFACE_EVENT_DONE;
            }
            else
            {
                event->msg->id = sender->req_status.id;
                ciot_iface_send_rsp(sender, event->msg);
            }
        }
    }

    if (event->type == CIOT_IFACE_EVENT_REQUEST)
    {
        CIOT_LOG_MSG_P(TAG, CIOT_LOGV, "RX REQ <- ", sender, event->msg);
        uint8_t id = event->msg->iface->id;
        if (id < self->ifaces.count && event->msg->type <= CIOT__MSG_TYPE__MSG_TYPE_REQUEST)
        {
            ciot_iface_t *iface = self->ifaces.list[id];
            if (iface != NULL)
            {
                ciot_iface_process_msg(iface, event->msg, sender);
                if (iface->req_status.state == CIOT_IFACE_REQ_STATE_IDLE)
                {
                    event->type = CIOT_IFACE_EVENT_DONE;
                }
            }
            else if(event->msg->type != CIOT__MSG_TYPE__MSG_TYPE_CUSTOM)
            {
                event->type = CIOT_IFACE_EVENT_ERROR;
                ciot_iface_send_error(sender, CIOT__IFACE_TYPE__IFACE_TYPE_UNKNOWN, id, event->msg, CIOT_ERR__NULL_ARG);
            }
        }
        else if(event->msg->type != CIOT__MSG_TYPE__MSG_TYPE_CUSTOM)
        {
            event->type = CIOT_IFACE_EVENT_ERROR;
            ciot_iface_send_error(sender, CIOT__IFACE_TYPE__IFACE_TYPE_UNKNOWN, id, event->msg, CIOT_ERR__INVALID_HEADER);
        }
    }

    self->recv.sender = NULL;
    self->status.state = CIOT__CIOT_STATE__CIOT_STATE_STARTED;
    CIOT_LOGV(TAG, "CIOT_STATE_STARTED");

    if(self->iface.event_handler != NULL)
    {
        self->iface.event_handler(sender, event, self->iface.event_args);
    }
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

static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *event_args)
{
    ciot_t self = (ciot_t)event_args;

    self->recv.event.type = event->type;
    self->recv.sender = sender;

    CIOT_LOGD(TAG, "%s(%lu) evt id: %d", ciot_iface_to_str(sender), sender->info.id, event->type);

    if (event->type == CIOT_IFACE_EVENT_DATA && self->iface.event_handler != NULL)
    {
        self->iface.event_handler(sender, event, self->iface.event_args);
    }

    if (self->status.state == CIOT__CIOT_STATE__CIOT_STATE_BUSY)
    {
        CIOT_LOGE(TAG, "CIoT core is busy");
        return CIOT_ERR__BUSY;
    }

    if (event->type == CIOT_IFACE_EVENT_REQUEST)
    {
        if (self->status.state != CIOT__CIOT_STATE__CIOT_STATE_STARTED)
        {
            CIOT_LOGE(TAG, "CIoT core is not started");
            return CIOT_ERR__BUSY;
        }

        ciot__msg__free_unpacked(self->recv.event.msg, NULL);
        if (sender->serializer != NULL)
        {
            self->recv.event.msg = sender->serializer->from_bytes(event->data, event->size);
        }
        else
        {
            self->recv.event.msg = ciot__msg__unpack(NULL, event->size, event->data);
        }

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
            self->status.state = CIOT__CIOT_STATE__CIOT_STATE_BUSY;
            CIOT_LOGV(TAG, "CIOT_STATE_BUSY");
        }
    }

    return CIOT_ERR__OK;
}
