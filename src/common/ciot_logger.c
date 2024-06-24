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
#include "ciot_msg.h"
#include "ciot_logger.h"
#include "ciot_config.h"
#include "ciot_log.h"

#if CIOT_CONFIG_FEATURE_LOGGER

typedef struct ciot_logger
{
    char buf[1023];
    ciot_iface_t *iface;
    ciot_msg_t msg;
    ciot_msg_data_t data;
    ciot_log_t log;
} ciot_logger_t;

static ciot_logger_t logger;

void ciot_logger_init(void *iface)
{
    logger.iface = (ciot_iface_t*)iface;
    ciot__msg__init(&logger.msg);
    ciot__msg_data__init(&logger.data);
    ciot__log__init(&logger.log);
    logger.msg.data = &logger.data;
    logger.data.log = &logger.log;
    logger.log.message = logger.buf;
    logger.msg.type = CIOT__MSG_TYPE__MSG_TYPE_LOG;
}

void ciot_log(ciot_log_level_t level, const char *tag, const char *fmt, ...)
{
    logger.log.level = level;
    logger.log.tag = (char*)tag;
    if(logger.iface == NULL) return;
    if(level > CIOT_CONFIG_LOG_LEVEL) return;
    va_list args;
    va_start(args, fmt);
    vsprintf(logger.buf, fmt, args);
    va_end(args);
    ciot_iface_send_msg(logger.iface, &logger.msg);
}

void ciot_logd(const char *tag, const char *fmt, ...)
{
    logger.log.level = CIOT__LOG_LEVEL__LOG_LEVEL_DEBUG;
    logger.log.tag = (char*)tag;
    if(logger.iface == NULL) return;
    if(logger.log.level > CIOT_CONFIG_LOG_LEVEL) return;
    va_list args;
    va_start(args, fmt);
    vsprintf(logger.buf, fmt, args);
    va_end(args);
    ciot_iface_send_msg(logger.iface, &logger.msg);
}

void ciot_logv(const char *tag, const char *fmt, ...)
{
    logger.log.level = CIOT__LOG_LEVEL__LOG_LEVEL_VERBOSE;
    logger.log.tag = (char*)tag;
    if(logger.iface == NULL) return;
    if(logger.log.level > CIOT_CONFIG_LOG_LEVEL) return;
    va_list args;
    va_start(args, fmt);
    vsprintf(logger.buf, fmt, args);
    va_end(args);
    ciot_iface_send_msg(logger.iface, &logger.msg);
}

void ciot_logi(const char *tag, const char *fmt, ...)
{
    logger.log.level = CIOT__LOG_LEVEL__LOG_LEVEL_INFO;
    logger.log.tag = (char*)tag;
    if(logger.iface == NULL) return;
    if(logger.log.level > CIOT_CONFIG_LOG_LEVEL) return;
    va_list args;
    va_start(args, fmt);
    vsprintf(logger.buf, fmt, args);
    va_end(args);
    ciot_iface_send_msg(logger.iface, &logger.msg);
}

void ciot_logw(const char *tag, const char *fmt, ...)
{
    logger.log.level = CIOT__LOG_LEVEL__LOG_LEVEL_WARNING;
    logger.log.tag = (char*)tag;
    if(logger.iface == NULL) return;
    if(logger.log.level > CIOT_CONFIG_LOG_LEVEL) return;
    va_list args;
    va_start(args, fmt);
    vsprintf(logger.buf, fmt, args);
    va_end(args);
    ciot_iface_send_msg(logger.iface, &logger.msg);
}

void ciot_loge(const char *tag, const char *fmt, ...)
{
    logger.log.level = CIOT__LOG_LEVEL__LOG_LEVEL_ERROR;
    logger.log.tag = (char*)tag;
    if(logger.iface == NULL) return;
    if(logger.log.level > CIOT_CONFIG_LOG_LEVEL) return;
    va_list args;
    va_start(args, fmt);
    vsprintf(logger.buf, fmt, args);
    va_end(args);
    ciot_iface_send_msg(logger.iface, &logger.msg);
}

#endif