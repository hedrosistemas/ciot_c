/**
 * @file ciot_s.h
 * @ingroup utils
 * @brief Header file for CIOT_S module.
 * @details The CIoT S module is an encoding/decoding tool that can be used to assit on the process of exchange data over an stream of bytes.
 * It's useful to transport data structures over an uart/spi/i2c or other serial communication interface. 
 * @version 0.1
 * @date 2023-10-09
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_S__H__
#define __CIOT_S__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

#include "ciot_err.h"
#include "ciot_iface.h"

#if CIOT_CONFIG_FEATURE_TIMER
#include "ciot_timer.h"
#endif

#define CIOT_S_BASE_ERR 0x0     /*!< Starting number of CIOT_S error codes */
#define CIOT_S_START_CH '{'     /*!< Message start character */
#define CIOT_S_LENGHT_SIZE 2    /*!< Number of bytes used to receive message length */
#define CIOT_S_END_CH '}'       /*!< Message end character */
#define CIOT_S_BUF_SIZE 512     /*!< Buffer size */
#define CIOT_S_HEADER_SIZE 3    /*!< Header size */

/**
 * @brief CIOT_S private struct typedef
 */
typedef struct ciot_s *ciot_s_t;

/**
 * @brief CIOT_S status
 */
typedef enum ciot_s_status
{
    CIOT_S_STATUS_WAIT_START_DATA,  /*!< Waiting start data character */
    CIOT_S_STATUS_WAIT_SIZE,        /*!< Waiting size */
    CIOT_S_STATUS_READ_DATA,        /*!< Waiting read data */
    CIOT_S_STATUS_TIMEOUT,          /*!< Data timeout */
} ciot_s_status_t;

/**
 * @brief Message handler function type definition
 */
typedef ciot_err_t(ciot_s_msg_handler_t)(ciot_iface_t *iface, uint8_t *data, int size);

/**
 * @brief CIOT_S config struct
 */
typedef struct ciot_s_cfg
{
    ciot_s_msg_handler_t *send_bytes;       /*!< Function used to send bytes */
    ciot_s_msg_handler_t *on_message_cb;    /*!< Callback called when receiving message */
    ciot_iface_t *iface;                    /*!< Interface instance pointer */
    bool bridge_mode;                       /*!< Enable bridge mode. In this mode, CIOT_S protocol will be disabled */
} ciot_s_cfg_t;

/**
 * @brief Create a new CIOT_S instance.
 *
 * @param cfg Configuration for CIOT_S.
 * @return Instance of CIOT_S.
 */
ciot_s_t ciot_s_new(ciot_s_cfg_t *cfg);

/**
 * @brief Send data using CIOT_S.
 *
 * @param self Instance of CIOT_S.
 * @param data Data to send.
 * @param size Size of data.
 * @return Error code.
 */
ciot_err_t ciot_s_send(ciot_s_t self, uint8_t *data, int size);

/**
 * @brief Process a byte.
 *
 * @param self Instance of CIOT_S.
 * @param byte Byte to process.
 * @return Error code.
 */
ciot_err_t ciot_s_process_byte(ciot_s_t self, uint8_t byte);

/**
 * @brief Set bridge mode for CIOT_S.
 *
 * @param self Instance of CIOT_S.
 * @param mode Bridge mode flag.
 * @return Error code.
 */
ciot_err_t ciot_s_set_bridge_mode(ciot_s_t self, bool mode);

#if CIOT_CONFIG_FEATURE_TIMER
/**
 * @brief Check for timeout in CIOT_S.
 *
 * @param self Instance of CIOT_S.
 * @return Error code.
 */
ciot_err_t ciot_s_check_timeout(ciot_s_t self);
#endif

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_S__H__
