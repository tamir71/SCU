CC	= gcc
CFLAGS	= -g -Wall
LDFLAGS	=
PROGS	= unique

all:	$(PROGS)

clean:;	$(RM) $(PROGS) *.o core

unique:	unique.o table.o
	$(CC) -o $@ $(LDFLAGS) unique.o table.o
