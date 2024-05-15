/**
 * @file serialization_test.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ciot/proto_serializer.h"

int app_main(void)
{
    // ciot_msg_t input = {
    //     .id = 10,
    //     .type = CIOT_MSG_TYPE_GET_CONFIG,
    //     .iface.id = 15,
    //     .iface.type = CIOT_IFACE_TYPE_BLE_SCN,
    //     .data.ble_scn.config = {
    //         .active = true,
    //         .brigde_mode = false,
    //         .interval = 55,
    //         .timeout = 200,
    //         .window = 37
    //     },
    // };

    ciot_msg_t input = {
        .id = 10,
        .type = CIOT_MSG_TYPE_GET_STATUS,
        .iface.id = 15,
        .iface.type = CIOT_IFACE_TYPE_BLE_SCN,
        .data.ble_scn.status = {
            .adv_info = {
                .mac = { 0x45, 0x48, 0x12, 0x00, 0xaa, 0xbb },
                .rssi = -65
            },
            .err_code = CIOT_ERR_BUSY,
            .state = CIOT_BLE_SCN_STATE_PASSIVE
        },
    };

    uint8_t bytes[255];

    int size = ciot_msg_to_bytes(bytes, &input);

    ciot_msg_t output = { 0 };

    int result = ciot_msg_from_bytes(&output, bytes, size);

    return 0;
}
