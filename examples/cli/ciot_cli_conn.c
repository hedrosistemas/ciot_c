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

#include "ciot.h"
#include "ciot_msg.h"

#include "ciot_storage_fs.h"
#include "ciot_sys.h"
#include "ciot_http_client.h"

static void ciot_cli_conn_init(void);
static int ciot_cli_conn_get(int argc, char const *argv[]);
static int ciot_cli_conn_test(int argc, char const *argv[]);
static int ciot_cli_conn_http(int argc, char const *argv[]);
static ciot_err_t ciot_cli_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args);
static void ciot_cli_conn_print_msg(const ProtobufCMessage *message);

static const char *TAG = "hg_tcp_conn";
static ciot_t ciot = NULL;
static ciot_iface_t *conn = NULL;
static ciot_msg_data_t *cfgs[2];
static ciot_iface_t *ifaces[2];
static ciot_iface_event_handler_fn *req_handler;

static bool ciot_started = false;

ciot_err_t ciot_cli_conn_start()
{
    ciot = ciot_new();

    ciot_storage_t storage = ciot_storage_fs_new();
    ciot_msg_data_t *conn_dat = ciot_storage_get_data(storage, CIOT_CLI_CONN_DAT_FILE);

    if (conn_dat->http_client != NULL)
    {
        conn = (ciot_iface_t *)ciot_http_client_new(CIOT_HANDLE);
    }

    cfgs[1] = conn_dat;
    ifaces[0] = (ciot_iface_t *)ciot;
    ifaces[1] = conn;

    ciot_cfg_t cfg = {
        .ifaces = ifaces,
        .cfgs = cfgs,
        .count = 1,
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
    ARGP(2, "get", ciot_cli_conn_get);
    ARGP(2, "test", ciot_cli_conn_test);
    ARGP(2, "http", ciot_cli_conn_http);
    return 0;
}

ciot_err_t ciot_cli_conn_send_msg(ciot_msg_t *msg)
{
    return ciot_iface_send_req(conn, msg);
}

ciot_err_t ciot_cli_conn_send_req(ciot_msg_t *msg, ciot_iface_event_handler_fn *req_handler_fn)
{
    req_handler = req_handler_fn;
    return ciot_iface_send_req(conn, msg);
}

static int ciot_cli_conn_get(int argc, char const *argv[])
{
    ciot_storage_t storage = ciot_storage_fs_new();
    ciot_msg_data_t *conn_data = ciot_storage_get_data(storage, CIOT_CLI_CONN_DAT_FILE);
    free(storage);

    if (conn_data == NULL)
    {
        printf("connection not configured\n");
        exit(-1);
    }

    if (conn_data->http_client != NULL)
    {
        printf("connection config:\n");
        printf("type: http\n");
        printf("url:  %s", conn_data->http_client->config->url);
        exit(0);
    }

    exit(-1);
}

static int ciot_cli_conn_test(int argc, char const *argv[])
{
    if(!ciot_started)
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

static int ciot_cli_conn_http(int argc, char const *argv[])
{
    ciot_msg_data_t conn_data = {
        .base = PROTOBUF_C_MESSAGE_INIT(&ciot__msg_data__descriptor),
        .http_client = &(ciot_http_client_data_t){
            .base = PROTOBUF_C_MESSAGE_INIT(&ciot__http_client_data__descriptor),
            .config = &(ciot_http_client_cfg_t){
                .base = PROTOBUF_C_MESSAGE_INIT(&ciot__http_client_cfg__descriptor),
                .method = CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_POST,
                .transport = CIOT__HTTP_CLIENT_TRANSPORT_TYPE__HTTP_TRANSPORT_TCP,
                .timeout = 20000}}};
    if (argv[3])
    {
        printf("configuring http url:%s\n", argv[3]);
        conn_data.http_client->config->url = (char *)argv[3];
    }
    ciot_storage_t storage = ciot_storage_fs_new();
    ciot_storage_set_data(storage, CIOT_CLI_CONN_DAT_FILE, &conn_data);
    free(storage);
    exit(0);
    return 0;
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
        exit(-1);
        break;
    case CIOT_IFACE_EVENT_REQUEST:
        CIOT_LOGI(TAG, "CIOT_IFACE_EVENT_REQUEST");
        break;
    case CIOT_IFACE_EVENT_DONE:
        CIOT_LOGI(TAG, "CIOT_IFACE_EVENT_DONE");
        if(req_handler != NULL) req_handler(sender, event, args);
        else ciot_cli_conn_print_msg(&event->msg->base);
        exit(0);
        break;
    case CIOT_IFACE_EVENT_INTERNAL:
        CIOT_LOGI(TAG, "CIOT_IFACE_EVENT_INTERNAL");
        break;
    case CIOT_IFACE_EVENT_CUSTOM:
        CIOT_LOGI(TAG, "CIOT_IFACE_EVENT_CUSTOM");
        break;
    default:
        break;
    }
    return CIOT_ERR__OK;
}

static void ciot_cli_conn_print_msg(const ProtobufCMessage *message)
{
    const ProtobufCFieldDescriptor *field_desc;
    unsigned i;
    static int depth = 0;

    if(message == NULL) return;

    for (i = 0; i < message->descriptor->n_fields; i++)
    {
        field_desc = &message->descriptor->fields[i];
        const void *field = ((const char *)message) + field_desc->offset;

        if(field_desc->type == PROTOBUF_C_TYPE_MESSAGE && (*(ProtobufCMessage**)field) == NULL)
        {
            continue;
        }

        for (size_t i = 0; i < depth; i++)
        {
            printf(" ");
        }

        printf("%s: ", field_desc->name);

        switch (field_desc->type)
        {
        case PROTOBUF_C_TYPE_INT32:
            printf("%d\n", *(int32_t *)field);
            break;
        case PROTOBUF_C_TYPE_UINT32:
            printf("%u\n", *(uint32_t *)field);
            break;
        case PROTOBUF_C_TYPE_INT64:
            printf("%" PRId64 "\n", *(int64_t *)field);
            break;
        case PROTOBUF_C_TYPE_UINT64:
            printf("%" PRIu64 "\n", *(uint64_t *)field);
            break;
        case PROTOBUF_C_TYPE_BOOL:
            printf("%s\n", *(protobuf_c_boolean *)field ? "true" : "false");
            break;
        case PROTOBUF_C_TYPE_STRING:
            printf("%s\n", *(char **)field);
            break;
        case PROTOBUF_C_TYPE_ENUM:
            printf("%d\n", *(int32_t *)field);
            break;
        case PROTOBUF_C_TYPE_BYTES:
        {
            ProtobufCBinaryData buf = *(ProtobufCBinaryData *)field;
            printf("[");
            for (size_t i = 0; i < buf.len; i++)
            {
                printf("%d", buf.data[i]);
                if(i != buf.len - 1) printf(", ");
            }
            printf("]\n");
            break;
        }
        case PROTOBUF_C_TYPE_MESSAGE:
            depth++;
            printf("{\n");
            ciot_cli_conn_print_msg(*(ProtobufCMessage**)field);
            depth--;
            for (size_t i = 0; i < depth; i++)
            {
                printf(" ");
            }
            printf("}\n");
            break;
        default:
            printf("Not supported\n");
            break;
        }
    }
}
