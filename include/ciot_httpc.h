/**
 * @file ciot_httpc.h
 * @brief Header file for CIOT HTTP client interface.
 * @version 0.1
 * @date 2023-10-10
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_HTTPC__H__
#define __CIOT_HTTPC__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_httpc_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

/**
 * @brief Structure representing the CIOT HTTP client interface.
 */
typedef struct ciot_httpc *ciot_httpc_t;

/**
 * @brief Enumeration of HTTP client event IDs.
 */
typedef enum ciot_httpc_event_id {
    CIOT_HTTPC_EVENT_CONNECTING = CIOT_IFACE_EVENT_CUSTOM, /**< Event ID for connecting. */
    CIOT_HTTPC_EVENT_CONNECTED, /**< Event ID for connected. */
} ciot_httpc_event_id_t;

/**
 * @brief Structure representing the CIOT HTTP client status message.
 */
typedef struct __attribute__((packed)) {
    ciot_msg_header_t header; /**< Message header. */
    ciot_httpc_status_t status; /**< HTTP client status. */
} ciot_httpc_status_msg_t;

/**
 * @brief Creates a new CIOT HTTP client interface instance.
 * @param handle The handle for the HTTP client interface.
 * @return A pointer to the new CIOT HTTP client instance.
 */
ciot_httpc_t ciot_httpc_new(void *handle);

/**
 * @brief Starts the CIOT HTTP client interface.
 * @param self The CIOT HTTP client instance.
 * @param cfg The HTTP client configuration.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_httpc_start(ciot_httpc_t self, ciot_httpc_cfg_t *cfg);

/**
 * @brief Stops the CIOT HTTP client interface.
 * @param self The CIOT HTTP client instance.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_httpc_stop(ciot_httpc_t self);

/**
 * @brief Processes a request for the CIOT HTTP client interface.
 * @param self The CIOT HTTP client instance.
 * @param req The HTTP client request to be processed.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_httpc_process_req(ciot_httpc_t self, ciot_httpc_req_t *req);

/**
 * @brief Sends data over the CIOT HTTP client interface.
 * @param self The CIOT HTTP client instance.
 * @param data The data to be sent.
 * @param size The size of the data.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_httpc_send_data(ciot_httpc_t self, uint8_t *data, int size);

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_HTTPC__H__
