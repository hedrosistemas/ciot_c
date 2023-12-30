/**
 * @file main.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-12-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MAIN__H__
#define __MAIN__H__

#include <Arduino.h>

#include "ciot.h"
#include "ciot_sys.h"
#include "ciot_uart.h"
#include "ciot_config.h"

#define APP_CONFIG_SYSTEM \
    {                     \
    }

#define APP_CONFIG_UART      \
    {                        \
        .baud_rate = 115200, \
    }

typedef enum app_iface
{
    APP_IFACE_SYS,
    APP_IFACE_UART,
    APP_IFACE_COUNT,
} app_iface_t;

typedef struct app
{
    ciot_t ciot;
    ciot_sys_t sys;
    ciot_uart_t uart;
    void *cfgs[APP_IFACE_COUNT];
    ciot_iface_t *ifaces[APP_IFACE_COUNT];
} app_t;

#endif //!__MAIN__H__