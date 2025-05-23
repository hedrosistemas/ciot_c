CIOT_PATH := $(subst \,/,$(CIOT_PATH))

PB_CIOT_PATH := $(CIOT_PATH)/ciot_protos
PB_CIOT_OPTIONS := src/proto/global.options
PB_OUT := src/proto

gen-ciot:
	generator\protoc --nanopb_opt=" -f $(PB_CIOT_OPTIONS) --c-style" --nanopb_out=$(PB_OUT) $(PB_CIOT_PATH)/ciot/proto/v2/*.proto --proto_path=$(PB_CIOT_PATH)

help:
	@echo gen-ciot: generate ANSI-C proto files
	