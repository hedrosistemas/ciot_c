# ciot_c Release

### Changed
    - fixed ota decrypted null handler error on ESP32
    - decreased OTA task priority on ESP32 to prevent wifi ap disconnection duging OTA
    - fixed NRF DFU over UART interface
    - fixed OTA triggering an error event on startup
