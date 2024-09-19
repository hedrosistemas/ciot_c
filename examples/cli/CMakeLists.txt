include(../../common/Common.cmake)

project(ciot_cli)

FILE(GLOB_RECURSE MAIN_SRCS *.c)

include_directories(
    ${CIOT_INCLUDE_DIRS}
    ${CIOT_PB_INCLUDE_DIRS}
    .
)
add_executable(${PROJECT_NAME}
    ${MAIN_SRCS}
    ${CIOT_SRCS}
    ${CIOT_MG_SRCS}
    ${CIOT_WIN_SRCS}
    ${CIOT_PB_V1_SRCS}
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()