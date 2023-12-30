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

typedef enum app_iface
{
    APP_IFACE_SYS,
    APP_IFACE_STORAGE,
    APP_IFACE_UART,
    APP_IFACE_HTTPS,
    APP_IFACE_HTTPC,
    APP_IFACE_MQTTC,
    APP_IFACE_COUNT,
} app_iface_t;

typedef struct app
{
    ciot_t ciot;
    ciot_sys_t sys;
    ciot_storage_t storage;
    ciot_uart_t uart;
    ciot_https_t https;
    ciot_httpc_t httpc;
    ciot_mqttc_t mqttc;
    ciot_iface_t *ifaces[APP_IFACE_COUNT];
    struct mg_mgr mgr;
} app_t;

static void app_start(app_t *self);
static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args);

static const ciot_storage_cfg_t storage_cfg = {
    .type = CIOT_STORAGE_TYPE_FS
};

static const ciot_uart_cfg_t uart_cfg = {
    .baud_rate = CIOT_CONFIG_UART_BAUD,
    .num = CIOT_CONFIG_UART_PORT,
    .parity = CIOT_CONFIG_UART_PARITY,
    .dtr = CIOT_CONFIG_UART_DTR,
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

static const char *TAG = "main";

void app_main()
{
    app_t app;
    app_start(&app);

    CIOT_LOGI(TAG, "App is running...", "");
    while (true)
    {
        ciot_sys_task(app.sys);
        ciot_uart_task(app.uart);
        mg_mgr_poll(&app.mgr, 1000);
    }

    CIOT_LOGI(TAG, "App end", "");
}

static void app_start(app_t *self)
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

    self->ifaces[APP_IFACE_STORAGE] = (ciot_iface_t*)self->storage;
    self->ifaces[APP_IFACE_SYS] = (ciot_iface_t*)self->sys;
    self->ifaces[APP_IFACE_UART] = (ciot_iface_t*)self->uart;
    self->ifaces[APP_IFACE_HTTPS] = (ciot_iface_t*)self->https;
    self->ifaces[APP_IFACE_HTTPC] = (ciot_iface_t*)self->httpc;
    self->ifaces[APP_IFACE_MQTTC] = (ciot_iface_t*)self->mqttc;

    ciot_register_event(self->ciot, ciot_iface_event_handler, self);

    ciot_cfg_t ciot_cfg = {
        .ifaces = self->ifaces,
        .cfgs = (void**)cfgs,
        .count = APP_IFACE_COUNT
    };
    ciot_start(self->ciot, &ciot_cfg);
}

static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args)
{
    app_t *self = (app_t *)args;

    if(event->id == CIOT_IFACE_EVENT_STARTED && sender->info.type == CIOT_IFACE_TYPE_UART)
    {
        ciot_msg_t msg = { 0 };
        msg.type = CIOT_MSG_TYPE_GET_STATUS;
        msg.iface.type = CIOT_IFACE_TYPE_SYSTEM;
        msg.iface.id = 0;
        ciot_iface_send_msg((ciot_iface_t*)self->uart, &msg, CIOT_MSG_HEADER_SIZE);
    }

    if(event->id == CIOT_IFACE_EVENT_DONE)
    {
        printf("Event done!\n");
    }

    return CIOT_OK;
}
