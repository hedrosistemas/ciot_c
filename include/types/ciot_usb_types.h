/**
 * @file ciot_usb_types.h
 * @ingroup hardware_types
 * @brief Defines data structures and types for CIOT USB functionality.
 * @version 0.1
 * @date 2023-10-10
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_USB_DATA__H__
#define __CIOT_USB_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

#include "ciot_common_types.h"

/**
 * @brief Enumeration for CIOT USB states.
 */
typedef enum __attribute__((packed))
{
    CIOT_USB_STATE_STOPPED, /**< USB stopped state */
    CIOT_USB_STATE_STARTED, /**< USB started state */
} ciot_usb_state_t;

/**
 * @brief Enumeration for CIOT USB request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_USB_REQ_UNKNOWN, /**< Unknown request type */
} ciot_usb_req_type_t;

/**
 * @brief Structure for CIOT USB configuration.
 */
typedef struct __attribute__((packed))
{
    bool bridge_mode; /**< Bridge mode flag */
} ciot_usb_cfg_t;

/**
 * @brief Structure for CIOT USB status.
 */
typedef struct __attribute__((packed))
{
    ciot_usb_state_t state; /**< USB state */
} ciot_usb_status_t;

/**
 * @brief Union for CIOT USB request data.
 */
typedef union __attribute__((packed))
{

} ciot_usb_req_data_u;

/**
 * @brief Structure for CIOT USB request.
 */
typedef struct __attribute__((packed))
{
    ciot_usb_req_type_t type; /**< Request type */
    ciot_usb_req_data_u data; /**< Request data */
} ciot_usb_req_t;

/**
 * @brief Union for CIOT USB event.
 */
typedef union ciot_usb_event
{
    ciot_event_data_t data; /**< Event data */
} ciot_usb_event_u;

/**
 * @brief Union for CIOT USB data.
 */
typedef union __attribute__((packed))
{
    ciot_usb_cfg_t config; /**< Configuration data */
    ciot_usb_status_t status; /**< Status data */
    ciot_usb_req_t request; /**< Request data */
    ciot_usb_event_u event; /**< Event data */
} ciot_usb_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_USB_DATA__H__
