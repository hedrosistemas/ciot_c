/**
 * @file ciot_cli_mqttc.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ciot_mqtt_client.h"
#include "include/ciot_cli.h"
#include "include/ciot_cli_conn.h"
#include "include/ciot_cli_mqttc.h"

static int ciot_cli_mqttc_stop(int argc, char const *argv[]);
static int ciot_cli_mqttc_start(int argc, char const *argv[]);

static const char *TAG = "ciot_cli";

int ciot_cli_mqttc(int argc, char const *argv[])
{
    ARGP(2, "stop", ciot_cli_mqttc_stop);
    ARGP(2, "start", ciot_cli_mqttc_start);
}

static int ciot_cli_mqttc_stop(int argc, char const *argv[])
{
    CIOT_LOGI(TAG, "stopping mqtt client id:%s", argv[4]);
    ciot_msg_t msg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg__descriptor),
        .type = CIOT__MSG_TYPE__MSG_TYPE_STOP,
        .iface = &(ciot_iface_info_t) {
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__iface_info__descriptor),
            .id = atoi(argv[4]),
            .type = CIOT__IFACE_TYPE__IFACE_TYPE_MQTT,
        },
    };
    return ciot_cli_conn_send_msg(&msg);
}

static int ciot_cli_mqttc_start(int argc, char const *argv[])
{
    ciot_msg_t msg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg__descriptor),
        .type = CIOT__MSG_TYPE__MSG_TYPE_START,
        .iface = &(ciot_iface_info_t) {
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__iface_info__descriptor),
            .id = atoi(argv[9]),
            .type = CIOT__IFACE_TYPE__IFACE_TYPE_MQTT,
        },
        .data = &(ciot_msg_data_t) {
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg_data__descriptor),
            .mqtt_client = &(ciot_mqtt_client_data_t) {
                .base = PROTOBUF_C_MESSAGE_INIT(&ciot__mqtt_client_data__descriptor),
                .config = &(ciot_mqtt_client_cfg_t) {
                    .base = PROTOBUF_C_MESSAGE_INIT(&ciot__mqtt_client_cfg__descriptor),
                    .client_id = (char*)argv[3],
                    .url = (char*)argv[4],
                    .user = (char*)argv[5],
                    .password = (char*)argv[6],
                    .topics = &(ciot_mqtt_client_topics_t) {
                        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__mqtt_client_topics_cfg__descriptor),
                        .pub = (char*)argv[7],
                        .sub = (char*)argv[8],
                    }
                },
            }
        }
    };
    printf("starting mqtt client:\n");
    ciot_msg_print(&msg.data->mqtt_client->config->base);
    return ciot_cli_conn_send_msg(&msg);
}
