/**
 * @file ciot_err.c
 * @author Wesley Santos (wesleypro37@gmail.com)
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
            return "CIOT_FAIL";
        case CIOT_OK:
            return "CIOT_OK";
        case CIOT_ERR_NULL_ARG:
            return "CIOT_ERR_NULL_ARG";
        case CIOT_ERR_INVALID_ID:
            return "CIOT_ERR_INVALID_ID";
        case CIOT_ERR_INVALID_TYPE:
            return "CIOT_ERR_INVALID_TYPE";
        case CIOT_ERR_OVERFLOW:
            return "CIOT_ERR_OVERFLOW";
        case CIOT_ERR_NOT_IMPLEMENTED:
            return "CIOT_ERR_NOT_IMPLEMENTED";
        case CIOT_ERR_NOT_SUPPORTED:
            return "CIOT_ERR_NOT_SUPPORTED";
        case CIOT_ERR_BUSY:
            return "CIOT_ERR_BUSY";
        case CIOT_ERR_INVALID_STATE:
            return "CIOT_ERR_INVALID_STATE";
        case CIOT_ERR_SERIALIZATION:
            return "CIOT_ERR_SERIALIZATION";
        case CIOT_ERR_DESERIALIZATION:
            return "CIOT_ERR_DESERIALIZATION";
        case CIOT_ERR_SEND_DATA:
            return "CIOT_ERR_SEND_DATA";
        case CIOT_ERR_INVALID_SIZE:
            return "CIOT_ERR_INVALID_SIZE";
        case CIOT_ERR_CLOSED:
            return "CIOT_ERR_CLOSED";
        case CIOT_ERR_NOT_FOUND:
            return "CIOT_ERR_NOT_FOUND";
        case CIOT_ERR_VALIDATION_FAILED:
            return "CIOT_ERR_VALIDATION_FAILED";
        case CIOT_ERR_CONNECTION:
            return "CIOT_ERR_CONNECTION";
        case CIOT_ERR_DISCONNECTION:
            return "CIOT_ERR_DISCONNECTION";
        case CIOT_ERR_EXCEPTION:
            return "CIOT_ERR_EXCEPTION";
        case CIOT_ERR_TERMINATOR_MISSING:
            return "CIOT_ERR_TERMINATOR_MISSING";
        case CIOT_ERR_INVALID_ARG:
            return "CIOT_ERR_INVALID_ARG";
    default:
#ifdef IDF_VER
    return esp_err_to_name(err);
#else
    return "Unknown Error";
#endif
    }
}

