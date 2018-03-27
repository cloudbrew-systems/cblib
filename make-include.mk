# Common definitions
INSTALL_INCLUDE_DIR = $(ROOT)/include
INSTALL_LIB_DIR = $(ROOT)/lib
INSTALL_BIN_DIR = $(ROOT)/bin
CLOUDBREW_INSTALL_DIR = /usr/local/cloudbrew
CLOUDBREW_HASH_DBNAME = cbHash.db
TEMP_UPLOAD = /tmp/upload

CC = gcc -g

ifeq (,$(ARCH))
        ARCH := $(shell uname -m)
endif
ifeq (x86_64, $(ARCH))
        ARCH_ARG := -m64
        SYS_LIB_DIR := /usr/lib64
else
        ARCH_ARG := -m32
        SYS_LIB_DIR := /usr/lib
endif

CFLAGS += $(ARCH_ARG)
LDFLAGS += $(ARCH_ARG)

