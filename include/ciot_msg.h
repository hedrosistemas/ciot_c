/**
 * @file ciot_msg.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_MSG__H__
#define __CIOT_MSG__H__

#include "ciot_err.h"
#include "ciot_iface.h"
#include "ciot_msg_types.h"

ciot_err_t ciot_msg_init(ciot_msg_t *msg);
ciot_msg_t* ciot_msg_get(ciot_msg_type_t type, ciot_iface_t *iface);
ciot_msg_t* ciot_msg_get_empty(ciot_msg_type_t type, ciot_iface_type_t iface_type, uint8_t iface_id);
const char *ciot_msg_type_to_str(ciot_msg_t *msg);
int ciot_msg_to_json(const ProtobufCMessage *message, char *json);
void ciot_msg_print(const ProtobufCMessage *message);

#endif  //!__CIOT_MSG__H__
