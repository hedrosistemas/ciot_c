/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "main.h"

static const ciot_sys_cfg_t sys_cfg = APP_CONFIG_SYSTEM;
static const ciot_uart_cfg_t uart_cfg = APP_CONFIG_UART;
static app_t app;

ciot_err_t app_event_handler(ciot_iface_t *iface, ciot_iface_event_t *event, void *args)
{
    return CIOT_OK;
}

void app_start()
{
    app.ciot = ciot_new();
    app.sys = ciot_sys_new(CIOT_HANDLE);
    app.uart = ciot_uart_new(&Serial);

    app.ifaces[APP_IFACE_SYS] = (ciot_iface_t*)app.sys;
    app.ifaces[APP_IFACE_UART] = (ciot_iface_t*)app.uart;

    app.cfgs[APP_IFACE_SYS] = (void*)&sys_cfg;
    app.cfgs[APP_IFACE_UART] = (void*)&uart_cfg;

    ciot_register_event(app.ciot, app_event_handler, &app);

    ciot_cfg_t ciot_cfg = {
        .ifaces = app.ifaces,
        .cfgs = app.cfgs,
        .count = APP_IFACE_COUNT
    };
    ciot_start(app.ciot, &ciot_cfg);
}

void app_main()
{
    app_start();

    while (true)
    {
        ciot_sys_task(app.sys);
        ciot_uart_task(app.uart);
    }
}
