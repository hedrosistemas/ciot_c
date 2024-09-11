/**
 * @file ciot_str.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_STR__H__
#define __CIOT_STR__H__

#include <string.h>
#include "ciot_err.h"

ciot_err_t ciot_strncpy(char *destiny, char *source, int size);

#endif  //!__CIOT_STR__H__
