# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly

cmake_minimum_required(VERSION 3.5)

set(CIOT_DIR ../../)

project(ciot_win32)

FILE(GLOB_RECURSE common ${CIOT_DIR}/src/common/*)
FILE(GLOB_RECURSE platform ${CIOT_DIR}/src/platform/mongoose/*)

include_directories(
    ${CIOT_DIR}/src/platform/mongoose
    ${CIOT_DIR}/include
    ${CIOT_DIR}/include/types
    .
)

add_executable(${PROJECT_NAME}
    ${common}
    ${platform}
    main.c
)

target_link_libraries(${PROJECT_NAME} ws2_32)
