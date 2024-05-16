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

#if CIOT_CONFIG_FEATURE_GPIO && (defined(CIOT_TARGET_WIN) || defined(CIOT_TARGET_LINUX))

#include <string.h>

struct ciot_gpio
{
    ciot_iface_t iface;
    ciot_gpio_cfg_t cfg;
    ciot_gpio_status_t status;
};

static const char *TAG = "ciot_gpio";

ciot_gpio_t self;

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
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_gpio_stop(ciot_gpio_t self)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_gpio_process_req(ciot_gpio_t self, ciot_gpio_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_gpio_send_data(ciot_gpio_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_gpio_set_state(ciot_gpio_t self, int gpio, ciot_gpio_state_t state)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_gpio_state_t ciot_gpio_get_state(ciot_gpio_t self, int gpio)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

#endif
