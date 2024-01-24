/**
 * @file ciot_s.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-09
 *
 * @copyright Copyright (c) 2023
 *
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

#define CIOT_S_BASE_ERR 0x0  /*!< Starting number of ciot_s error codes */
#define CIOT_S_START_CH '{'  /*!< Message start character */
#define CIOT_S_LENGHT_SIZE 2 /*!< Number of bytes used to receive message length */
#define CIOT_S_END_CH '}'    /*!< Message end character */
#define CIOT_S_BUF_SIZE 512  /*!< Buffer size*/
#define CIOT_S_HEADER_SIZE 3 /*!< Header size */

/**
 * @brief ciot_s private struct typedef
 *
 */
typedef struct ciot_s *ciot_s_t;

/**
 * @brief ciot_s status
 *
 */
typedef enum ciot_s_status
{
    CIOT_S_STATUS_WAIT_START_DATA, /*! Waiting start data character */
    CIOT_S_STATUS_WAIT_SIZE,       /*! Waiting size */
    CIOT_S_STATUS_READ_DATA,       /*! Waiting read data */
    CIOT_S_STATUS_TIMEOUT,         /*! Data timeout */
} ciot_s_status_t;

/**
 * @brief Message handler function type definition
 *
 */
typedef ciot_err_t(ciot_s_msg_handler_t)(ciot_iface_t *iface, uint8_t *data, int size);

/**
 * @brief ciot_s config struct
 *
 */
typedef struct ciot_s_cfg
{
    ciot_s_msg_handler_t *send_bytes;      /*! Function used to send bytes */
    ciot_s_msg_handler_t *on_message_cb;   /*! Callback called when receiving message  */
    ciot_iface_t *iface;                   /*! Iface instance ptr */
    bool bridge_mode;                      /*! Enable bridge mode. At this mode ciot_s protocol will be disabled */
} ciot_s_cfg_t;

ciot_s_t ciot_s_new(ciot_s_cfg_t *cfg);
ciot_err_t ciot_s_send(ciot_s_t self, uint8_t *data, int size);
ciot_err_t ciot_s_process_byte(ciot_s_t self, uint8_t byte);
ciot_err_t ciot_s_set_bridge_mode(ciot_s_t self, bool mode);
#if CIOT_CONFIG_FEATURE_TIMER
ciot_err_t ciot_s_check_timeout(ciot_s_t self);
#endif

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_S__H__