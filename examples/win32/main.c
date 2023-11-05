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
#include "ciot_storage.h"
#include "ciot_uart.h"
#include "ciot_https.h"
#include "ciot_httpc.h"
#include "ciot_httpc.h"
#include "ciot_mqttc.h"

#include "ciot_config.h"

#define CIOT_IFACES_COUNT 6

typedef struct app
{
    ciot_t ciot;
    ciot_sys_t sys;
    ciot_storage_t storage;
    ciot_uart_t uart;
    ciot_https_t https;
    ciot_httpc_t httpc;
    ciot_mqttc_t mqttc;
    struct mg_mgr mgr;
} app_t;

static void app_init(app_t *self);

static const ciot_storage_cfg_t storage_cfg = {
    .type = CIOT_STORAGE_TYPE_FS
};

static const ciot_uart_cfg_t uart_cfg = {
    .baud_rate = CIOT_CONFIG_UART_BAUD,
    .num = CIOT_CONFIG_UART_PORT,
};

static const ciot_https_cfg_t https_cfg = {
    .address = CIOT_CONFIG_HTTPS_ADDRESS,
    .route = CIOT_CONFIG_HTTPS_ROUTE,
};

static const ciot_httpc_cfg_t httpc_cfg = {
    .url = CIOT_CONFIG_HTTPC_URL,
    .transport = CIOT_CONFIG_HTTPC_TRANSPORT,  
    .method = CIOT_CONFIG_HTTPC_METHOD,
    .timeout = CIOT_CONFIG_HTTPC_TIMEOUT,
};

static const ciot_mqttc_cfg_t mqttc_cfg = {
    .client_id = CIOT_CONFIG_MQTTC_ID,
    .url = CIOT_CONFIG_MQTTC_URL,
    .port = CIOT_CONFIG_MQTTC_PORT,
    .qos = CIOT_CONFIG_MQTTC_QOS,
    .topics = {
        .b2d = CIOT_CONFIG_MQTTC_TOPIC_B2D,
        .d2b = CIOT_CONFIG_MQTTC_TOPIC_D2B,
    }
};

static const void *cfgs[] = {
    &storage_cfg,
    NULL,
    &uart_cfg,
    &https_cfg,
    &httpc_cfg,
    &mqttc_cfg,
};

static ciot_iface_t* ifaces[CIOT_IFACES_COUNT];

static const char *TAG = "main";

int main()
{
    app_t app;
    app_init(&app);

    ifaces[0] = (ciot_iface_t*)app.storage;
    ifaces[1] = (ciot_iface_t*)app.sys;
    ifaces[2] = (ciot_iface_t*)app.uart;
    ifaces[3] = (ciot_iface_t*)app.https;
    ifaces[4] = (ciot_iface_t*)app.httpc;
    ifaces[5] = (ciot_iface_t*)app.mqttc;

    ciot_cfg_t ciot_cfg = {
        .ifaces = ifaces,
        .cfgs = cfgs,
        .count = CIOT_IFACES_COUNT
    };
    ciot_start(app.ciot, &ciot_cfg);

    CIOT_LOGI(TAG, "App is running...", "");
    while (true)
    {
        ciot_sys_task(app.sys);
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
    self->storage = ciot_storage_new(NULL);
    self->uart = ciot_uart_new(NULL);
    self->https = ciot_https_new(&self->mgr);
    self->httpc = ciot_httpc_new(&self->mgr);
    self->mqttc = ciot_mqttc_new(&self->mgr);
}
