/**
 * @file ciot_nrf_dfu.h
 * @ingroup software_interfaces
 * @brief Header file for CIOT Nordic DFU functionality.
 * @version 0.1
 * @date 2024-04-18
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2024
 */

#ifndef __CIOT_NRF_DFU__H__
#define __CIOT_NRF_DFU__H__

#include "ciot_dfu.h"

/**
 * @brief Timeout value in seconds for CIOT Nordic DFU.
 */
#define CIOT_NRF_DFU_TIMEOUT_SEC 2

/**
 * @brief Maximum packet length for DFU over UART.
 */
#define CIOT_NRF_DFU_MAX_DFU_PKT_LEN_UART 64

/**
 * @brief Maximum packet length for DFU over BLE.
 */
#define CIOT_NRF_DFU_MAX_DFU_PKT_LEN_BLE 20

/**
 * @brief Enumeration for CIOT Nordic DFU packet types.
 */
typedef enum ciot_nrf_dfu_packet_type
{
    CIOT_NRF_DFU_PACKET_TYPE_INIT = 0x01, /**< DFU initialization packet type. */
    CIOT_NRF_DFU_PACKET_TYPE_APP_IMAGE, /**< DFU application image packet type. */
} ciot_nrf_dfu_packet_type_t;

/**
 * @brief Enumeration for CIOT Nordic DFU operations.
 */
typedef enum ciot_nrf_dfu_op
{
    CIOT_NRF_DFU_OP_PROTOCOL_VERSION = 0x00,  //!< Retrieve protocol version.
    CIOT_NRF_DFU_OP_OBJECT_CREATE = 0x01,     //!< Create selected object.
    CIOT_NRF_DFU_OP_RECEIPT_NOTIF_SET = 0x02, //!< Set receipt notification.
    CIOT_NRF_DFU_OP_CRC_GET = 0x03,           //!< Request CRC of selected object.
    CIOT_NRF_DFU_OP_OBJECT_EXECUTE = 0x04,    //!< Execute selected object.
    CIOT_NRF_DFU_OP_OBJECT_SELECT = 0x06,     //!< Select object.
    CIOT_NRF_DFU_OP_MTU_GET = 0x07,           //!< Retrieve MTU size.
    CIOT_NRF_DFU_OP_OBJECT_WRITE = 0x08,      //!< Write selected object.
    CIOT_NRF_DFU_OP_PING = 0x09,              //!< Ping.
    CIOT_NRF_DFU_OP_HARDWARE_VERSION = 0x0A,  //!< Retrieve hardware version.
    CIOT_NRF_DFU_OP_FIRMWARE_VERSION = 0x0B,  //!< Retrieve firmware version.
    CIOT_NRF_DFU_OP_ABORT = 0x0C,             //!< Abort the DFU procedure.
    CIOT_NRF_DFU_OP_RESPONSE = 0x60,          //!< Response.
    CIOT_NRF_DFU_OP_SLIP_PACKET_END = 0xC0,   //!< Slip end of packet.
    CIOT_NRF_DFU_OP_INVALID = 0xFF,           //!< Invalid request.
} ciot_nrf_dfu_op_t;

/**
 * @brief Enumeration for CIOT Nordic DFU results.
 */
typedef enum ciot_nrf_dfu_result
{
    CIOT_NRF_DFU_RES_CODE_INVALID = 0x00,                 //!< Invalid opcode.
    CIOT_NRF_DFU_RES_CODE_SUCCESS = 0x01,                 //!< Operation successful.
    CIOT_NRF_DFU_RES_CODE_OP_CODE_NOT_SUPPORTED = 0x02,   //!< Opcode not supported.
    CIOT_NRF_DFU_RES_CODE_INVALID_PARAMETER = 0x03,       //!< Missing or invalid parameter value.
    CIOT_NRF_DFU_RES_CODE_INSUFFICIENT_RESOURCES = 0x04,  //!< Not enough memory for the data object.
    CIOT_NRF_DFU_RES_CODE_INVALID_OBJECT = 0x05,          //!< Data object does not match firmware and hardware requirements, wrong signature, or parsing failure.
    CIOT_NRF_DFU_RES_CODE_UNSUPPORTED_TYPE = 0x07,        //!< Not a valid object type for Create request.
    CIOT_NRF_DFU_RES_CODE_OPERATION_NOT_PERMITTED = 0x08, //!< DFU process state does not allow this operation.
    CIOT_NRF_DFU_RES_CODE_OPERATION_FAILED = 0x0A,        //!< Operation failed.
    CIOT_NRF_DFU_RES_CODE_EXT_ERROR = 0x0B,               //!< Extended error. See @ref nrf_dfu_ext_error_code_t.
} ciot_nrf_dfu_result_t;

