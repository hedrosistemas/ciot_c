/**
 * @file ciot_s.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdlib.h>
#include <stdbool.h>

#include "ciot_log.h"
#include "ciot.h"

struct ciot_s
{
    ciot_iface_t **ifaces;
    int ifaces_count;
    ciot_iface_event_handler_t *event_handler;
    void *event_args;
    ciot_state_t state;
    // TODO:
    // void *iface_id_queue;  // Queue of ifaces id that have sended an event to ciot
};

static ciot_err_t ciot_iface_event_handler(void *sender, ciot_iface_event_t *event, void *event_args);

static const char *TAG = "ciot";

ciot_t ciot_new(void)
{
    return calloc(1, sizeof(struct ciot_s));
}

ciot_err_t ciot_set_iface_list(ciot_t self, ciot_iface_t *ifaces[], int count)
{
    self->ifaces = ifaces;
    self->ifaces_count = count;

    for (size_t i = 0; i < count; i++)
    {
        self->ifaces[i]->info.id = i;
        ciot_iface_register_event(self->ifaces[i], ciot_iface_event_handler, self);
    }

    return CIOT_OK;
}

ciot_err_t ciot_register_event(ciot_t self, ciot_iface_event_handler_t event_handler, void *event_args)
{
    CIOT_NULL_CHECK(self);
    self->event_handler = event_handler;
    self->event_args = event_args;
    return CIOT_OK;
}

/*
    TODO: implementar uma fila de eventos
*/
static ciot_err_t ciot_iface_event_handler(void *sender, ciot_iface_event_t *event, void *event_args)
{
    ciot_t self = (ciot_t)event_args;

    if (event->id == CIOT_IFACE_EVENT_DATA)
    {
        uint8_t id = event->msg.iface.id;
        ciot_msg_iface_type_t type = event->msg.iface.type;
        if(self->ifaces[id]->info.type == type)
        {
            return ciot_iface_send_data(self->ifaces[id], &event->msg, event->size);
        }
        else
        {
            CIOT_LOGE(TAG, "Invalid type at iface[%d]", id);
            return CIOT_ERR_INVALID_TYPE;
        }
    }
    else if(self->event_handler != NULL)
    {
        return self->event_handler(sender, event, self->event_args);
    }
}
