/**
 * @file ciot_serializer.h
 * @brief Header file for CIOT Serializer module.
 * @version 0.1
 * @date 2024-04-13
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2024
 */

#ifndef __CIOT_SERIALIZER__H__
#define __CIOT_SERIALIZER__H__

#include <inttypes.h>
#include "types/ciot_msg_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief CIOT Serializer instance pointer.
 */
typedef struct ciot_serializer *ciot_serializer_t;

/**
 * @brief Function pointer type for serializing to bytes.
 *
 * @param bytes Destination buffer for serialized data.
 * @param msg CIOT message to serialize.
 * @return Number of bytes serialized.
 */
typedef int (ciot_serializer_to_bytes_fn)(uint8_t *bytes, ciot_msg_t *msg);

/**
 * @brief Function pointer type for deserializing from bytes.
 *
 * @param msg CIOT message to fill with deserialized data.
 * @param bytes Source buffer containing serialized data.
 * @param size Size of the serialized data in bytes.
 * @return Number of bytes consumed during deserialization.
 */
typedef int (ciot_serializer_from_bytes_fn)(ciot_msg_t *msg, uint8_t *bytes, int size);

/**
 * @brief Enum representing CIOT Serializer types.
 */
typedef enum ciot_serializer_type
{
    CIOT_SERIALIZER_TYPE_NONE,   /*!< No serializer type specified */
    CIOT_SERIALIZER_TYPE_PROTOBUF, /*!< Protocol Buffers serializer */
    CIOT_SERIALIZER_TYPE_CUSTOM,  /*!< Custom serializer */
} ciot_serializer_type_t;

/**
 * @brief CIOT Serializer structure.
 */
struct ciot_serializer
{
    ciot_serializer_type_t type;            /*!< Serializer type */
    ciot_serializer_to_bytes_fn *to_bytes;  /*!< Function pointer for serializing to bytes */
    ciot_serializer_from_bytes_fn *from_bytes; /*!< Function pointer for deserializing from bytes */
};

/**
 * @brief Serialize a CIOT message to bytes using the specified serializer.
 *
 * @param self CIOT Serializer instance.
 * @param bytes Destination buffer for serialized data.
 * @param msg CIOT message to serialize.
 * @return Number of bytes serialized.
 */
int ciot_serializer_to_bytes(ciot_serializer_t self, uint8_t *bytes, ciot_msg_t *msg);

/**
 * @brief Deserialize bytes to a CIOT message using the specified serializer.
 *
 * @param self CIOT Serializer instance.
 * @param msg CIOT message to fill with deserialized data.
 * @param bytes Source buffer containing serialized data.
 * @param size Size of the serialized data in bytes.
 * @return Number of bytes consumed during deserialization.
 */
int ciot_serializer_from_bytes(ciot_serializer_t self, ciot_msg_t *msg, uint8_t *bytes, int size);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_SERIALIZER__H__
