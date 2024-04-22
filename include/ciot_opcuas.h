/**
 * @file ciot_opcuas.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_OPCUAS__H__
#define __CIOT_OPCUAS__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_opcuas_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef struct ciot_opcuas *ciot_opcuas_t;

typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;
    ciot_opcuas_status_t status;
} ciot_opcuas_status_msg_t;

ciot_opcuas_t ciot_opcuas_new(void *handle);
ciot_err_t ciot_opcuas_start(ciot_opcuas_t self, ciot_opcuas_cfg_t *cfg);
ciot_err_t ciot_opcuas_stop(ciot_opcuas_t self);
ciot_err_t ciot_opcuas_process_req(ciot_opcuas_t self, ciot_opcuas_req_t *req);
ciot_err_t ciot_opcuas_send_data(ciot_opcuas_t self, uint8_t *data, int size);

ciot_err_t ciot_opcuas_add_node(ciot_opcuas_t self, uint16_t type, char *localization, char *display_name, char *node_id);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_OPCUAS__H__
