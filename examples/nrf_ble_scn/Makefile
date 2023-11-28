SHELL := /bin/bash
TARGET = pca10056
SD = s140

build:
	$(MAKE) -C $(TARGET)/$(SD)/armgcc -f Makefile

flash:
	$(MAKE) flash -C $(TARGET)/$(SD)/armgcc -f Makefile

flash_softdevice:
	$(MAKE) flash_softdevice -C $(TARGET)/$(SD)/armgcc -f Makefile

erase:
	$(MAKE) erase -C $(TARGET)/$(SD)/armgcc -f Makefile

recover:
	nrfjprog --recover