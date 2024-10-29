/**
 * @file ciot_cli_conn.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-09-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "include/ciot_cli_conn.h"
#include "include/ciot_cli.h"
#include "ciot_utils.h"

#include "ciot.h"
#include "ciot_msg.h"

#include "ciot_storage_fs.h"
#include "ciot_sys.h"
#include "ciot_uart.h"
#include "ciot_http_client.h"
#include "ciot_mqtt_client.h"
#include "ciot_timer.h"

static void ciot_cli_conn_init(void);
static int ciot_cli_conn_list(int argc, char const *argv[]);
static int ciot_cli_conn_get(int argc, char const *argv[]);
static int ciot_cli_conn_select(int argc, char const *argv[]);
static int ciot_cli_conn_test(int argc, char const *argv[]);
static int ciot_cli_conn_uart(int argc, char const *argv[]);
static int ciot_cli_conn_http(int argc, char const *argv[]);
static int ciot_cli_conn_mqtt(int argc, char const *argv[]);
static ciot_msg_data_t *ciot_cli_get_conn_data(void);
static void ciot_cli_set_conn_data(ciot_msg_data_t *conn_data);
static ciot_err_t ciot_cli_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args);

static const char *TAG = "ciot_tcp_conn";
static ciot_t ciot = NULL;
static ciot_iface_t *conn = NULL;
static ciot_msg_data_t *cfgs[2];
static ciot_iface_t *ifaces[2];
static ciot_iface_event_handler_fn *req_handler;

static bool ciot_started = false;
static char mqtt_client_id[48];

ciot_err_t ciot_cli_conn_start()
{
    ciot = ciot_new();

    ciot_storage_t storage = ciot_storage_fs_new();
    ciot_msg_data_t *conn_data = ciot_storage_get_data(storage, CIOT_CLI_CONN_DAT_FILE);
    ciot_iface_type_t type = conn_data && conn_data->payload.len == 1 ? conn_data->payload.data[0] : CIOT__IFACE_TYPE__IFACE_TYPE_UNKNOWN;

    if (type == CIOT__IFACE_TYPE__IFACE_TYPE_UNKNOWN || conn_data == NULL)
    {
        printf("ERROR: connection not configured.\n");
        exit(CIOT__ERR__CONNECTION);
    }

    if (type == CIOT__IFACE_TYPE__IFACE_TYPE_UART && conn_data && conn_data->uart)
    {
        conn = (ciot_iface_t *)ciot_uart_new(CIOT_HANDLE);
    }

    if (type == CIOT__IFACE_TYPE__IFACE_TYPE_HTTP_CLIENT && conn_data && conn_data->http_client)
    {
        conn = (ciot_iface_t *)ciot_http_client_new(CIOT_HANDLE);
    }

    if (type == CIOT__IFACE_TYPE__IFACE_TYPE_MQTT && conn_data && conn_data->mqtt_client)
    {
        conn = (ciot_iface_t *)ciot_mqtt_client_new(CIOT_HANDLE);
        sprintf(mqtt_client_id, "%s-%llu", conn_data->mqtt_client->config->client_id, ciot_timer_now());
        conn_data->mqtt_client->config->client_id = mqtt_client_id;
    }

    if (conn == NULL)
    {
        printf("selected connection (%s) is not configured\n", ciot__iface_type__descriptor.values[type].name);
        exit(CIOT__ERR__CONNECTION);
    }

    cfgs[1] = conn_data;
    ifaces[0] = (ciot_iface_t *)ciot;
    ifaces[1] = conn;

    ciot_cfg_t cfg = {
        .ifaces = ifaces,
        .cfgs = cfgs,
        .count = conn_data ? 2 : 1,
    };
    ciot_iface_set_event_handler((ciot_iface_t *)ciot, ciot_cli_event_handler, NULL);
    ciot_start(ciot, &cfg);
}

ciot_err_t ciot_cli_conn_task()
{
    ciot_task(ciot);
}

int ciot_cli_conn(int argc, char const *argv[])
{
    ARGP(2, "list", ciot_cli_conn_list);
    ARGP(2, "get", ciot_cli_conn_get);
    ARGP(2, "select", ciot_cli_conn_select);
    ARGP(2, "test", ciot_cli_conn_test);
    ARGP(2, "uart", ciot_cli_conn_uart);
    ARGP(2, "http", ciot_cli_conn_http);
    ARGP(2, "mqtt", ciot_cli_conn_mqtt);
    return 0;
}

ciot_err_t ciot_cli_conn_send_msg(ciot_msg_t *msg)
{
    ciot_msg_print(&msg->base);
    return ciot_iface_send_req(conn, msg);
}

ciot_err_t ciot_cli_conn_send_req(ciot_msg_t *msg, ciot_iface_event_handler_fn *req_handler_fn)
{
    req_handler = req_handler_fn;
    ciot_msg_print(&msg->base);
    return ciot_iface_send_req(conn, msg);
}

ciot_err_t ciot_cli_conn_send_data(uint8_t *data, int size)
{
    return conn->send_data(conn, data, size);
}

static int ciot_cli_conn_list(int argc, char const *argv[])
{
    for (size_t i = 0; i < ciot__iface_type__descriptor.n_values; i++)
    {
        printf("%d: %s\n", i, ciot__iface_type__descriptor.values[i].name);
    }
    exit(0);
}

static int ciot_cli_conn_get(int argc, char const *argv[])
{
    ciot_storage_t storage = ciot_storage_fs_new();
    ciot_msg_data_t *conn_data = ciot_storage_get_data(storage, CIOT_CLI_CONN_DAT_FILE);
    ciot_iface_type_t type = conn_data && conn_data->payload.len == 1 ? conn_data->payload.data[0] : CIOT__IFACE_TYPE__IFACE_TYPE_UNKNOWN;
    free(storage);

    if (conn_data == NULL)
    {
        printf("connection not configured\n");
        exit(-1);
    }

    printf("connection config:\n");
    printf("selected connection: %s\n", ciot__iface_type__descriptor.values[type].name);
    ciot_msg_print(&conn_data->base);
    exit(0);
}

static int ciot_cli_conn_select(int argc, char const *argv[])
{
    ciot_iface_type_t type = atoi(argv[3]);
    ciot_storage_t storage = ciot_storage_fs_new();
    ciot_msg_data_t *conn_data = ciot_storage_get_data(storage, CIOT_CLI_CONN_DAT_FILE);
    conn_data->payload.len = 1;
    conn_data->payload.data = (uint8_t*)&type;
    printf("selected interface %s\n", ciot__iface_type__descriptor.values[type].name);
    ciot_storage_set_data(storage, CIOT_CLI_CONN_DAT_FILE, conn_data);
    exit(0);
}

static int ciot_cli_conn_test(int argc, char const *argv[])
{
    if (!ciot_started)
    {
        return 0;
    }
    ciot_msg_t msg = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg__descriptor),
        .type = CIOT__MSG_TYPE__MSG_TYPE_INFO,
        .iface = &(ciot_iface_info_t){
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__iface_info__descriptor),
            .id = 0,
            .type = CIOT__IFACE_TYPE__IFACE_TYPE_CIOT,
        },
    };
    return ciot_cli_conn_send_msg(&msg);
}

static int ciot_cli_conn_uart(int argc, char const *argv[])
{
    ciot_msg_data_t *conn_data = ciot_cli_get_conn_data();
    ciot_iface_type_t type = CIOT__IFACE_TYPE__IFACE_TYPE_UART;
    ciot_uart_data_t uart_data = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__uart_data__descriptor),
        .config = &(ciot_uart_cfg_t){
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__uart_cfg__descriptor),
            .num = argc > 3 ? atoi(argv[3]) : 0,
            .baud_rate = argc > 4 ? atoi(argv[4]) : 115200,
            .dtr = argc > 5 ? atoi(argv[5]) : 0,
        },
    };
    printf("Configuring uart:\n");
    conn_data->payload.len = 1;
    conn_data->payload.data = (uint8_t*)&type;
    conn_data->uart = &uart_data;
    ciot_msg_print(&conn_data->uart->config->base);
    ciot_cli_set_conn_data(conn_data);
    exit(0);
    return 0;
}

static int ciot_cli_conn_http(int argc, char const *argv[])
{
    ciot_msg_data_t *conn_data = ciot_cli_get_conn_data();
    ciot_iface_type_t type = CIOT__IFACE_TYPE__IFACE_TYPE_HTTP_CLIENT;
    ciot_http_client_data_t httpc_data = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__http_client_data__descriptor),
        .config = &(ciot_http_client_cfg_t){
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__http_client_cfg__descriptor),
            .url = argc > 3 ? (char *)argv[3] : "http://127.0.0.1/v1/ciot",
            .method = CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_POST,
            .transport = CIOT__HTTP_CLIENT_TRANSPORT_TYPE__HTTP_TRANSPORT_TCP,
            .timeout = argc > 4 ? atoi(argv[4]) : 20000,
        },
    };
    printf("Configuring http:\n");
    conn_data->payload.len = 1;
    conn_data->payload.data = (uint8_t*)&type;
    conn_data->http_client = &httpc_data;
    ciot_msg_print(&conn_data->http_client->config->base);
    ciot_cli_set_conn_data(conn_data);
    exit(0);
    return 0;
}

static int ciot_cli_conn_mqtt(int argc, char const *argv[])
{
    ciot_msg_data_t *conn_data = ciot_cli_get_conn_data();
    ciot_iface_type_t type = CIOT__IFACE_TYPE__IFACE_TYPE_MQTT;
    char client_id[64];
    sprintf(client_id, "%s-%llu", argv[3], ciot_timer_now());
    ciot_mqtt_client_data_t mqtt_data = {
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
    };
    printf("configuring mqtt:\n");
    conn_data->payload.len = 1;
    conn_data->payload.data = (uint8_t*)&type;
    conn_data->mqtt_client = &mqtt_data;
    ciot_msg_print(&conn_data->mqtt_client->config->base);
    ciot_cli_set_conn_data(conn_data);
    exit(0);
    return 0;
}

static ciot_msg_data_t *ciot_cli_get_conn_data(void)
{
    ciot_storage_t storage = ciot_storage_fs_new();
    ciot_msg_data_t *conn_data = ciot_storage_get_data(storage, CIOT_CLI_CONN_DAT_FILE);
    free(storage);
    if(conn_data == NULL)
    {
        conn_data = calloc(1, sizeof(ciot_msg_data_t));
        ciot__msg_data__init(conn_data);
    }
    return conn_data;
}

static void ciot_cli_set_conn_data(ciot_msg_data_t *conn_data)
{
    ciot_storage_t storage = ciot_storage_fs_new();
    ciot_storage_set_data(storage, CIOT_CLI_CONN_DAT_FILE, conn_data);
    free(storage);
}

static ciot_err_t ciot_cli_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args)
{
    switch (event->type)
    {
    case CIOT_IFACE_EVENT_UNKNOWN:
        CIOT_LOGI(TAG, "CIOT_IFACE_EVENT_UNKNOWN");
        break;
    case CIOT_IFACE_EVENT_DATA:
        CIOT_LOGI(TAG, "CIOT_IFACE_EVENT_DATA");
        break;
    case CIOT_IFACE_EVENT_STARTED:
        CIOT_LOGI(TAG, "CIOT_IFACE_EVENT_STARTED");
        if (sender->info.type == CIOT__IFACE_TYPE__IFACE_TYPE_CIOT)
        {
            ciot_started = true;
            ciot_cli_run_cmd();
        }
        break;
    case CIOT_IFACE_EVENT_STOPPED:
        CIOT_LOGI(TAG, "CIOT_IFACE_EVENT_STOPPED");
        exit(-1);
        break;
    case CIOT_IFACE_EVENT_ERROR:
        CIOT_LOGI(TAG, "CIOT_IFACE_EVENT_ERROR");
        ciot_msg_print(&event->msg->base);
        exit(-1);
        break;
    case CIOT_IFACE_EVENT_REQUEST:
        CIOT_LOGI(TAG, "CIOT_IFACE_EVENT_REQUEST");
        ciot_msg_print(&event->msg->base);
        break;
    case CIOT_IFACE_EVENT_DONE:
        CIOT_LOGI(TAG, "CIOT_IFACE_EVENT_DONE");
        if (req_handler != NULL)
        {
            req_handler(sender, event, args);
        }
        else
        {
            ciot_msg_print(&event->msg->base);
            exit(0);
        }
        break;
    case CIOT_IFACE_EVENT_INTERNAL:
        CIOT_LOGI(TAG, "CIOT_IFACE_EVENT_INTERNAL");
        break;
    case CIOT_IFACE_EVENT_CUSTOM:
        CIOT_LOGI(TAG, "CIOT_IFACE_EVENT_CUSTOM");
        break;
    default:
        CIOT_LOGI(TAG, "Other event type: %d", event->type);
        break;
    }
    return CIOT__ERR__OK;
}
