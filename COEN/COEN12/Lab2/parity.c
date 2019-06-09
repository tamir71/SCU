/*
 * File:        parity.c
 *
 * Copyright:	2017, Darren C. Atkinson
 *
 * Description: This file contains the main function for testing a set
 *              abstract data type for strings.  It is deliberately stupid.
 *
 *              The program takes a single file as a command line argument.
 *              A set is used to maintain a collection of words that occur
 *              an odd number of times.  The counts of total words and
 *              words appearing an odd number of times are printed.
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
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
    char buffer[BUFSIZ];
    SET *odd;
    int words;


    /* Check usage and open the file. */

    if (argc != 2) {
        fprintf(stderr, "usage: %s file1\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: cannot open %s\n", argv[0], argv[1]);
        exit(EXIT_FAILURE);
    }


    /* Insert or delete words to compute their parity. */

    words = 0;
    odd = createSet(MAX_SIZE);

    while (fscanf(fp, "%s", buffer) == 1) {
        words ++;

        if (findElement(odd, buffer))
            removeElement(odd, buffer);
        else
            addElement(odd, buffer);
    }

    printf("%d total words\n", words);
    printf("%d words occur an odd number of times\n", numElements(odd));
    fclose(fp);

    destroySet(odd);
    exit(EXIT_SUCCESS);
}
