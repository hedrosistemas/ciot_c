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
