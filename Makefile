CC=gcc
CFLAGS=-Wall -g -pedantic
PROG=fork
SRC=fork.c

default:
	${CC} ${CFLAGS} -o ${PROG} ${SRC}

fork:

clean:
	rm -f fork core*
