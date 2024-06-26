/**
 * @file ciot_ntp.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_NTP__H__
#define __CIOT_NTP__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_ntp_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef struct ciot_ntp *ciot_ntp_t;

typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;
    ciot_ntp_status_t status;
} ciot_ntp_status_msg_t;

ciot_ntp_t ciot_ntp_new(void *handle);
ciot_err_t ciot_ntp_start(ciot_ntp_t self, ciot_ntp_cfg_t *cfg);
ciot_err_t ciot_ntp_stop(ciot_ntp_t self);
ciot_err_t ciot_ntp_process_req(ciot_ntp_t self, ciot_ntp_req_t *req);
ciot_err_t ciot_ntp_send_data(ciot_ntp_t self, uint8_t *data, int size);

ciot_err_t ciot_ntp_set(ciot_ntp_t ntp);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_NTP__H__