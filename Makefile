gen-c:
	$(MAKE) gen L=c O=../src/proto -C proto -f Makefile
	
gen-py:
	$(MAKE) gen L=python O=../scripts -C proto -f Makefile

help:
	@echo gen-c: generate ANSI-C proto files
	@echo gen-py: generate python proto files