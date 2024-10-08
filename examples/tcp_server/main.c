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

ciot_msg_data_t socket_cfg = {
    .socket = &(ciot_socket_data_t) {
        .config = &(ciot_socket_cfg_t) {
            .type = CIOT__SOCKET_TYPE__SOCKET_TYPE_TCP_SERVER,
            .address = "http://127.0.0.1",
            .port = 5050,
        }
    }
};

app_t self;

static void app_start()
{
    self.ifaces.ciot = ciot_new();
    self.ifaces.list[APP_IFACE_ID_CIOT] = (ciot_iface_t*)self.ifaces.ciot;
    self.ifaces.cfgs[APP_IFACE_ID_CIOT] = NULL;

    self.ifaces.sys = ciot_sys_new(CIOT_HANDLE);
    self.ifaces.list[APP_IFACE_ID_SYS] = (ciot_iface_t*)self.ifaces.sys;
    self.ifaces.cfgs[APP_IFACE_ID_SYS] = NULL;

    self.ifaces.socket = ciot_socket_new(CIOT_HANDLE);
    self.ifaces.list[APP_IFACE_ID_SOCKET] = (ciot_iface_t*)self.ifaces.socket;
    self.ifaces.cfgs[APP_IFACE_ID_SOCKET] = &socket_cfg;

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
