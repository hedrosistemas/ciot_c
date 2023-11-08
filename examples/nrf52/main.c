/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "nrf_uart.h"

#include "ciot.h"
#include "ciot_log.h"
#include "ciot_sys.h"
#include "ciot_uart.h"
#include "ciot_usb.h"

#include "ciot_config.h"

typedef enum app_iface
{
    APP_IFACE_SYS,
    APP_IFACE_UART0,
    APP_IFACE_UART1,
    APP_IFACE_USB,
    APP_IFACE_COUNT,
} app_iface_t;

typedef struct app
{
    ciot_t ciot;
    ciot_sys_t sys;
    ciot_uart_t uart0;
    ciot_uart_t uart1;
    ciot_usb_t usb;
    ciot_iface_t *ifaces[APP_IFACE_COUNT];
} app_t;

static void app_start(app_t *self);

static const ciot_sys_cfg_t sys_cfg;

static const ciot_usb_cfg_t usb_cfg;

static const ciot_uart_cfg_t uart0_cfg = {
    .baud_rate = CIOT_CONFIG_UART_BAUD,
    .num = CIOT_CONFIG_UART0_PORT,
    .rx_pin = CIOT_CONFIG_UART0_RX_PIN,
    .tx_pin = CIOT_CONFIG_UART0_TX_PIN,
    .flow_control = NRF_UART_HWFC_DISABLED,
    .parity = NRF_UART_PARITY_EXCLUDED
};

static const ciot_uart_cfg_t uart1_cfg = {
    .baud_rate = CIOT_CONFIG_UART_BAUD,
    .num = CIOT_CONFIG_UART1_PORT,
    .rx_pin = CIOT_CONFIG_UART1_RX_PIN,
    .tx_pin = CIOT_CONFIG_UART1_TX_PIN,
    .flow_control = NRF_UART_HWFC_DISABLED,
    .parity = NRF_UART_PARITY_EXCLUDED
};

static const void *cfgs[] = {
    &sys_cfg,
    &uart0_cfg,
    &uart1_cfg,
    &usb_cfg,
};

static const char *TAG = "main";

int main()
{
    app_t app;
    app_start(&app);
    
    CIOT_LOGI(TAG, "%s", "App is running");
    while (true)
    {
        ciot_sys_task(app.sys);
        ciot_usb_task(app.usb);
        ciot_uart_task(app.uart0);
        ciot_uart_task(app.uart1);
    }

    return 0;
}

static void app_start(app_t *self)
{
    CIOT_LOGI(TAG, "%s", "App is initializing");

    self->ciot = ciot_new();
    self->sys = ciot_sys_new(NULL);
    self->uart0 = ciot_uart_new(NULL);
    self->uart1 = ciot_uart_new(NULL);
    self->usb = ciot_usb_new(NULL);

    self->ifaces[APP_IFACE_SYS] = (ciot_iface_t*)self->sys;
    self->ifaces[APP_IFACE_UART0] = (ciot_iface_t*)self->uart0;
    self->ifaces[APP_IFACE_UART1] = (ciot_iface_t*)self->uart1;
    self->ifaces[APP_IFACE_USB] = (ciot_iface_t*)self->usb;

    ciot_cfg_t ciot_cfg = {
        .ifaces = self->ifaces,
        .cfgs = cfgs,
        .count = APP_IFACE_COUNT,
    };
    ciot_start(self->ciot, &ciot_cfg);
}
