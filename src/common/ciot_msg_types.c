/**
 * @file ciot_msg_types.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_msg_types.h"

const char *ciot_msg_type_to_str(ciot_msg_t *msg)
{
    if(msg == NULL)
    {
        return "NULL";
    }

    switch (msg->type)
    {
    case CIOT_MSG_TYPE_UNKNOWN:
        return "MSG_UNKNOWN";
    case CIOT_MSG_TYPE_START:
        return "MSG_START";
    case CIOT_MSG_TYPE_STOP:
        return "MSG_STOP";
    case CIOT_MSG_TYPE_GET_CONFIG:
        return "MSG_GET_CONFIG";
    case CIOT_MSG_TYPE_GET_STATUS:
        return "MSG_GET_STATUS";
    case CIOT_MSG_TYPE_REQUEST:
        return "MSG_REQUEST";
    case CIOT_MSG_TYPE_ERROR:
        return "MSG_ERROR";
    case CIOT_MSG_TYPE_EVENT:
        return "MSG_EVENT";
    default:
        return "MSG_CUSTOM";
    }
}
