/**
 * @file ciot_timer.h
 * @brief Header file for CIOT timer module.
 * @version 0.1
 * @date 2024-01-09
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2024
 */

#ifndef __CIOT_TIMER__H__
#define __CIOT_TIMER__H__

#include <inttypes.h>
#include <stdbool.h>

#include "ciot_err.h"

/**
 * @brief Event handler function type definition for CIOT timer module.
 *
 * @param args Event arguments.
 */
typedef void (*ciot_timer_event_handler_t)(void *args);

/**
 * @brief Configuration structure for CIOT timer.
 */
typedef struct ciot_timer_cfg
{
    ciot_timer_event_handler_t event_handler;  /*!< Event handler function pointer */
    void *event_args;                          /*!< Event handler arguments */
} ciot_timer_cfg_t;

/**
 * @brief Start the CIOT timer module with the given configuration.
 *
 * @param cfg Configuration for the timer module.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_timer_start(ciot_timer_cfg_t *cfg);

/**
 * @brief Get the current timestamp from the CIOT timer.
 *
 * @return Current timestamp in milliseconds.
 */
uint64_t ciot_timer_get(void);

/**
 * @brief Compare the current timer value with an interval.
 *
 * @param timer Pointer to the timer value to compare.
 * @param interval Interval value to compare against.
 * @return True if the timer value is greater than or equal to the interval, false otherwise.
 */
bool ciot_timer_compare(uint64_t *timer, uint16_t interval);

#endif  //!__CIOT_TIMER__H__
