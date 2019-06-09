CC	= gcc
CFLAGS	= -g -Wall
PROGS	= sort huffman

all:		$(PROGS)

clean:;		$(RM) $(PROGS) *.o core

sort:		sort.o pqueue.o
		$(CC) -o sort sort.o pqueue.o

huffman:	huffman.o pqueue.o pack.o
		$(CC) -o huffman huffman.o pqueue.o pack.o
