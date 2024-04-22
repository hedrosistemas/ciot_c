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
        return "CIOT_MSG_TYPE_UNKNOWN";
    case CIOT_MSG_TYPE_START:
        return "CIOT_MSG_TYPE_START";
    case CIOT_MSG_TYPE_STOP:
        return "CIOT_MSG_TYPE_STOP";
    case CIOT_MSG_TYPE_GET_CONFIG:
        return "CIOT_MSG_TYPE_GET_CONFIG";
    case CIOT_MSG_TYPE_GET_STATUS:
        return "CIOT_MSG_TYPE_GET_STATUS";
    case CIOT_MSG_TYPE_REQUEST:
        return "CIOT_MSG_TYPE_REQUEST";
    case CIOT_MSG_TYPE_ERROR:
        return "CIOT_MSG_TYPE_ERROR";
    case CIOT_MSG_TYPE_EVENT:
        return "CIOT_MSG_TYPE_EVENT";
    default:
        return "Custom msg type";
    }
}
