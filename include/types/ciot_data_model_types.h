/**
 * @file ciot_data_model.h
 * @brief Defines data types and structures for the CIOT data model.
 * @version 0.1
 * @date 2023-10-10
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_DATA_MODEL__H__
#define __CIOT_DATA_MODEL__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/**
 * @brief Enumeration for CIOT data model states.
 */
typedef enum __attribute__((packed))
{
    CIOT_DATA_MODEL_STATE_IDLE, /**< Idle state */
} ciot_data_model_state_t;

/**
 * @brief Enumeration for CIOT data model request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_DATA_MODEL_REQ_UNKNOWN, /**< Unknown request type */
} ciot_data_model_req_type_t;

/**
 * @brief Structure for CIOT data model configuration.
 */
typedef struct __attribute__((packed))
{

} ciot_data_model_cfg_t;

/**
 * @brief Structure for CIOT data model status.
 */
typedef struct __attribute__((packed))
{
    ciot_data_model_state_t state; /**< State */
} ciot_data_model_status_t;

/**
 * @brief Union for CIOT data model request data.
 */
typedef union __attribute__((packed))
{

} ciot_data_model_req_data_u;

/**
 * @brief Structure for CIOT data model request.
 */
typedef struct __attribute__((packed))
{
    ciot_data_model_req_type_t type; /**< Request type */
    ciot_data_model_req_data_u data; /**< Request data */
} ciot_data_model_req_t;

/**
 * @brief Union for CIOT data model data.
 */
typedef union __attribute__((packed))
{
    ciot_data_model_cfg_t config; /**< Configuration */
    ciot_data_model_status_t status; /**< Status */
    ciot_data_model_req_t request; /**< Request */
} ciot_data_model_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_DATA_MODEL__H__
