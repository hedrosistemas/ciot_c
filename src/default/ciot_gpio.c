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

static int set_bit(int bit_position, int value);
static int get_bit(int bit_position);
static uint64_t states_mask;
struct ciot_gpio
{
    ciot_gpio_base_t base;
};

ciot_gpio_t ciot_gpio_new(void *handle, int count)
{
    ciot_gpio_t self = calloc(1, sizeof(struct ciot_gpio));
    ciot_gpio_init(self, count);
    self->base.set_state = (ciot_hal_gpio_set_state_fn*)set_bit;
    self->base.get_state = get_bit;
    return self;
}

ciot_err_t ciot_gpio_start(ciot_gpio_t self, ciot_gpio_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    return ciot_gpio_set_cfg(self, cfg);
}

ciot_err_t ciot_gpio_stop(ciot_gpio_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    return CIOT_ERR_NOT_IMPLEMENTED;
}

static int set_bit(int bit_position, int value)
{
    if (value)
    {
        states_mask |= (1ULL << bit_position);
    }
    else
    {
        states_mask &= ~(1ULL << bit_position);
    }
    return 0;
}

static int get_bit(int bit_position)
{
    return (states_mask >> bit_position) & 1ULL;
}
