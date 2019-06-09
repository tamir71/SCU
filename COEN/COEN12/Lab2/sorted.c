/*  Tamir Enkhjargal
    COEN 12 Lab 2
    April 17, 2019

    Creating Lab 2, sorted functionality. */

/* Calling necessary libraries */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <assert.h>
#include <stdbool.h>

/* ---------------------------------------------------------------------- */

/* Defining other necessary variables or function prototypes */

SET *createSet(int maxElts);
void addElement(SET *sp, char *elt);
int numElements(SET *sp);
void removeElement(SET *sp, char *elt);
char *findElement(SET *sp, char *elt);
char **getElements(SET *sp);
void destroySet(SET *sp);
static int search(SET *sp, char *elt, bool *found);

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
    bool found = false;
    int index, j; 
    index = search(sp, elt, &found);
    if(found == false) {
        for(j = sp->count; j > index; j--) {
            sp->data[j] = sp->data[j-1];
        }
        sp->data[index]=strdup(elt);
        sp->count++;
    }
}

/* ---------------------------------------------------------------------- */

/* Private Search Function */

static int search(SET *sp, char *elt, bool *found) {
    assert(sp != NULL);
    int lo = 0;
    int hi = sp->count - 1;
    int i, mid;
    while (lo <= hi) {
        mid = (hi+lo)/2;
        if(strcmp(elt, sp->data[mid]) < 0) {
            hi = mid-1;
        }
        else if(strcmp(elt, sp->data[mid]) > 0) {
            lo = mid+1;
        }
        else {
            *found = true;
            return mid;
        }
    }
    *found = false;
    return lo;
}

/* ---------------------------------------------------------------------- */

/* Remove Element Function */

void removeElement(SET *sp, char *elt) {
    assert(sp != NULL);
    int index;
    int j;
    bool found = false;
    index = search(sp, elt, &found);
    if(found == true) {
        free(sp->data[index]);
        for(j = index; j < sp->count; j++) {
            sp->data[j] = sp->data[j+1];
        }
        sp->count--;
    }
}

/* ---------------------------------------------------------------------- */

/* Find Element Function  */

char *findElement(SET *sp, char *elt) {
    assert(sp != NULL);
    bool found = false;
    search(sp, elt, &found);
    if(found == true) {
        return elt;
    }
    return NULL;
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
