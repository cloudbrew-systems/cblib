# 								#
# Makefile for CloudBrew Systems	#
# 								#

ROOT = .

include $(ROOT)/make-include.mk

all:
	mkdir -p $(INSTALL_INCLUDE_DIR)
	mkdir -p $(INSTALL_LIB_DIR)
	mkdir -p $(INSTALL_BIN_DIR)
	mkdir -p $(TEMP_UPLOAD)
	make -C 3rdParty
	make -C src
	make -C cloudbrew
	make -C node binding

install:
	make -C 3rdParty install
	make -C src install
	make -C cloudbrew install

clean:
	rm -Rf $(INSTALL_INCLUDE_DIR)
	rm -Rf $(INSTALL_LIB_DIR)
	rm -Rf $(INSTALL_BIN_DIR)
	sudo rm -f $(SYS_LIB_DIR)/libCloudBrew.so
	make -C src clean
	make -C cloudbrew clean
	make -C node clean

