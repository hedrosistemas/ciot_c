/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "main.h"

static const char *TAG = "hg_ble_install";

ciot_uart_cfg_t uart_cfg;

static ciot_err_t app_event_handler(ciot_iface_t *iface, ciot_iface_event_t *event, void *args);

static void app_start(app_t *self)
{
    self->ciot = ciot_new();
    self->uart = ciot_uart_new(CIOT_HANDLE);

    self->ifaces[APP_IFACE_UART] = (ciot_iface_t*)self->uart;
    self->cfgs[APP_IFACE_UART] = &uart_cfg;

    ciot_register_event(self->ciot, app_event_handler, self);

    ciot_cfg_t ciot_cfg = {
        .ifaces = self->ifaces,
        .cfgs = self->cfgs,
        .count = APP_IFACE_COUNT};
    ciot_start(self->ciot, &ciot_cfg);
}

void app_main(void)
{
    CIOT_LOGI(TAG, "App Info:");
    CIOT_LOGI(TAG, "Hardware: %s", CIOT_CONFIG_HARDWARE_NAME);
    CIOT_LOGI(TAG, "Version: %d.%d.%d", CIOT_CONFIG_APP_VER);

    static app_t app;
    app_start(&app);

    while (true)
    {
        ciot_uart_task(app.uart);
    }
}

static ciot_err_t app_event_handler(ciot_iface_t *iface, ciot_iface_event_t *event, void *args)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}