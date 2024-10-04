/**
 * @file ciot_cli_wifi.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ciot_wifi.h"
#include "include/ciot_cli.h"
#include "include/ciot_cli_conn.h"
#include "include/ciot_cli_wifi.h"

static int ciot_cli_wifi_sta(int argc, char const *argv[]);
static int ciot_cli_wifi_stop(int argc, char const *argv[]);
static int ciot_cli_wifi_start(int argc, char const *argv[]);

static const char *TAG = "ciot_cli";

int ciot_cli_wifi(int argc, char const *argv[])
{
    ARGP(2, "stop", ciot_cli_wifi_stop);
    ARGP(2, "start", ciot_cli_wifi_start);
}

static int ciot_cli_wifi_stop(int argc, char const *argv[])
{
    CIOT_LOGI(TAG, "stopping wifi station id:%s", argv[3]);
    ciot_msg_t msg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg__descriptor),
        .type = CIOT__MSG_TYPE__MSG_TYPE_STOP,
        .iface = &(ciot_iface_info_t) {
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__iface_info__descriptor),
            .id = atoi(argv[3]),
            .type = CIOT__IFACE_TYPE__IFACE_TYPE_WIFI,
        },
    };
    return ciot_cli_conn_send_msg(&msg);
}

static int ciot_cli_wifi_start(int argc, char const *argv[])
{
    CIOT_LOGI(TAG, "starting wifi station ssid:%s pass:%s id:%s", argv[4], argv[5], argv[6]);
    ciot_msg_t msg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg__descriptor),
        .type = CIOT__MSG_TYPE__MSG_TYPE_START,
        .iface = &(ciot_iface_info_t) {
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__iface_info__descriptor),
            .type = CIOT__IFACE_TYPE__IFACE_TYPE_WIFI,
            .id = atoi(argv[6]),
        },
        .data = &(ciot_msg_data_t) {
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg_data__descriptor),
            .wifi = &(ciot_wifi_data_t) {
                .base = PROTOBUF_C_MESSAGE_INIT(&ciot__wifi_data__descriptor),
                .config = &(ciot_wifi_cfg_t) {
                    .base = PROTOBUF_C_MESSAGE_INIT(&ciot__wifi_cfg__descriptor),
                    .type = atoi(argv[3]),
                    .ssid = (char*)argv[4],
                    .password = (char*)argv[5],
                }
            }
        }
    };
    return ciot_cli_conn_send_msg(&msg);
}
