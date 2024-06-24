/**
 * @file ciot_msg_types.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_MSG_TYPES__H__
#define __CIOT_MSG_TYPES__H__

#include "ciot/proto/v1/msg.pb-c.h"

typedef Ciot__Msg ciot_msg_t;
typedef Ciot__MsgType ciot_msg_type_t;
typedef Ciot__MsgData ciot_msg_data_t;
typedef Ciot__MsgError ciot_msg_error_t;
typedef Ciot__MsgHeader ciot_msg_header_t;

#endif  //!__CIOT_MSG_TYPES__H__
