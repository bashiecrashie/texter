CC=gcc
IN=main.c texterfuncs.c stringfuncs.c help.c
OUT=texter
ARGS_OUT=-o

all: build

build:

	$(CC) -g $(IN) $(ARGS_OUT) $(OUT)
