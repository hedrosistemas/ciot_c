/**
 * @file ciot_common_types.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_COMMON_TYPES__H__
#define __CIOT_COMMON_TYPES__H__

#include <inttypes.h>

typedef struct ciot_event_data
{
    void *ptr;
    int size;
} ciot_event_data_t;

#endif  //!__CIOT_COMMON_TYPES__H__