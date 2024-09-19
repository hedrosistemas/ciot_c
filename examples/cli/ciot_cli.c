/**
 * @file ciot_cli.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ciot.h"

#include "include/ciot_cli.h"
#include "include/ciot_cli_conn.h"
#include "include/ciot_cli_sys.h"
#include "include/ciot_cli_wifi.h"
#include "include/ciot_cli_mqttc.h"
#include "include/ciot_cli_default.h"

static const char *TAG = "ciot_cli";

static int default_argc = DEFAULT_ARGC_MQTTC_START;
static const char *default_argv[] = DEFAULT_ARGV_MQTTC_START;

static bool run_cmd = false;

static int ciot_cli_list(int argc, char const *argv[]);
static ciot_err_t ciot_cli_list_process_rsp(ciot_iface_t *sender, ciot_iface_event_t *event, void *args);
static int ciot_cli_info(int argc, char const *argv[]);
static int ciot_cli_status(int argc, char const *argv[]);
static int ciot_cli_cfg(int argc, char const *argv[]);
static int ciot_cli_save(int argc, char const *argv[]);

int main(int argc, char const *argv[])
{
    CIOT_LOGI(TAG, "hg tcp cli running");

    if(argc == 1)
    {
        default_argv[0] = argv[0];
        argc = default_argc;
        argv = default_argv;
    }

    ARGP(1, "conn", ciot_cli_conn);

    ciot_cli_conn_start();
    
    while (true)
    {
        ciot_cli_conn_task();
        if(run_cmd)
        {
            ARGP(1, "list", ciot_cli_list);
            ARGP(1, "save", ciot_cli_save);
            ARGP(1, "info", ciot_cli_info);
            ARGP(1, "status", ciot_cli_status);
            ARGP(1, "cfg", ciot_cli_cfg);
            ARGP(1, "conn", ciot_cli_conn);
            ARGP(1, "sys", ciot_cli_sys);
            ARGP(1, "wifi", ciot_cli_wifi);
            ARGP(1, "mqttc", ciot_cli_mqttc);
            run_cmd = false;
        }
    }

    return 0;
}

void ciot_cli_run_cmd()
{
    run_cmd = true;
}

static int ciot_cli_list(int argc, char const *argv[])
{
    ciot_msg_t msg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg__descriptor),
        .type = CIOT__MSG_TYPE__MSG_TYPE_INFO,
        .iface = &(ciot_iface_info_t){
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__iface_info__descriptor),
            .id = 0,
            .type = CIOT__IFACE_TYPE__IFACE_TYPE_CIOT,
        },
    };
    ciot_cli_conn_send_req(&msg, ciot_cli_list_process_rsp);
}

static ciot_err_t ciot_cli_list_process_rsp(ciot_iface_t *sender, ciot_iface_event_t *event, void *args)
{
    ciot_msg_t *msg = event->msg;
    if(msg->iface->id == 0 && 
       msg->iface->type == CIOT__IFACE_TYPE__IFACE_TYPE_CIOT &&
       msg->type == CIOT__MSG_TYPE__MSG_TYPE_INFO)
    {
        uint8_t count = msg->data->ciot->info->ifaces.len;
        uint8_t *types = msg->data->ciot->info->ifaces.data;
        for (size_t i = 0; i < count; i++)
        {
            printf("id:%d\ttype:%d [%s]\n", i, types[i], ciot__iface_type__descriptor.values[types[i]].name);
        }
    }
}

static int ciot_cli_info(int argc, char const *argv[])
{
    printf("getting information of interface id:%s, type:%s\n", argv[2], argv[3]);
    ciot_msg_t msg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg__descriptor),
        .type = CIOT__MSG_TYPE__MSG_TYPE_INFO,
        .iface = &(ciot_iface_info_t){
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__iface_info__descriptor),
            .id = atoi(argv[2]),
            .type = atoi(argv[3]),
        },
    };
    ciot_cli_conn_send_msg(&msg);
}

static int ciot_cli_status(int argc, char const *argv[])
{
    printf("getting status information of interface id:%s, type:%s\n", argv[2], argv[3]);
    ciot_msg_t msg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg__descriptor),
        .type = CIOT__MSG_TYPE__MSG_TYPE_STATUS,
        .iface = &(ciot_iface_info_t){
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__iface_info__descriptor),
            .id = atoi(argv[2]),
            .type = atoi(argv[3]),
        },
    };
    ciot_cli_conn_send_msg(&msg);
}

static int ciot_cli_cfg(int argc, char const *argv[])
{
    printf("getting information of interface id:%s, type:%s\n", argv[2], argv[3]);
    ciot_msg_t msg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg__descriptor),
        .type = CIOT__MSG_TYPE__MSG_TYPE_CONFIG,
        .iface = &(ciot_iface_info_t){
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__iface_info__descriptor),
            .id = atoi(argv[2]),
            .type = atoi(argv[3]),
        },
    };
    ciot_cli_conn_send_msg(&msg);
}

static int ciot_cli_save(int argc, char const *argv[])
{
    printf("saving cfg of interface id:%s\n", argv[2]);
    ciot_msg_t msg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg__descriptor),
        .type = CIOT__MSG_TYPE__MSG_TYPE_REQUEST,
        .iface = &(ciot_iface_info_t){
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__iface_info__descriptor),
            .id = 0,
            .type = CIOT__IFACE_TYPE__IFACE_TYPE_CIOT,
        },
        .data = &(ciot_msg_data_t) {
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg_data__descriptor),
            .ciot = &(ciot_data_t) {
                .base = PROTOBUF_C_MESSAGE_INIT(&ciot__ciot_data__descriptor),
                .request = &(ciot_req_t) {
                    .base = PROTOBUF_C_MESSAGE_INIT(&ciot__ciot_req__descriptor),
                    .type = CIOT__CIOT_REQ_TYPE__CIOT_REQ_TYPE_SAVE_IFACE_CFG,
                    .iface_id = atoi(argv[2]),
                }
            }
        }
    };
    ciot_cli_conn_send_msg(&msg);
}
