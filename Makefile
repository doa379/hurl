include config.mk

OBJ=$(SRC:.c=.o)
FLAG=Release

all: release

.c.o:
	@echo CC	$@
	@${CC} ${FLAGS} ${CFLAGS} ${INCS} $< -c -o $@

${OBJ}: ${HDR_CONFIG} config.mk

release: ${OBJ}
	@echo Linking ${FLAG}...
	@${CC} ${FLAGS} ${LIBSPATH} ${LIBS} ${REL_LFLAGS} $? \
    -o ${REL_LIB}
	@echo ${REL_LIB}

debug: FLAG=Debug CFLAGS=${DBG_CFLAGS}
debug: ${OBJ}
	@echo Linking ${FLAG}...
	@${CC} ${FLAGS} ${LIBSPATH} ${LIBS} ${DBG_LFLAGS} $? \
    -o ${DBG_LIB}
	@echo ${DBG_LIB}

clean:
	@echo Cleaning...
	rm -rf ${OBJ} ${REL_LIB} ${DBG_LIB}

.SUFFIXES: .c .o
.PHONY: all clean
