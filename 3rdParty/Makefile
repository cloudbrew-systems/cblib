ROOT = ..

include $(ROOT)/make-include.mk

CJSON_NAME := cJSON
CJSON_PATH := $(CJSON_NAME)Files
CJSON_PKG := $(CJSON_PATH).zip
CJSON_LIB := lib$(CJSON_NAME).so
CJSON_OBJ := $(CJSON_NAME).o

NVM_NAME := nvm
NVM_VERSION := v0.31.3
NVM_PATH := $(NVM_NAME)-$(NVM_VERSION)

all: $(CJSON_PATH) $(NVM_PATH) install

$(CJSON_PATH):
	unzip -u $(CJSON_PKG) && cd $(CJSON_NAME)
	$(CC) $(CFLAGS) -Wall -fPIC -c $(CJSON_NAME)/$(CJSON_NAME).c -o $(CJSON_OBJ)
	$(CC) -lm -shared $(LDFLAGS) -o $(CJSON_LIB) $(CJSON_OBJ)

$(NVM_PATH):
	curl -o- https://raw.githubusercontent.com/creationix/$(NVM_NAME)/$(NVM_VERSION)/install.sh | bash
	source ~/.bashrc

install:
	cp $(CJSON_NAME)/$(CJSON_NAME).h $(INSTALL_INCLUDE_DIR)
	sudo install -m 755 $(CJSON_LIB) $(SYS_LIB_DIR)
	bash node_install.sh
	sudo ldconfig

clean: clean-cjson clean-nvm

clean-cjson:
	rm -Rf $(CJSON_NAME)
	rm -Rf __MACOSX
	rm -f $(CJSON_OBJ)
	rm -f $(CJSON_LIB)
	sudo rm -f $(SYS_LIB_DIR)/$(CJSON_LIB)

clean-nvm:
	rm -Rf ~/.$(NVM_NAME)

