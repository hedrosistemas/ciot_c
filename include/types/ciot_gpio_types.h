/**
 * @file ciot_gpio_types.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __CIOT_GPIO_TYPES__H__
#define __CIOT_GPIO_TYPES__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

typedef enum __attribute__((packed))
{
    CIOT_GPIO_STATE_ERR=-1,
    CIOT_GPIO_STATE_LOW,
    CIOT_GPIO_STATE_HIGH
} ciot_gpio_state_t;

typedef enum __attribute__((packed))
{
    CIOT_GPIO_REQ_UNKNOWN,
    CIOT_GPIO_REQ_CONFIG,
    CIOT_GPIO_REQ_SET_STATE,
    CIOT_GPIO_REQ_GET_STATE,
} ciot_gpio_req_type_t;

typedef enum __attribute__((packed))
{
    CIOT_GPIO_MODE_DIABLED,
    CIOT_GPIO_MODE_INPUT,
    CIOT_GPIO_MODE_OUTPUT,
} ciot_gpio_mode_t;

typedef enum __attribute__((packed))
{
    CIOT_GPIO_PULL_DISABLED,
    CIOT_GPIO_PULLUP,
    CIOT_GPIO_PULLDOWN,
} ciot_gpio_pull_mode_t;

typedef struct __attribute__((packed))
{
    uint64_t pin_mask;
    ciot_gpio_mode_t mode;
    ciot_gpio_pull_mode_t pull;
} ciot_gpio_cfg_t;

typedef struct __attribute__((packed))
{
    uint64_t status_mask;
} ciot_gpio_status_t;

typedef struct __attribute__((packed))
{
    uint32_t num;
    ciot_gpio_state_t state;
} ciot_gpio_state_info_t;

typedef struct __attribute__((packed))
{
    uint32_t num;
} ciot_gpio_req_get_state_t;

typedef union __attribute__((packed))
{
    ciot_gpio_cfg_t config;
    ciot_gpio_state_info_t set_state;
    ciot_gpio_state_info_t get_state;
} ciot_gpio_req_data_u;

typedef struct __attribute__((packed))
{
    ciot_gpio_req_type_t type;
    ciot_gpio_req_data_u data;
} ciot_gpio_req_t;

typedef union __attribute__((packed))
{
    ciot_gpio_cfg_t config;
    ciot_gpio_status_t status;
    ciot_gpio_req_t request;
} ciot_gpio_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_GPIO_TYPES__H__