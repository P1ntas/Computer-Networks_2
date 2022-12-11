# Makefile for RCOM - Project 2

COMPILER_TYPE = gnu
CC = gcc

PROG = main
SRCS = clientTCP.c parsing.c

CFLAGS= -Wall -g

$(PROG): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(PROG)

all: $(BIN)

clean:
	rm -f $(PROG)