/**
 * @brief Enumeration for CIOT Nordic DFU extended error codes.
 */
typedef enum ciot_nrf_dfu_ext_error_code
{
    NRF_DFU_EXT_ERROR_NO_ERROR = 0x00,             //!< No extended error code set.
    NRF_DFU_EXT_ERROR_INVALID_ERROR_CODE = 0x01,   //!< Invalid error code.
    NRF_DFU_EXT_ERROR_WRONG_COMMAND_FORMAT = 0x02, //!< Incorrect command format.
    NRF_DFU_EXT_ERROR_UNKNOWN_COMMAND = 0x03,      //!< Unknown or unsupported command.
    NRF_DFU_EXT_ERROR_INIT_COMMAND_INVALID = 0x04, //!< Invalid init command or missing fields.
    NRF_DFU_EXT_ERROR_FW_VERSION_FAILURE = 0x05,   //!< Firmware version too low.
    NRF_DFU_EXT_ERROR_HW_VERSION_FAILURE = 0x06,   //!< Hardware version mismatch.
    NRF_DFU_EXT_ERROR_SD_VERSION_FAILURE = 0x07,   //!< SoftDevice version mismatch.
    NRF_DFU_EXT_ERROR_SIGNATURE_MISSING = 0x08,    //!< Signature missing in init packet.
    NRF_DFU_EXT_ERROR_WRONG_HASH_TYPE = 0x09,      //!< Unsupported hash type.
    NRF_DFU_EXT_ERROR_HASH_FAILED = 0x0A,          //!< Hash calculation failed.
    NRF_DFU_EXT_ERROR_WRONG_SIGNATURE_TYPE = 0x0B, //!< Unknown or unsupported signature type.
    NRF_DFU_EXT_ERROR_VERIFICATION_FAILED = 0x0C,  //!< Hash verification failed.
    NRF_DFU_EXT_ERROR_INSUFFICIENT_SPACE = 0x0D,   //!< Insufficient space for firmware.
} ciot_nrf_dfu_ext_error_code_t;

/**
 * @brief Enumeration for CIOT Nordic DFU states.
 */
typedef enum ciot_nrf_dfu_state
{
    CIOT_NRF_DFU_STATE_ERROR = -1, /**< Error state. */
    CIOT_NRF_DFU_STATE_IDLE, /**< Idle state. */
    CIOT_NRF_DFU_STATE_SEND_PING, /**< Sending ping state. */
    CIOT_NRF_DFU_STATE_WAITING_PING_RESP, /**< Waiting for ping response state. */
    CIOT_NRF_DFU_STATE_CREATE_OBJECT, /**< Creating object state. */
    CIOT_NRF_DFU_STATE_WAITING_CREATE_OBJ, /**< Waiting for object creation state. */
    CIOT_NRF_DFU_STATE_WRITE_DFU_PACKAGE, /**< Writing DFU package state. */
    CIOT_NRF_DFU_STATE_REQUEST_CRC, /**< Requesting CRC state. */
    CIOT_NRF_DFU_STATE_WAITING_CRC, /**< Waiting for CRC state. */
    CIOT_NRF_DFU_STATE_REQUEST_EXECUTE, /**< Requesting execute state. */
    CIOT_NRF_DFU_STATE_WAITING_EXECUTE, /**< Waiting for execute state. */
    CIOT_NRF_DFU_STATE_COMPLETED, /**< Completed state. */
} ciot_nrf_dfu_state_t;

