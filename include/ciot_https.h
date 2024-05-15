/**
 * @file ciot_https.h
 * @ingroup software_interfaces
 * @brief Header file for CIOT HTTP server interface.
 * @version 0.1
 * @date 2023-10-10
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_HTTPS__H__
#define __CIOT_HTTPS__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_https_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

/**
 * @brief Structure representing the CIOT HTTP server interface.
 */
typedef struct ciot_https *ciot_https_t;

/**
 * @brief Enumeration of HTTP server event IDs.
 */
typedef enum ciot_https_event_id {
    CIOT_HTTPS_EVENT_DATA = CIOT_IFACE_EVENT_CUSTOM, /**< Event ID for data received. */
} ciot_https_event_id_t;

/**
 * @brief Structure representing the CIOT HTTP server status message.
 */
typedef struct __attribute__((packed)) {
    ciot_msg_header_t header; /**< Message header. */
    ciot_https_status_t status; /**< HTTP server status. */
} ciot_https_status_msg_t;

/**
 * @brief Creates a new CIOT HTTP server interface instance.
 * @param handle The handle for the HTTP server interface.
 * @return A pointer to the new CIOT HTTP server instance.
 */
ciot_https_t ciot_https_new(void *handle);

/**
 * @brief Starts the CIOT HTTP server interface.
 * @param self The CIOT HTTP server instance.
 * @param cfg The HTTP server configuration.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_https_start(ciot_https_t self, ciot_https_cfg_t *cfg);

/**
 * @brief Stops the CIOT HTTP server interface.
 * @param self The CIOT HTTP server instance.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_https_stop(ciot_https_t self);

/**
 * @brief Processes a request for the CIOT HTTP server interface.
 * @param self The CIOT HTTP server instance.
 * @param req The HTTP server request to be processed.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_https_process_req(ciot_https_t self, ciot_https_req_t *req);

/**
 * @brief Sends data over the CIOT HTTP server interface.
 * @param self The CIOT HTTP server instance.
 * @param data The data to be sent.
 * @param size The size of the data.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_https_send_data(ciot_https_t self, uint8_t *data, int size);

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_HTTPS__H__
