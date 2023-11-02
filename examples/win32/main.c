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

#include "ciot_sys.h"
#include "ciot_uart.h"
#include "ciot_https.h"
#include "ciot_httpc.h"
#include "ciot_httpc.h"
#include "ciot_mqttc.h"

#include "ciot_custom_config.h"

static struct mg_mgr mgr;

static ciot_sys_t sys;
static ciot_uart_t uart;
static ciot_https_t https;
static ciot_httpc_t httpc;
static ciot_mqttc_t mqttc;

static ciot_err_t uart_start(void);
static ciot_err_t https_start(void);
static ciot_err_t httpc_start(void);
static ciot_err_t mqttc_start(void);

int main()
{
    sys = ciot_sys_new(NULL);

    ciot_sys_init();
    mg_mgr_init(&mgr);

    uart_start();
    https_start();
    httpc_start();
    mqttc_start();

    while (true)
    {
        ciot_uart_task(uart);
        mg_mgr_poll(&mgr, 1000);
    }

    return 0;
}

static ciot_err_t uart_start(void)
{
    uart = ciot_uart_new(NULL);
    ciot_uart_cfg_t uart_cfg = {
        .baud_rate = CIOT_CONFIG_UART_BAUD,
        .num = CIOT_CONFIG_UART_PORT,
    };
    return ciot_uart_start(uart, &uart_cfg);
}

static ciot_err_t https_start(void)
{
    https = ciot_https_new(&mgr);
    ciot_https_cfg_t https_cfg = {
        .address = "127.0.0.1",
        .port = 8080,
        .route = "/v1/ciot",
    };
    return ciot_https_start(https, &https_cfg);
}

static ciot_err_t httpc_start(void)
{
    httpc = ciot_httpc_new(&mgr);
    ciot_httpc_cfg_t httpc_cfg = {
        .url = "v1/ciot",
        .transport = CIOT_HTTPC_TRANSPORT_TCP,  
        .method = CIOT_HTTPC_METHOD_POST,
        .timeout = CIOT_CONFIG_HTTPC_TIMEOUT,
    };
    return ciot_httpc_start(httpc, &httpc_cfg);
}

static ciot_err_t mqttc_start(void)
{
    mqttc = ciot_mqttc_new(&mgr);
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
    return ciot_mqttc_start(mqttc, &mqtt_cfg);
}

