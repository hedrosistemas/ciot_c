/**
 * @file ciot_timer.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <time.h>
#include "ciot_timer.h"

uint64_t ciot_timer_now()
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
