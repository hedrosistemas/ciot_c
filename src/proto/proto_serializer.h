/**
 * @file proto_serializer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __PROTO_SERIALIZER__H__
#define __PROTO_SERIALIZER__H__

#include <inttypes.h>
#include "types/ciot_msg_types.h"
#include "ciot_serializer.h"

ciot_serializer_t proto_serializer_new(void);
int proto_serializer_to_bytes(uint8_t *bytes, ciot_msg_t *msg);
int proto_serializer_from_bytes(ciot_msg_t *msg, uint8_t *bytes, int size);

#endif  //!__PROTO_SERIALIZER__H__
