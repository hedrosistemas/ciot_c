/**
 * @file ciot_ota.h
 * @ingroup software_interfaces
 * @brief Header file for CIOT OTA (Over-the-Air) functionality.
 * @version 0.1
 * @date 2023-10-17
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_OTA__H__
#define __CIOT_OTA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_ota_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

#ifndef CIOT_CONFIG_OTA_TASK_STACK_SIZE
#define CIOT_CONFIG_OTA_TASK_STACK_SIZE 8192 /**< Default stack size for OTA task. */
#endif
#ifndef CIOT_CONFIG_OTA_TASK_PRIORITY
#define CIOT_CONFIG_OTA_TASK_PRIORITY (tskIDLE_PRIORITY + 4) /**< Default priority for OTA task. */
#endif
#ifndef CIOT_CONFIG_OTA_TASK_CORE_ID
#define CIOT_CONFIG_OTA_TASK_CORE_ID 1 /**< Default core ID for OTA task. */
#endif
#ifndef CIOT_CONFIG_OTA_BUF_SIZE
#define CIOT_CONFIG_OTA_BUF_SIZE 1024 /**< Default buffer size for OTA. */
#endif

/**
 * @brief Opaque pointer to CIOT OTA structure.
 */
typedef struct ciot_ota *ciot_ota_t;

/**
 * @brief Enumeration of CIOT OTA event IDs.
 */
typedef enum ciot_ota_event_id
{
    CIOT_OTA_EVENT_CONNECTED = CIOT_IFACE_EVENT_CUSTOM, /**< Connected event. */
    CIOT_OTA_EVENT_READING_INFO, /**< Reading information event. */
    CIOT_OTA_EVENT_DECRYPTING, /**< Decrypting event. */
    CIOT_OTA_EVENT_WRITING, /**< Writing event. */
    CIOT_OTA_EVENT_UPDATING_APP, /**< Updating application event. */
} ciot_ota_event_id_t;

/**
 * @brief Structure for CIOT OTA status message.
 */
typedef struct __attribute__((packed))
{
    ciot_msg_header_t header; /**< Message header. */
    ciot_ota_status_t status; /**< OTA status. */
} ciot_ota_status_msg_t;

/**
 * @brief Create a new CIOT OTA instance.
 *
 * @param handle Pointer to the handle.
 * @return Instance of CIOT OTA.
 */
ciot_ota_t ciot_ota_new(void *handle);

/**
 * @brief Start CIOT OTA.
 *
 * @param self Instance of CIOT OTA.
 * @param cfg Configuration for OTA.
 * @return Error code.
 */
ciot_err_t ciot_ota_start(ciot_ota_t self, ciot_ota_cfg_t *cfg);

/**
 * @brief Stop CIOT OTA.
 *
 * @param self Instance of CIOT OTA.
 * @return Error code.
 */
ciot_err_t ciot_ota_stop(ciot_ota_t self);

/**
 * @brief Process OTA request for CIOT OTA.
 *
 * @param self Instance of CIOT OTA.
 * @param req OTA request.
 * @return Error code.
 */
ciot_err_t ciot_ota_process_req(ciot_ota_t self, ciot_ota_req_t *req);

/**
 * @brief Send data for CIOT OTA.
 *
 * @param self Instance of CIOT OTA.
 * @param data Data to send.
 * @param size Size of data.
 * @return Error code.
 */
ciot_err_t ciot_ota_send_data(ciot_ota_t self, uint8_t *data, int size);

/**
 * @brief Rollback CIOT OTA.
 *
 * @param self Instance of CIOT OTA.
 * @return Error code.
 */
ciot_err_t ciot_ota_rollback(ciot_ota_t self);

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_OTA__H__
