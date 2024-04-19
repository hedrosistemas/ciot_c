/**
 * @file ciot_crc.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_CRC__H__
#define __CIOT_CRC__H__

#if defined(CIOT_TARGET_ESP32)

#include "esp32/rom/crc.h"
#include "ciot_crc.h"

uint32_t ciot_crc32_le(uint32_t crc, uint8_t const *buf, uint32_t len)
{
    return crc32_le(crc, buf, len);
}

uint32_t ciot_crc32_be(uint32_t crc, uint8_t const *buf, uint32_t len)
{
    return crc32_be(crc, buf, len);
}

uint16_t ciot_crc16_le(uint16_t crc, uint8_t const *buf, uint32_t len)
{
    return crc16_le(crc, buf, len);
}

uint16_t ciot_crc16_be(uint16_t crc, uint8_t const *buf, uint32_t len)
{
    return crc_16_be(crc, buf, len);
}

uint8_t ciot_crc8_le(uint8_t crc, uint8_t const *buf, uint32_t len)
{
    return crc8_le(crc, buf, len);
}

uint8_t ciot_crc8_be(uint8_t crc, uint8_t const *buf, uint32_t len)
{
    return crc8_be(crc, buf, len);
}

#endif  //!__CIOT_CRC__H__

#endif 