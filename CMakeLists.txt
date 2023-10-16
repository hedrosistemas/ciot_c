cmake_minimum_required(VERSION 3.16.0)

option(CIOT_CONFIG_USE_MONGOOSE "Enable mongoose instead idf on ESP32" OFF)

if(DEFINED ENV{IDF_PATH})
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
    project(ciot_c)
else()
    project(ciot_c)
    
    FILE(GLOB_RECURSE infa_src ${CMAKE_SOURCE_DIR}/main/infra/mg/*)
    FILE(GLOB_RECURSE ifaces_src ${CMAKE_SOURCE_DIR}/main/interfaces/*)
    FILE(GLOB_RECURSE mg_src ${CMAKE_SOURCE_DIR}/main/mongoose/*)
    FILE(GLOB app_src ${CMAKE_SOURCE_DIR}/main/*)

    include_directories(AFTER
        ${CMAKE_SOURCE_DIR}/main/data
        ${CMAKE_SOURCE_DIR}/main/infra
        ${CMAKE_SOURCE_DIR}/main/interfaces
        ${CMAKE_SOURCE_DIR}/main/mongoose
        ${CMAKE_SOURCE_DIR}/main
    )

    add_executable(${PROJECT_NAME} ${infa_src} 
                                   ${ifaces_src} 
                                   ${ifaces_src} 
                                   ${mg_src} 
                                   ${app_src})

    if(WIN32)
        target_link_libraries(${PROJECT_NAME} ws2_32)
    endif()
endif()
