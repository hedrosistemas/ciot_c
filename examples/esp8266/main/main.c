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

#include "ciot_log.h"
#include "ciot.h"
#include "ciot_sys.h"
#include "ciot_storage.h"
#include "ciot_wifi.h"
#include "ciot_https.h"
#include "ciot_ntp.h"
#include "ciot_mqttc.h"

#include "ciot_config.h"

typedef enum app_iface
{
    APP_IFACE_CIOT,
    APP_IFACE_SYS,
    APP_IFACE_STORAGE,
    APP_IFACE_HTTPS,
    APP_IFACE_WIFI_AP,
    APP_IFACE_WIFI_STA,
    APP_IFACE_NTP,
    APP_IFACE_MQTTC,
    APP_IFACE_COUNT,
} app_iface_t;

typedef struct app
{
    ciot_t ciot;
    ciot_sys_t sys;
    ciot_storage_t storage;
    ciot_https_t https;
    ciot_wifi_t wifi_ap;
    ciot_wifi_t wifi_sta;
    ciot_ntp_t ntp;
    ciot_mqttc_t mqttc;
    ciot_iface_t *ifaces[APP_IFACE_COUNT];
    void *cfgs[APP_IFACE_COUNT];
} app_t;

static void app_start(app_t *self);
static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args);

static ciot_sys_cfg_t sys_cfg = CIOT_CONFIG_SYS;
static ciot_storage_cfg_t storage_cfg = CIOT_CONFIG_STORAGE;
static ciot_https_cfg_t https_cfg = CIOT_CONFIG_HTTPS;
static ciot_wifi_cfg_t wifi_ap_cfg = CIOT_CONFIG_WIFI_AP;

static const char *TAG = "main";

int app_main()
{
    app_t app;
    app_start(&app);

    CIOT_LOGI(TAG, "App is running...");
    while (true)
    {
        ciot_sys_task(app.sys);
    }

    CIOT_LOGI(TAG, "App end");

    return 0;
}

static void app_start(app_t *self)
{
    CIOT_LOGI(TAG, "App is initializing...");

    self->ciot = ciot_new();
    self->sys = ciot_sys_new(CIOT_HANDLE);
    self->storage = ciot_storage_new(CIOT_HANDLE);
    self->https = ciot_https_new(CIOT_HANDLE);
    self->wifi_ap = ciot_wifi_new(CIOT_HANDLE);
    self->wifi_sta = ciot_wifi_new(CIOT_HANDLE);
    self->ntp = ciot_ntp_new(CIOT_HANDLE);
    self->mqttc = ciot_mqttc_new(CIOT_HANDLE);

    self->ifaces[APP_IFACE_CIOT] = (ciot_iface_t*)self->ciot;
    self->ifaces[APP_IFACE_SYS] = (ciot_iface_t*)self->sys;
    self->ifaces[APP_IFACE_STORAGE] = (ciot_storage_t*)self->storage;
    self->ifaces[APP_IFACE_HTTPS] = (ciot_iface_t*)self->https;
    self->ifaces[APP_IFACE_WIFI_AP] = (ciot_iface_t*)self->wifi_ap;
    self->ifaces[APP_IFACE_WIFI_STA] = (ciot_iface_t*)self->wifi_sta;
    self->ifaces[APP_IFACE_NTP] = (ciot_iface_t*)self->ntp;
    self->ifaces[APP_IFACE_MQTTC] = (ciot_iface_t*)self->mqttc;
    
    self->cfgs[APP_IFACE_SYS] = &sys_cfg;
    self->cfgs[APP_IFACE_STORAGE] = &storage_cfg;
    self->cfgs[APP_IFACE_HTTPS] = &https_cfg;
    self->cfgs[APP_IFACE_WIFI_AP] = &wifi_ap_cfg;

    ciot_register_event(self->ciot, ciot_iface_event_handler, self);

    ciot_cfg_t ciot_cfg = {
        .ifaces = self->ifaces,
        .cfgs = self->cfgs,
        .count = APP_IFACE_COUNT
    };
    ciot_start(self->ciot, &ciot_cfg);
}

static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args)
{
    // app_t *self = (app_t *)args;
    return CIOT_OK;
}
