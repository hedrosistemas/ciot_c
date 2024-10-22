/**
 * @file ciot_cli_ota.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-09-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "include/ciot_cli.h"
#include "include/ciot_cli_ota.h"
#include "include/ciot_cli_conn.h"
#include "ciot_ota.h"
#include "ciot_storage_fs.h"
#include "ciot_http_server.h"

#define CIOT_CLI_OTA_DAT_FILE "ota.dat"

static const char *TAG = "ciot_cli_ota";

static int ciot_cli_ota_get(int argc, const char *argv[]);
static int ciot_cli_ota_set(int argc, const char *argv[]);
static int ciot_cli_ota_local(int argc, const char *argv[]);
static int ciot_cli_ota_remote(int argc, const char *argv[]);

static int ciot_cli_ota_send_request(const char *argv[]);

static ciot_err_t ciot_cli_ota_event_handler(ciot_iface_t *iface, ciot_iface_event_t *event, void *args);

int ciot_cli_ota(int argc, const char *argv[])
{
    ARGP(2, "get", ciot_cli_ota_get);
    ARGP(2, "set", ciot_cli_ota_set);
    ARGP(2, "local", ciot_cli_ota_local);
    ARGP(2, "remote", ciot_cli_ota_remote);
    return 0;
}

static int ciot_cli_ota_get(int argc, const char *argv[])
{
    ciot_storage_t storage = ciot_storage_fs_new();
    ciot_msg_data_t *ota_data = ciot_storage_get_data(storage, CIOT_CLI_OTA_DAT_FILE);
    free(storage);

    if (ota_data == NULL)
    {
        printf("ota not configured\n");
        exit(-1);
    }

    if (ota_data->ota != NULL)
    {
        ciot_msg_print(&ota_data->ota->base);
        exit(0);
    }

    exit(-1);
}

static int ciot_cli_ota_set(int argc, const char *argv[])
{
    ciot_msg_data_t ota_data = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg_data__descriptor),
        .ota = &(ciot_ota_data_t){
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__ota_data__descriptor),
            .config = &(ciot_ota_cfg_t){
                .base = PROTOBUF_C_MESSAGE_INIT(&ciot__ota_cfg__descriptor),
                .url = (char *)argv[3],
                .force = (argc >= 4) ? atoi(argv[4]) : false,
                .encrypted = (argc >= 5) ? atoi(argv[5]) : false,
                .restart = (argc >= 6) ? atoi(argv[6]) : true,
            },
        },
    };
    printf("saving ota configuration:\n");
    ciot_msg_print(&ota_data.base);
    ciot_storage_t storage = ciot_storage_fs_new();
    ciot_storage_set_data(storage, CIOT_CLI_OTA_DAT_FILE, &ota_data);
    exit(0);
    return 0;
}

static int ciot_cli_ota_local(int argc, const char *argv[])
{
    ciot_http_server_t http_server = ciot_http_server_new(CIOT_HANDLE);
    ciot_http_server_cfg_t cfg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__http_server_cfg__descriptor),
        .address = (char*)argv[3],
        .route = "/v1/ciot/ota",
        .port = 8181,
        .root = argc > 6 ? (char*)argv[6] : ".",
    };
    printf("starting ota server:\n");
    ciot_msg_print(&cfg.base);
    ciot_iface_set_event_handler((ciot_iface_t *)http_server, ciot_cli_ota_event_handler, (void *)argv);
    ciot_http_server_start(http_server, &cfg);
    return 0;
}

static int ciot_cli_ota_remote(int argc, const char *argv[])
{
    return 0;
}

static int ciot_cli_ota_send_request(const char *argv[])
{
    ciot_storage_t storage = ciot_storage_fs_new();
    char url[128] = {0};
    sprintf(url, "%s:8181/%s", argv[3], argv[4]);
    ciot_msg_t msg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg__descriptor),
        .type = CIOT__MSG_TYPE__MSG_TYPE_START,
        .iface = &(ciot_iface_info_t){
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__iface_info__descriptor),
            .id = atoi(argv[5]),
            .type = CIOT__IFACE_TYPE__IFACE_TYPE_OTA,
        },
        .data = &(ciot_msg_data_t){
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg_data__descriptor),
            .ota = &(ciot_ota_data_t){
                .base = PROTOBUF_C_MESSAGE_INIT(&ciot__ota_data__descriptor),
                .config = &(ciot_ota_cfg_t){
                    .base = PROTOBUF_C_MESSAGE_INIT(&ciot__ota_cfg__descriptor),
                    .url = url,
                    .force = true,
                    .encrypted = false,
                    .restart = true,
                },
            },
        },
    };
    printf("Sending OTA command\n");
    ciot_msg_print(&msg.base);
    ciot_cli_conn_send_req(&msg, ciot_cli_ota_event_handler);
    return 0;
}

static ciot_err_t ciot_cli_ota_event_handler(ciot_iface_t *iface, ciot_iface_event_t *event, void *args)
{
    const char **argv = args;

    if (event->type == CIOT_IFACE_EVENT_STARTED)
    {
        printf("OTA server started\n");
        return ciot_cli_ota_send_request(argv);
    }

    if (event->type == CIOT_IFACE_EVENT_DONE ||
        event->type == CIOT_IFACE_EVENT_ERROR)
    {
        ciot_msg_print(&event->msg->base);
    }

    CIOT_LOGI(TAG, "event received: %d", event->type);
    
    return CIOT__ERR__OK;
}
