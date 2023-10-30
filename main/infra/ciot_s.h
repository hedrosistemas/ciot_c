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

#include <inttypes.h>

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
} ciot_s_status_t;

/**
 * @brief Message handler function type definition
 *
 */
typedef ciot_err_t(ciot_s_msg_handler_t)(ciot_s_t s, char *data, int size);

/**
 * @brief ciot_s config struct
 *
 */
typedef struct ciot_s_cfg
{
    ciot_s_msg_handler_t *on_message_cb;   /*! Callback called when receiving message  */
    void *handler;                         /*! Optional handler to store data that can be used on ciot_s_write_bytes*/
} ciot_s_cfg_t;

ciot_s_t ciot_s_new(ciot_s_cfg_t *cfg);
ciot_err_t ciot_s_send(ciot_s_t s, char *data, int size);
ciot_err_t ciot_s_process_byte(ciot_s_t s, char byte);
ciot_err_t ciot_s_get_handler(ciot_s_t s, void *handler);

extern ciot_err_t ciot_s_write_bytes(ciot_s_t s, char *bytes, int size);

#endif //!__CIOT_S__H__