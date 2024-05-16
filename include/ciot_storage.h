/**
 * @file ciot_storage.h
 * @ingroup hardware_interfaces
 * @brief Header file for CIOT Storage module.
 * @version 0.1
 * @date 2023-11-04
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_STORAGE__H__
#define __CIOT_STORAGE__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_storage_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

/**
 * @brief CIOT Storage instance pointer.
 */
typedef struct ciot_storage *ciot_storage_t;

/**
 * @brief CIOT Storage status message structure.
 */
typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;      /*!< Message header */
    ciot_storage_status_t status;  /*!< Storage status */
} ciot_storage_status_msg_t;

/**
 * @brief Create a new CIOT Storage instance.
 *
 * @param handle Pointer to the storage handle.
 * @return CIOT Storage instance pointer.
 */
ciot_storage_t ciot_storage_new(void *handle);

/**
 * @brief Initialize the CIOT Storage module.
 *
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_storage_init(void);

/**
 * @brief Start the CIOT Storage module with the given configuration.
 *
 * @param self CIOT Storage instance.
 * @param cfg Configuration for the storage module.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_storage_start(ciot_storage_t self, ciot_storage_cfg_t *cfg);

/**
 * @brief Stop the CIOT Storage module.
 *
 * @param self CIOT Storage instance.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_storage_stop(ciot_storage_t self);

/**
 * @brief Process a storage request.
 *
 * @param self CIOT Storage instance.
 * @param req Storage request to process.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_storage_process_req(ciot_storage_t self, ciot_storage_req_t *req);

/**
 * @brief Send data using the CIOT Storage module.
 *
 * @param self CIOT Storage instance.
 * @param data Pointer to the data to be sent.
 * @param size Size of the data in bytes.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_storage_send_data(ciot_storage_t self, uint8_t *data, int size);

/**
 * @brief Save data to storage.
 *
 * @param self CIOT Storage instance.
 * @param path Path where data will be saved.
 * @param data Pointer to the data to save.
 * @param size Size of the data in bytes.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_storage_save(ciot_storage_t self, char *path, uint8_t *data, int size);

/**
 * @brief Load data from storage.
 *
 * @param self CIOT Storage instance.
 * @param path Path from where data will be loaded.
 * @param data Pointer to store the loaded data.
 * @param size Size of the data buffer in bytes.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_storage_load(ciot_storage_t self, char *path, uint8_t *data, int size);

/**
 * @brief Delete data from storage.
 *
 * @param self CIOT Storage instance.
 * @param path Path of the data to delete.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_storage_delete(ciot_storage_t self, char *path);

/**
 * @brief Format the storage.
 *
 * @param self CIOT Storage instance.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_storage_format(ciot_storage_t self);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_STORAGE__H__
