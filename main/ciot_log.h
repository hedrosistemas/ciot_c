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

#ifdef  IDF_VER

#include "esp_log.h"

#define CIOT_LOG_INFO ESP_LOG_INFO

#define CIOT_LOGI ESP_LOGI
#define CIOT_LOGW ESP_LOGW
#define CIOT_LOGE ESP_LOGE
#define CIOT_LOG_BUFFER_HEX ESP_LOG_BUFFER_HEX

#else

#define CIOT_LOGI(TAG, MASK, ...) \
    do { \
        printf("[%s] <INFO>: ", TAG); \
        printf(MASK, __VA_ARGS__); \
        printf("\n"); \
    } while (0)

#define CIOT_LOGW(TAG, MASK, ...) \
    do { \
        printf("[%s] <WARN>: ", TAG); \
        printf(MASK, __VA_ARGS__); \
        printf("\n"); \
    } while (0)

#define CIOT_LOGE(TAG, MASK, ...) \
    do { \
        printf("[%s] <ERRO>: ", TAG); \
        printf(MASK, __VA_ARGS__); \
        printf("\n"); \
    } while (0)

#endif  //IDF_VER

#endif  //!__CIOT_LOG__H__