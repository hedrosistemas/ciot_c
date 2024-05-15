/**
 * @file ciot_eth.h
 * @ingroup hardware_interfaces
 * @brief Header file for CIOT Ethernet interface.
 * @version 0.1
 * @date 2023-10-17
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_ETH__H__
#define __CIOT_ETH__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_tcp_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

/**
 * @brief Structure representing the CIOT Ethernet interface.
 */
typedef struct ciot_eth *ciot_eth_t;

/**
 * @brief Enumeration of CIOT Ethernet event IDs.
 */
typedef enum {
    CIOT_ETH_EVENT_START = CIOT_IFACE_EVENT_CUSTOM, /**< Ethernet start event. */
    CIOT_ETH_EVENT_STOP, /**< Ethernet stop event. */
    CIOT_ETH_EVENT_CONNECTED, /**< Ethernet connected event. */
    CIOT_ETH_EVENT_DISCONNECTED, /**< Ethernet disconnected event. */
} ciot_eth_event_id_t;

/**
 * @brief Structure representing the CIOT Ethernet status message.
 */
typedef struct __attribute__((packed)) {
    ciot_msg_header_t header; /**< Message header. */
    ciot_tcp_status_t status; /**< TCP status. */
} ciot_eth_status_msg_t;

/**
 * @brief Creates a new CIOT Ethernet interface instance.
 * @param handle The handle for the Ethernet interface.
 * @return A pointer to the new CIOT Ethernet instance.
 */
ciot_eth_t ciot_eth_new(void *handle);

/**
 * @brief Starts the CIOT Ethernet interface.
 * @param self The CIOT Ethernet instance.
 * @param cfg The TCP configuration for Ethernet.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_eth_start(ciot_eth_t self, ciot_tcp_cfg_t *cfg);

/**
 * @brief Stops the CIOT Ethernet interface.
 * @param self The CIOT Ethernet instance.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_eth_stop(ciot_eth_t self);

/**
 * @brief Processes a request for the CIOT Ethernet interface.
 * @param self The CIOT Ethernet instance.
 * @param req The TCP request to be processed.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_eth_process_req(ciot_eth_t self, ciot_tcp_req_t *req);

/**
 * @brief Sends data over the CIOT Ethernet interface.
 * @param self The CIOT Ethernet instance.
 * @param data The data to be sent.
 * @param size The size of the data.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_eth_send_data(ciot_eth_t self, uint8_t *data, int size);

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_ETH__H__
