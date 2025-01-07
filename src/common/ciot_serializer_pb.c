/**
 * @file ciot_serializer_pb.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ciot_serializer_pb.h"

#include <pb_encode.h>
#include <pb_decode.h>

#include <stdlib.h>

static int ciot_serializer_pb_to_bytes(uint8_t *bytes, int size, ciot_msg_t *msg);
static int ciot_serializer_pb_from_bytes(uint8_t *bytes, int size, ciot_msg_t *msg);

ciot_serializer_t ciot_serializer_pb_new(void)
{
    ciot_serializer_t self = calloc(1, sizeof(struct ciot_serializer));
    self->type = CIOT_SERIALIZER_TYPE_PROTOBUF;
    self->to_bytes = ciot_serializer_pb_to_bytes;
    self->from_bytes = ciot_serializer_pb_from_bytes;
    return self;
}

static int ciot_serializer_pb_to_bytes(uint8_t *bytes, int size, ciot_msg_t *msg)
{
    pb_ostream_t stream = pb_ostream_from_buffer(bytes, size);
    pb_encode(&stream, CIOT_MSG_FIELDS, msg);
    return stream.bytes_written;
}

static int ciot_serializer_pb_from_bytes(uint8_t *bytes, int size, ciot_msg_t *msg)
{
    pb_istream_t stream = pb_istream_from_buffer(bytes, size);
    bool status = pb_decode(&stream, CIOT_MSG_FIELDS, msg);
    return status ? sizeof(ciot_msg_t) : 0;
}
