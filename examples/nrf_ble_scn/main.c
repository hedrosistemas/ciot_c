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

#include "ciot.h"
#include "ciot_log.h"
#include "ciot_sys.h"
#include "ciot_ble.h"
#include "ciot_ble_scn.h"
#include "ciot_uart.h"
#include "ciot_config.h"

typedef enum app_iface
{
    APP_IFACE_SYS,
    APP_IFACE_BLE,
    APP_IFACE_BLE_SCN,
    APP_IFACE_UART,
    APP_IFACE_COUNT,
} app_iface_t;

typedef struct app_ifaces
{
    ciot_sys_t sys;
    ciot_ble_t ble;
    ciot_ble_scn_t ble_scn;
    ciot_uart_t uart;
    ciot_iface_t *list[APP_IFACE_COUNT];
    ciot_ble_ifaces_t ble_ifaces;
} app_ifaces_t;

typedef struct app
{
    ciot_t ciot;
    app_ifaces_t ifaces;
} app_t;

static void app_start(app_t *self);
static ciot_err_t app_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args);

static const ciot_sys_cfg_t sys_cfg;

static const ciot_ble_cfg_t ble_cfg = {
    .set_mac = false,
};

static const ciot_ble_scn_cfg_t ble_scn_cfg = {
    .active = CIOT_CONFIG_BLE_SCN_ACTIVE,
    .brigde_mode = CIOT_CONFIG_BLE_SCN_BRIGDE_MODE,
    .interval = CIOT_CONFIG_BLE_SCN_INTERVAL,
    .timeout = CIOT_CONFIG_BLE_SCN_TIMEOUT,
    .window = CIOT_CONFIG_BLE_SCN_WINDOW,
};

static const ciot_uart_cfg_t uart_cfg = {
    .baud_rate = CIOT_CONFIG_UART_BAUD,
    .num = CIOT_CONFIG_UART0_PORT,
    .rx_pin = CIOT_CONFIG_UART0_RX_PIN,
    .tx_pin = CIOT_CONFIG_UART0_TX_PIN,
    .flow_control = CIOT_CONFIG_UART_HWFC,
    .parity = CIOT_CONFIG_UART_PARITY,
    .bridge_mode = CIOT_CONFIG_UART_BRIDGE_MODE,
};

static const void *cfgs[APP_IFACE_COUNT] = {
    &sys_cfg,
    &ble_cfg,
    &ble_scn_cfg,
    &uart_cfg,
};

int main()
{
    app_t app;
    app_start(&app);

    while (true)
    {
        ciot_sys_task(app.ifaces.sys);
        ciot_ble_task(app.ifaces.ble);
    }

    return 0;
}

static void app_start(app_t *self)
{
    self->ciot = ciot_new();

    self->ifaces.sys = ciot_sys_new(NULL);
    self->ifaces.ble_scn = ciot_ble_scn_new(NULL);
    self->ifaces.uart = ciot_uart_new(NULL);

    self->ifaces.ble_ifaces.scanner = self->ifaces.ble_scn;
    self->ifaces.ble = ciot_ble_new(NULL, &self->ifaces.ble_ifaces);

    self->ifaces.list[APP_IFACE_SYS] = (ciot_iface_t*)self->ifaces.sys;
    self->ifaces.list[APP_IFACE_BLE] = (ciot_iface_t*)self->ifaces.ble;
    self->ifaces.list[APP_IFACE_BLE_SCN] = (ciot_iface_t*)self->ifaces.ble_scn;
    self->ifaces.list[APP_IFACE_UART] = (ciot_iface_t*)self->ifaces.uart;

    ciot_register_event(self->ciot, app_event_handler, self);

    ciot_cfg_t ciot_cfg = {
        .ifaces = self->ifaces.list,
        .cfgs = cfgs,
        .count = APP_IFACE_COUNT,
    };
    ciot_start(self->ciot, &ciot_cfg);
}

static void bytes_to_hex(uint8_t *bytes, size_t len, char * hex)
{
    int i;
    for (i = 0; i < len; i++)
    {
        if (bytes[i] <= 0x0F)
        {
            sprintf(&hex[i << 1], "0%X", bytes[i]);
        }
        else
        {
            sprintf(&hex[i << 1], "%X", bytes[i]);
        }
    }
}

static ciot_err_t app_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args)
{
    app_t *self = (app_t*)args;

    if(event->id == CIOT_IFACE_EVENT_DATA && sender->info.id == APP_IFACE_BLE_SCN)
    {
        int size = event->size * 2 + 1;
        char data[size];
        bytes_to_hex((uint8_t*)event->data, event->size, data);
        data[size - 1] = '\n';
        ciot_uart_send_bytes(self->ifaces.list[APP_IFACE_UART], (uint8_t*)data, size);
    }

    return CIOT_OK;
}
