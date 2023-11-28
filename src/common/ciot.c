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

struct ciot
{
    ciot_iface_t **ifaces;
    const void **cfgs;
    int ifaces_count;
    ciot_iface_event_handler_t *event_handler;
    void *event_args;
    ciot_state_t state;
    ciot_storage_t storage;
    int bridges_idx;
};

static ciot_err_t ciot_set_iface_list(ciot_t self, ciot_iface_t *ifaces[], int count);
static ciot_err_t ciot_ifaces_start(ciot_t self);
static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *event_args);

static const char *TAG = "ciot";

ciot_t ciot_new(void)
{
    return calloc(1, sizeof(struct ciot));
}

ciot_err_t ciot_start(ciot_t self, ciot_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);

    ciot_err_t ret = CIOT_OK;

    self->cfgs = cfg->cfgs;

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
    self->ifaces = ifaces;
    self->ifaces_count = count;

    ciot_err_t ret = CIOT_OK;

    for (size_t i = 0; i < count; i++)
    {
        if (self->ifaces[i] != NULL)
        {
            self->ifaces[i]->info.id = i;
            ciot_err_t err = ciot_iface_register_event(self->ifaces[i], ciot_iface_event_handler, self);
            if (err != CIOT_OK)
            {
                CIOT_LOGE(TAG, "Interface id:%d type%d register event error: %d", i, self->ifaces[i]->info.type, err);
                ret = err;
            }
        }
        else
        {
            CIOT_LOGE(TAG, "Interface with id %d is null.", i);
            ret = CIOT_ERR_NULL_ARG;
        }
    }

    return ret;
}

static ciot_err_t ciot_ifaces_start(ciot_t self)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(self->ifaces);

    ciot_err_t ret = CIOT_OK;

    if (self->ifaces_count > 0)
    {
        for (size_t i = 0; i < self->ifaces_count; i++)
        {
#if CIOT_CONFIG_FETURE_STORAGE
            if (self->storage != NULL)
            {
                char filepath[32];
                sprintf(filepath, "iface_cfg_%d.dat", i);
                ciot_err_t err = ciot_storage_load(self->storage, filepath, (uint8_t *)self->cfgs[i], self->ifaces[i]->base.cfg.size);
                if (err == CIOT_OK)
                {
                    CIOT_LOGI(TAG, "file:%s founded. loading cfg file into interface id:%d type:%d", filepath, i, self->ifaces[i]->info.type);
                }
            }
#endif
            if (self->ifaces[i] != NULL && self->cfgs[i] != NULL)
            {
                ciot_err_t err = self->ifaces[i]->base.start(self->ifaces[i], (ciot_msg_data_u *)self->cfgs[i]);
                if (err != CIOT_OK && err != CIOT_ERR_NOT_IMPLEMENTED)
                {
                    CIOT_LOGE(TAG, "Interface id:%d type:%d cannot start. Error: %d", i, self->ifaces[i]->info.type, err);
                    ret = err;
                }
                else if(self->ifaces[i]->info.type == CIOT_IFACE_TYPE_BRIDGE && self->bridges_idx == CIOT_BRIDGE_NULL_TARGET)
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

    if (sender->base.req.pending)
    {
        bool iface_equal = memcmp(&sender->base.req.iface, &event->data->request.iface, sizeof(ciot_msg_iface_info_t)) == 0;
        bool type_equal = sender->base.req.type == event->data->request.type;
        bool error = event->data->request.type == CIOT_MSG_TYPE_ERROR;
        if(iface_equal && (type_equal || error))
        {
            sender->base.req.pending = false;
            event->id = CIOT_IFACE_EVENT_DONE;
        }
        else
        {
            return CIOT_ERR_BUSY;
        }
    }

    if (event->id == CIOT_IFACE_EVENT_REQUEST)
    {
        uint8_t id = event->data->request.iface.id;
        return ciot_iface_process_msg(self->ifaces[id], &event->data->request, sender);
    }

    if (event->id == CIOT_IFACE_EVENT_DATA && self->bridges_idx != CIOT_BRIDGE_NULL_TARGET)
    {
        for (size_t i = self->bridges_idx; i < self->ifaces_count; i++)
        {
            if(self->ifaces[i]->info.type == CIOT_IFACE_TYPE_BRIDGE)
            {
                int target_id = ciot_bridge_get_target_id((ciot_bridge_t)self->ifaces[i], sender->info.id);
                if(target_id != CIOT_BRIDGE_NULL_TARGET) {
                    ciot_iface_send_data(self->ifaces[target_id], event->data, event->size);
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
