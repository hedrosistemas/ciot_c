/**
 * @file ciot_timer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_TIMER__H__
#define __CIOT_TIMER__H__

#include <inttypes.h>
#include <stdbool.h>

#include "ciot_err.h"

typedef void (*ciot_timer_event_handler_t)(void *args);

typedef struct ciot_timer_cfg
{
    ciot_timer_event_handler_t event_handler;
    void *event_args;
} ciot_timer_cfg_t;

ciot_err_t ciot_timer_start(ciot_timer_cfg_t *cfg);
uint64_t ciot_timer_get(void);
bool ciot_timer_compare(uint64_t *timer, uint16_t interval);

#endif  //!__CIOT_TIMER__H__