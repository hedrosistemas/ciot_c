/**
 * @file ciot_cli_sys.c,
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ciot_sys.h"
#include "include/ciot_cli.h"
#include "include/ciot_cli_conn.h"
#include "include/ciot_cli_sys.h"

static const char *TAG = "ciot_cli_sys";

static int ciot_cli_sys_rst(int argc, char const *argv[]);
static int ciot_cli_sys_inf(int argc, char const *argv[]);

int ciot_cli_sys(int argc, char const *argv[])
{
    ARGP(2, "rst", ciot_cli_sys_rst);
    ARGP(2, "inf", ciot_cli_sys_inf);
}

static int ciot_cli_sys_rst(int argc, char const *argv[])
{
    CIOT_LOGI(TAG, "sending system restart request id:%s", argv[3]);
    ciot_msg_t msg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg__descriptor),
        .type = CIOT__MSG_TYPE__MSG_TYPE_REQUEST,
        .iface = &(ciot_iface_info_t) {
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__iface_info__descriptor),
            .id = atoi(argv[3]),
            .type = CIOT__IFACE_TYPE__IFACE_TYPE_SYS,
        },
        .data = &(ciot_msg_data_t) {
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg_data__descriptor),
            .sys = &(ciot_sys_data_t) {
                .base = PROTOBUF_C_MESSAGE_INIT(&ciot__sys_data__descriptor),
                .request = &(ciot_sys_req_t) {
                    .base = PROTOBUF_C_MESSAGE_INIT(&ciot__sys_req__descriptor),
                    .type = CIOT__SYS_REQ_TYPE__SYS_REQ_TYPE_RESTART,
                }
            }
        }
    };
    return ciot_cli_conn_send_msg(&msg);
}

static int ciot_cli_sys_inf(int argc, char const *argv[])
{
    CIOT_LOGI(TAG, "requesting system information id:%s", argv[3]);
    ciot_msg_t msg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg__descriptor),
        .type = CIOT__MSG_TYPE__MSG_TYPE_INFO,
        .iface = &(ciot_iface_info_t) {
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__iface_info__descriptor),
            .id = atoi(argv[3]),
            .type = CIOT__IFACE_TYPE__IFACE_TYPE_SYS,
        },
    };
    return ciot_cli_conn_send_msg(&msg);
}
