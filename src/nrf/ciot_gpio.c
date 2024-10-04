/**
 * @file ciot_gpio.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "ciot_gpio.h"
#include "ciot_err.h"

// static const char *TAG = "ciot_gpio";

struct ciot_gpio
{
    ciot_gpio_base_t base;
};

ciot_gpio_t ciot_gpio_new(void *handle)
{
    ciot_gpio_t self = calloc(1, sizeof(struct ciot_gpio));
    ciot_gpio_init(self);
    return self;
}

ciot_err_t ciot_gpio_start(ciot_gpio_t self, ciot_gpio_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_gpio_stop(ciot_gpio_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    return CIOT_ERR__NOT_IMPLEMENTED;
}
