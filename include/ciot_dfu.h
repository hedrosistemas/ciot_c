/**
 * @file ciot_dfu.h
 * @ingroup software_interfaces
 * @brief Header file for Device Firmware Update (DFU) functionality in CIOT library.
 * @version 0.1
 * @date 2024-03-20
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2024
 */

#ifndef __CIOT_DFU__H__
#define __CIOT_DFU__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_dfu_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef struct ciot_dfu *ciot_dfu_t; /**< Opaque pointer to a CIOT DFU object. */

/**
 * @brief Enumerates DFU event IDs.
 */
typedef enum ciot_dfu_event_id {
    CIOT_DFU_EVENT_STATE_CHANGED = CIOT_IFACE_EVENT_CUSTOM, /**< DFU state changed event. */
} ciot_dfu_event_id_t;

/**
 * @brief Struct for DFU status message.
 */
typedef struct __attribute__((packed)) {
    ciot_msg_header_t header; /**< Header for the DFU status message. */
    ciot_dfu_status_t status; /**< Status of the DFU operation. */
} ciot_dfu_status_msg_t;

/**
 * @brief Creates a new CIOT DFU object.
 * @param handle Pointer to the handle.
 * @return Pointer to the created DFU object.
 */
ciot_dfu_t ciot_dfu_new(void *handle);

/**
 * @brief Starts the DFU process.
 * @param self Pointer to the DFU object.
 * @param cfg Pointer to the DFU configuration.
 * @return Error code indicating the status of the operation.
 */
ciot_err_t ciot_dfu_start(ciot_dfu_t self, ciot_dfu_cfg_t *cfg);

/**
 * @brief Stops the DFU process.
 * @param self Pointer to the DFU object.
 * @return Error code indicating the status of the operation.
 */
ciot_err_t ciot_dfu_stop(ciot_dfu_t self);

/**
 * @brief Processes a DFU request.
 * @param self Pointer to the DFU object.
 * @param req Pointer to the DFU request.
 * @return Error code indicating the status of the operation.
 */
ciot_err_t ciot_dfu_process_req(ciot_dfu_t self, ciot_dfu_req_t *req);

/**
 * @brief Sends data during the DFU process.
 * @param self Pointer to the DFU object.
 * @param data Pointer to the data to be sent.
 * @param size Size of the data to be sent.
 * @return Error code indicating the status of the operation.
 */
ciot_err_t ciot_dfu_send_data(ciot_dfu_t self, uint8_t *data, int size);

/**
 * @brief Performs the DFU task.
 * @param self Pointer to the DFU object.
 * @return Error code indicating the status of the operation.
 */
ciot_err_t ciot_dfu_task(ciot_dfu_t self);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_DFU__H__
