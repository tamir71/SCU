/*
 * Function:	pqueue.h
 *
 * Copyright:	2017, Darren C. Atkinson
 *
 * Description:	This file contains the public function and type
 *		declarations for a priority queue abstract data type for
 *		generic pointer types.
 */

# ifndef PQUEUE_H
# define PQUEUE_H

typedef struct pqueue PQ;

PQ *createQueue(int (*compare)());

void destroyQueue(PQ *pq);

int numEntries(PQ *pq);

void addEntry(PQ *pq, void *entry);

void *removeEntry(PQ *pq);

# endif /* PQUEUE_H */
