set(CIOT_DIR ../../..)

FILE(GLOB_RECURSE common ${CIOT_DIR}/src/common/*)
FILE(GLOB_RECURSE platform ${CIOT_DIR}/src/esp32/*)

idf_component_register(SRCS 
                        ${common}
                        ${platform}
                        main.c
                       INCLUDE_DIRS
                        .
                        ${CIOT_DIR}/include
)
