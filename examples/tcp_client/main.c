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

static ciot_err_t app_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args);

ciot_msg_data_t socket_cfg = {
    .socket = &(ciot_socket_data_t) {
        .config = &(ciot_socket_cfg_t) {
            .type = CIOT__SOCKET_TYPE__SOCKET_TYPE_TCP_CLIENT,
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

    ciot_iface_set_event_handler((ciot_iface_t*)self.ifaces.ciot, app_event_handler, &self);

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

static ciot_err_t app_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args)
{
    app_t *app = args;

    if(sender->info.type == CIOT__IFACE_TYPE__IFACE_TYPE_SOCKET && event->type == CIOT_IFACE_EVENT_STARTED)
    {
        ciot_msg_t msg = CIOT__MSG__INIT;
        ciot_iface_info_t iface_info = CIOT__IFACE_INFO__INIT;
        msg.iface = &iface_info;
        msg.type = CIOT__MSG_TYPE__MSG_TYPE_INFO;
        msg.iface->id = APP_IFACE_ID_SYS;
        msg.iface->type = CIOT__IFACE_TYPE__IFACE_TYPE_SYS;
        ciot_iface_send_req(sender, &msg);
    }

    if(sender->info.type == CIOT__IFACE_TYPE__IFACE_TYPE_SOCKET && 
       event->type == CIOT_IFACE_EVENT_DONE &&
       event->msg->type == CIOT__MSG_TYPE__MSG_TYPE_INFO &&
       event->msg->iface->type == CIOT__IFACE_TYPE__IFACE_TYPE_SYS)
    {
        ciot_sys_info_t *info = event->msg->data->sys->info;
        CIOT_LOGI(TAG, "Connected device system information:");
        CIOT_LOGI(TAG, "Hardware Name: %s", info->hw_name);
        CIOT_LOGI(TAG, "Hardware Type: %s", ciot__sys_hw__descriptor.values[info->hardware].name);
        CIOT_LOGI(TAG, "Firwmare Version: %d.%d.%d", info->app_ver.data[0], info->app_ver.data[1], info->app_ver.data[2]);
    }

    return CIOT__ERR__OK;
}
