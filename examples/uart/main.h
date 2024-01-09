/**
 * @file main.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __MAIN__H__
#define __MAIN__H__

#include "ciot.h"
#include "ciot_sys.h"
#include "ciot_uart.h"
#include "ciot_ble.h"
#include "ciot_ble_scn.h"

typedef enum app_ifaces
{
    APP_IFACE_UART,
    APP_IFACE_COUNT,
} app_ifaces_t;

typedef struct app
{
    ciot_t ciot;
    ciot_uart_t uart;
    ciot_iface_t *ifaces[APP_IFACE_COUNT];
    void *cfgs[APP_IFACE_COUNT];
} app_t;

#endif  //!__MAIN__H__
