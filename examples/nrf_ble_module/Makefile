SD = s140
TARGET = pca10056
ARMGCC_PATH = $(TARGET)/$(SD)/armgcc

compile:
	$(MAKE) -C $(ARMGCC_PATH) -f Makefile

flash:
	@echo Flashing: $(ARMGCC_PATH)
	nrfjprog --recover
	$(MAKE) flash_softdevice -C $(ARMGCC_PATH) -f Makefile
	$(MAKE) flash -C $(ARMGCC_PATH) -f Makefile
	$(MAKE) flash-sn -C Makefile