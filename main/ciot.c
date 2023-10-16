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
};

static ciot_err_t ciot_iface_event_handler(void *sender, ciot_iface_event_t *event, void *event_args);

ciot_t ciot_new(void)
{
    return calloc(1, sizeof(struct ciot_n));
}

ciot_err_t ciot_set_iface_list(ciot_t this, ciot_iface_t *iface_list[], int count)
{
    this->iface_list.items = iface_list;
    this->iface_list.count = count;

    for (size_t i = 0; i < count; i++)
    {
        this->iface_list.items[i]->info.id = i;
        ciot_iface_register_event(this->iface_list.items[i], ciot_iface_event_handler, this);
    }

    return CIOT_OK;
}

ciot_err_t ciot_register_event(ciot_t this, ciot_iface_event_handler_t event_handler, void *event_args)
{
    CIOT_ERR_NULL_CHECK(this);
    this->event_handler = event_handler;
    this->event_args = event_args;
    return CIOT_OK;
}

static ciot_err_t ciot_iface_event_handler(void *sender, ciot_iface_event_t *event, void *event_args)
{
    ciot_t this = event_args;
    ciot_err_t err = CIOT_OK;
    ciot_iface_t *iface_snd = sender;
    ciot_iface_t *iface_rcv = this->iface_list.items[event->msg.iface.id];

    if (this->state == CIOT_STATE_BUSY && this->iface_busy->info.id != iface_snd->info.id)
    {
        event->msg.error = CIOT_ERR_BUSY;
        event->msg.iface = this->iface_busy->info;
        event->size = CIOT_MSG_SIZE;
        err = ciot_iface_send_data(iface_snd, &event->msg, event->size);
    }

    if (event->msg.iface.id >= this->iface_list.count)
    {
        event->msg.error = CIOT_ERR_INVALID_ID;
        event->size = CIOT_MSG_SIZE;
        err = ciot_iface_send_data(this->iface_rsp, &event->msg, event->size);
    }

    switch (event->id)
    {
    case CIOT_IFACE_EVENT_UNKNOWN:
        err = CIOT_ERR_INVALID_ID;
        break;
    case CIOT_IFACE_EVENT_STARTED:
    case CIOT_IFACE_EVENT_STOPPED:
    case CIOT_IFACE_EVENT_ERROR:
        if(this->state == CIOT_STATE_BUSY)
        {
            if(this->iface_busy->info.id == iface_snd->info.id)
            {
                this->state = CIOT_STATE_IDLE;
                err = ciot_iface_send_data(this->iface_rsp, &event->msg, event->size);
            }
        }
    case CIOT_IFACE_EVENT_DATA:
        if(this->state != CIOT_STATE_BUSY)
        {
            if(event->msg.type == CIOT_MSG_TYPE_GET_CONFIG || event->msg.type == CIOT_MSG_TYPE_GET_STATUS)
            {
                ciot_iface_process_msg(iface_rcv, &event->msg, &event->size);
                event->msg.iface = iface_rcv->info;
                err = ciot_iface_send_data(iface_snd, &event->msg, event->size);
            }
            else
            {
                this->state = CIOT_STATE_BUSY;
                this->iface_rsp = sender;
            }
        }
        else if(this->iface_busy->info.id == iface_snd->info.id)
        {
            this->state = CIOT_STATE_IDLE;
            err = ciot_iface_send_data(this->iface_rsp, &event->msg, event->size);
        }
        break;
    case CIOT_IFACE_EVENT_CUSTOM:
        
        break;
    }

    if(this->event_handler != NULL)
    {
        this->event_handler(this, event, this->event_args);
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
    //         this->iface_rsp = iface_snd;
    //         this->iface_busy = iface_rcv;
    //         this->state = CIOT_STATE_BUSY;
    //         return ciot_iface_process_msg(iface_rcv, &event->msg, &event->size);
    //     }
    //     break;
    // case CIOT_IFACE_EVENT_RESPONSE:
    //     if (this->state == CIOT_STATE_BUSY)
    //     {
    //         this->state = CIOT_STATE_IDLE;
    //         event->msg.iface = iface_rcv->info;
    //         return ciot_iface_send_data(this->iface_rsp, &event->msg, event->size);
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
