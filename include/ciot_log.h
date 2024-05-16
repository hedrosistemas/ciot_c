/**
 * @file ciot_log.h
 * @ingroup core
 * @brief Header file for CIOT logging functionality.
 * @version 0.1
 * @date 2023-10-18
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_LOG__H__
#define __CIOT_LOG__H__

#include "ciot_config.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Enumeration for CIOT log levels.
     */
    typedef enum ciot_log_level
    {
        CIOT_LOG_LEVEL_NONE, /**< No logging. */
        CIOT_LOG_LEVEL_ERROR, /**< Error level logging. */
        CIOT_LOG_LEVEL_WARNING, /**< Warning level logging. */
        CIOT_LOG_LEVEL_INFO, /**< Info level logging. */
        CIOT_LOG_LEVEL_VERBOSE, /**< Verbose level logging. */
        CIOT_LOG_LEVEL_DEBUG, /**< Debug level logging. */
    } ciot_log_level_t;

#ifdef IDF_VER

#include "esp_log.h"

// Forwarding logging macros to ESP-IDF logging macros
#define CIOT_LOGD ESP_LOGD
#define CIOT_LOGV ESP_LOGV
#define CIOT_LOGI ESP_LOGI
#define CIOT_LOGW ESP_LOGW
#define CIOT_LOGE ESP_LOGE
#define CIOT_LOG_BUFFER_HEX(tag, data, size) ESP_LOG_BUFFER_HEX_LEVEL(tag, data, size, ESP_LOG_DEBUG)

#else

#include <stdio.h>

/**
 * @brief Macro to log hexadecimal data.
 */
#define CIOT_LOG_BUFFER_HEX(TAG, data, size) CIOT_LOG_HEX(TAG, data, size)

/**
 * @brief Macro to log debug level messages.
 */
#define CIOT_LOGD(TAG, MASK, ...)                          \
    do                                                     \
    {                                                      \
        if (CIOT_CONFIG_LOG_LEVEL >= CIOT_LOG_LEVEL_DEBUG) \
        {                                                  \
            printf("[%s] <DBG>: ", TAG);                   \
            printf(MASK, ##__VA_ARGS__);                   \
            printf("\n");                                  \
        }                                                  \
    } while (0)

/**
 * @brief Macro to log verbose level messages.
 */
#define CIOT_LOGV(TAG, MASK, ...)                            \
    do                                                       \
    {                                                        \
        if (CIOT_CONFIG_LOG_LEVEL >= CIOT_LOG_LEVEL_VERBOSE) \
        {                                                    \
            printf("[%s] <VRB>: ", TAG);                     \
            printf(MASK, ##__VA_ARGS__);                     \
            printf("\n");                                    \
        }                                                    \
    } while (0)

/**
 * @brief Macro to log info level messages.
 */
#define CIOT_LOGI(TAG, MASK, ...)                         \
    do                                                    \
    {                                                     \
        if (CIOT_CONFIG_LOG_LEVEL >= CIOT_LOG_LEVEL_INFO) \
        {                                                 \
            printf("[%s] <INF>: ", TAG);                  \
            printf(MASK, ##__VA_ARGS__);                  \
            printf("\n");                                 \
        }                                                 \
    } while (0)

/**
 * @brief Macro to log warning level messages.
 */
#define CIOT_LOGW(TAG, MASK, ...)                            \
    do                                                       \
    {                                                        \
        if (CIOT_CONFIG_LOG_LEVEL >= CIOT_LOG_LEVEL_WARNING) \
        {                                                    \
            printf("[%s] <WRN>: ", TAG);                     \
            printf(MASK, ##__VA_ARGS__);                     \
            printf("\n");                                    \
        }                                                    \
    } while (0)

/**
 * @brief Macro to log error level messages.
 */
#define CIOT_LOGE(TAG, MASK, ...)                          \
    do                                                     \
    {                                                      \
        if (CIOT_CONFIG_LOG_LEVEL >= CIOT_LOG_LEVEL_ERROR) \
        {                                                  \
            printf("[%s] <ERR>: ", TAG);                   \
            printf(MASK, ##__VA_ARGS__);                   \
            printf("\n");                                  \
        }                                                  \
    } while (0)

#endif // IDF_VER

/**
 * @brief Macro to log a message with additional information.
 */
#define CIOT_LOG_MSG(TAG, LOG_MACRO, header, sender, msg) \
    LOG_MACRO(TAG, header "id:%d %d:%s %d:%s %d:%s",      \
              msg.id,                                     \
              sender->info.id,                            \
              ciot_iface_to_str(sender),                  \
              msg.type,                                   \
              ciot_msg_type_to_str(&msg),                 \
              msg.iface.id,                               \
              ciot_iface_type_to_str(msg.iface.type))

/**
 * @brief Macro to log a message pointer with additional information.
 */
#define CIOT_LOG_MSG_P(TAG, LOG_MACRO, header, sender, msg) \
    LOG_MACRO(TAG, header "id:%d %d:%s %d:%s %d:%s",        \
              msg->id,                                      \
              sender->info.id,                              \
              ciot_iface_to_str(sender),                    \
              msg->type,                                    \
              ciot_msg_type_to_str(msg),                    \
              msg->iface.id,                                \
              ciot_iface_type_to_str(msg->iface.type))

/**
 * @brief Macro to log hexadecimal data.
 */
#define CIOT_LOG_HEX(TAG, data, size)                      \
    do                                                     \
    {                                                      \
        if (CIOT_CONFIG_LOG_LEVEL >= CIOT_LOG_LEVEL_DEBUG) \
        {                                                  \
            uint8_t *u8ptr = data;                         \
            for (size_t i = 0; i < size; i++)              \
            {                                              \
                printf("%02X", u8ptr[i]);                  \
            }                                              \
            printf("\n");                                  \
        }                                                  \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_LOG__H__
