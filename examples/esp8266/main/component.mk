#
# Main component makefile.
#
# This Makefile can be left empty. By default, it will take the sources in the 
# src/ directory, compile them and link them into lib(subdirectory_name).a 
# in the build directory. This behaviour is entirely configurable,
# please read the ESP-IDF documents if you need to do this.
#

CIOT_DIR := ../../..

EXTRA_COMPONENT_DIRS += CIOT_DIR

COMPONENT_ADD_INCLUDEDIRS += \
  . \
  $(CIOT_DIR)/include \
  $(CIOT_DIR)/include/types \
  $(CIOT_DIR)/src/platform/mongoose \

COMPONENT_SRCDIRS += $(CIOT_DIR)/src/common
COMPONENT_SRCDIRS += $(CIOT_DIR)/src/platform/mongoose
