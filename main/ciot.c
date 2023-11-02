/**
 * @file ciot_n.c
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
#include "ciot.h"

typedef struct ciot_iface_list
{
    ciot_iface_t **items;
    int count;
} ciot_iface_list_t;

struct ciot_n
{
    ciot_iface_list_t iface_list;
    ciot_iface_t *iface_rsp;
    ciot_iface_t *iface_busy;
    ciot_iface_event_handler_t *event_handler;
    void *event_args;
    ciot_state_t state;

    // TODO:
    // void *iface_id_queue;  // Queue of ifaces id that have sended an event to ciot
};

static ciot_err_t ciot_iface_event_handler(void *sender, ciot_iface_event_t *event, void *event_args);

ciot_t ciot_new(void)
{
    return calloc(1, sizeof(struct ciot_n));
}

ciot_err_t ciot_set_iface_list(ciot_t self, ciot_iface_t *iface_list[], int count)
{
    self->iface_list.items = iface_list;
    self->iface_list.count = count;

    for (size_t i = 0; i < count; i++)
    {
        self->iface_list.items[i]->info.id = i;
        ciot_iface_register_event(self->iface_list.items[i], ciot_iface_event_handler, self);
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
    ciot_t self = event_args;
    ciot_err_t err = CIOT_OK;
    ciot_iface_t *iface_snd = sender;
    ciot_iface_t *iface_rcv = self->iface_list.items[event->msg.iface.id];

    if (self->state == CIOT_STATE_BUSY && self->iface_busy->info.id != iface_snd->info.id)
    {
        event->msg.error = CIOT_ERR_BUSY;
        event->msg.iface = self->iface_busy->info;
        event->size = CIOT_MSG_SIZE;
        err = ciot_iface_send_data(iface_snd, &event->msg, event->size);
    }

    if (event->msg.iface.id >= self->iface_list.count)
    {
        event->msg.error = CIOT_ERR_INVALID_ID;
        event->size = CIOT_MSG_SIZE;
        err = ciot_iface_send_data(self->iface_rsp, &event->msg, event->size);
    }

    switch (event->id)
    {
    case CIOT_IFACE_EVENT_UNKNOWN:
        err = CIOT_ERR_INVALID_ID;
        break;
    case CIOT_IFACE_EVENT_STARTED:
    case CIOT_IFACE_EVENT_STOPPED:
    case CIOT_IFACE_EVENT_ERROR:
        if(self->state == CIOT_STATE_BUSY)
        {
            if(self->iface_busy->info.id == iface_snd->info.id)
            {
                self->state = CIOT_STATE_IDLE;
                err = ciot_iface_send_data(self->iface_rsp, &event->msg, event->size);
            }
        }
        break;
    case CIOT_IFACE_EVENT_DATA:
    case CIOT_IFACE_EVENT_REQ_DONE:
        if(self->state != CIOT_STATE_BUSY)
        {
            if(event->msg.type == CIOT_MSG_TYPE_GET_CONFIG || event->msg.type == CIOT_MSG_TYPE_GET_STATUS)
            {
                ciot_iface_process_msg(iface_rcv, &event->msg, &event->size);
                event->msg.iface = iface_rcv->info;
                err = ciot_iface_send_data(iface_snd, &event->msg, event->size);
            }
            else
            {
                self->state = CIOT_STATE_BUSY;
                self->iface_rsp = sender;
            }
        }
        else if(self->iface_busy->info.id == iface_snd->info.id)
        {
            self->state = CIOT_STATE_IDLE;
            err = ciot_iface_send_data(self->iface_rsp, &event->msg, event->size);
        }
        break;
    case CIOT_IFACE_EVENT_CUSTOM:
        
        break;
    }

    if(self->event_handler != NULL)
    {
        self->event_handler(self, event, self->event_args);
    }

    return err;

    // switch (event->id)
    // {
    // case CIOT_IFACE_EVENT_REQUEST:
    //     if (sync_msg)
    //     {
    //         ciot_iface_process_msg(iface_rcv, &event->msg, &event->size);
    //         event->msg.iface = iface_rcv->info;
    //         return ciot_iface_send_data(iface_snd, &event->msg, event->size);
    //     }
    //     else
    //     {
    //         self->iface_rsp = iface_snd;
    //         self->iface_busy = iface_rcv;
    //         self->state = CIOT_STATE_BUSY;
    //         return ciot_iface_process_msg(iface_rcv, &event->msg, &event->size);
    //     }
    //     break;
    // case CIOT_IFACE_EVENT_RESPONSE:
    //     if (self->state == CIOT_STATE_BUSY)
    //     {
    //         self->state = CIOT_STATE_IDLE;
    //         event->msg.iface = iface_rcv->info;
    //         return ciot_iface_send_data(self->iface_rsp, &event->msg, event->size);
    //     }
    //     else
    //     {
    //         return CIOT_ERR_INVALID_ID;
    //     }
    // case CIOT_IFACE_EVENT_CUSTOM:
    //     // return custom event to main application
    //     return CIOT_OK;
    // default:
    //     event->msg.error = CIOT_ERR_INVALID_TYPE;
    //     return ciot_iface_send_data(iface_snd, &event->msg, CIOT_MSG_SIZE);
    // }
}