/**
 * @brief Structure for CIOT Nordic DFU packet.
 */
typedef struct ciot_nrf_dfu_packet
{
    ciot_nrf_dfu_packet_type_t type; /**< Packet type. */
    uint32_t size; /**< Packet size. */
    uint8_t *data; /**< Packet data. */
    bool transferred; /**< Transferred flag. */
} ciot_nrf_dfu_packet_t;

/**
 * @brief Structure for CIOT Nordic DFU configuration.
 */
typedef struct ciot_nrf_dfu_cfg
{
    ciot_dfu_cfg_t dfu; /**< DFU configuration. */
    ciot_nrf_dfu_packet_t init_packet; /**< Initialization packet. */
    ciot_nrf_dfu_packet_t app_image; /**< Application image packet. */
    uint32_t max_package_len; /**< Maximum packet length. */
    ciot_iface_t *iface; /**< Interface pointer. */
} ciot_nrf_dfu_cfg_t;

/**
 * @brief Create a new CIOT Nordic DFU instance.
 *
 * @param cfg Pointer to the configuration.
 * @return Instance of CIOT DFU.
 */
ciot_dfu_t ciot_nrf_dfu_new(ciot_nrf_dfu_cfg_t *cfg);

/**
 * @brief Start CIOT Nordic DFU.
 *
 * @param self Instance of CIOT DFU.
 * @param cfg Configuration for DFU.
 * @return Error code.
 */
ciot_err_t ciot_nrf_dfu_start(ciot_dfu_t self, ciot_dfu_cfg_t *cfg);

/**
 * @brief Stop CIOT Nordic DFU.
 *
 * @param self Instance of CIOT DFU.
 * @return Error code.
 */
ciot_err_t ciot_nrf_dfu_stop(ciot_dfu_t self);

/**
 * @brief Process DFU request for CIOT Nordic DFU.
 *
 * @param self Instance of CIOT DFU.
 * @param req DFU request.
 * @return Error code.
 */
ciot_err_t ciot_nrf_dfu_process_req(ciot_dfu_t self, ciot_dfu_req_t *req);

/**
 * @brief Send data for CIOT Nordic DFU.
 *
 * @param self Instance of CIOT DFU.
 * @param data Data to send.
 * @param size Size of data.
 * @return Error code.
 */
ciot_err_t ciot_nrf_dfu_send_data(ciot_dfu_t self, uint8_t *data, int size);

/**
 * @brief Perform CIOT Nordic DFU task.
 *
 * @param self Instance of CIOT DFU.
 * @return Error code.
 */
ciot_err_t ciot_nrf_dfu_task(ciot_dfu_t self);

/**
 * @brief Send firmware for CIOT Nordic DFU.
 *
 * @param self Instance of CIOT DFU.
 * @return Error code.
 */
ciot_err_t ciot_nrf_dfu_send_firmware(ciot_dfu_t self);

/**
 * @brief Read file for CIOT Nordic DFU.
 *
 * @param object Object to read into.
 * @param name Name of the file.
 * @return Error code.
 */
ciot_err_t ciot_nrf_dfu_read_file(ciot_nrf_dfu_packet_t *object, const char *name);

/**
 * @brief Start bootloader for CIOT Nordic DFU.
 *
 * @param self Instance of CIOT DFU.
 * @param iface Interface pointer.
 * @param sys_id System ID.
 * @return Error code.
 */
ciot_err_t ciot_nrf_dfu_start_bootloader(ciot_dfu_t self, ciot_iface_t *iface, int sys_id);

/**
 * @brief Get the state of CIOT Nordic DFU.
 *
 * @param self Instance of CIOT DFU.
 * @return State of DFU.
 */
ciot_nrf_dfu_state_t ciot_nrf_dfu_state(ciot_dfu_t self);

#endif //!__CIOT_NRF_DFU__H__
