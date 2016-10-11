ROOT := ..

include $(ROOT)/make-include.mk

APP = cloudbrew
APP_UPLOAD = cbUpload
APP_DOWNLOAD = cbDownload
APP_CBSQLITE = cbSqlite

STR_SETUP = setup

CB_LIB = -lCloudBrew
CB_OBJS = cloudbrew.o
CB_UPLOAD_OBJS = cbUpload.o
CB_DOWNLOAD_OBJS = cbDownload.o
CB_SQLITE_OBJS = cbSqlite.o

CJSON_LIB = -lcJSON
INCLUDES = -I$(INSTALL_INCLUDE_DIR)

all: $(APP) $(APP_UPLOAD) $(APP_DOWNLOAD) $(APP_CBSQLITE) install

$(APP): $(CB_OBJS)
	$(CC) -o $@ $(CFLAGS) -pthread $(INSTALL_LIB_DIR)/sqlite3.o $(CB_OBJS) $(CB_LIB) -ldl $(CJSON_LIB) -lm

$(APP_UPLOAD): $(CB_UPLOAD_OBJS)
	$(CC) -o $@ $(CFLAGS) -pthread $(INSTALL_LIB_DIR)/sqlite3.o $(CB_UPLOAD_OBJS) $(CB_LIB) -ldl $(CJSON_LIB) -lm

$(APP_DOWNLOAD): $(CB_DOWNLOAD_OBJS)
	$(CC) -o $@ $(CFLAGS) -pthread $(INSTALL_LIB_DIR)/sqlite3.o $(CB_DOWNLOAD_OBJS) $(CB_LIB) -ldl $(CJSON_LIB) -lm

$(APP_CBSQLITE): $(CB_SQLITE_OBJS)
	$(CC) -o $@ $(CFLAGS) -pthread $(INSTALL_LIB_DIR)/sqlite3.o $(CB_SQLITE_OBJS) $(CB_LIB) -ldl $(CJSON_LIB) -lm

.c.o: 
	$(CC) $(CFLAGS) -Wall -fPIC $(INCLUDES) -c $<

clean:
	rm -f $(APP) $(APP_UPLOAD) $(APP_DOWNLOAD) $(APP_CBSQLITE) *.o

install:
	sudo install -m 755 $(APP) $(APP_UPLOAD) $(APP_DOWNLOAD) $(APP_CBSQLITE) $(INSTALL_BIN_DIR)
	cd $(INSTALL_BIN_DIR) && ./$(APP_CBSQLITE) $(STR_SETUP)


