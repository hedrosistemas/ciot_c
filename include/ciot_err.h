/**
 * @file ciot_err.h
 * @ingroup core
 * @brief Header file for CIOT error handling.
 * @version 0.1
 * @date 2023-10-09
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_ERR__H__
#define __CIOT_ERR__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_log.h"

/**
 * @brief Base error code for CIOT library.
 */
#define CIOT_ERR_BASE 0x0

/**
 * @brief Macro to log an error.
 * @param x The error code.
 */
#define CIOT_ERROR_LOG(x) CIOT_LOGE(TAG, "%s:%d %s", __FILE__, __LINE__, ciot_err_to_message(ciot_err))

/**
 * @brief Macro to check for a null pointer and return an error if found.
 * @param x The pointer to check.
 */
#define CIOT_NULL_CHECK(x) \
    if (x == NULL)         \
    return CIOT_ERR_NULL_ARG

/**
 * @brief Macro to print an error message if an operation fails.
 * @param x The operation to check for errors.
 */
#define CIOT_ERROR_PRINT(x)           \
    do                                \
    {                                 \
        ciot_err_t ciot_err = x;      \
        if (ciot_err != CIOT_OK)      \
        {                             \
            CIOT_ERROR_LOG(ciot_err); \
        }                             \
    } while (0)

/**
 * @brief Macro to return an error if an operation fails.
 * @param x The operation to check for errors.
 */
#define CIOT_ERROR_RETURN(x)          \
    do                                \
    {                                 \
        ciot_err_t ciot_err = x;      \
        if (ciot_err != CIOT_OK)      \
        {                             \
            CIOT_ERROR_LOG(ciot_err); \
            return ciot_err;          \
        }                             \
    } while (0)

/**
 * @brief Enumeration of CIOT error codes.
 */
typedef enum {
    CIOT_FAIL = -1, /**< General failure. */
    CIOT_OK, /**< Operation successful. */
    CIOT_ERR_NULL_ARG = CIOT_ERR_BASE + 1, /**< Null argument error. */
    CIOT_ERR_INVALID_ID, /**< Invalid ID error. */
    CIOT_ERR_INVALID_TYPE, /**< Invalid type error. */
    CIOT_ERR_OVERFLOW, /**< Overflow error. */
    CIOT_ERR_NOT_IMPLEMENTED, /**< Not implemented error. */
    CIOT_ERR_NOT_SUPPORTED, /**< Operation not supported error. */
    CIOT_ERR_BUSY, /**< Busy error. */
    CIOT_ERR_INVALID_STATE, /**< Invalid state error. */
    CIOT_ERR_SERIALIZATION, /**< Serialization error. */
    CIOT_ERR_DESERIALIZATION, /**< Deserialization error. */
    CIOT_ERR_SEND_DATA, /**< Error sending data. */
    CIOT_ERR_RECV_DATA, /**< Error receiving data. */
    CIOT_ERR_INVALID_SIZE, /**< Invalid size error. */
    CIOT_ERR_CLOSED, /**< Closed error. */
    CIOT_ERR_NOT_FOUND, /**< Not found error. */
    CIOT_ERR_VALIDATION_FAILED, /**< Validation failed error. */
    CIOT_ERR_CONNECTION, /**< Connection error. */
    CIOT_ERR_DISCONNECTION, /**< Disconnection error. */
    CIOT_ERR_EXCEPTION, /**< Exception error. */
    CIOT_ERR_TERMINATOR_MISSING, /**< Terminator missing error. */
    CIOT_ERR_INVALID_ARG, /**< Invalid argument error. */
    CIOT_ERR_NO_MEMORY, /**< Out of memory error. */
    CIOT_ERR_TIMEOUT, /**< Timeout error. */
    CIOT_ERR_MONGOOSE, /**< Mongoose error. */
    CIOT_ERR_IMPOSSIBLE_OP, /**< Impossible operation error. */
    CIOT_ERR_CHECKSUM, /**< Checksum error. */
} ciot_err_t;

/**
 * @brief Converts a CIOT error code to a human-readable message.
 * @param err The error code.
 * @return A pointer to the error message.
 */
const char *ciot_err_to_message(ciot_err_t err);

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_ERR__H__
