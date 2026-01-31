INCS=-I . \
  -I /usr/include \
  -I /usr/local/include \

LIBSPATH= -L . -Wl,-R . '-Wl,-R$$ORIGIN' \
  -L /usr/lib \
  -L /usr/lib64 \
  -L /usr/local/lib

LIBS=

CC=cc
FLAGS=-Wall -fPIE -fPIC -pedantic

DBG_CFLAGS=-O1 -g -fno-omit-frame-pointer
DBG_LFLAGS=

CFLAGS=${DBG_CFLAGS}

SRC0=../src/lib.c ../src/client.c client.c
BIN0=client.bin
SRC1=
BIN1=
