/**
 * @file ciot_gpio.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_GPIO__H__
#define __CIOT_GPIO__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_gpio_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef struct ciot_gpio *ciot_gpio_t;

typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;
    ciot_gpio_status_t status;
} ciot_gpio_status_msg_t;

ciot_gpio_t ciot_gpio_new(void *handle);
ciot_err_t ciot_gpio_start(ciot_gpio_t self, ciot_gpio_cfg_t *cfg);
ciot_err_t ciot_gpio_stop(ciot_gpio_t self);
ciot_err_t ciot_gpio_process_req(ciot_gpio_t self, ciot_gpio_req_t *req);
ciot_err_t ciot_gpio_send_data(ciot_gpio_t self, uint8_t *data, int size);

ciot_err_t ciot_gpio_set_state(ciot_gpio_t self, int gpio, ciot_gpio_state_t state);
ciot_gpio_state_t ciot_gpio_get_state(ciot_gpio_t self, int gpio);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_GPIO__H__