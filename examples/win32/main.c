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

#include "mongoose.h"

#include "ciot.h"
#include "ciot_log.h"
#include "ciot_sys.h"
#include "ciot_uart.h"
#include "ciot_https.h"
#include "ciot_httpc.h"
#include "ciot_httpc.h"
#include "ciot_mqttc.h"

#include "ciot_custom_config.h"

typedef struct app
{
    ciot_t ciot;
    ciot_sys_t sys;
    ciot_uart_t uart;
    ciot_https_t https;
    ciot_httpc_t httpc;
    ciot_mqttc_t mqttc;
    struct mg_mgr mgr;
} app_t;

static void app_init(app_t *self);
static void app_start(app_t *self);
static ciot_err_t app_uart_start(app_t *self);
static ciot_err_t app_https_start(app_t *self);
static ciot_err_t app_httpc_start(app_t *self);
static ciot_err_t app_mqttc_start(app_t *self);

static const char *TAG = "main";

int main()
{
    app_t app;
    app_init(&app);
    app_start(&app);

    ciot_iface_t* iface_list[] = {
        (ciot_iface_t*)app.sys,
        (ciot_iface_t*)app.uart,
        (ciot_iface_t*)app.https,
        (ciot_iface_t*)app.httpc,
        (ciot_iface_t*)app.mqttc,
    };
    ciot_set_iface_list(app.ciot, iface_list, sizeof(iface_list) / sizeof(ciot_iface_t*));

    CIOT_LOGI(TAG, "App is running...", "");
    while (true)
    {
        ciot_uart_task(app.uart);
        mg_mgr_poll(&app.mgr, 1000);
    }

    CIOT_LOGI(TAG, "App end", "");

    return 0;
}

static void app_init(app_t *self)
{
    CIOT_LOGI(TAG, "App is initializing...", "");
    mg_mgr_init(&self->mgr);
    self->ciot = ciot_new();
    self->sys = ciot_sys_new(NULL);
    self->uart = ciot_uart_new(NULL);
    self->https = ciot_https_new(&self->mgr);
    self->httpc = ciot_httpc_new(&self->mgr);
    self->mqttc = ciot_mqttc_new(&self->mgr);
}

static void app_start(app_t *self)
{
    CIOT_LOGI(TAG, "App is starting...", "");
    app_uart_start(self);
    app_https_start(self);
    app_httpc_start(self);
    app_mqttc_start(self);
}

static ciot_err_t app_uart_start(app_t *self)
{
    ciot_uart_cfg_t uart_cfg = {
        .baud_rate = CIOT_CONFIG_UART_BAUD,
        .num = CIOT_CONFIG_UART_PORT,
    };
    return ciot_uart_start(self->uart, &uart_cfg);
}

static ciot_err_t app_https_start(app_t *self)
{
    ciot_https_cfg_t https_cfg = {
        .address = "127.0.0.1",
        .port = 8080,
        .route = "/v1/ciot",
    };
    return ciot_https_start(self->https, &https_cfg);
}

static ciot_err_t app_httpc_start(app_t *self)
{
    ciot_httpc_cfg_t httpc_cfg = {
        .url = "v1/ciot",
        .transport = CIOT_HTTPC_TRANSPORT_TCP,  
        .method = CIOT_HTTPC_METHOD_POST,
        .timeout = CIOT_CONFIG_HTTPC_TIMEOUT,
    };
    return ciot_httpc_start(self->httpc, &httpc_cfg);
}

static ciot_err_t app_mqttc_start(app_t *self)
{
    ciot_mqttc_cfg_t mqtt_cfg = {
        .client_id = "mqtt_client_id",
        .url = "mqtt://test.mosquitto.org",
        .port = 1883,
        .qos = 0,
        .topics = {
            .b2d = "CIOT/B2D",
            .d2b = "CIOT/D2B",
        }
    };
    return ciot_mqttc_start(self->mqttc, &mqtt_cfg);
}
