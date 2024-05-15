/**
 * @file ciot_common_types.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_COMMON_TYPES__H__
#define __CIOT_COMMON_TYPES__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

typedef struct ciot_event_data
{
    uint8_t *ptr;
    int size;
} ciot_event_data_t;

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_COMMON_TYPES__H__