# ciot_c Release

### Changed
    - fixed ota decrypted null handler error on ESP32
    - decreased OTA task priority on ESP32 to prevent wifi ap disconnection duging OTA
    - fixed NRF DFU over UART interface
    - fixed OTA triggering an error event on startup
    - fixed ESP32 resetting starting UART interface
    - created request do perform OTA Rollback
    - increased pAddress buffer size on ciot_tcp windows implementation