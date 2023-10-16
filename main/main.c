/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdbool.h>

#include "ciot.h"
#include "ciot_https.h"
#include "ciot_httpc.h"
#include "ciot_mqttc.h"

static void test(ciot_httpc_t httpc);

int app_main(void)
{
    ciot_https_t https = ciot_https_new(NULL);
    ciot_httpc_t httpc = ciot_httpc_new(NULL);
    ciot_mqttc_t mqtt = ciot_mqttc_new(NULL);
    ciot_t ciot = ciot_new();

    ciot_https_cfg_t https_cfg = {
        .address = "http://0.0.0.0:4444",
        .route = "/",
    };
    ciot_https_start(https, &https_cfg);

    ciot_httpc_cfg_t httpc_cfg = {
        .url = "http://localhost:4444",
        .method = CIOT_HTTPC_METHOD_POST,
        .timeout = 50000
    };
    ciot_httpc_start(httpc, &httpc_cfg);

    ciot_iface_t *ifaces[] = { 
        (ciot_iface_t*)https,
        (ciot_iface_t*)httpc,
        (ciot_iface_t*)mqtt 
    };
    ciot_set_iface_list(ciot, ifaces, 2);

    test(httpc);

    while (true)
    {

    }
    return 0;
}

static void test(ciot_httpc_t httpc)
{
    ciot_msg_t msg = {
        .iface.id = 1,
        .iface.type = CIOT_IFACE_TYPE_HTTP_CLIENT,
        .type = CIOT_MSG_TYPE_GET_STATUS,
    };
    ciot_httpc_send_data(httpc, (uint8_t*)&msg, CIOT_MSG_SIZE - sizeof(msg.error));
}
