/**
 * @file ciot_ntp.h
 * @ingroup software_interfaces
 * @brief Header file for CIOT NTP (Network Time Protocol) functionality.
 * @version 0.1
 * @date 2023-10-17
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_NTP__H__
#define __CIOT_NTP__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_ntp_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

/**
 * @brief Opaque pointer to CIOT NTP structure.
 */
typedef struct ciot_ntp *ciot_ntp_t;

/**
 * @brief Structure for CIOT NTP status message.
 */
typedef struct __attribute__((packed))
{
    ciot_msg_header_t header; /**< Message header. */
    ciot_ntp_status_t status; /**< NTP status. */
} ciot_ntp_status_msg_t;

/**
 * @brief Create a new CIOT NTP instance.
 *
 * @param handle Pointer to the handle.
 * @return Instance of CIOT NTP.
 */
ciot_ntp_t ciot_ntp_new(void *handle);

/**
 * @brief Start CIOT NTP.
 *
 * @param self Instance of CIOT NTP.
 * @param cfg Configuration for NTP.
 * @return Error code.
 */
ciot_err_t ciot_ntp_start(ciot_ntp_t self, ciot_ntp_cfg_t *cfg);

/**
 * @brief Stop CIOT NTP.
 *
 * @param self Instance of CIOT NTP.
 * @return Error code.
 */
ciot_err_t ciot_ntp_stop(ciot_ntp_t self);

/**
 * @brief Process NTP request for CIOT NTP.
 *
 * @param self Instance of CIOT NTP.
 * @param req NTP request.
 * @return Error code.
 */
ciot_err_t ciot_ntp_process_req(ciot_ntp_t self, ciot_ntp_req_t *req);

/**
 * @brief Send data for CIOT NTP.
 *
 * @param self Instance of CIOT NTP.
 * @param data Data to send.
 * @param size Size of data.
 * @return Error code.
 */
ciot_err_t ciot_ntp_send_data(ciot_ntp_t self, uint8_t *data, int size);

/**
 * @brief Set CIOT NTP configuration.
 *
 * @param ntp Instance of CIOT NTP.
 * @return Error code.
 */
ciot_err_t ciot_ntp_set(ciot_ntp_t ntp);

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_NTP__H__
