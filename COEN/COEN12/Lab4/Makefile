CC	= gcc
CFLAGS	= -g -Wall
PROGS	= maze radix unique parity

all:	$(PROGS)

clean:;	$(RM) $(PROGS) *.o core

maze:	maze.o list.o
	$(CC) -o maze maze.o list.o -lcurses

radix:	radix.o list.o
	$(CC) -o radix radix.o list.o -lm

unique:	unique.o set.o list.o
	$(CC) -o unique unique.o set.o list.o

parity:	parity.o set.o list.o
	$(CC) -o parity parity.o set.o list.o
