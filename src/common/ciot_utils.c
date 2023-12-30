/**
 * @file ciot_utils.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_utils.h"
#include "stdio.h"

void bytes_to_hex(char *dst, uint8_t *src, size_t size, bool reverse)
{
    int i;
    for (i = 0; i < size; i++)
    {
        int idx = reverse ? (size - i - 1) : i;
        if (src[idx] <= 0x0F)
        {
            sprintf(&dst[i << 1], "0%X", src[idx]);
        }
        else
        {
            sprintf(&dst[i << 1], "%X", src[idx]);
        }
    }
}
