/**
 * @file ciot_gpio_base.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include <string.h>
#include "ciot_gpio.h"
#include "ciot_config.h"
#include "ciot_timer.h"

static const char *TAG = "ciot_gpio";

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);

ciot_err_t ciot_gpio_init(ciot_gpio_t self, int count)
{
    ciot_gpio_base_t *base = (ciot_gpio_base_t*)self;

    CIOT_LOGI(TAG, "Init");

    ciot_iface_init(&base->iface);
    ciot__gpio_data__init(&base->data);
    ciot__gpio_cfg__init(&base->cfg);
    ciot__gpio_status__init(&base->status);

    base->iface.ptr = self;
    base->iface.process_req = ciot_iface_process_req;
    base->iface.get_data = ciot_iface_get_data;
    base->iface.send_data = ciot_iface_send_data;
    base->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_CUSTOM;

    base->gpio_pins = calloc(count, sizeof(uint8_t));
    base->gpio_modes = calloc(count, sizeof(uint8_t));
    base->gpio_pull = calloc(count, sizeof(uint8_t));
    base->gpio_states = calloc(count, sizeof(uint8_t));

    base->cfg.pins.data = base->gpio_pins;
    base->cfg.modes.data = base->gpio_modes;
    base->cfg.pull.data = base->gpio_pull;
    base->status.states.data = base->gpio_states;

    base->cfg.pins.len = count;
    base->cfg.modes.len = count;
    base->cfg.pull.len = count;
    base->status.states.len = count;

    return CIOT_ERR__OK;
}

ciot_err_t ciot_gpio_task(ciot_gpio_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    ciot_gpio_base_t *base = (ciot_gpio_base_t*)self;

    if(ciot_timer_millis() > base->timer)
    {
        base->timer = ciot_timer_millis() + base->cfg.blink_interval;

        if(base->blink)
        {
            base->blink = false;
            for (size_t i = 0; i < base->cfg.pins.len; i++)
            {
                if(base->cfg.modes.data[i] == CIOT__GPIO_MODE__GPIO_MODE_INPUT ||
                   base->cfg.modes.data[i] == CIOT__GPIO_MODE__GPIO_MODE_DISABLED)
                {
                    continue;
                }

                int num = base->cfg.pins.data[i];
                ciot_gpio_state_t state = base->status.states.data[i];

                if(state == CIOT__GPIO_STATE__GPIO_STATE_LOW || state == CIOT__GPIO_STATE__GPIO_STATE_HIGH)
                {
                    base->set_state(num, state);
                    base->status.states.data[i] = state;
                }

                if(state == CIOT__GPIO_STATE__GPIO_STATE_BLINKING)
                {
                    base->set_state(num, !base->get_state(num));
                    base->blink = true;
                }
            }
        }
    }

    if(ciot_timer_millis() < base->cfg.blink_interval)
    {
        base->timer = 0;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
{
    ciot_gpio_t self = iface->ptr;

    switch (req->type)
    {
        case CIOT__MSG_TYPE__MSG_TYPE_START:
            return ciot_gpio_start(self, req->data->gpio->config);
        case CIOT__MSG_TYPE__MSG_TYPE_STOP:
            return ciot_gpio_stop(self);
        case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
            return ciot_gpio_process_req(self, req->data->gpio->request);
    default:
        break;
    }
    
    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_gpio_base_t *self = iface->ptr;

    self->data.config = NULL;
    self->data.status = NULL;
    self->data.request = NULL;

    switch (msg->type)
    {
    case CIOT__MSG_TYPE__MSG_TYPE_CONFIG:
        self->data.config = &self->cfg;
        break;
    case CIOT__MSG_TYPE__MSG_TYPE_STATUS:
        self->data.status = &self->status;
        break;
    default:
        break;
    }

    self->iface.data.gpio = &self->data;
    msg->data = &self->iface.data;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_gpio_process_req(ciot_gpio_t self, ciot_gpio_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_gpio_set_cfg(ciot_gpio_t self, ciot_gpio_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    CIOT_ERR_VALUE_CHECK(cfg->pins.len, cfg->pins.len, CIOT_ERR__INVALID_ARG);
    ciot_gpio_base_t *base = (ciot_gpio_base_t*)self;
    memcpy(base->cfg.pins.data, cfg->pins.data, cfg->pins.len);
    memcpy(base->cfg.modes.data, cfg->modes.data, cfg->pins.len);
    memcpy(base->cfg.pull.data, cfg->pull.data, cfg->pins.len);
    base->cfg.blink_interval = cfg->blink_interval;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_gpio_get_cfg(ciot_gpio_t self, ciot_gpio_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    ciot_gpio_base_t *base = (ciot_gpio_base_t*)self;
    *cfg = base->cfg;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_gpio_get_status(ciot_gpio_t self, ciot_gpio_status_t *status)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    ciot_gpio_base_t *base = (ciot_gpio_base_t*)self;
    *status = base->status;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_gpio_set_state(ciot_gpio_t self, uint16_t id, ciot_gpio_state_t state)
{
    CIOT_ERR_NULL_CHECK(self);
    ciot_gpio_base_t *base = (ciot_gpio_base_t*)self;
    int num = base->cfg.pins.data[id];

    if(state == CIOT__GPIO_STATE__GPIO_STATE_LOW || state == CIOT__GPIO_STATE__GPIO_STATE_HIGH)
    {
        base->set_state(num, state);
        base->status.states.data[id] = state;
    }

    if(state == CIOT__GPIO_STATE__GPIO_STATE_BLINK && base->status.states.data[id] != CIOT__GPIO_STATE__GPIO_STATE_BLINKING)
    {
        base->blink = true;
        base->set_state(num, !base->get_state(num));
    }

    if(state == CIOT__GPIO_STATE__GPIO_STATE_BLINKING)
    {
        base->blink = true;
        base->status.states.data[id] = state;
    }

    return CIOT_ERR__OK;
}

ciot_gpio_state_t ciot_gpio_get_state(ciot_gpio_t self, uint16_t id)
{
    CIOT_ERR_NULL_CHECK(self);
    ciot_gpio_base_t *base = (ciot_gpio_base_t*)self;
    CIOT_ERR_NULL_CHECK(base->get_state);
    int num = base->cfg.pins.data[id];
    return base->get_state(num);
}
