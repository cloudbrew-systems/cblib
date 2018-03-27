ROOT := ..

include $(ROOT)/make-include.mk

APP = cloudbrew
APP_UPLOAD = cbUpload
APP_DOWNLOAD = cbDownload

STR_SETUP = setup

CB_LIB = -lCloudBrew
CB_OBJS = cloudbrew.o
CB_UPLOAD_OBJS = cbUpload.o
CB_DOWNLOAD_OBJS = cbDownload.o

CJSON_LIB = -lcJSON
INCLUDES = -I$(INSTALL_INCLUDE_DIR)

all: $(APP) $(APP_UPLOAD) $(APP_DOWNLOAD) install

$(APP): $(CB_OBJS)
	$(CC) -o $@ $(CFLAGS) -pthread $(CB_OBJS) $(CB_LIB) -ldl $(CJSON_LIB) -lm

$(APP_UPLOAD): $(CB_UPLOAD_OBJS)
	$(CC) -o $@ $(CFLAGS) -pthread $(CB_UPLOAD_OBJS) $(CB_LIB) -ldl $(CJSON_LIB) -lm

$(APP_DOWNLOAD): $(CB_DOWNLOAD_OBJS)
	$(CC) -o $@ $(CFLAGS) -pthread $(CB_DOWNLOAD_OBJS) $(CB_LIB) -ldl $(CJSON_LIB) -lm

.c.o: 
	$(CC) $(CFLAGS) -Wall -fPIC $(INCLUDES) -c $<

clean:
	rm -f $(APP) $(APP_UPLOAD) $(APP_DOWNLOAD) *.o

install:
	sudo install -m 755 $(APP) $(APP_UPLOAD) $(APP_DOWNLOAD) $(INSTALL_BIN_DIR)

