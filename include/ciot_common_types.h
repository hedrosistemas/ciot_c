/**
 * @file ciot_common_types.h
w * @brief Defines common types used in CIOT modules.
 * @version 0.1
 * @date 2023-11-14
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_COMMON_TYPES__H__
#define __CIOT_COMMON_TYPES__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/** @brief Structure for event data in CIOT modules */
typedef struct ciot_event_data
{
    uint8_t *ptr; /**< Pointer to the event data */
    int size; /**< Size of the event data in bytes */
} ciot_event_data_t;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_COMMON_TYPES__H__
