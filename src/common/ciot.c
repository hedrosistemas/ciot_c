/**
 * @file ciot.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "ciot_log.h"
#include "ciot.h"

typedef struct
{
    ciot_iface_t iface;
    ciot_cfg_t cfg;
    ciot_status_t status;
} ciot_base_t;

typedef struct ciot_ifaces
{
    ciot_iface_t **list;
    void **cfgs;
    uint8_t count;
} ciot_ifaces_t;

struct ciot
{
    ciot_base_t base;
    ciot_ifaces_t ifaces;
    ciot_iface_event_handler_t *event_handler;
    void *event_args;
    ciot_state_t state;
    ciot_storage_t storage;
    int bridges_idx;
};

static ciot_err_t ciot_set_iface_list(ciot_t self, ciot_iface_t *ifaces[], int count);
static ciot_err_t ciot_ifaces_start(ciot_t self);
static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *event_args);

static ciot_err_t ciot_stop(ciot_t self);
static ciot_err_t ciot_process_req(ciot_t self, ciot_req_t *req);
static ciot_err_t ciot_send_data(ciot_t self, uint8_t *data, int size);

static const char *TAG = "ciot";

#ifdef CIOT_TARGET_WIN

#if defined(CIOT_TARGET_MONGOOSE)
#include "mongoose.h"
#endif

#include "windows.h"

void app_main();

int main(char **args)
{
#if defined(CIOT_TARGET_MONGOOSE)
    mg_mgr_init(CIOT_HANDLE);
#endif
    app_main();
}

#endif  //_WIN32

#ifdef  CIOT_TARGET_ARDUINO

void loop() {}

#endif  //CIOT_TARGET_ARDUINO

ciot_t ciot_new(void)
{
    ciot_t self = calloc(1, sizeof(struct ciot));
    self->base.iface.base.ptr = self;
    self->base.iface.base.start = (ciot_iface_start_fn *)ciot_start;
    self->base.iface.base.stop = (ciot_iface_stop_fn *)ciot_stop;
    self->base.iface.base.process_req = (ciot_iface_process_req_fn *)ciot_process_req;
    self->base.iface.base.send_data = (ciot_iface_send_data_fn *)ciot_send_data;
    self->base.iface.base.cfg.ptr = &self->base.cfg;
    self->base.iface.base.cfg.size = sizeof(self->base.cfg);
    self->base.iface.base.status.ptr = &self->base.status;
    self->base.iface.base.status.size = sizeof(self->base.status);
    self->base.iface.info.type = CIOT_IFACE_TYPE_CIOT;
    return self;
}

ciot_err_t ciot_start(ciot_t self, ciot_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);

    ciot_err_t ret = CIOT_OK;

    self->ifaces.cfgs = cfg->cfgs;

    ciot_err_t err = ciot_set_iface_list(self, cfg->ifaces, cfg->count);
    if (err != CIOT_OK)
    {
        CIOT_LOGE(TAG, "Set iface list error: %d", err);
        ret = err;
    }

    self->bridges_idx = -1;

    err = ciot_ifaces_start(self);
    if (err != CIOT_OK && err != CIOT_ERR_NOT_IMPLEMENTED)
    {
        CIOT_LOGE(TAG, "Ifaces start error: %d", err);
        ret = err;
    }

    return ret;
}

ciot_err_t ciot_set_storage(ciot_t self, ciot_storage_t storage)
{
    CIOT_NULL_CHECK(self);
    self->storage = storage;
    return CIOT_OK;
}

ciot_err_t ciot_register_event(ciot_t self, ciot_iface_event_handler_t event_handler, void *event_args)
{
    CIOT_NULL_CHECK(self);
    self->event_handler = event_handler;
    self->event_args = event_args;
    return CIOT_OK;
}

static ciot_err_t ciot_set_iface_list(ciot_t self, ciot_iface_t *ifaces[], int count)
{
    self->ifaces.list = ifaces;
    self->ifaces.count = count;

    ciot_err_t ret = CIOT_OK;

    for (size_t i = 0; i < count; i++)
    {
        if (self->ifaces.list[i] != NULL)
        {
            self->ifaces.list[i]->info.id = i;
            ciot_err_t err = ciot_iface_register_event(self->ifaces.list[i], ciot_iface_event_handler, self);
            if (err != CIOT_OK)
            {
                CIOT_LOGE(TAG, "Interface id:%d type%d register event error: %d", i, self->ifaces.list[i]->info.type, err);
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

static ciot_err_t ciot_ifaces_start(ciot_t self)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(self->ifaces.list);

    ciot_err_t ret = CIOT_OK;

    if (self->ifaces.count > 0)
    {
        for (size_t i = 0; i < self->ifaces.count; i++)
        {
#if CIOT_CONFIG_FEATURE_STORAGE
            if (self->storage != NULL && self->ifaces.list[i] != NULL)
            {
                char filepath[32] = {0};
                sprintf(filepath, "iface_cfg_%d.dat", i);
                ciot_err_t err = ciot_storage_load(self->storage, filepath, (uint8_t *)self->ifaces.list[i]->base.cfg.ptr, self->ifaces.list[i]->base.cfg.size);
                if (err == CIOT_OK)
                {
                    CIOT_LOGI(TAG, "file: %s founded. loading cfg file into interface id %d type %s", filepath, i, ciot_iface_to_str(self->ifaces.list[i]));
                    self->ifaces.cfgs[i] = self->ifaces.list[i]->base.cfg.ptr;
                }
            }
#endif
            if (self->ifaces.list[i] != NULL && self->ifaces.cfgs[i] != NULL)
            {
                ciot_err_t err = self->ifaces.list[i]->base.start(self->ifaces.list[i], (ciot_msg_data_u *)self->ifaces.cfgs[i]);
                if (err != CIOT_OK && err != CIOT_ERR_NOT_IMPLEMENTED)
                {
                    CIOT_LOGE(TAG, "Interface id:%d type:%d cannot start. Error: %d", i, self->ifaces.list[i]->info.type, err);
                    ret = err;
                }
                else if(self->ifaces.list[i]->info.type == CIOT_IFACE_TYPE_BRIDGE && self->bridges_idx == CIOT_BRIDGE_NULL_TARGET)
                {
                    self->bridges_idx = i;
                }
            }
        }
    }

    return ret;
}

static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *event_args)
{
    ciot_t self = (ciot_t)event_args;

    if(sender->base.req.status == CIOT_IFACE_REQ_STATUS_SENDED)
    {
        bool iface_equal = memcmp(&sender->base.req.iface, &event->data->msg.iface, sizeof(ciot_msg_iface_info_t)) == 0;
        bool type_equal = sender->base.req.type == event->data->msg.type;
        bool id_equal = sender->base.req.id == event->data->msg.id;
        bool error = event->data->msg.type == CIOT_MSG_TYPE_ERROR;
        if(!id_equal)
        {
            CIOT_LOGE(TAG, "Invalid response id: %d. Expecteded: %d", event->data->msg.id, sender->base.req.id);
        }
        if(iface_equal && id_equal && (type_equal || error))
        {
            sender->base.req.status = CIOT_IFACE_REQ_STATUS_IDLE;
            event->id = CIOT_IFACE_EVENT_DONE;

            if(error)
            {
                CIOT_LOGV(TAG, "RX ERR <- id:%d sender:%s msgt:%s iface:%s error:%s", 
                    event->data->msg.id,
                    ciot_iface_to_str(sender),
                    ciot_msg_type_to_str(&event->data->msg),
                    ciot_iface_type_to_str(event->data->msg.iface.type),
                    ciot_err_to_message(event->data->msg.data.error.code));
            }
            else
            {
                CIOT_LOGV(TAG, "RX RSP <- id:%d sender:%s msgt:%s iface:%s", 
                    event->data->msg.id,
                    ciot_iface_to_str(sender),
                    ciot_msg_type_to_str(&event->data->msg),
                    ciot_iface_type_to_str(event->data->msg.iface.type));
            }
        }
    }

    if(sender->base.req.status == CIOT_IFACE_REQ_STATUS_RECEIVED)
    {
        bool type_equal = sender->base.req.type == event->data->msg.type;
        bool error = event->id == CIOT_IFACE_EVENT_ERROR || event->data->msg.type == CIOT_MSG_TYPE_ERROR;
        if(type_equal || error)
        {
            int iface_id = sender->base.req.iface.id;
            sender->base.req.status = CIOT_IFACE_REQ_STATUS_IDLE;
            event->data->msg.id = sender->base.req.id;
            ciot_iface_send_rsp(self->ifaces.list[iface_id], (ciot_msg_t*)event->data, event->size);
        }
    }

    if (event->id == CIOT_IFACE_EVENT_REQUEST)
    {
        CIOT_LOGV(TAG, "RX REQ <- id:%d sender:%s msgt:%s iface:%s", 
                event->data->msg.id,
                ciot_iface_to_str(sender),
                ciot_msg_type_to_str(&event->data->msg),
                ciot_iface_type_to_str(event->data->msg.iface.type));

        if(event->data->msg.type < CIOT_MSG_TYPE_CUSTOM)
        {
            uint8_t id = event->data->msg.iface.id;
            ciot_err_t err = ciot_iface_process_msg(self->ifaces.list[id], &event->data->msg, sender);
            if(self->ifaces.list[id]->base.req.status == CIOT_IFACE_REQ_STATUS_IDLE)
            {
                event->id = CIOT_IFACE_EVENT_DONE;
            }
            else
            {
                return err;
            }
        }
    }

    if (event->id == CIOT_IFACE_EVENT_DATA && self->bridges_idx != CIOT_BRIDGE_NULL_TARGET)
    {
        for (size_t i = self->bridges_idx; i < self->ifaces.count; i++)
        {
            if(self->ifaces.list[i]->info.type == CIOT_IFACE_TYPE_BRIDGE)
            {
                int target_id = ciot_bridge_get_target_id((ciot_bridge_t)self->ifaces.list[i], sender->info.id);
                if(target_id != CIOT_BRIDGE_NULL_TARGET) {
                    ciot_iface_send_data(self->ifaces.list[target_id], event->data, event->size);
                }
            }
        }
    }
    
    if (self->event_handler != NULL)
    {
        return self->event_handler(sender, event, self->event_args);
    }

    return CIOT_OK;
}

static ciot_err_t ciot_stop(ciot_t self)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

static ciot_err_t ciot_process_req(ciot_t self, ciot_req_t *req)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(req);

    switch (req->type)
    {
    case CIOT_REQ_UNKNOWN:
        return CIOT_ERR_INVALID_ID;
#if CIOT_CONFIG_FEATURE_STORAGE
    case CIOT_REQ_SAVE_IFACE_CFG:
    {
        CIOT_NULL_CHECK(self->storage);
        char filepath[32];
        int iface_id = req->data.save_iface_cfg.iface_id;
        sprintf(filepath, "iface_cfg_%d.dat", iface_id);
        req->data.result.err = ciot_storage_save(self->storage, filepath, (uint8_t *)self->ifaces.list[iface_id]->base.cfg.ptr, self->ifaces.list[iface_id]->base.cfg.size);
        self->base.iface.base.req.status = CIOT_IFACE_REQ_STATUS_IDLE;
        break;
    }
    case CIOT_REQ_DELETE_IFACE_CFG:
    {
        CIOT_NULL_CHECK(self->storage);
        char filepath[32];
        int iface_id = req->data.save_iface_cfg.iface_id;
        sprintf(filepath, "iface_cfg_%d.dat", iface_id);
        req->data.result.err = ciot_storage_delete(self->storage, filepath);
        self->base.iface.base.req.status = CIOT_IFACE_REQ_STATUS_IDLE;
        break;
    }
#endif // CIOT_CONFIG_FEATURE_STORAGE
    case CIOT_REQ_PROXY_MSG:
    {
        ciot_msg_t *msg = (ciot_msg_t*)req->data.proxy_msg.data;
        ciot_iface_send_req(self->ifaces.list[msg->iface.id], msg, req->data.proxy_msg.size);
        break;
    }
    default:
        break;
    }

    return req->data.result.err;
}

static ciot_err_t ciot_send_data(ciot_t self, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(data);
    return CIOT_ERR_NOT_SUPPORTED;
}
