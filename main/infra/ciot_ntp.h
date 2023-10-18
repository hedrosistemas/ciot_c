/**
 * @file ciot_ntp.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_NTP__H__
#define __CIOT_NTP__H__

#include "ciot_ntp_data.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef struct ciot_ntp *ciot_ntp_t;

ciot_ntp_t ciot_ntp_new(void *handle);

ciot_err_t ciot_ntp_start(ciot_ntp_t this, ciot_ntp_cfg_t *cfg);
ciot_err_t ciot_ntp_stop(ciot_ntp_t this);
ciot_err_t ciot_ntp_process_req(ciot_ntp_t this, ciot_ntp_req_t *req);
ciot_err_t ciot_ntp_send_data(ciot_ntp_t this, uint8_t *data, int size);

ciot_err_t ciot_ntp_set(ciot_ntp_t ntp);

#endif  //!__CIOT_NTP__H__