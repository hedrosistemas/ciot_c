gen-c:
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\ble_adv.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\ble_scn.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\ble.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\gpio.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\dfu.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\ciot.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\errors.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\event.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\http_client.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\http_server.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\iface.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\logger.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\mbus.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\mbus_client.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\mbus_server.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\mqtt_client.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\msg.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\ntp.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\ota.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\storage.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\sys.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\tcp.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\uart.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\usb.proto --proto_path=proto
	generator\protoc --nanopb_opt="-v -f src/proto/global.options --c-style" --nanopb_out=src\proto proto\ciot\proto\v2\wifi.proto --proto_path=proto
	
gen-py:
	$(MAKE) gen L=python O=../scripts -C proto -f Makefile

help:
	@echo gen-c: generate ANSI-C proto files
	@echo gen-py: generate python proto files
	