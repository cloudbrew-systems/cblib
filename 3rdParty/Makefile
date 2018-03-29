ROOT = ..

include $(ROOT)/make-include.mk

MONGODB_VERSION := 3.2.8
MONGODB_PATH := mongodb-linux-$(ARCH)-rhel70-$(MONGODB_VERSION)
MONGODB_PKG := $(MONGODB_PATH).tgz

SQLITE_NAME := sqlite-autoconf
SQLITE_VERSION := 3130000
SQLITE_PATH := $(SQLITE_NAME)-$(SQLITE_VERSION)
SQLITE_PKG := $(SQLITE_PATH).tar.gz

NVM_NAME := nvm
NVM_VERSION := v0.31.3
NVM_PATH := $(NVM_NAME)-$(NVM_VERSION)

REDIS_NAME := redis
REDIS_VERSION := 3.2.1
REDIS_PATH := $(REDIS_NAME)-$(REDIS_VERSION)
REDIS_PKG := $(REDIS_PATH).tar.gz

all: $(MONGODB_PATH) $(CJSON_PATH) $(SQLITE_PATH) $(NVM_PATH) $(REDIS_PATH) install

$(MONGODB_PATH):
	tar zxvf $(MONGODB_PKG)
	sudo mkdir -p /data/db

$(SQLITE_PATH):
	tar zxf $(SQLITE_PKG) && cd $(SQLITE_PATH)
	cd $(SQLITE_PATH) && ./configure --prefix=/usr --enable-threadsafe CFLAGS="-Os -DSQLITE_OMIT_TRIGGERS"
	cd $(SQLITE_PATH) && make

$(NVM_PATH):
	curl -o- https://raw.githubusercontent.com/creationix/$(NVM_NAME)/$(NVM_VERSION)/install.sh | bash
	source ~/.bashrc

$(REDIS_PATH):
	tar zxf $(REDIS_PKG)
	cd $(REDIS_PATH) && make

install:
	sudo mkdir -p $(CLOUDBREW_INSTALL_DIR)/mongodb
	sudo cp -Rf $(MONGODB_PATH)/* $(CLOUDBREW_INSTALL_DIR)/mongodb
	bash mongo_path.sh
	cd $(SQLITE_PATH) && sudo make install
	cp -f $(SQLITE_PATH)/sqlite3.o $(INSTALL_LIB_DIR)
	bash node_install.sh
	cd $(REDIS_PATH) && sudo make install
	sudo ldconfig

clean: clean-mongodb clean-sqlite clean-nvm clean-redis

wipeout: wipeout-mongodb wipeout-sqlite clean-nvm clean-redis

clean-mongodb:
	rm -Rf $(MONGODB_PATH)
	sudo rm -Rf $(CLOUDBREW_INSTALL_DIR)/mongodb

wipeout-mongodb:
	rm -Rf $(MONGODB_PATH)
	sudo rm -Rf $(CLOUDBREW_INSTALL_DIR)/mongodb
	sudo rm -Rf /data/db

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

clean-redis:
	cd $(REDIS_PATH) && make clean
	rm -Rf $(REDIS_PATH)
