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
        return "UNKNOWN";
    case CIOT_MSG_TYPE_START:
        return "START";
    case CIOT_MSG_TYPE_STOP:
        return "STOP";
    case CIOT_MSG_TYPE_GET_CONFIG:
        return "GET_CONFIG";
    case CIOT_MSG_TYPE_GET_STATUS:
        return "GET_STATUS";
    case CIOT_MSG_TYPE_REQUEST:
        return "REQUEST";
    case CIOT_MSG_TYPE_ERROR:
        return "ERROR";
    case CIOT_MSG_TYPE_EVENT:
        return "EVENT";
    default:
        return "CUSTOM";
    }
}
