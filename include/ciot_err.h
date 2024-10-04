/**
 * @file ciot_err.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-06-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __CIOT_ERR__H__
#define __CIOT_ERR__H__

#include "ciot/proto/v1/errors.pb-c.h"
#include "ciot_log.h"

typedef CiotErr ciot_err_t;

#define CIOT_ERR_LOG(TAG, x) CIOT_LOGE(TAG, "%s:%d %s", __FILE__, __LINE__, ciot_err_to_message(x))

#define CIOT_ERR_NULL_CHECK(x)                        \
    if (x == NULL)                                    \
    {                                                 \
        CIOT_ERR_LOG("ciot_err", CIOT_ERR__NULL_ARG); \
        return CIOT_ERR__NULL_ARG;                    \
    }

#define CIOT_ERR_INDEX_CHECK(index, min, max) \
    if (index < min)                          \
        return CIOT_ERR__INVALID_INDEX;       \
    if (index > max)                          \
        return CIOT_ERR__INVALID_INDEX;

#define CIOT_ERR_STATE_CHECK(current, expected)            \
    if (current != expected)                               \
    {                                                      \
        CIOT_ERR_LOG("ciot_err", CIOT_ERR__INVALID_STATE); \
        return CIOT_ERR__INVALID_STATE;                    \
    }

#define CIOT_ERR_VALUE_CHECK(current, expected, err) \
    if (current != expected)                         \
    {                                                \
        CIOT_ERR_LOG("ciot_err", err);               \
        return err;                                  \
    }

#define CIOT_ERR_EMPTY_STRING_CHECK(x)                       \
    if (x[0] == '\0')                                        \
    {                                                        \
        /*CIOT_ERR_LOG("ciot_err", CIOT_ERR__INVALID_ARG);*/ \
        return CIOT_ERR__INVALID_ARG;                        \
    }

#define CIOT_ERR_RETURN(x)                      \
    do                                          \
    {                                           \
        ciot_err_t ciot_err = x;                \
        if (ciot_err != CIOT_ERR__OK)           \
        {                                       \
            CIOT_ERR_LOG("ciot_err", ciot_err); \
            return ciot_err;                    \
        }                                       \
    } while (0)

#define CIOT_ERR_PRINT(TAG, x)           \
    do                                   \
    {                                    \
        ciot_err_t ciot_err = x;         \
        if (ciot_err != CIOT_ERR__OK)    \
        {                                \
            CIOT_ERR_LOG(TAG, ciot_err); \
        }                                \
    } while (0)

const char *ciot_err_to_message(ciot_err_t err);

#endif //!__CIOT_ERR__H__
