/**
 * @file integration.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-11-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>

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

#include "expected_data.h"

#define CIOT_IFACES_COUNT 5

typedef enum app_state
{
    APP_STATE_START,
    APP_STATE_WAITING_CONFIG,
    APP_STATE_CFG_DONE,
    APP_STATE_WAITING_STATUS,
    APP_STATE_STATUS_DONE,
} app_state_t;

typedef enum app_iface_id
{
    APP_IFACE_SYSTEM,
    APP_IFACE_STORAGE,
    APP_IFACE_UART,
    APP_IFACE_HTTPC,
    APP_IFACE_MQTTC,
} app_iface_id_t;

typedef enum app_host_iface_id
{
    APP_HOST_IFACE_STORAGE,
    APP_HOST_IFACE_SYSTEM,
    APP_HOST_IFACE_UART,
    APP_HOST_IFACE_HTTPS,
    APP_HOST_IFACE_HTTPC,
    APP_HOST_IFACE_MQTTC,
} app_host_iface_id_t;

typedef struct app
{
    ciot_t ciot;
    ciot_sys_t sys;
    ciot_storage_t storage;
    ciot_uart_t uart;
    ciot_httpc_t httpc;
    ciot_mqttc_t mqttc;
    struct mg_mgr mgr;
    app_state_t state;
} app_t;

static void app_init(app_t *self);
static void app_task(app_t *self);
static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args);
static char *get_iface_name_from_type(ciot_msg_iface_type_t type);

static const ciot_storage_cfg_t storage_cfg = {
    .type = CIOT_STORAGE_TYPE_FS};

static const ciot_uart_cfg_t uart_cfg = {
    .baud_rate = CIOT_CONFIG_UART_BAUD,
    .num = CIOT_CONFIG_UART_PORT,
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
    }};

static const void *cfgs[] = {
    &storage_cfg,
    NULL,
    &uart_cfg,
    &httpc_cfg,
    &mqttc_cfg,
};

static const ciot_msg_iface_type_t host_iface_types[] = {
    CIOT_IFACE_TYPE_STORAGE,
    CIOT_IFACE_TYPE_SYSTEM,
    CIOT_IFACE_TYPE_UART,
    CIOT_IFACE_TYPE_HTTP_SERVER,
    CIOT_IFACE_TYPE_HTTP_CLIENT,
    CIOT_IFACE_TYPE_MQTT
};

static app_iface_id_t app_iface_id = APP_IFACE_UART;
static app_host_iface_id_t host_iface_id = APP_HOST_IFACE_STORAGE;
static app_host_iface_id_t host_initial_iface = APP_HOST_IFACE_STORAGE;

static ciot_iface_t *ifaces[CIOT_IFACES_COUNT];

static const char *TAG = "integration_test";

int main(void *args)
{
    app_t app = {0};
    app_init(&app);

    ifaces[0] = (ciot_iface_t *)app.storage;
    ifaces[1] = (ciot_iface_t *)app.sys;
    ifaces[2] = (ciot_iface_t *)app.uart;
    ifaces[3] = (ciot_iface_t *)app.httpc;
    ifaces[4] = (ciot_iface_t *)app.mqttc;

    ciot_cfg_t ciot_cfg = {
        .ifaces = ifaces,
        .cfgs = cfgs,
        .count = CIOT_IFACES_COUNT};
    ciot_start(app.ciot, &ciot_cfg);

    ciot_register_event(app.ciot, ciot_iface_event_handler, &app);

    CIOT_LOGI(TAG, "App is running...", "");
    while (true)
    {
        ciot_sys_task(app.sys);
        ciot_uart_task(app.uart);
        app_task(&app);
        mg_mgr_poll(&app.mgr, 1000);
    }

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
    self->httpc = ciot_httpc_new(&self->mgr);
    self->mqttc = ciot_mqttc_new(&self->mgr);
}

static void app_task(app_t *self)
{
    ciot_msg_t msg;
    char *app_iface = get_iface_name_from_type(ifaces[app_iface_id]->info.type);
    char *host_iface = get_iface_name_from_type(host_iface_types[host_iface_id]);

    switch (self->state)
    {
    case APP_STATE_START:
        CIOT_LOGI(TAG, "Testing connection of %s interface with host %s interface.", app_iface, host_iface);
        msg.iface.id = host_iface_id;
        msg.iface.type = host_iface_types[host_iface_id];
        msg.type = CIOT_MSG_TYPE_GET_STATUS;
        ciot_iface_send_msg(ifaces[app_iface_id], &msg, CIOT_MSG_SIZE);
        self->state = APP_STATE_WAITING_STATUS;
        break;
    case APP_STATE_STATUS_DONE:
        msg.iface.id = host_iface_id;
        msg.iface.type = host_iface_types[host_iface_id];
        msg.type = CIOT_MSG_TYPE_GET_CONFIG;
        ciot_iface_send_msg(ifaces[app_iface_id], &msg, CIOT_MSG_SIZE);
        self->state = APP_STATE_WAITING_CONFIG;
        break;
    case APP_STATE_CFG_DONE:
        if(host_iface_id < APP_HOST_IFACE_MQTTC)
        {
            host_iface_id++;
            if(host_iface_id == APP_HOST_IFACE_HTTPC)
            {
                host_iface_id++;
            }
        }
        else
        {
            if(app_iface_id < APP_IFACE_MQTTC)
            {
                app_iface_id++;
                host_iface_id = host_initial_iface;
            }
            else
            {
                CIOT_LOGI(TAG, "Integration tests finished.", "");
                exit(0);
            }
        }
        self->state = APP_STATE_START;
        break;
    default:
        break;
    }
}

static void test_assert(void *v1, void *v2, int size, char *sucess_msg, char *failure_msg)
{
    if (memcmp(v1, v2, size) == 0)
    {
        CIOT_LOGI(TAG, "%s", sucess_msg);
    }
    else
    {
        CIOT_LOGE(TAG, "%s", failure_msg);
    }
}

static ciot_err_t ciot_iface_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args)
{
    app_t *self = (app_t *)args;

    if (event->id != CIOT_IFACE_EVENT_DONE)
    {
        return CIOT_OK;
    }

    switch (self->state)
    {
    case APP_STATE_WAITING_STATUS:
        if(event->msg.iface.type == host_iface_types[host_iface_id])
        {
            char *host_iface = get_iface_name_from_type(host_iface_types[host_iface_id]);
            CIOT_LOGI(TAG, "%s status received", host_iface);
            self->state = APP_STATE_STATUS_DONE;
        }
        break;
    case APP_STATE_WAITING_CONFIG:
        if(event->msg.iface.type == host_iface_types[host_iface_id])
        {
            char *host_iface = get_iface_name_from_type(host_iface_types[host_iface_id]);
            CIOT_LOGI(TAG, "%s config received", host_iface);
            self->state = APP_STATE_CFG_DONE;
        }
        break;
    }

    return CIOT_OK;
}

static char *get_iface_name_from_type(ciot_msg_iface_type_t type)
{
    switch (type)
    {
        case CIOT_IFACE_TYPE_UNKNOWN:
            return "UNKNOWN";
        case CIOT_IFACE_TYPE_STORAGE:
            return "STORAGE";
        case CIOT_IFACE_TYPE_SYSTEM:
            return "SYSTEM";
        case CIOT_IFACE_TYPE_UART:
            return "UART";
        case CIOT_IFACE_TYPE_USB:
            return "USB";
        case CIOT_IFACE_TYPE_TCP:
            return "TCP";
        case CIOT_IFACE_TYPE_ETH:
            return "ETH";
        case CIOT_IFACE_TYPE_WIFI:
            return "WIFI";
        case CIOT_IFACE_TYPE_BLE:
            return "BLE";
        case CIOT_IFACE_TYPE_NTP:
            return "NTP";
        case CIOT_IFACE_TYPE_OTA:
            return "OTA";
        case CIOT_IFACE_TYPE_HTTP_CLIENT:
            return "HTTP_CLIENT";
        case CIOT_IFACE_TYPE_HTTP_SERVER:
            return "HTTP_SERVER";
        case CIOT_IFACE_TYPE_MQTT:
            return "MQTT";
    }
}
