/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include "main.h"

static const char *TAG = "main";

ciot_msg_data_t uart_cfg = {
    .uart = &(ciot_uart_data_t) {
        .config = &(ciot_uart_cfg_t) {
            .num = 5,
            .baud_rate = 250000
        }
    }
};

app_t self;

static void app_start()
{
    CIOT_LOGI(TAG, "Starting application");

    self.ifaces.ciot = ciot_new();
    self.ifaces.list[APP_IFACE_ID_CIOT] = (ciot_iface_t*)self.ifaces.ciot;
    self.ifaces.cfgs[APP_IFACE_ID_CIOT] = NULL;

    self.ifaces.sys = ciot_sys_new(CIOT_HANDLE);
    self.ifaces.list[APP_IFACE_ID_SYS] = (ciot_iface_t*)self.ifaces.sys;
    self.ifaces.cfgs[APP_IFACE_ID_SYS] = NULL;

    self.ifaces.uart = ciot_uart_new(CIOT_HANDLE);
    self.ifaces.list[APP_IFACE_ID_UART] = (ciot_iface_t*)self.ifaces.uart;
    self.ifaces.cfgs[APP_IFACE_ID_UART] = &uart_cfg;

    self.ifaces.ble = ciot_ble_new(CIOT_HANDLE);
    self.ifaces.list[APP_IFACE_ID_BLE] = (ciot_iface_t*)self.ifaces.ble;
    self.ifaces.cfgs[APP_IFACE_ID_BLE] = NULL;

    self.ifaces.ble_adv = ciot_ble_adv_new(CIOT_HANDLE);
    self.ifaces.list[APP_IFACE_ID_BLE_ADV] = (ciot_iface_t*)self.ifaces.ble_adv;
    self.ifaces.cfgs[APP_IFACE_ID_BLE_ADV] = NULL;

    self.ifaces.ble_scn = ciot_ble_scn_new(CIOT_HANDLE);
    self.ifaces.list[APP_IFACE_ID_BLE_SCN] = (ciot_iface_t*)self.ifaces.ble_scn;
    self.ifaces.cfgs[APP_IFACE_ID_BLE_SCN] = NULL;

    ciot_cfg_t ciot_cfg = {
        .ifaces = self.ifaces.list,
        .cfgs = self.ifaces.cfgs,
        .count = APP_IFACE_ID_COUNT
    };
    ciot_start(self.ifaces.ciot, &ciot_cfg);
}

static void app_task()
{
    ciot_sys_task(self.ifaces.sys);
    ciot_task(self.ifaces.ciot);
}

int main()
{
    app_start();

    while (true)
    {
        app_task();
    }
    
    return 0;
}
