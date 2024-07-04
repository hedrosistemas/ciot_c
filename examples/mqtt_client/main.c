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

ciot_msg_data_t http_server_cfg = {
    .http_server = &(ciot_http_server_data_t) {
        .config = &(ciot_http_server_cfg_t) {
            .address = "http://127.0.0.1",
            .port = 5050,
            .route = "/v1/ciot"
        }
    }
};

ciot_msg_data_t mqtt_client_cfg = {
    .mqtt_client = &(ciot_mqtt_client_data_t) {
        .config = &(ciot_mqtt_client_cfg_t) {
            .client_id = "ciot_mqtt_client",
            .url = "mqtt://test.mosquitto.org",
            .port = 1883,
            .transport = CIOT__MQTT_CLIENT_TRANSPORT__MQTT_TRANSPORT_OVER_TCP,
            .qos = 0,
            .topics = &(ciot_mqtt_client_topics_t) {
                .b2d = "ciot/b2d",
                .d2b = "ciot/d2b"
            }
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

    self.ifaces.http_server = ciot_http_server_new(CIOT_HANDLE);
    self.ifaces.list[APP_IFACE_ID_HTTP_SERVER] = (ciot_iface_t*)self.ifaces.http_server;
    self.ifaces.cfgs[APP_IFACE_ID_HTTP_SERVER] = &http_server_cfg;

    self.ifaces.mqtt_client = ciot_mqtt_client_new(CIOT_HANDLE);
    self.ifaces.list[APP_IFACE_ID_MQTT_CLIENT] = (ciot_iface_t*)self.ifaces.mqtt_client;
    self.ifaces.cfgs[APP_IFACE_ID_MQTT_CLIENT] = &mqtt_client_cfg;

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
