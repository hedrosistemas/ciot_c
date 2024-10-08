/**
 * @file ciot_gpio.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_GPIO__H__
#define __CIOT_GPIO__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"

#include "ciot/proto/v1/gpio.pb-c.h"

typedef struct ciot_gpio *ciot_gpio_t;
typedef Ciot__GpioCfg ciot_gpio_cfg_t;
typedef Ciot__GpioReq ciot_gpio_req_t;
typedef Ciot__GpioStatus ciot_gpio_status_t;
typedef Ciot__GpioData ciot_gpio_data_t;
typedef Ciot__GpioState ciot_gpio_state_t;
typedef Ciot__GpioPull ciot_gpio_pull_t;

typedef int (ciot_hal_gpio_set_state_fn)(int num, int state);
typedef int (ciot_hal_gpio_get_state_fn)(int num);

typedef struct ciot_gpio_base
{
    ciot_iface_t iface;
    ciot_gpio_cfg_t cfg;
    ciot_gpio_status_t status;
    ciot_gpio_req_t req;
    ciot_gpio_data_t data;
    ciot_hal_gpio_set_state_fn *set_state;
    ciot_hal_gpio_get_state_fn *get_state;
    uint8_t *gpio_states;
    uint8_t *gpio_pins;
    uint8_t *gpio_modes;
    uint8_t *gpio_pull;
    uint64_t timer;
    bool blink;
} ciot_gpio_base_t;

ciot_gpio_t ciot_gpio_new(void *handle, int count);
ciot_err_t ciot_gpio_init(ciot_gpio_t self, int count);
ciot_err_t ciot_gpio_task(ciot_gpio_t self);
ciot_err_t ciot_gpio_start(ciot_gpio_t self, ciot_gpio_cfg_t *cfg);
ciot_err_t ciot_gpio_stop(ciot_gpio_t self);
ciot_err_t ciot_gpio_process_req(ciot_gpio_t self, ciot_gpio_req_t *req);
ciot_err_t ciot_gpio_set_cfg(ciot_gpio_t self, ciot_gpio_cfg_t *cfg);
ciot_err_t ciot_gpio_get_cfg(ciot_gpio_t self, ciot_gpio_cfg_t *cfg);
ciot_err_t ciot_gpio_get_status(ciot_gpio_t self, ciot_gpio_status_t *status);
ciot_err_t ciot_gpio_set_state(ciot_gpio_t self, uint16_t id, ciot_gpio_state_t state);
ciot_gpio_state_t ciot_gpio_get_state(ciot_gpio_t self, uint16_t id);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_GPIO__H__