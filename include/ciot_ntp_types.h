/**
 * @file ciot_ntp_data.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __CIOT_NTP_DATA__H__
#define __CIOT_NTP_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <time.h>

#include "ciot_config.h"

#ifndef CIOT_CONFIG_NTP_SERVERS_COUNT
#define CIOT_CONFIG_NTP_SERVERS_COUNT 0
#endif

typedef enum __attribute__((packed))
{
    HG_NTP_STATE_RESET,
    HG_NTP_STATE_COMPLETED,
    HG_NTP_STATE_IN_PROGRESS,
} ciot_ntp_state_t;

typedef enum __attribute__((packed))
{
    CIOT_NTP_REQ_UNKNOWN,
} ciot_ntp_req_type_t;

typedef struct __attribute__((packed))
{
#if CIOT_CONFIG_FEATURE_NTP
    uint8_t op_mode;
    uint8_t sync_mode;
    uint32_t sync_interval;
    char timezone[16];
    char server[CIOT_CONFIG_NTP_SERVERS_COUNT][64];
#endif
} ciot_ntp_cfg_t;

typedef struct __attribute__((packed))
{
    ciot_ntp_state_t state;
    time_t last_sync;
    uint16_t sync_count;
    uint8_t init : 1;
    uint8_t sync : 1;
    uint8_t reserve : 6;
} ciot_ntp_status_t;

typedef union __attribute__((packed))
{

} ciot_ntp_req_data_u;

typedef struct __attribute__((packed))
{
    ciot_ntp_req_type_t type;
    ciot_ntp_req_data_u data;
} ciot_ntp_req_t;

typedef union __attribute__((packed))
{
#if CIOT_CONFIG_FEATURE_NTP
    ciot_ntp_cfg_t config;
    ciot_ntp_status_t status;
    ciot_ntp_req_t request;
#endif
} ciot_ntp_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_NTP_DATA__H__