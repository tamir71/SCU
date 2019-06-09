/*  Tamir Enkhjargal
    COEN 12 Lab 1
    April 3, 2019

    Reading and counting the number of words from a textfile */

/* Calling necessary libraries */ 

#include <stdio.h>
#include <stdlib.h>

/* ---------------------------------------------------------------------- */

/* Defining other necessary variables or functions */

#define MAX_WORD_LENGTH 30

/* ---------------------------------------------------------------------- */

int main(int argc, char *argv[]) {
    FILE *fptr;
    char str[MAX_WORD_LENGTH];
    int counter = 0;
    if (argc != 2) {                                                        /* Test if file name was given as an argument */
        printf("The name of the file is missing!\n");
        return 0;
    }
    if ((fptr = fopen(argv[1], "r")) == NULL) {
        printf("Cannot open the file %s\n", argv[1]);                       /* Check if file is able to be opened */
    }
    else {
        while(fscanf(fptr, "%s", str) == 1) {                               // While reading character by character
            counter++;                                                      // Increase the counter by one per read
        }
    }
    printf("%d\n", counter);
    fclose(fptr);                                                           /* Close file after done */
}

/* ---------------------------------------------------------------------- */
