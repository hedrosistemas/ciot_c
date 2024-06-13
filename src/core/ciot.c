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
#include <string.h>

#include "ciot.h"
#include "ciot_log.h"
#include "ciot_err.h"

typedef Ciot__CiotStatus ciot_status_t;

typedef struct ciot_ifaces
{
    ciot_iface_t **list;
    ciot_msg_data_t **cfgs;
    uint8_t count;
} ciot_ifaces_t;

typedef struct ciot_starting
{
    uint8_t iface_id;
    bool waiting_result;
} ciot_starting_t;

typedef struct ciot_recv
{
    ciot_iface_t *sender;
    ciot_iface_event_t event;
    ciot_msg_t buf;
} ciot_recv_t;

struct ciot
{
    ciot_iface_t iface;
    ciot_cfg_t cfg;
    ciot_status_t status;
    ciot_ifaces_t ifaces;
    ciot_iface_event_handler_fn *event_handler;
    void *event_args;
    ciot_starting_t starting;
    ciot_recv_t recv;
    ciot_msg_error_t error;
};

static const char *TAG = "ciot";

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);

static ciot_err_t ciot_starting_task(ciot_t self);
static ciot_err_t ciot_busy_task(ciot_t self);
static ciot_err_t ciot_start_iface(ciot_t self, ciot_iface_t *iface, ciot_msg_data_t *cfg);
static ciot_err_t ciot_set_iface_list(ciot_t self, ciot_iface_t *ifaces[], int count);
static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *event_args);

ciot_t ciot_new(void)
{
    ciot_t self = calloc(1, sizeof(struct ciot));
    self->iface.ptr = self;
    self->iface.process_req = ciot_iface_process_req;
    self->iface.get_data = ciot_iface_get_data;
    self->iface.send_data = ciot_iface_send_data;
    self->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_CIOT;
    return self;
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
        return CIOT_ERR__NOT_IMPLEMENTED;
    default:
        break;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_t self = iface->ptr;

    switch (msg->type)
    {
    case CIOT__MSG_TYPE__MSG_TYPE_CONFIG:
        return CIOT_ERR__NOT_SUPPORTED;
    case CIOT__MSG_TYPE__MSG_TYPE_STATUS:
        msg->data->ciot->status = &self->status;
        break;
    default:
        return CIOT_ERR__NOT_FOUND;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    CIOT_ERR_NULL_CHECK(iface);
    CIOT_ERR_NULL_CHECK(data);
    return CIOT_ERR__NOT_SUPPORTED;
}

ciot_err_t ciot_start(ciot_t self, ciot_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    if(self->status.state != CIOT__CIOT_STATE__CIOT_STATE_IDLE)
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
    CIOT_LOGI(TAG, "CIOT_STATE_IDLE");
    return CIOT_ERR__OK;
}

ciot_err_t ciot_set_event_handler(ciot_t self, ciot_iface_event_handler_fn event_handler, void *event_args)
{
    CIOT_ERR_NULL_CHECK(self);
    self->event_handler = event_handler;
    self->event_args = event_args;
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
        if(self->recv.sender != NULL && 
           self->recv.event.type == CIOT_IFACE_EVENT_STARTED && 
           self->starting.iface_id == self->recv.sender->info.id)
        {
            CIOT_LOGI(TAG, "Interface [%lu]:%s Started", self->recv.sender->info.id, ciot_iface_to_str(self->recv.sender));
            self->starting.iface_id++;
            self->starting.waiting_result = false;
        }
    }
    else
    {
        uint8_t id = self->starting.iface_id;
        ciot_iface_t *iface = self->ifaces.list[id];
        ciot_msg_data_t *cfg = self->ifaces.cfgs[id];
        ciot_err_t err = ciot_start_iface(self, iface, cfg);
        if (err == CIOT_ERR__OK)
        {
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
    if(self->recv.sender == NULL)
    {
        return CIOT_ERR__OK;
    }

    ciot_iface_event_t *event = &self->recv.event;
    ciot_iface_t *sender = self->recv.sender;

    if(sender->req_status.state != CIOT_IFACE_REQ_STATE_IDLE)
    {
        if(ciot_iface_event_is_ack(event) &&
           ciot_iface_is_equal(&sender->info, event->msg->iface) &&
           sender->req_status.id == event->msg->id)
        {
            sender->req_status.state = CIOT_IFACE_REQ_STATE_IDLE;
            if(sender->req_status.state == CIOT_IFACE_REQ_STATE_SENDED)
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

    if(event->type == CIOT_IFACE_EVENT_REQUEST)
    {
        CIOT_LOG_MSG_P(TAG, CIOT_LOGV, "RX REQ <- ", sender, event->msg);
        uint8_t id = event->msg->iface->id;
        if(id < self->ifaces.count && event->msg->type <= CIOT__MSG_TYPE__MSG_TYPE_REQUEST)
        {
            ciot_iface_t *iface = self->ifaces.list[id];
            if(iface != NULL)
            {
                ciot_iface_process_msg(iface, event->msg, sender);
                if(iface->req_status.state == CIOT_IFACE_REQ_STATE_IDLE)
                {
                    event->type = CIOT_IFACE_EVENT_DONE;
                }
                else
                {
                    event->type = CIOT_IFACE_EVENT_ERROR;
                }
            }
        }
    }

    self->status.state = CIOT__CIOT_STATE__CIOT_STATE_STARTED;
    CIOT_LOGI(TAG, "CIOT_STATE_STARTED");

    return ciot_iface_send_event(sender, event);
}

static ciot_err_t ciot_start_iface(ciot_t self, ciot_iface_t *iface, ciot_msg_data_t *cfg)
{
    CIOT_ERR_NULL_CHECK(iface);
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
            ciot_err_t err = ciot_iface_set_event_handler(iface, ciot_iface_event_handler, self);
            if (err != CIOT_ERR__OK)
            {
                CIOT_LOGE(TAG, "Interface id:%d type%d register event error: %d", i, iface->info.type, err);
                ret = err;
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

    CIOT_LOGD(TAG, "%s(%lu) evt id: %d", ciot_iface_to_str(sender), sender->info.id, event->type);

    if (self->status.state == CIOT__CIOT_STATE__CIOT_STATE_BUSY)
    {
        CIOT_LOGE(TAG, "CIoT core is busy");
        return CIOT_ERR__BUSY;
    }

    if (event->type == CIOT_IFACE_EVENT_REQUEST || event->type == CIOT_IFACE_EVENT_DATA)
    {
        if (self->status.state != CIOT__CIOT_STATE__CIOT_STATE_STARTED)
        {
            CIOT_LOGE(TAG, "CIoT core is not started");
            return CIOT_ERR__BUSY;
        }
        if (sender->serializer != NULL)
        {
            sender->serializer->from_bytes(&self->recv.buf, event->data, event->size);
            self->recv.event.msg = &self->recv.buf;
        }
        else
        {
            ciot__msg__free_unpacked(self->recv.event.msg, NULL);
            self->recv.event.msg = ciot__msg__unpack(NULL, event->size, event->data);
        }
        self->status.state = CIOT__CIOT_STATE__CIOT_STATE_BUSY;
        CIOT_LOGI(TAG, "CIOT_STATE_BUSY");
    }

    self->recv.event.type = event->type;
    self->recv.sender = sender;

    return CIOT_ERR__OK;
}
