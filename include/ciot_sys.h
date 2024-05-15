/**
 * @file ciot_sys.h
 * @ingroup software_interfaces
 * @brief Header file for CIOT System module.
 * @version 0.1
 * @date 2023-10-17
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_SYS__H__
#define __CIOT_SYS__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_sys_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

/**
 * @brief Event bit for CIOT System module.
 */
#define CIOT_SYS_EVT_BIT_POOLING 0x00000001

/**
 * @brief CIOT System instance pointer.
 */
typedef struct ciot_sys *ciot_sys_t;

/**
 * @brief CIOT System status message structure.
 */
typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;      /*!< Message header */
    ciot_sys_status_t status;      /*!< System status */
} ciot_sys_status_msg_t;

/**
 * @brief Create a new CIOT System instance.
 *
 * @param handle Pointer to the system handle.
 * @return CIOT System instance pointer.
 */
ciot_sys_t ciot_sys_new(void *handle);

/**
 * @brief Start the CIOT System module with the given configuration.
 *
 * @param self CIOT System instance.
 * @param cfg Configuration for the system module.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_sys_start(ciot_sys_t self, ciot_sys_cfg_t *cfg);

/**
 * @brief Stop the CIOT System module.
 *
 * @param self CIOT System instance.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_sys_stop(ciot_sys_t self);

/**
 * @brief Process a system request.
 *
 * @param self CIOT System instance.
 * @param req System request to process.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_sys_process_req(ciot_sys_t self, ciot_sys_req_t *req);

/**
 * @brief Send data using the CIOT System module.
 *
 * @param self CIOT System instance.
 * @param data Pointer to the data to be sent.
 * @param size Size of the data in bytes.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_sys_send_data(ciot_sys_t self, uint8_t *data, int size);

/**
 * @brief Reset the CIOT System module.
 *
 * @param self CIOT System instance.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_sys_rst(ciot_sys_t self);

/**
 * @brief Perform system task operations.
 *
 * @param self CIOT System instance.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_sys_task(ciot_sys_t self);

/**
 * @brief Set event bits for the CIOT System module.
 *
 * @param self CIOT System instance.
 * @param event_bits Event bits to set.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_sys_set_event_bits(ciot_sys_t self, int event_bits);

/**
 * @brief Put the system to sleep for the specified duration.
 *
 * @param ms Duration in milliseconds.
 */
void ciot_sys_sleep(long ms);

/**
 * @brief Update system features with the given features configuration.
 *
 * @param features Pointer to the system features configuration.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_sys_update_features(ciot_sys_features_t *features);

/**
 * @brief Get the hardware information of the system.
 *
 * @return Hardware information of the system.
 */
ciot_sys_hw_t ciot_sys_get_hw(void);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_SYS__H__
