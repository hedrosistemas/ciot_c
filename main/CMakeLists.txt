FILE(GLOB_RECURSE infa_src ${CMAKE_SOURCE_DIR}/main/infra/idf/*)
FILE(GLOB_RECURSE common ${CMAKE_SOURCE_DIR}/main/infra/common/*)
FILE(GLOB_RECURSE ifaces_src ${CMAKE_SOURCE_DIR}/main/interfaces/*)
FILE(GLOB app_src ${CMAKE_SOURCE_DIR}/main/*)

idf_component_register(SRCS ${infa_src} 
                            ${ifaces_src} 
                            ${app_src}
                       INCLUDE_DIRS data 
                                    infra 
                                    common
                                    interfaces .)