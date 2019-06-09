/*
 * File:	radix.c
 *
 * Copyright:	2017, Darren C. Atkinson
 *
 * Description:	Read a sequence of non-negative integers from the
 *		standard input and sort then using radix sort.  Each
 *		integer in the list is dropped into a bucket by its least
 *		significant digit.  After all integers are placed in
 *		buckets, the buckets are copied back into the list and we
 *		repeat the process, but with the next most significant
 *		digit.  After all digits have been processed, the list is
 *		sorted!  Since the buckets need to preserve the order of
 *		insertion, we need to implement a queue.  A list provides
 *		this functionality for us.  The algorithm can be found at
 *		wikipedia.org/wiki/Radix_sort.
 */

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include "list.h"

# define r 10


/*
 * Function:	main
 *
 * Description:	Driver function for the radix application.
 */

int main(void)
{
    int i, x, niter, div, max, *p;
    LIST *a, *lists[r];


    max = 0;
    a = createList(NULL);

    for (i = 0; i < r; i ++)
	lists[i] = createList(NULL);


    /* Read in the numbers and record the maximum as we go along. */

    while (scanf("%d", &x) == 1) {
	if (x >= 0) {
	    p = malloc(sizeof(int));
	    assert(p != NULL);
	    *p = x;

	    addLast(a, p);

	    if (x > max)
		max = x;

	} else {
	    fprintf(stderr, "Sorry, only non-negative values allowed.\n");
	    exit(EXIT_FAILURE);
	}
    }

    div = 1;
    niter = ceil(log(max + 1) / log(r));

    while (niter --) {


	/* Move the numbers from the list to the buckets. */

	while (numItems(a) > 0) {
	    p = removeFirst(a);
	    addLast(lists[*p / div % r], p);
	}


	/* Move the numbers from the buckets back into the list. */

	for (i = 0; i < r; i ++)
	    while (numItems(lists[i]) > 0)
		addLast(a, removeFirst(lists[i]));

	div = div * r;
    }


    /* Print out the numbers. */

    while (numItems(a) > 0) {
	p = removeFirst(a);
	printf("%d\n", *p);
	free(p);
    }

    exit(EXIT_SUCCESS);
}
