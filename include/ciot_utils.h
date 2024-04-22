/**
 * @file ciot_util.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_UTILS__H__
#define __CIOT_UTILS__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

void bytes_to_hex(char *dst, uint8_t *src, size_t size, bool reverse);

uint32_t crc32_compute(uint8_t const *p_data, uint32_t size, uint32_t const *p_crc);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_UTILS__H__