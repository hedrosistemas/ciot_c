/**
 * @file ciot_err.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-08
 * 
 * @copyright Copyright (c) 2024
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
        case CIOT_ERR__OK:
            return "OK";
        case CIOT_ERR__NULL_ARG:
            return "NULL_ARG";
        case CIOT_ERR__INVALID_ID:
            return "INVALID_ID";
        case CIOT_ERR__INVALID_TYPE:
            return "INVALID_TYPE";
        case CIOT_ERR__OVERFLOW:
            return "OVERFLOW";
        case CIOT_ERR__NOT_IMPLEMENTED:
            return "NOT_IMPLEMENTED";
        case CIOT_ERR__NOT_SUPPORTED:
            return "NOT_SUPPORTED";
        case CIOT_ERR__BUSY:
            return "BUSY";
        case CIOT_ERR__INVALID_STATE:
            return "INVALID_STATE";
        case CIOT_ERR__SERIALIZATION:
            return "SERIALIZATION";
        case CIOT_ERR__DESERIALIZATION:
            return "DESERIALIZATION";
        case CIOT_ERR__SEND_DATA:
            return "SEND_DATA";
        case CIOT_ERR__RECV_DATA:
            return "RECV_DATA";
        case CIOT_ERR__INVALID_SIZE:
            return "INVALID_SIZE";
        case CIOT_ERR__CLOSED:
            return "CLOSED";
        case CIOT_ERR__NOT_FOUND:
            return "NOT_FOUND";
        case CIOT_ERR__VALIDATION_FAILED:
            return "VALIDATION_FAILED";
        case CIOT_ERR__CONNECTION:
            return "CONNECTION";
        case CIOT_ERR__DISCONNECTION:
            return "DISCONNECTION";
        case CIOT_ERR__EXCEPTION:
            return "EXCEPTION";
        case CIOT_ERR__INVALID_ARG:
            return "INVALID_ARG";
        case CIOT_ERR__NO_MEMORY:
            return "NO_MEMORY";
        case CIOT_ERR__TIMEOUT:
            return "TIMEOUT";
        case CIOT_ERR__MONGOOSE:
            return "MONGOOSE";
        case CIOT_ERR__IMPOSSIBLE_OP:
            return "IMPOSSIBLE_OP";
        case CIOT_ERR__CHECKSUM:
            return "CHECKSUM";
        case CIOT_ERR__PROTOCOL_VIOLATION:
            return "PROTOCOL_VIOLATION";
        case CIOT_ERR__FAIL:
            return "FAIL";
    default:
#ifdef IDF_VER
    return esp_err_to_name(err);
#else
    return "UNKNOWN";
#endif
    }
}
