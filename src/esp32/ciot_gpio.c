/**
 * @file ciot_gpio.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_gpio.h"
#include "ciot_config.h"

#if CIOT_CONFIG_FEATURE_GPIO && defined(CIOT_TARGET_ESP32)

#include <string.h>
#include "driver/gpio.h"

struct ciot_gpio
{
    ciot_iface_t iface;
    ciot_gpio_cfg_t cfg;
    ciot_gpio_status_t status;
};

static const char *TAG = "ciot_gpio";

ciot_gpio_t ciot_gpio_new(void *handle)
{
    ciot_gpio_t self = calloc(1, sizeof(struct ciot_gpio));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_gpio_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_gpio_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_gpio_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_gpio_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(self->status);
    self->iface.info.type = CIOT_IFACE_TYPE_NTP;
    return self;
}

ciot_err_t ciot_gpio_start(ciot_gpio_t self, ciot_gpio_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);
    gpio_config_t gpio_cfg = {
        .pin_bit_mask = cfg->pin_mask,
        .mode = cfg->mode,
        .pull_down_en = cfg->pull == CIOT_GPIO_PULLDOWN,
        .pull_up_en = cfg->pull == CIOT_GPIO_PULLUP,
    };
    esp_err_t err = gpio_config(&gpio_cfg);
    if(err == ESP_OK)
    {
        memcpy(&self->cfg, &cfg, sizeof(cfg));
    }
    return err;
}

ciot_err_t ciot_gpio_stop(ciot_gpio_t self)
{
    CIOT_NULL_CHECK(self);
    gpio_config_t gpio_cfg = {
        .pin_bit_mask = self->cfg.pin_mask,
        .mode = GPIO_MODE_DISABLE,
        .pull_down_en = self->cfg.pull == CIOT_GPIO_PULLDOWN,
        .pull_up_en = self->cfg.pull == CIOT_GPIO_PULLUP,
    };
    esp_err_t err = gpio_config(&gpio_cfg);
    if(err == ESP_OK)
    {
        self->cfg.mode = CIOT_GPIO_MODE_DIABLED;
    }
    return err;
}

ciot_err_t ciot_gpio_process_req(ciot_gpio_t self, ciot_gpio_req_t *req)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(req);

    switch (req->type)
    {
    case CIOT_GPIO_REQ_UNKNOWN:
        return CIOT_ERR_INVALID_TYPE;
    case CIOT_GPIO_REQ_CONFIG:
        self->iface.base.req.status = CIOT_IFACE_REQ_STATUS_IDLE;
        return ciot_gpio_start(self, &req->data.config);
    case CIOT_GPIO_REQ_GET_STATE:
        req->data.get_state.state = ciot_gpio_get_state(self, req->data.get_state.num);
        self->iface.base.req.response_size = CIOT_MSG_GET_SIZE(req);
        self->iface.base.req.status = CIOT_IFACE_REQ_STATUS_IDLE;
        return CIOT_OK;
    default:
        return CIOT_ERR_INVALID_TYPE;
    }
}

ciot_err_t ciot_gpio_send_data(ciot_gpio_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_gpio_set_state(ciot_gpio_t self, int gpio, ciot_gpio_state_t state)
{
    return gpio_set_level(gpio, state);
}

ciot_gpio_state_t ciot_gpio_get_state(ciot_gpio_t self, int gpio)
{
    return gpio_get_level(gpio);
}

#endif
