/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-12-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "main.h"

device_t self;

ciot_msg_data_t http_server_cfg = {
    .which_type = CIOT_MSG_DATA_HTTP_SERVER_TAG,
    .http_server = {
        .which_type = CIOT_HTTP_SERVER_DATA_CONFIG_TAG,
        .config = {
            .address = "http://127.0.0.1",
            .route = "/v1/device",
            .port = 5050,
        },
    },
};

ciot_msg_data_t mqtt_client_cfg = {
    .which_type = CIOT_MSG_DATA_MQTT_CLIENT_TAG,
    .mqtt_client = {
        .which_type = CIOT_MQTT_CLIENT_DATA_CONFIG_TAG,
        .config = {
            .client_id = "ciot/device/256848",
            .url = "mqtt://test.mosquitto.org:1883",
            .has_topics = true,
            .topics = {
                .pub = "ciot/device/pub",
                .sub = "ciot/device/sub",
            },
        },
    },
};

ciot_msg_data_t uart_cfg = {
    .which_type = CIOT_MSG_DATA_UART_TAG,
    .uart = {
        .which_type = CIOT_UART_DATA_CONFIG_TAG,
        .config = {
            .baud_rate = 115200,
            .num = 4,
        }
    }
};

static void device_start()
{
    self.serializer = ciot_serializer_pb_new();
    self.decoder.handle = ciot_decoder_s_new(self.decoder.buf, sizeof(self.decoder.buf));

    self.ifaces.ciot = ciot_new();
    self.ifaces.list[DEVICE_IFACE_ID_CIOT] = (ciot_iface_t *)self.ifaces.ciot;
    self.ifaces.cfgs[DEVICE_IFACE_ID_CIOT] = NULL;

    self.ifaces.sys = ciot_sys_new(CIOT_HANDLE);
    self.ifaces.list[DEVICE_IFACE_ID_SYS] = (ciot_iface_t *)self.ifaces.sys;
    self.ifaces.cfgs[DEVICE_IFACE_ID_SYS] = NULL;

    self.ifaces.http_server = ciot_http_server_new(CIOT_HANDLE);
    self.ifaces.list[DEVICE_IFACE_ID_HTTP_SERVER] = (ciot_iface_t *)self.ifaces.http_server;
    self.ifaces.cfgs[DEVICE_IFACE_ID_HTTP_SERVER] = &http_server_cfg;

    self.ifaces.mqtt_client = ciot_mqtt_client_new(CIOT_HANDLE);
    self.ifaces.list[DEVICE_IFACE_ID_MQTT_CLIENT] = (ciot_iface_t *)self.ifaces.mqtt_client;
    self.ifaces.cfgs[DEVICE_IFACE_ID_MQTT_CLIENT] = &mqtt_client_cfg;

    self.ifaces.uart = ciot_uart_new(CIOT_HANDLE);
    self.ifaces.list[DEVICE_IFACE_ID_UART] = (ciot_iface_t *)self.ifaces.uart;
    self.ifaces.cfgs[DEVICE_IFACE_ID_UART] = &uart_cfg;

    ciot_iface_set_serializer((ciot_iface_t*)self.ifaces.http_server, self.serializer);
    ciot_iface_set_serializer((ciot_iface_t*)self.ifaces.mqtt_client, self.serializer);
    ciot_iface_set_serializer((ciot_iface_t*)self.ifaces.uart, self.serializer);
    ciot_iface_set_decoder((ciot_iface_t*)self.ifaces.uart, self.decoder.handle);

    ciot_cfg_t ciot_cfg = {
        .ifaces = {
            .list = self.ifaces.list,
            .cfgs = self.ifaces.cfgs,
            .count = DEVICE_IFACE_ID_COUNT,
        },
    };
    ciot_start(self.ifaces.ciot, &ciot_cfg);
}

static void device_task()
{
    ciot_task(self.ifaces.ciot);
    ciot_sys_task(self.ifaces.sys);
    ciot_uart_task(self.ifaces.uart);
}

int main(void)
{
    device_start();

    while (true)
    {
        device_task();
    }
    
    return 0;
}
