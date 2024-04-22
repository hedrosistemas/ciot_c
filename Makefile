gen:
	$(MAKE) gen L=c O=../src/proto -C proto -f Makefile

help:
	@echo gen: generate proto files