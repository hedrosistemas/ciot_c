# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly

cmake_minimum_required(VERSION 3.5)

set(CIOT_DIR ../)

project(ciot_serialization_test)

FILE(GLOB_RECURSE proto ${CIOT_DIR}/src/proto/ciot/*)
FILE(GLOB_RECURSE common ${CIOT_DIR}/src/common/*)
FILE(GLOB_RECURSE mongoose ${CIOT_DIR}/src/mg/*)
FILE(GLOB_RECURSE win ${CIOT_DIR}/src/win/*)

include_directories(
    ${CIOT_DIR}/src/mg
    ${CIOT_DIR}/src/ciot
    ${CIOT_DIR}/src/proto
    ${CIOT_DIR}/include
    .
)

add_executable(${PROJECT_NAME}
    ${CIOT_DIR}/src/proto/protobuf-c/protobuf-c.c
    ${proto}
    ${common}
    ${mongoose}
    ${win}
    serialization_test.c
)

target_link_libraries(${PROJECT_NAME} ws2_32)
