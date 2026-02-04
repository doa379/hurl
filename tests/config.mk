INCS=-I . \
  -I /usr/include \
  -I /usr/local/include \

LIBSPATH= -L . -Wl,-R . '-Wl,-R$$ORIGIN' \
	-L .. \
  -L /usr/lib \
  -L /usr/lib64 \
  -L /usr/local/lib

LIBS=-l hurl~dbg

CC=cc
FLAGS=-Wall -fPIE -fPIC -pedantic

DBG_CFLAGS=-O1 -g \
	-fno-omit-frame-pointer
DBG_LFLAGS=

CFLAGS=${DBG_CFLAGS}

SRC0=connect.c
BIN0=connect.bin
SRC1=client.c
BIN1=client.bin
SRC2=server.c
BIN2=server.bin
