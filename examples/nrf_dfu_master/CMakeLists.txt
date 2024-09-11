include(../../common/Common.cmake)

project(nrf_dfu_master)

FILE(GLOB_RECURSE MAIN_SRCS *.c)

include_directories(
    ${CIOT_INCLUDE_DIRS}
    .
)

add_executable(${PROJECT_NAME}
    ${CIOT_SRCS}
    ${CIOT_MG_SRCS}
    ${CIOT_WIN_SRCS}
    ${MAIN_SRCS}
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()