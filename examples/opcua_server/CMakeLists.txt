include(../../common/Common.cmake)

project(opcua_server)

FILE(GLOB_RECURSE MAIN_SRCS ../opcua_server/*)

include_directories(
    ${CIOT_INCLUDE_DIRS}
    include
    config
    .
)

add_executable(${PROJECT_NAME}
    ${CIOT_OPEN62}
    ${MAIN_SRCS}
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()
