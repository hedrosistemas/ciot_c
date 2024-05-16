/**
 * @file ciot_serializer.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ciot_serializer.h"

#if CIOT_CONFIG_FEATURE_SERIALIZER

#include <stdlib.h>

int ciot_serializer_to_bytes(ciot_serializer_t self, uint8_t *bytes, ciot_msg_t *msg)
{
    if(self == NULL || self->to_bytes == NULL)
    {
        return 0;
    }
    return self->to_bytes(bytes, msg);   
}

int ciot_serializer_from_bytes(ciot_serializer_t self, ciot_msg_t *msg, uint8_t *bytes, int size)
{
    if(self == NULL || self->from_bytes == NULL)
    {
        return 0;
    }
    return self->from_bytes(msg, bytes, size);
}

#endif
