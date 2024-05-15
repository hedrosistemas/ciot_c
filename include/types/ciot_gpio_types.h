/**
 * @file ciot_gpio_types.h
 * @ingroup hardware_types
 * @brief Defines data types and structures for CIOT GPIO (General Purpose Input/Output).
 * @version 0.1
 * @date 2023-10-10
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_GPIO_TYPES__H__
#define __CIOT_GPIO_TYPES__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/**
 * @brief Enumeration for CIOT GPIO states.
 */
typedef enum __attribute__((packed))
{
    CIOT_GPIO_STATE_ERR = -1, /**< Error state */
    CIOT_GPIO_STATE_LOW, /**< Low state */
    CIOT_GPIO_STATE_HIGH /**< High state */
} ciot_gpio_state_t;

/**
 * @brief Enumeration for CIOT GPIO request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_GPIO_REQ_UNKNOWN, /**< Unknown request type */
    CIOT_GPIO_REQ_CONFIG, /**< Configure GPIO request type */
    CIOT_GPIO_REQ_SET_STATE, /**< Set GPIO state request type */
    CIOT_GPIO_REQ_GET_STATE /**< Get GPIO state request type */
} ciot_gpio_req_type_t;

/**
 * @brief Enumeration for CIOT GPIO modes.
 */
typedef enum __attribute__((packed))
{
    CIOT_GPIO_MODE_DIABLED, /**< Disabled mode */
    CIOT_GPIO_MODE_INPUT, /**< Input mode */
    CIOT_GPIO_MODE_OUTPUT /**< Output mode */
} ciot_gpio_mode_t;

/**
 * @brief Enumeration for CIOT GPIO pull modes.
 */
typedef enum __attribute__((packed))
{
    CIOT_GPIO_PULL_DISABLED, /**< Pull disabled mode */
    CIOT_GPIO_PULLUP, /**< Pull-up mode */
    CIOT_GPIO_PULLDOWN /**< Pull-down mode */
} ciot_gpio_pull_mode_t;

/**
 * @brief Structure for CIOT GPIO configuration.
 */
typedef struct __attribute__((packed))
{
    uint64_t pin_mask; /**< Pin mask */
    ciot_gpio_mode_t mode; /**< Mode */
    ciot_gpio_pull_mode_t pull; /**< Pull mode */
} ciot_gpio_cfg_t;

/**
 * @brief Structure for CIOT GPIO status.
 */
typedef struct __attribute__((packed))
{
    uint64_t status_mask; /**< Status mask */
} ciot_gpio_status_t;

/**
 * @brief Structure for CIOT GPIO state information.
 */
typedef struct __attribute__((packed))
{
    uint32_t num; /**< Number */
    ciot_gpio_state_t state; /**< State */
} ciot_gpio_state_info_t;

/**
 * @brief Structure for CIOT GPIO request to get state.
 */
typedef struct __attribute__((packed))
{
    uint32_t num; /**< Number */
} ciot_gpio_req_get_state_t;

/**
 * @brief Union for CIOT GPIO request data.
 */
typedef union __attribute__((packed))
{
    ciot_gpio_cfg_t config; /**< Configuration */
    ciot_gpio_state_info_t set_state; /**< Set state information */
    ciot_gpio_req_get_state_t get_state; /**< Get state request */
} ciot_gpio_req_data_u;

/**
 * @brief Structure for CIOT GPIO request.
 */
typedef struct __attribute__((packed))
{
    ciot_gpio_req_type_t type; /**< Request type */
    ciot_gpio_req_data_u data; /**< Request data */
} ciot_gpio_req_t;

/**
 * @brief Union for CIOT GPIO data.
 */
typedef union __attribute__((packed))
{
    ciot_gpio_cfg_t config; /**< Configuration */
    ciot_gpio_status_t status; /**< Status */
    ciot_gpio_req_t request; /**< Request */
} ciot_gpio_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_GPIO_TYPES__H__
