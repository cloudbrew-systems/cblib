
ROOT := ..

include $(ROOT)/make-include.mk

CB_LIB = libCloudBrew.so
OBJS = MemMgr.o accountHandling.o fileHandling.o brewEngine.o cbLog.o dbSqlite.o
INCLUDES = -I$(INSTALL_INCLUDE_DIR)

all: $(CB_LIB) install

$(CB_LIB): $(OBJS)
	$(CC) -fPIC -shared $(LDFLAGS) -o $@ $^

.c.o: 
	$(CC) $(CFLAGS) -Wall -fPIC $(INCLUDES) -c $<

install:
	install -m 644 *.h $(INSTALL_INCLUDE_DIR)
	sudo install -m 755 $(CB_LIB) $(SYS_LIB_DIR)
	sudo ldconfig

clean:
	rm -f *.o *.so

