/**
 * @file ciot_tcp_types.h
 * @ingroup hardware_types
 * @brief Defines data types and structures for CIOT TCP functionality.
 * @version 0.1
 * @date 2023-10-10
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_TCP_DATA__H__
#define __CIOT_TCP_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/**
 * @brief Enumeration for CIOT TCP connection states.
 */
typedef enum __attribute__((packed))
{
    CIOT_TCP_STATE_ERROR = -1, /**< Error state */
    CIOT_TCP_STATE_STOPPED, /**< Stopped state */
    CIOT_TCP_STATE_STARTED, /**< Started state */
    CIOT_TCP_STATE_CONNECTING, /**< Connecting state */
    CIOT_TCP_STATE_CONNECTED, /**< Connected state */
} ciot_tcp_state_t;

/**
 * @brief Enumeration for CIOT TCP DHCP (Dynamic Host Configuration Protocol) states.
 */
typedef enum __attribute__((packed))
{
    CIOT_TCP_DHCP_STATE_IDLE, /**< Idle DHCP state */
    CIOT_TCP_DHCP_STATE_STARTED, /**< Started DHCP state */
    CIOT_TCP_DHCP_STATE_STOPPED, /**< Stopped DHCP state */
} ciot_tcp_dhcp_state_t;

/**
 * @brief Enumeration for CIOT TCP DHCP configuration types.
 */
typedef enum __attribute__((packed))
{
    CIOT_TCP_DHCP_CFG_NO_CHANGE, /**< No change in DHCP configuration */
    CIOT_TCP_DHCP_CFG_CLIENT, /**< DHCP client configuration */
    CIOT_TCP_DHCP_CFG_SERVER, /**< DHCP server configuration */
    CIOT_TCP_DHCP_CFG_DISABLED, /**< DHCP disabled configuration */
} ciot_tcp_dhcp_cfg_t;

/**
 * @brief Enumeration for CIOT TCP request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_TCP_REQ_UNKNOWN, /**< Unknown TCP request type */
} ciot_tcp_req_type_t;

/**
 * @brief Structure for CIOT TCP configuration.
 */
typedef struct __attribute__((packed))
{
    ciot_tcp_dhcp_cfg_t dhcp; /**< DHCP configuration */
    uint8_t ip[4]; /**< IP address */
    uint8_t gateway[4]; /**< Gateway address */
    uint8_t mask[4]; /**< Subnet mask */
    uint8_t dns[4]; /**< DNS address */
} ciot_tcp_cfg_t;

/**
 * @brief Structure for CIOT TCP DHCP status.
 */
typedef struct __attribute__((packed))
{
    ciot_tcp_dhcp_state_t client; /**< DHCP client state */
    ciot_tcp_dhcp_state_t server; /**< DHCP server state */
} ciot_tcp_dhcp_status_t;

/**
 * @brief Structure for CIOT TCP information.
 */
typedef struct __attribute__((packed))
{
    uint8_t mac[6]; /**< MAC address */
    uint8_t ip[4]; /**< IP address */
} ciot_tcp_info_t;

/**
 * @brief Structure for CIOT TCP status.
 */
typedef struct __attribute__((packed))
{
    ciot_tcp_state_t state; /**< TCP state */
    uint8_t conn_count; /**< Connection count */
    ciot_tcp_dhcp_status_t dhcp; /**< DHCP status */
    ciot_tcp_info_t info; /**< TCP information */
} ciot_tcp_status_t;

/**
 * @brief Union for CIOT TCP request data.
 */
typedef union __attribute__((packed))
{

} ciot_tcp_req_data_u;

/**
 * @brief Structure for CIOT TCP request.
 */
typedef struct __attribute__((packed))
{
    ciot_tcp_req_type_t type; /**< Request type */
    ciot_tcp_req_data_u data; /**< Request data */
} ciot_tcp_req_t;

/**
 * @brief Union for CIOT TCP data.
 */
typedef union __attribute__((packed))
{
    ciot_tcp_cfg_t config; /**< TCP configuration */
    ciot_tcp_status_t status; /**< TCP status */
    ciot_tcp_req_t request; /**< TCP request */
} ciot_tcp_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_TCP_DATA__H__
