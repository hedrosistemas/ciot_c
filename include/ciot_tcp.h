/**
 * @file ciot_tcp.h
 * @ingroup hardware_interfaces
 * @brief Header file for CIOT TCP module.
 * @version 0.1
 * @date 2023-10-17
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_TCP__H__
#define __CIOT_TCP__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_tcp_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

/**
 * @brief Enumeration of CIOT TCP connection types.
 */
typedef enum ciot_tcp_type
{
    CIOT_TCP_TYPE_UNKNOWN,     /*!< Unknown TCP type */
    CIOT_TCP_TYPE_WIFI_STA,    /*!< WiFi station TCP type */
    CIOT_TCP_TYPE_WIFI_AP,     /*!< WiFi access point TCP type */
    CIOT_TCP_TYPE_ETHERNET,    /*!< Ethernet TCP type */
} ciot_tcp_type_t;

/**
 * @brief Handle structure for CIOT TCP.
 */
typedef struct ciot_tcp_handle
{
    void *netif;                /*!< Network interface pointer */
    ciot_tcp_cfg_t *cfg;        /*!< TCP configuration pointer */
    ciot_tcp_status_t *status;  /*!< TCP status pointer */
} ciot_tcp_handle_t;

/**
 * @brief CIOT TCP instance pointer.
 */
typedef struct ciot_tcp *ciot_tcp_t;

/**
 * @brief CIOT TCP status message structure.
 */
typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;       /*!< Message header */
    ciot_tcp_status_t status;       /*!< TCP status */
} ciot_tcp_status_msg_t;

/**
 * @brief Initialize the CIOT TCP module.
 *
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_tcp_init(void);

/**
 * @brief Create a new CIOT TCP instance.
 *
 * @param handle Handle for the TCP instance.
 * @return CIOT TCP instance pointer.
 */
ciot_tcp_t ciot_tcp_new(ciot_tcp_handle_t *handle);

/**
 * @brief Start the CIOT TCP module with the given configuration.
 *
 * @param self CIOT TCP instance.
 * @param cfg Configuration for the TCP module.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_tcp_start(ciot_tcp_t self, ciot_tcp_cfg_t *cfg);

/**
 * @brief Stop the CIOT TCP module.
 *
 * @param self CIOT TCP instance.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_tcp_stop(ciot_tcp_t self);

/**
 * @brief Process a TCP request.
 *
 * @param self CIOT TCP instance.
 * @param req TCP request to process.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_tcp_process_req(ciot_tcp_t self, ciot_tcp_req_t *req);

/**
 * @brief Send data using the CIOT TCP module.
 *
 * @param self CIOT TCP instance.
 * @param data Pointer to the data to be sent.
 * @param size Size of the data in bytes.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_tcp_send_data(ciot_tcp_t self, uint8_t *data, int size);

/**
 * @brief Register an event handler for the CIOT TCP module.
 *
 * @param tcp CIOT TCP instance.
 * @param event_handler Event handler function pointer.
 * @param event_args Event handler arguments.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_tcp_register_event(ciot_tcp_t tcp, ciot_iface_event_handler_t event_handler, void *event_args);

/**
 * @brief Get the IP address of the CIOT TCP module.
 *
 * @param self CIOT TCP instance.
 * @param ip Array to store the IP address (4 bytes).
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_tcp_get_ip(ciot_tcp_t self, uint8_t ip[4]);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_TCP__H__
