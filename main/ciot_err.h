/**
 * @file ciot_err.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_ERR__H__
#define __CIOT_ERR__H__

#define CIOT_ERR_BASE 0x0

#define CIOT_ERR_NULL_CHECK(x) if(x == NULL) return CIOT_ERR_NULL_ARG

typedef enum __attribute__((packed)) {
    CIOT_FAIL=-1,
    CIOT_OK,
    CIOT_ERR_NULL_ARG=CIOT_ERR_BASE+1,
    CIOT_ERR_INVALID_ID,
    CIOT_ERR_INVALID_TYPE,
    CIOT_ERR_OVERFLOW,
    CIOT_ERR_NOT_IMPLEMENTED,
    CIOT_ERR_NOT_SUPPORTED,
    CIOT_ERR_BUSY,
    CIOT_ERR_INVALID_STATE,
    CIOT_ERR_SERIALIZATION,
    CIOT_ERR_DESERIALIZATION,
    CIOT_ERR_SEND_DATA,
    CIOT_ERR_INVALID_SIZE,
    CIOT_ERR_CLOSED,
    CIOT_ERR_NOT_FOUND,
    CIOT_ERR_VALIDATION_FAILED,
    CIOT_ERR_CONNECTION,
    CIOT_ERR_DISCONNECTION,
    CIOT_ERR_EXCEPTION,
    CIOT_ERR_TERMINATOR_MISSING,
} ciot_err_t;

#endif  //!__CIOT_ERR__H__