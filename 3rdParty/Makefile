ROOT = ..

include $(ROOT)/make-include.mk

SQLITE_NAME := sqlite-autoconf
SQLITE_VERSION := 3130000
SQLITE_PATH := $(SQLITE_NAME)-$(SQLITE_VERSION)
SQLITE_PKG := $(SQLITE_PATH).tar.gz

NVM_NAME := nvm
NVM_VERSION := v0.31.3
NVM_PATH := $(NVM_NAME)-$(NVM_VERSION)

all: $(SQLITE_PATH) $(NVM_PATH) install

$(SQLITE_PATH):
	tar zxf $(SQLITE_PKG) && cd $(SQLITE_PATH)
	cd $(SQLITE_PATH) && ./configure --prefix=/usr --enable-threadsafe CFLAGS="-Os -DSQLITE_OMIT_TRIGGERS"
	cd $(SQLITE_PATH) && make

$(NVM_PATH):
	curl -o- https://raw.githubusercontent.com/creationix/$(NVM_NAME)/$(NVM_VERSION)/install.sh | bash
	source ~/.bashrc

install:
	sudo mkdir -p $(CLOUDBREW_INSTALL_DIR)/mongodb
	cd $(SQLITE_PATH) && sudo make install
	cp -f $(SQLITE_PATH)/sqlite3.o $(INSTALL_LIB_DIR)
	sudo ldconfig

clean: clean-sqlite clean-nvm

wipeout: wipeout-sqlite clean-nvm

clean-sqlite:
	cd $(SQLITE_PATH) && make clean
	rm -Rf $(SQLITE_PATH)
	rm -f $(INSTALL_LIB_DIR)/sqlite3.o

wipeout-sqlite:
	cd $(SQLITE_PATH) && make clean
	rm -Rf $(SQLITE_PATH)
	rm -f $(INSTALL_LIB_DIR)/sqlite3.o
	rm -f ~/$(CLOUDBREW_HASH_DBNAME)
	rm -f ~/$(CLOUDBREW_HASH_DBNAME).log

clean-nvm:
	rm -Rf ~/.$(NVM_NAME)
