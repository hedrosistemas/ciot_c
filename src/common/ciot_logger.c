/**
 * @file ciot_logger.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdarg.h>
#include <stdio.h>
#include "ciot_logger.h"
#include "ciot_config.h"
#include "ciot_iface.h"
#include "ciot_log.h"

#if CIOT_CONFIG_FEATURE_LOGGER

typedef struct ciot_logger
{
    ciot_iface_t *iface;
    ciot_msg_t msg;
    ciot_msg_data_t data;
    ciot_log_data_t log;
} ciot_logger_t;

static ciot_logger_t logger;

void ciot_logger_init(void *iface)
{
    logger.iface = (ciot_iface_t*)iface;
    logger.msg.data.which_type = CIOT_MSG_DATA_LOG_TAG;
}

void ciot_log(ciot_log_level_t level, const char *tag, const char *fmt, ...)
{
    if(logger.iface == NULL) return;
    if(level > CIOT_CONFIG_LOG_LEVEL) return;
    logger.log.level = level;
    strcpy(logger.log.tag, tag);
    va_list args;
    va_start(args, fmt);
    vsprintf(logger.log.message, fmt, args);
    va_end(args);
    ciot_iface_send_msg(logger.iface, &logger.msg);
}

void ciot_logd(const char *tag, const char *fmt, ...)
{
    if(logger.iface == NULL) return;
    if(CIOT_LOG_LEVEL_DEBUG > CIOT_CONFIG_LOG_LEVEL) return;
    logger.log.level = CIOT_LOG_LEVEL_DEBUG;
    strcpy(logger.log.tag, tag);
    va_list args;
    va_start(args, fmt);
    vsprintf(logger.log.message, fmt, args);
    va_end(args);
    ciot_iface_send_msg(logger.iface, &logger.msg);
}

void ciot_logv(const char *tag, const char *fmt, ...)
{
    if(logger.iface == NULL) return;
    if(CIOT_LOG_LEVEL_VERBOSE > CIOT_CONFIG_LOG_LEVEL) return;
    logger.log.level = CIOT_LOG_LEVEL_VERBOSE;
    strcpy(logger.log.tag, tag);
    va_list args;
    va_start(args, fmt);
    vsprintf(logger.log.message, fmt, args);
    va_end(args);
    ciot_iface_send_msg(logger.iface, &logger.msg);
}

void ciot_logi(const char *tag, const char *fmt, ...)
{
    if(logger.iface == NULL) return;
    if(CIOT_LOG_LEVEL_INFO > CIOT_CONFIG_LOG_LEVEL) return;
    logger.log.level = CIOT_LOG_LEVEL_INFO;
    strcpy(logger.log.tag, tag);
    va_list args;
    va_start(args, fmt);
    vsprintf(logger.log.message, fmt, args);
    va_end(args);
    ciot_iface_send_msg(logger.iface, &logger.msg);
}

void ciot_logw(const char *tag, const char *fmt, ...)
{
    if(logger.iface == NULL) return;
    if(CIOT_LOG_LEVEL_WARNING > CIOT_CONFIG_LOG_LEVEL) return;
    logger.log.level = CIOT_LOG_LEVEL_WARNING;
    strcpy(logger.log.tag, tag);
    va_list args;
    va_start(args, fmt);
    vsprintf(logger.log.message, fmt, args);
    va_end(args);
    ciot_iface_send_msg(logger.iface, &logger.msg);
}

void ciot_loge(const char *tag, const char *fmt, ...)
{
    if(logger.iface == NULL) return;
    if(CIOT_LOG_LEVEL_ERROR > CIOT_CONFIG_LOG_LEVEL) return;
    logger.log.level = CIOT_LOG_LEVEL_ERROR;
    strcpy(logger.log.tag, tag);
    va_list args;
    va_start(args, fmt);
    vsprintf(logger.log.message, fmt, args);
    va_end(args);
    ciot_iface_send_msg(logger.iface, &logger.msg);
}

#endif