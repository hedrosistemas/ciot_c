/**
 * @file ciot_serializer_pb.h
 * @ingroup serialization
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief Header file for the Protocol Buffers serializer module.
 * @version 0.1
 * @date 2024-02-28
 * 
 * @details This file contains declarations for functions related to serializing
 *          Protocol Buffers format messages to bytes and deserializing bytes to
 *          Protocol Buffers format messages.
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_SERIALIZER_PB__H__
#define __CIOT_SERIALIZER_PB__H__

#include <inttypes.h>
#include "types/ciot_msg_types.h"
#include "ciot_serializer.h"

/**
 * @brief Creates a new Protocol Buffers serializer instance.
 * 
 * @return A new instance of the Protocol Buffers serializer.
 */
ciot_serializer_t ciot_serializer_pb_new(void);

/**
 * @brief Converts a Protocol Buffers format message to bytes.
 * 
 * @param bytes Pointer to the buffer where the serialized bytes will be stored.
 * @param msg Pointer to the Protocol Buffers format message to be serialized.
 * @return The number of bytes written to the buffer, or a negative value on error.
 */
int ciot_serializer_pb_to_bytes(uint8_t *bytes, ciot_msg_t *msg);

/**
 * @brief Converts bytes to a Protocol Buffers format message.
 * 
 * @param msg Pointer to the Protocol Buffers format message structure where
 *            the deserialized message will be stored.
 * @param bytes Pointer to the buffer containing the serialized bytes.
 * @param size The size of the buffer containing the serialized bytes.
 * @return The number of bytes read from the buffer, or a negative value on error.
 */
int ciot_serializer_pb_from_bytes(ciot_msg_t *msg, uint8_t *bytes, int size);

#endif  //!__CIOT_SERIALIZER_PB__H__
