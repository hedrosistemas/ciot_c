/**
 * @file ciot_timer.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-01-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ciot_config.h"

#if CIOT_CONFIG_FEATURE_TIMER && !defined(CIOT_TARGET_NRF)

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "ciot_timer.h"

ciot_err_t ciot_timer_start(ciot_timer_cfg_t *cfg)
{
    return CIOT_OK;
}

uint64_t ciot_timer_get(void)
{
    return time(NULL);
}

bool ciot_timer_compare(uint64_t *timer, uint16_t interval)
{
    if (time(NULL) >= *timer)
    {
        *timer = time(NULL) + interval;
        return true;
    }
    return false;
}

#endif
