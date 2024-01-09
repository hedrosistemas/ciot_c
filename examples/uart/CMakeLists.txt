cmake_minimum_required(VERSION 3.5)

set(CIOT_DIR E:/Projetos/ciot-platform/ciot-c)

project(uart_sample)

FILE(GLOB_RECURSE common ${CIOT_DIR}/src/common/*)
FILE(GLOB_RECURSE win ${CIOT_DIR}/src/win/*)

include_directories(
    ${CIOT_DIR}/include
    .
)

add_executable(${PROJECT_NAME}
    ${common}
    ${win}
    main.c
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()