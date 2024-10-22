/**
 * @file ciot_str.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ciot_str.h"

ciot_err_t ciot_strncpy(char *destiny, char *source, int size)
{
    CIOT_ERR_NULL_CHECK(source);
    CIOT_ERR_NULL_CHECK(destiny);
    CIOT_ERR_EMPTY_STRING_CHECK(source);
    strncpy(destiny, source, size);
    return CIOT__ERR__OK;
}

