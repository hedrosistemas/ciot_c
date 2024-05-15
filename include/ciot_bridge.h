/**
 * @file ciot_bridge.h
 * @ingroup software_interfaces
 * @brief Defines functions and types for CIOT Bridge module.
 * @version 0.1
 * @date 2023-11-13
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_BRIDGE__H__
#define __CIOT_BRIDGE__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_bridge_types.h" /**< Include CIOT Bridge types */
#include "ciot_iface.h" /**< Include CIOT interface */
#include "ciot_err.h" /**< Include CIOT error handling */

#define CIOT_BRIDGE_NULL_TARGET -1 /**< Null target ID for CIOT Bridge */

/** @brief Pointer to a CIOT Bridge object */
typedef struct ciot_bridge *ciot_bridge_t;

/** @brief Structure for CIOT Bridge status message */
typedef struct __attribute__((packed))
{
    ciot_msg_header_t header; /**< Message header */
    ciot_bridge_status_t status; /**< Bridge status */
} ciot_bridge_status_msg_t;

/** @brief Create a new CIOT Bridge object
 * 
 * @param handle Pointer to the handle
 * @return Pointer to the created CIOT Bridge object
 */
ciot_bridge_t ciot_bridge_new(void *handle);

/** @brief Start the CIOT Bridge module
 * 
 * @param self Pointer to the CIOT Bridge object
 * @param cfg Pointer to the Bridge configuration
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_bridge_start(ciot_bridge_t self, ciot_bridge_cfg_t *cfg);

/** @brief Stop the CIOT Bridge module
 * 
 * @param self Pointer to the CIOT Bridge object
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_bridge_stop(ciot_bridge_t self);

/** @brief Process a Bridge module request
 * 
 * @param self Pointer to the CIOT Bridge object
 * @param req Pointer to the Bridge request
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_bridge_process_req(ciot_bridge_t self, ciot_bridge_req_t *req);

/** @brief Send data using the CIOT Bridge module
 * 
 * @param self Pointer to the CIOT Bridge object
 * @param data Pointer to the data to be sent
 * @param size Size of the data in bytes
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_bridge_send_data(ciot_bridge_t self, uint8_t *data, int size);

/** @brief Get the target ID for a sender in the CIOT Bridge module
 * 
 * @param self Pointer to the CIOT Bridge object
 * @param sender_id Sender ID
 * @return Target ID for the sender, or CIOT_BRIDGE_NULL_TARGET if not found
 */
int ciot_bridge_get_target_id(ciot_bridge_t self, uint8_t sender_id);

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_BRIDGE__H__
