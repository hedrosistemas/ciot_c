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
#include "ciot_uart.h"
#include "ciot_bridge.h"

#include "ciot_config.h"

typedef enum app_iface
{
    APP_IFACE_UART1,
    APP_IFACE_UART2,
    APP_IFACE_BRIDGE,
    APP_IFACE_COUNT,
} app_iface_t;

typedef struct app
{
    ciot_t ciot;
    ciot_uart_t uart1;
    ciot_uart_t uart2;
    ciot_bridge_t bridge;
    ciot_iface_t *ifaces[APP_IFACE_COUNT];
} app_t;

static void app_start(app_t *self);
static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args);

static const ciot_uart_cfg_t uart1_cfg = {
    .baud_rate = CIOT_CONFIG_UART1_BAUD,
    .num = CIOT_CONFIG_UART1_PORT,
    .dtr = CIOT_CONFIG_UART1_DTR,
    .bridge_mode = CIOT_CONFIG_UART1_BRIDGE,
};

static const ciot_uart_cfg_t uart2_cfg = {
    .baud_rate = CIOT_CONFIG_UART2_BAUD,
    .num = CIOT_CONFIG_UART2_PORT,
    .dtr = CIOT_CONFIG_UART2_DTR,
    .bridge_mode = CIOT_CONFIG_UART1_BRIDGE,
};

static const ciot_bridge_cfg_t bridge_cfg = {
    .ifaces_id = {
        APP_IFACE_UART1,
        APP_IFACE_UART2
    }
};

static const void *cfgs[] = {
    &uart1_cfg,
    &uart2_cfg,
    &bridge_cfg,
};

static const char *TAG = "main";

int main()
{
    app_t app;
    app_start(&app);

    CIOT_LOGI(TAG, "App is running...", "");
    while (true)
    {
        ciot_uart_task(app.uart1);
        ciot_uart_task(app.uart2);
    }

    CIOT_LOGI(TAG, "App end", "");

    return 0;
}

static void app_start(app_t *self)
{
    CIOT_LOGI(TAG, "App is initializing...", "");

    self->ciot = ciot_new();
    self->uart1 = ciot_uart_new(NULL);
    self->uart2 = ciot_uart_new(NULL);
    self->bridge = ciot_bridge_new(NULL);

    self->ifaces[APP_IFACE_UART1] = (ciot_iface_t*)self->uart1;
    self->ifaces[APP_IFACE_UART2] = (ciot_iface_t*)self->uart2;
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
    if(event->id == CIOT_IFACE_EVENT_DATA)
    {
        printf("Event done!\n");
    }

    return CIOT_OK;
}
