/**
 * @file ciot_mbus.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __CIOT_MBUS__H__
#define __CIOT_MBUS__H__

#include <inttypes.h>

typedef struct ciot_mbus_server_coils
{
    uint8_t *values;
    uint8_t count;
} ciot_mbus_server_coils_t;

typedef struct ciot_mbus_server_regs
{
    uint16_t *values;
    uint16_t count;
} ciot_mbus_server_regs_t;

typedef struct ciot_mbus_data
{
    ciot_mbus_server_coils_t coils;
    ciot_mbus_server_regs_t regs;
} ciot_mbus_data_t;

#endif  //!__CIOT_MBUS__H__