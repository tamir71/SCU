/*
 * File:        counts.c
 *
 * Copyright:	2017, Darren C. Atkinson
 *
 * Description: This file contains the main function for testing a set
 *              abstract data type for strings.
 *
 *              The program takes one file as a command line argument and
 *              counts the number of times each word appears in the file.
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "set.h"

struct entry {
    char *word;
    int count;
};


/* This is sufficient for the test cases in /scratch/coen12. */

# define MAX_SIZE 18000


/*
 * Function:    strhash
 *
 * Description: Return a hash value for a string S.
 */

static unsigned strhash(char *s)
{
    unsigned hash = 0;


    while (*s != '\0')
        hash = 31 * hash + *s ++;

    return hash;
}


/*
 * Function:	hashEntry
 *
 * Description:	Return a hash value for an entry based on its word.
 */

static unsigned hashEntry(struct entry *ep)
{
    return strhash(ep->word);
}


/*
 * Function:	compareEntries
 *
 * Description:	Compare two entries as in strcmp().
 */

static int compareEntries(struct entry *ep1, struct entry *ep2)
{
    return strcmp(ep1->word, ep2->word);
}


/*
 * Function:    main
 *
 * Description: Driver function for the test application.
 */

int main(int argc, char *argv[])
{
    FILE *fp;
    char buffer[BUFSIZ];
    struct entry e, *ep, **entries;
    SET *counts;
    int i;


    /* Check usage and open the file. */

    if (argc != 2) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: cannot open %s\n", argv[0], argv[1]);
        exit(EXIT_FAILURE);
    }


    /* Increment the count on each word read. */

    counts = createSet(MAX_SIZE, compareEntries, hashEntry);

    while (fscanf(fp, "%s", buffer) == 1) {
	e.word = buffer;
	ep = findElement(counts, &e);

	if (ep == NULL) {
	    ep = malloc(sizeof(struct entry));
	    assert(ep != NULL);

	    ep->word = strdup(buffer);
	    assert(ep->word != NULL);

	    ep->count = 1;
	    addElement(counts, ep);

	} else
	    ep->count ++;
    }


    /* Print out the counts for each word. */

    entries = getElements(counts);

    for (i = 0; i < numElements(counts); i ++) {
	printf("%s: %d\n", entries[i]->word, entries[i]->count);
	free(entries[i]->word);
	free(entries[i]);
    }

    free(entries);

    destroySet(counts);
    exit(EXIT_SUCCESS);
}
