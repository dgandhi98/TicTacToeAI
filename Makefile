#
# File: Makefile
# Creator: George Ferguson
# Created: Mon Nov 28 13:52:02 2016
# Time-stamp: <Mon Nov 28 14:31:03 EST 2016 ferguson>
#
CC = gcc
SRCS = Agent.c GameState.c main.c
HDRS = Agent.h GameState.h
OBJS = $(SRCS:.c=.o)
EXE = tictac

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	-rm $(OBJS) $(EXE)
