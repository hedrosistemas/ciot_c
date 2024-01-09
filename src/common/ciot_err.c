/**
 * @file ciot_err.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_err.h"

#ifdef IDF_VER
#include "esp_err.h"
#endif

const char *ciot_err_to_message(ciot_err_t err)
{
    switch (err)
    {
        case CIOT_FAIL:
            return "FAIL";
        case CIOT_OK:
            return "OK";
        case CIOT_ERR_NULL_ARG:
            return "NULL_ARG";
        case CIOT_ERR_INVALID_ID:
            return "INVALID_ID";
        case CIOT_ERR_INVALID_TYPE:
            return "INVALID_TYPE";
        case CIOT_ERR_OVERFLOW:
            return "OVERFLOW";
        case CIOT_ERR_NOT_IMPLEMENTED:
            return "NOT_IMPLEMENTED";
        case CIOT_ERR_NOT_SUPPORTED:
            return "NOT_SUPPORTED";
        case CIOT_ERR_BUSY:
            return "BUSY";
        case CIOT_ERR_INVALID_STATE:
            return "INVALID_STATE";
        case CIOT_ERR_SERIALIZATION:
            return "SERIALIZATION";
        case CIOT_ERR_DESERIALIZATION:
            return "DESERIALIZATION";
        case CIOT_ERR_SEND_DATA:
            return "SEND_DATA";
        case CIOT_ERR_INVALID_SIZE:
            return "INVALID_SIZE";
        case CIOT_ERR_CLOSED:
            return "CLOSED";
        case CIOT_ERR_NOT_FOUND:
            return "NOT_FOUND";
        case CIOT_ERR_VALIDATION_FAILED:
            return "VALIDATION_FAILED";
        case CIOT_ERR_CONNECTION:
            return "CONNECTION";
        case CIOT_ERR_DISCONNECTION:
            return "DISCONNECTION";
        case CIOT_ERR_EXCEPTION:
            return "EXCEPTION";
        case CIOT_ERR_TERMINATOR_MISSING:
            return "TERMINATOR_MISSING";
        case CIOT_ERR_INVALID_ARG:
            return "INVALID_ARG";
    default:
#ifdef IDF_VER
    return esp_err_to_name(err);
#else
    return "UNKNOWN";
#endif
    }
}

