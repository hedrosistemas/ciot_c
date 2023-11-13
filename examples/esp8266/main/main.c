/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>

#include "mongoose.h"

#include "ciot.h"
#include "ciot_log.h"
#include "ciot_sys.h"
#include "ciot_https.h"
#include "ciot_httpc.h"
#include "ciot_httpc.h"
#include "ciot_mqttc.h"

#include "ciot_config.h"

typedef enum app_iface
{
    APP_IFACE_SYS,
    APP_IFACE_HTTPS,
    APP_IFACE_HTTPC,
    APP_IFACE_MQTTC,
    APP_IFACE_COUNT,
} app_iface_t;

typedef struct app
{
    ciot_t ciot;
    ciot_sys_t sys;
    ciot_https_t https;
    ciot_httpc_t httpc;
    ciot_mqttc_t mqttc;
    ciot_iface_t *ifaces[APP_IFACE_COUNT];
    struct mg_mgr mgr;
} app_t;

static void app_start(app_t *self);
static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args);

static const ciot_sys_cfg_t sys_cfg;

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
    &sys_cfg,
    &https_cfg,
    &httpc_cfg,
    &mqttc_cfg,
};

static const char *TAG = "main";

int app_main()
{
    app_t app;
    app_start(&app);

    CIOT_LOGI(TAG, "App is running...");
    while (true)
    {
        ciot_sys_task(app.sys);
        mg_mgr_poll(&app.mgr, 1000);
    }

    CIOT_LOGI(TAG, "App end");

    return 0;
}

static void app_start(app_t *self)
{
    CIOT_LOGI(TAG, "App is initializing...");
    mg_mgr_init(&self->mgr);
    self->ciot = ciot_new();
    self->sys = ciot_sys_new(NULL);
    self->https = ciot_https_new(&self->mgr);
    self->httpc = ciot_httpc_new(&self->mgr);
    self->mqttc = ciot_mqttc_new(&self->mgr);

    self->ifaces[APP_IFACE_SYS] = (ciot_iface_t*)self->sys;
    self->ifaces[APP_IFACE_HTTPS] = (ciot_iface_t*)self->https;
    self->ifaces[APP_IFACE_HTTPC] = (ciot_iface_t*)self->httpc;
    self->ifaces[APP_IFACE_MQTTC] = (ciot_iface_t*)self->mqttc;

    ciot_register_event(self->ciot, ciot_iface_event_handler, self);

    ciot_cfg_t ciot_cfg = {
        .ifaces = self->ifaces,
        .cfgs = cfgs,
        .count = APP_IFACE_COUNT
    };
    ciot_start(self->ciot, &ciot_cfg);
}

static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args)
{
    // app_t *self = (app_t *)args;

    CIOT_LOGI(TAG, "event %d received from sender id:%d type:%d", event->id, sender->info.id, sender->info.type);

    return CIOT_OK;
}
