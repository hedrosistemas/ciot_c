/**
 * @file ciot_wifi.h
 * @ingroup hardware_interfaces
 * @brief Header file for CIOT Wi-Fi module.
 * @version 0.1
 * @date 2023-10-18
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_WIFI__H__
#define __CIOT_WIFI__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_wifi_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

/**
 * @brief Default configuration values for Wi-Fi Access Point (AP).
 */
#ifndef CIOT_CONFIG_WIFI_AP_AUTH
#define CIOT_CONFIG_WIFI_AP_AUTH 0
#endif
#ifndef CIOT_CONFIG_WIFI_AP_MAX_CONN
#define CIOT_CONFIG_WIFI_AP_MAX_CONN 1
#endif

typedef struct ciot_wifi *ciot_wifi_t;

/**
 * @brief Enumeration of Wi-Fi event IDs.
 */
typedef enum ciot_wifi_event_id {
    CIOT_WIFI_EVENT_STA_START = CIOT_IFACE_EVENT_CUSTOM, ///< Event for Wi-Fi STA start.
    CIOT_WIFI_EVENT_STA_STOP,                             ///< Event for Wi-Fi STA stop.
    CIOT_WIFI_EVENT_STA_CONNECTED,                        ///< Event for Wi-Fi STA connected.
    CIOT_WIFI_EVENT_STA_DISCONNECTED,                     ///< Event for Wi-Fi STA disconnected.
    CIOT_WIFI_EVENT_AP_START,                             ///< Event for Wi-Fi AP start.
    CIOT_WIFI_EVENT_AP_STOP,                              ///< Event for Wi-Fi AP stop.
    CIOT_WIFI_EVENT_AP_STACONNECTED,                      ///< Event for Wi-Fi AP STA connected.
    CIOT_WIFI_EVENT_AP_STADISCONNECTED,                   ///< Event for Wi-Fi AP STA disconnected.
} ciot_wifi_event_id_t;

/**
 * @brief Packed structure for Wi-Fi status message.
 */
typedef struct __attribute__((packed)) {
    ciot_msg_header_t header; ///< Message header.
    ciot_wifi_status_t status; ///< Wi-Fi status.
} ciot_wifi_status_msg_t;

/**
 * @brief Create a new CIOT Wi-Fi instance.
 *
 * @param handle Pointer to the Wi-Fi handle.
 * @return Pointer to the created CIOT Wi-Fi instance.
 */
ciot_wifi_t ciot_wifi_new(void *handle);

/**
 * @brief Create a new CIOT Wi-Fi instance for Access Point (AP) mode.
 *
 * @param handle Pointer to the Wi-Fi handle.
 * @return Pointer to the created CIOT Wi-Fi instance for AP mode.
 */
ciot_wifi_t ciot_wifi_ap_new(void *handle);

/**
 * @brief Create a new CIOT Wi-Fi instance for Station (STA) mode.
 *
 * @param handle Pointer to the Wi-Fi handle.
 * @return Pointer to the created CIOT Wi-Fi instance for STA mode.
 */
ciot_wifi_t ciot_wifi_sta_new(void *handle);

/**
 * @brief Start the CIOT Wi-Fi module.
 *
 * @param self Pointer to the CIOT Wi-Fi instance.
 * @param cfg Pointer to the Wi-Fi configuration.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_wifi_start(ciot_wifi_t self, ciot_wifi_cfg_t *cfg);

/**
 * @brief Stop the CIOT Wi-Fi module.
 *
 * @param self Pointer to the CIOT Wi-Fi instance.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_wifi_stop(ciot_wifi_t self);

/**
 * @brief Process a Wi-Fi request.
 *
 * @param self Pointer to the CIOT Wi-Fi instance.
 * @param req Pointer to the Wi-Fi request.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_wifi_process_req(ciot_wifi_t self, ciot_wifi_req_t *req);

/**
 * @brief Send data over Wi-Fi.
 *
 * @param self Pointer to the CIOT Wi-Fi instance.
 * @param data Pointer to the data buffer.
 * @param size Size of the data buffer.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_wifi_send_data(ciot_wifi_t self, uint8_t *data, int size);

/**
 * @brief Get the MAC address of the Wi-Fi module.
 *
 * @param self Pointer to the CIOT Wi-Fi instance.
 * @param type Type of Wi-Fi (AP or STA).
 * @param mac Buffer to store the MAC address.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_wifi_get_mac(ciot_wifi_t self, ciot_wifi_type_t type, uint8_t mac[6]);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_WIFI__H__
