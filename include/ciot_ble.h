/**
 * @file ciot_ble.h
 * @ingroup hardware_interfaces
 * @brief Defines functions and types for CIOT Bluetooth Low Energy (BLE) module.
 * @version 0.1
 * @date 2023-11-20
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_BLE__H__
#define __CIOT_BLE__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_ble_types.h" /**< Include BLE types */
#include "ciot_err.h" /**< Include CIOT error handling */
#include "ciot_ble_scn.h" /**< Include CIOT BLE scanner */

/** @brief Pointer to a CIOT BLE object */
typedef struct ciot_ble *ciot_ble_t;

/** @brief Enumeration for CIOT BLE MAC type */
typedef enum ciot_ble_mac_type
{
    CIOT_BLE_MAC_TYPE_UNKNOWN, /**< Unknown MAC type */
    CIOT_BLE_MAC_TYPE_HARDWARE, /**< Hardware MAC type */
    CIOT_BLE_MAC_TYPE_SOFTWARE, /**< Software MAC type */
    CIOT_BLE_MAC_TYPE_REAL, /**< Real MAC type */
} ciot_ble_mac_type_t;

/** @brief Structure for CIOT BLE interface configuration */
typedef struct ciot_ble_ifaces
{
    ciot_ble_scn_t scanner; /**< BLE scanner object */
    // ciot_ble_adv_t adv; /**< BLE advertiser object */
} ciot_ble_ifaces_t;

/** @brief Structure for CIOT BLE status message */
typedef struct __attribute__((packed))
{
    ciot_msg_header_t header; /**< Message header */
    ciot_ble_status_t status; /**< BLE status */
} ciot_ble_status_msg_t;

/** @brief Create a new CIOT BLE object
 * 
 * @param handle Pointer to the handle
 * @return Pointer to the created CIOT BLE object
 */
ciot_ble_t ciot_ble_new(void *handle);

/** @brief Start the CIOT BLE module
 * 
 * @param self Pointer to the CIOT BLE object
 * @param cfg Pointer to the BLE configuration
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_ble_start(ciot_ble_t self, ciot_ble_cfg_t *cfg);

/** @brief Stop the CIOT BLE module
 * 
 * @param self Pointer to the CIOT BLE object
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_ble_stop(ciot_ble_t self);

/** @brief Process a BLE module request
 * 
 * @param self Pointer to the CIOT BLE object
 * @param req Pointer to the BLE request
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_ble_process_req(ciot_ble_t self, ciot_ble_req_t *req);

/** @brief Send data using the CIOT BLE module
 * 
 * @param self Pointer to the CIOT BLE object
 * @param data Pointer to the data to be sent
 * @param size Size of the data in bytes
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_ble_send_data(ciot_ble_t self, uint8_t *data, int size);

/** @brief Perform a task for the CIOT BLE module
 * 
 * @param self Pointer to the CIOT BLE object
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_ble_task(ciot_ble_t self);

/** @brief Set the MAC address for the CIOT BLE module
 * 
 * @param self Pointer to the CIOT BLE object
 * @param mac MAC address to set
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_ble_set_mac(ciot_ble_t self, uint8_t mac[6]);

/** @brief Get the MAC address from the CIOT BLE module
 * 
 * @param self Pointer to the CIOT BLE object
 * @param type Type of MAC address to retrieve
 * @param mac Pointer to store the retrieved MAC address
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_ble_get_mac(ciot_ble_t self, ciot_ble_mac_type_t type, uint8_t mac[6]);

/** @brief Set the interfaces for the CIOT BLE module
 * 
 * @param self Pointer to the CIOT BLE object
 * @param ifaces Pointer to the BLE interfaces configuration
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_ble_set_ifaces(ciot_ble_t self, ciot_ble_ifaces_t *ifaces);

/** @brief Check if a MAC address is valid for the CIOT BLE module
 * 
 * @param self Pointer to the CIOT BLE object
 * @param mac MAC address to check
 * @return true if the MAC address is valid, false otherwise
 */
bool ciot_ble_mac_is_valid(ciot_ble_t self, uint8_t mac[6]);

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_BLE__H__
