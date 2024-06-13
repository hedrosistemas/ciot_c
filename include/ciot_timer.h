/**
 * @file ciot_timer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_TIMER__H__
#define __CIOT_TIMER__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stdbool.h>

uint64_t ciot_timer_now();
bool ciot_timer_compare(uint64_t *timer, uint16_t interval);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_TIMER__H__
