#
# Makefile for CloudBrew Systems	#
#

ROOT = .

include $(ROOT)/make-include.mk

all:
	mkdir -p $(INSTALL_INCLUDE_DIR)
	mkdir -p $(INSTALL_LIB_DIR)
	mkdir -p $(INSTALL_BIN_DIR)
	mkdir -p $(TEMP_UPLOAD)
	make -C src
	make -C cloudbrew
	make -C node binding

install:
	make -C src install
	make -C cloudbrew install

## MOST COMMONLY USED. CLEANS EVERYTHING EXCEPT 3RD PARTY STUFF ##
clean:
	rm -Rf $(INSTALL_INCLUDE_DIR)
	rm -Rf $(INSTALL_LIB_DIR)
	rm -Rf $(INSTALL_BIN_DIR)
	sudo rm -f $(SYS_LIB_DIR)/libCloudBrew.so
	make -C src clean
	make -C cloudbrew clean
	make -C node clean

## CLEANS ALL INCLUDING 3RD PARTY STUFF AND CB INSTALL DIR ##
wipeout:
	rm -Rf $(INSTALL_INCLUDE_DIR)
	rm -Rf $(INSTALL_LIB_DIR)
	rm -Rf $(INSTALL_BIN_DIR)
	sudo rm -f $(SYS_LIB_DIR)/libCloudBrew.so
	make -C src clean
	make -C cloudbrew clean
	make -C node clean
	sudo rm -Rf $(CLOUDBREW_INSTALL_DIR)
	rm -Rf $(TEMP_UPLOAD)
