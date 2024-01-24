/**
 * @file ciot_log.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __CIOT_LOG__H__
#define __CIOT_LOG__H__

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum ciot_log_level
    {
        CIOT_LOG_LEVEL_NONE,
        CIOT_LOG_LEVEL_ERROR,
        CIOT_LOG_LEVEL_WARNING,
        CIOT_LOG_LEVEL_INFO,
        CIOT_LOG_LEVEL_VERBOSE,
        CIOT_LOG_LEVEL_DEBUG,
    } ciot_log_level_t;

#ifdef IDF_VER

#include "esp_log.h"

#define CIOT_LOGD ESP_LOGD
#define CIOT_LOGV ESP_LOGV
#define CIOT_LOGI ESP_LOGI
#define CIOT_LOGW ESP_LOGW
#define CIOT_LOGE ESP_LOGE
#define CIOT_LOG_BUFFER_HEX ESP_LOG_BUFFER_HEX

#else

#include <stdio.h>

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

#define CIOT_LOG_MSG(TAG, LOG_MACRO, header, sender, msg) \
    LOG_MACRO(TAG, header "id:%d %d:%s %d:%s %d:%s",      \
              msg.id,                                     \
              sender->info.id,                            \
              ciot_iface_to_str(sender),                  \
              msg.type,                                   \
              ciot_msg_type_to_str(&msg),                 \
              msg.iface.id,                               \
              ciot_iface_type_to_str(msg.iface.type))

#define CIOT_LOG_MSG_P(TAG, LOG_MACRO, header, sender, msg) \
    LOG_MACRO(TAG, header "id:%d %d:%s %d:%s %d:%s",        \
              msg->id,                                      \
              sender->info.id,                              \
              ciot_iface_to_str(sender),                    \
              msg->type,                                    \
              ciot_msg_type_to_str(msg),                    \
              msg->iface.id,                                \
              ciot_iface_type_to_str(msg->iface.type))

#define CIOT_LOG_HEX(data, size)\
    do\
    {\
        uint8_t *u8ptr = data;\
        for (size_t i = 0; i < size; i++)\
        {\
            printf("%02X", u8ptr[i]);\
        }\
        printf("\n");\
    } while (0)

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_LOG__H__