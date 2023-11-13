set(CIOT_DIR ../../../)

FILE(GLOB_RECURSE infa_src ${CIOT_DIR}/main/infra/idf/*)
FILE(GLOB_RECURSE ifaces_src ${CIOT_DIR}/main/interfaces/*)
FILE(GLOB app_src ${CIOT_DIR}/main/*)

idf_component_register(SRCS 
                        ${infa_src}
                        ${ifaces_src}
                        ${mg_src}
                        ${app_src}
                       INCLUDE_DIRS
                        .
                        ${CIOT_DIR}/main/types
                        ${CIOT_DIR}/main/infra
                        ${CIOT_DIR}/main/interfaces
                        ${CIOT_DIR}/main/mongoose
                        ${CIOT_DIR}/main
)
