INCS=-I src \
  -I /usr/include \
  -I /usr/local/include \

LIBSPATH= -L . -Wl,-R . '-Wl,-R$$ORIGIN' \
  -L /usr/lib \
  -L /usr/lib64 \
  -L /usr/local/lib

LIBS=-l ssl -l crypto

CC=cc
FLAGS=-Wall -fPIE -fPIC -pedantic

REL_CFLAGS=-O3
REL_LFLAGS=-s -shared
REL_LIB=libhurl.so

DBG_CFLAGS=-O1 -g -fno-omit-frame-pointer
DBG_LFLAGS=-shared
DBG_BIN=libhurl~dbg.so

# Compiler optim'n to be set manually :/
#CFLAGS=${REL_CFLAGS}
CFLAGS=${DBG_CFLAGS}

HDR_CONFIG=config.h
SRC=src/lib.c \
	src/tls.c \
  src/client.c \
  src/server.c
