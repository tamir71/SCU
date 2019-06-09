/*
 * File:        unique.c
 *
 * Copyright:	2017, Darren C. Atkinson
 *
 * Description: This file contains the main function for testing a set
 *              abstract data type for strings.
 *
 *              The program takes two files as command line arguments, the
 *              second of which is optional.  All words in the first file
 *              are inserted into the set and the counts of total words and
 *              total words in the set are printed.  If the second file is
 *              given then all words in the second file are deleted from
 *              the set and the count printed.
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "set.h"


/* This is sufficient for the test cases in /scratch/coen12. */

# define MAX_SIZE 18000


/*
 * Function:    main
 *
 * Description: Driver function for the test application.
 */

int main(int argc, char *argv[])
{
    FILE *fp;
    char buffer[BUFSIZ], **elts;
    SET *unique;
    int i, words;
    bool lflag = false;


    /* Check usage and open the first file. */

    if (argc > 1 && strcmp(argv[1], "-l") == 0) {
	lflag = true;
	argc --;

	for (i = 1; i < argc; i ++)
	    argv[i] = argv[i + 1];
    }

    if (argc == 1 || argc > 3) {
        fprintf(stderr, "usage: %s [-l] file1 [file2]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: cannot open %s\n", argv[0], argv[1]);
        exit(EXIT_FAILURE);
    }


    /* Insert all words into the set. */

    words = 0;
    unique = createSet(MAX_SIZE);

    while (fscanf(fp, "%s", buffer) == 1) {
        words ++;
        addElement(unique, buffer);
    }

    fclose(fp);

    if (!lflag) {
	printf("%d total words\n", words);
	printf("%d distinct words\n", numElements(unique));
    }


    /* Try to open the second file. */

    if (argc == 3) {
        if ((fp = fopen(argv[2], "r")) == NULL) {
            fprintf(stderr, "%s: cannot open %s\n", argv[0], argv[2]);
            exit(EXIT_FAILURE);
        }


        /* Delete all words in the second file. */

        while (fscanf(fp, "%s", buffer) == 1)
            removeElement(unique, buffer);

	fclose(fp);

	if (!lflag)
	    printf("%d remaining words\n", numElements(unique));
    }


    /* Print the list of words if desired. */

    if (lflag) {
	elts = getElements(unique);

	for (i = 0; i < numElements(unique); i ++)
	    printf("%s\n", elts[i]);

	free(elts);
    }

    destroySet(unique);
    exit(EXIT_SUCCESS);
}
