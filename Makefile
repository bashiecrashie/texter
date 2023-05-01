CC=gcc
IN=main.c readfuncs.c convertfuncs.c writefuncs.c
OUT=texter
ARGS_OUT=-o

all: build

build:

	$(CC) $(IN) $(ARGS_OUT) $(OUT)
