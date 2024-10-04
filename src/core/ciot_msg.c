/**
 * @file ciot_msg.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ciot_msg.h"
#include "ciot_iface.h"
#include "ciot/proto/v1/msg.pb-c.h"

static ciot_msg_t msg;
static ciot_iface_info_t iface_info;
static ciot_msg_data_t msg_data;
static const char *TAG = "ciot_msg";

ciot_err_t ciot_msg_init(ciot_msg_t *msg)
{
    ciot__msg__init(msg);
    ciot__iface_info__init(&iface_info);
    ciot__msg_data__init(&msg_data);
    msg->iface = &iface_info;
    msg->data = &msg_data;
    return CIOT_ERR__OK;
}

ciot_msg_t* ciot_msg_get(ciot_msg_type_t type, ciot_iface_t *iface)
{
    ciot_msg_init(&msg);
    msg.type = type;
    msg.iface->id = iface->info.id;
    msg.iface->type = iface->info.type;
    iface->get_data(iface, &msg);
    return &msg;
}

ciot_msg_t* ciot_msg_get_empty(ciot_msg_type_t type, ciot_iface_type_t iface_type, uint8_t iface_id)
{
    ciot_msg_init(&msg);
    msg.type = type;
    msg.iface->type = iface_type;
    msg.iface->id = iface_id;
    return &msg;
}

const char *ciot_msg_type_to_str(ciot_msg_t *msg)
{
    if(msg == NULL)
    {
        return "NULL";
    }

    switch (msg->type)
    {
        case CIOT__MSG_TYPE__MSG_TYPE_UNKNOWN:
            return "MSG_TYPE_UNKNOWN";
        case CIOT__MSG_TYPE__MSG_TYPE_START:
            return "MSG_TYPE_START";
        case CIOT__MSG_TYPE__MSG_TYPE_STOP:
            return "MSG_TYPE_STOP";
        case CIOT__MSG_TYPE__MSG_TYPE_CONFIG:
            return "MSG_TYPE_CONFIG";
        case CIOT__MSG_TYPE__MSG_TYPE_INFO:
            return "MSG_TYPE_INFO";
        case CIOT__MSG_TYPE__MSG_TYPE_STATUS:
            return "MSG_TYPE_STATUS";
        case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
            return "MSG_TYPE_REQUEST";
        case CIOT__MSG_TYPE__MSG_TYPE_ERROR:
            return "MSG_TYPE_ERROR";
        case CIOT__MSG_TYPE__MSG_TYPE_EVENT:
            return "MSG_TYPE_EVENT";
    default:
        return "MSG_TYPE_CUSTOM";
    }
}

int ciot_msg_to_json(const ProtobufCMessage *message, char *json)
{
    const ProtobufCFieldDescriptor *field_desc;
    unsigned i;
    static int depth = 1;
    static int idx = 0;

    idx += sprintf(&json[idx], "{\n");

    if (message == NULL)
    {
        CIOT_LOGE(TAG, "null message");
        return 0;
    }

    if (message->descriptor == NULL)
    {
        CIOT_LOGE(TAG, "null descriptor");
        return 0;
    }

    for (i = 0; i < message->descriptor->n_fields; i++)
    {
        field_desc = &message->descriptor->fields[i];
        const void *field = ((const char *)message) + field_desc->offset;

        if ((*(void **)field) == NULL && (field_desc->type == PROTOBUF_C_TYPE_MESSAGE || field_desc->type == PROTOBUF_C_TYPE_STRING || field_desc->type == PROTOBUF_C_TYPE_BYTES))
        {
            continue;
        }

        for (size_t i = 0; i < depth; i++)
        {
            idx += sprintf(&json[idx], " ");
        }

        idx += sprintf(&json[idx], "\"%s\": ", field_desc->name);

        switch (field_desc->type)
        {
        case PROTOBUF_C_TYPE_INT32:
            idx += sprintf(&json[idx], "%d,\n", *(int *)field);
            break;
        case PROTOBUF_C_TYPE_UINT32:
            idx += sprintf(&json[idx], "%u,\n", *(unsigned int *)field);
            break;
        case PROTOBUF_C_TYPE_INT64:
            idx += sprintf(&json[idx], "%" PRId64 ",\n", *(int64_t *)field);
            break;
        case PROTOBUF_C_TYPE_UINT64:
            idx += sprintf(&json[idx], "%" PRIu64 ",\n", *(uint64_t *)field);
            break;
        case PROTOBUF_C_TYPE_BOOL:
            idx += sprintf(&json[idx], "%s,\n", *(protobuf_c_boolean *)field ? "true" : "false");
            break;
        case PROTOBUF_C_TYPE_STRING:
            idx += *(char **)field ? sprintf(&json[idx], "\"%s\",\n", *(char **)field) : sprintf(&json[idx], "null\n");
            break;
        case PROTOBUF_C_TYPE_ENUM:
        {
            const ProtobufCEnumDescriptor *enum_descr = field_desc->descriptor;
            int value = *(int *)field;
            idx += sprintf(&json[idx], "\"%s\",\n", enum_descr->values[value].name);
            break;
        }
        case PROTOBUF_C_TYPE_BYTES:
        {
            ProtobufCBinaryData buf = *(ProtobufCBinaryData *)field;
            if (buf.len >= 6)
            {
                idx += sprintf(&json[idx], "\"");
                for (size_t i = 0; i < buf.len; i++)
                {
                    idx += sprintf(&json[idx], "%02X", buf.data[i]);
                }
                idx += sprintf(&json[idx], "\",\n");
            }
            else
            {
                idx += sprintf(&json[idx], "[");
                for (size_t i = 0; i < buf.len; i++)
                {
                    idx += sprintf(&json[idx], "%d", buf.data[i]);
                    if (i != buf.len - 1)
                        idx += sprintf(&json[idx], ", ");
                }
                idx += sprintf(&json[idx], "],\n");
            }
            break;
        }
        case PROTOBUF_C_TYPE_MESSAGE:
            depth++;
            ciot_msg_to_json(*(ProtobufCMessage **)field, json);
            depth--;
            break;
        default:
            idx += sprintf(&json[idx], "Not supported\n");
            break;
        }
    }

    idx-=2;
    idx += sprintf(&json[idx], "\n");
    for (size_t i = 0; i < depth-1; i++)
    {
        idx += sprintf(&json[idx], " ");
    }
    idx += sprintf(&json[idx], "}");

    if(depth == 1) 
    {
        idx += sprintf(&json[idx], "\n");
        int size = idx;
        idx = 0;
        return size;
    }
    else
    {
        idx += sprintf(&json[idx], ",\n");
    }

    return 0;
}

void ciot_msg_print(const ProtobufCMessage *message)
{
    char json[2048];
    ciot_msg_to_json(message, json);
    printf(json);
}
