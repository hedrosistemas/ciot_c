/**
 * @file ciot_ble_scn.h
 * @ingroup hardware_interfaces
 * @brief Defines functions and types for CIOT Bluetooth Low Energy (BLE) scanner.
 * @version 0.1
 * @date 2023-11-18
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_BLE_SCN__H__
#define __CIOT_BLE_SCN__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_ble_scn_types.h" /**< Include BLE scanner types */
#include "ciot_iface.h" /**< Include CIOT interface */
#include "ciot_err.h" /**< Include CIOT error handling */

/** @brief Pointer to a CIOT BLE scanner object */
typedef struct ciot_ble_scn *ciot_ble_scn_t;

/** @brief Structure for CIOT BLE scanner status message */
typedef struct __attribute__((packed))
{
    ciot_msg_header_t header; /**< Message header */
    ciot_ble_scn_status_t status; /**< BLE scanner status */
} ciot_ble_scn_status_msg_t;

/** @brief Create a new CIOT BLE scanner object
 * 
 * @param handle Pointer to the handle
 * @return Pointer to the created CIOT BLE scanner object
 */
ciot_ble_scn_t ciot_ble_scn_new(void *handle);

/** @brief Start the CIOT BLE scanner
 * 
 * @param self Pointer to the CIOT BLE scanner object
 * @param cfg Pointer to the BLE scanner configuration
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_ble_scn_start(ciot_ble_scn_t self, ciot_ble_scn_cfg_t *cfg);

/** @brief Stop the CIOT BLE scanner
 * 
 * @param self Pointer to the CIOT BLE scanner object
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_ble_scn_stop(ciot_ble_scn_t self);

/** @brief Process a BLE scanner request
 * 
 * @param self Pointer to the CIOT BLE scanner object
 * @param req Pointer to the BLE scanner request
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_ble_scn_process_req(ciot_ble_scn_t self, ciot_ble_scn_req_t *req);

/** @brief Send data using the CIOT BLE scanner
 * 
 * @param self Pointer to the CIOT BLE scanner object
 * @param data Pointer to the data to be sent
 * @param size Size of the data in bytes
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_ble_scn_send_data(ciot_ble_scn_t self, uint8_t *data, int size);

/** @brief Handle a BLE scanner event
 * 
 * @param self Pointer to the CIOT BLE scanner object
 * @param event Pointer to the event
 * @param event_args Pointer to the event arguments
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_ble_scn_handle_event(ciot_ble_scn_t self, void *event, void *event_args);

/** @brief Get advertising information from the CIOT BLE scanner
 * 
 * @param self Pointer to the CIOT BLE scanner object
 * @param adv_info Pointer to the advertising information structure
 * @return CIOT error code indicating success or failure
 */
ciot_err_t ciot_ble_scn_get_adv_info(ciot_ble_scn_t self, ciot_ble_scn_adv_info_t *adv_info);

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_BLE_SCN__H__
