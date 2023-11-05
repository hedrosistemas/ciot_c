# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly

cmake_minimum_required(VERSION 3.5)

set(CIOT_DIR ../../)

project(ciot_win32)

FILE(GLOB_RECURSE infa_src ${CIOT_DIR}/main/infra/mg/*)
FILE(GLOB_RECURSE ifaces_src ${CIOT_DIR}/main/interfaces/*)
FILE(GLOB_RECURSE mg_src ${CIOT_DIR}/main/mongoose/*)
FILE(GLOB app_src ${CIOT_DIR}/main/*)

include_directories(
    ${CIOT_DIR}/main/types
    ${CIOT_DIR}/main/infra
    ${CIOT_DIR}/main/interfaces
    ${CIOT_DIR}/main/mongoose
    ${CIOT_DIR}/main
    .
)

add_executable(${PROJECT_NAME}
    ${infa_src}
    ${ifaces_src}
    ${mg_src}
    ${app_src}
    main.c
)

target_link_libraries(${PROJECT_NAME} ws2_32)
