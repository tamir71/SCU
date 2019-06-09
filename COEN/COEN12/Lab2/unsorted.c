/*  Tamir Enkhjargal
    COEN 12 Lab 2
    April 10, 2019

    Creating Lab 2, unsorted functionality. */

/* Calling necessary libraries */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <assert.h>

/* ---------------------------------------------------------------------- */

/* Defining other necessary variables or function prototypes */

SET *createSet(int maxElts);
void addElement(SET *sp, char *elt);
int numElements(SET *sp);
void removeElement(SET *sp, char *elt);
char *findElement(SET *sp, char *elt);
char **getElements(SET *sp);
void destroySet(SET *sp);
static int search(SET *sp, char *elt);

/* ---------------------------------------------------------------------- */

/* Creating the structure for our SET */

typedef struct set {
    char **data;
    int length;
    int count;
} SET;

/* ---------------------------------------------------------------------- */

/* Create Set Function */

SET *createSet(int maxElts) {
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(char*)*maxElts);
    assert(sp->data != NULL);
    return sp;
}

/* ---------------------------------------------------------------------- */

/* Destroy Set Function */

void destroySet(SET *sp) {
    assert(sp != NULL);
    int i;
    for (i = 0; i < sp->count; i++) {
        free(sp->data[i]);
    }
    free(sp->data);
    free(sp);
}

/* ---------------------------------------------------------------------- */

/* Number of Elements Function */

int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->count;
}

/* ---------------------------------------------------------------------- */

/* Add Element Function */

void addElement(SET *sp, char *elt) {
    assert(sp != NULL);
    if (search(sp, elt) == -1) {
        elt = strdup(elt);
        assert(elt != NULL);
        sp->data[sp->count] = elt;
        sp->count++;
    }
}

/* ---------------------------------------------------------------------- */

/* Private Search Function */

static int search(SET *sp, char *elt) {
    assert(sp != NULL);
    int i;
    for (i = 0; i < sp->count; i++) {
        if (strcmp(sp->data[i], elt) == 0) {
            return i;
        }
    }
    return -1;
}

/* ---------------------------------------------------------------------- */

/* Remove Element Function */

void removeElement(SET *sp, char *elt) {
    assert(sp != NULL);
    int index;
    index = search(sp, elt);
    if(index != -1) {
        free(sp->data[index]);
        sp->data[index] = sp->data[sp->count-1];
        sp->count--;
    }
}

/* ---------------------------------------------------------------------- */

/* Find Element Function  */

char *findElement(SET *sp, char *elt) {
    assert(sp != NULL);
    int index;
    index = search(sp, elt);
    if (index == -1) {
        return NULL;
    }
    else {
        return sp->data[index];
    }
}

/* ---------------------------------------------------------------------- */

/* Get Elements Function */

char** getElements(SET *sp) {
    assert(sp != NULL);
    int i;
    char **array;
    array = malloc(sizeof(char *)*(sp->count));
    for (i = 0; i < sp->count; i++) {
        strcpy(array[i],sp->data[i]);
    }
    return array;
}

/* ---------------------------------------------------------------------- */
