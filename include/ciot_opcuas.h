/**
 * @file ciot_opcuas.h
 * @ingroup software_interfaces
 * @brief Header file for CIOT OPC UA Server (OPCUAS) functionality.
 * @version 0.1
 * @date 2024-04-21
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2024
 */

#ifndef __CIOT_OPCUAS__H__
#define __CIOT_OPCUAS__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_opcuas_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

/**
 * @brief Opaque pointer to CIOT OPCUAS structure.
 */
typedef struct ciot_opcuas *ciot_opcuas_t;

/**
 * @brief Structure for CIOT OPCUAS status message.
 */
typedef struct __attribute__((packed))
{
    ciot_msg_header_t header; /**< Message header. */
    ciot_opcuas_status_t status; /**< OPCUAS status. */
} ciot_opcuas_status_msg_t;

/**
 * @brief Create a new CIOT OPCUAS instance.
 *
 * @param handle Pointer to the handle.
 * @return Instance of CIOT OPCUAS.
 */
ciot_opcuas_t ciot_opcuas_new(void *handle);

/**
 * @brief Start CIOT OPCUAS.
 *
 * @param self Instance of CIOT OPCUAS.
 * @param cfg Configuration for OPCUAS.
 * @return Error code.
 */
ciot_err_t ciot_opcuas_start(ciot_opcuas_t self, ciot_opcuas_cfg_t *cfg);

/**
 * @brief Stop CIOT OPCUAS.
 *
 * @param self Instance of CIOT OPCUAS.
 * @return Error code.
 */
ciot_err_t ciot_opcuas_stop(ciot_opcuas_t self);

/**
 * @brief Process OPCUAS request for CIOT OPCUAS.
 *
 * @param self Instance of CIOT OPCUAS.
 * @param req OPCUAS request.
 * @return Error code.
 */
ciot_err_t ciot_opcuas_process_req(ciot_opcuas_t self, ciot_opcuas_req_t *req);

/**
 * @brief Send data for CIOT OPCUAS.
 *
 * @param self Instance of CIOT OPCUAS.
 * @param data Data to send.
 * @param size Size of data.
 * @return Error code.
 */
ciot_err_t ciot_opcuas_send_data(ciot_opcuas_t self, uint8_t *data, int size);

/**
 * @brief Add a node to CIOT OPCUAS.
 *
 * @param self Instance of CIOT OPCUAS.
 * @param type Type of the node.
 * @param localization Localization of the node.
 * @param display_name Display name of the node.
 * @param node_id Node ID of the node.
 * @return Error code.
 */
ciot_err_t ciot_opcuas_add_node(ciot_opcuas_t self, uint16_t type, char *localization, char *display_name, char *node_id);

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_OPCUAS__H__
