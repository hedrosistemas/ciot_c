/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdbool.h>

#include "ciot.h"
#include "ciot_log.h"
#include "ciot_usb.h"
#include "ciot_uart.h"
#include "ciot_bridge.h"

#include "ciot_config.h"

typedef enum app_iface
{
    APP_IFACE_UART,
    APP_IFACE_USB,
    APP_IFACE_BRIDGE,
    APP_IFACE_COUNT,
} app_iface_t;

typedef struct app
{
    ciot_t ciot;
    ciot_uart_t uart;
    ciot_usb_t usb;
    ciot_bridge_t bridge;
    ciot_iface_t *ifaces[APP_IFACE_COUNT];
} app_t;

static void app_start(app_t *self);
static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args);

static ciot_usb_cfg_t usb_cfg = {
    .bridge_mode = CIOT_CONFIG_USB_BRIDGE_MODE,
};

static ciot_uart_cfg_t uart_cfg = {
    .baud_rate = CIOT_CONFIG_UART_BAUD,
    .num = CIOT_CONFIG_UART0_PORT,
    .rx_pin = CIOT_CONFIG_UART0_RX_PIN,
    .tx_pin = CIOT_CONFIG_UART0_TX_PIN,
    .flow_control = CIOT_CONFIG_UART0_FLOW_CONTROL,
    .parity = CIOT_CONFIG_UART0_PARITY,
    .bridge_mode = CIOT_CONFIG_UART0_BRIDGE,
};

static ciot_bridge_cfg_t bridge_cfg = {
    .ifaces_id = {
        APP_IFACE_UART,
        APP_IFACE_USB,
    }
};

static void *cfgs[] = {
    &uart_cfg,
    &usb_cfg,
    &bridge_cfg,
};

static const char *TAG = "main";

int main()
{
    app_t app;
    app_start(&app);

    CIOT_LOGI(TAG, "App is running...");
    while (true)
    {
        ciot_usb_task(app.usb);
        ciot_uart_task(app.uart);
    }

    CIOT_LOGI(TAG, "App end");

    return 0;
}

static void app_start(app_t *self)
{
    CIOT_LOGI(TAG, "App is initializing...");

    self->ciot = ciot_new();
    self->usb = ciot_usb_new(NULL);
    self->uart = ciot_uart_new(NULL);
    self->bridge = ciot_bridge_new(NULL);

    self->ifaces[APP_IFACE_UART] = (ciot_iface_t*)self->uart;
    self->ifaces[APP_IFACE_USB] = (ciot_iface_t*)self->usb;
    self->ifaces[APP_IFACE_BRIDGE] = (ciot_iface_t*)self->bridge;

    ciot_register_event(self->ciot, ciot_iface_event_handler, self);

    ciot_cfg_t ciot_cfg = {
        .ifaces = self->ifaces,
        .cfgs = cfgs,
        .count = APP_IFACE_COUNT
    };
    ciot_start(self->ciot, &ciot_cfg);
}

static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args)
{
    return CIOT_OK;
}
