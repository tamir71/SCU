CC	= gcc
CFLAGS	= -g -Wall
LDFLAGS	=
PROGS	= unique parity counts

all:	$(PROGS)

clean:;	$(RM) $(PROGS) *.o core

unique:	unique.o table.o
	$(CC) -o $@ $(LDFLAGS) unique.o table.o

parity:	parity.o table.o
	$(CC) -o $@ $(LDFLAGS) parity.o table.o

counts:	counts.o table.o
	$(CC) -o $@ $(LDFLAGS) counts.o table.o
