/*  Tamir Enkhjargal
    COEN 12 Lab 4
    May 19, 2019

    Creating Lab 4. Set implementation */

/* Calling necessary libraries */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <assert.h>
#include <stdbool.h>
#include "list.h"
#define alpha 20

/* ---------------------------------------------------------------------- */

/* Defining the private function search() */

static int search(SET *sp, void *elt, bool *found);

/* ---------------------------------------------------------------------- */

/* Creating the structure for our Set */

typedef struct set {
    LIST **data;
    int length;
    int count;
    int (*compare)();
    unsigned (*hash)();
} SET;

/* ---------------------------------------------------------------------- */

/* Create set function, O(n) runtime */

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    SET *sp = malloc(sizeof(SET));                  // Allocate memory for pointer
    assert(sp != NULL);                             // check if successful
    sp->length = maxElts/alpha;                     // set max elements
    sp->count = 0;                                  // start counter at 0
    sp->compare = compare;                          // call compare function
    sp->hash = hash;                                // call hash function
    sp->data = malloc(sizeof(LIST *)*sp->length);   // Allocate memory for data pointer
    assert(sp->data != NULL);                       // check if successful
    int i;
    for(i = 0; i < sp->length; i++) {               // loop through to make a list in
        sp->data[i] = createList(sp->compare);      // each data point
    }
    return sp;
}

/* ---------------------------------------------------------------------- */

/* Destroy set function, O(n) runtime */

void destroySet(SET *sp) {
    assert(sp != NULL);
    int i;
    for(i = 0; i < sp->length; i++) {               // loop through
        destroyList(sp->data[i]);                   // call destroyList()
    }
    free(sp->data);                                 // then free the data
    free(sp);                                       // free sp overall
    return;
}

/* ---------------------------------------------------------------------- */

/* Number of elements function, O(1) runtime */

int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->count;
}

/* ---------------------------------------------------------------------- */

/* Add element function, O(n) runtime  */

void addElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int index = search(sp, elt, &found);            // call search function
    if(found == false) {                            // if didn't find
        addLast(sp->data[index], elt);              // add to end of the list
        sp->count++;                                // increase counter
    }
    return;
}

/* ---------------------------------------------------------------------- */

/* Remove element function, O(n) runtime */

void removeElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int index = search(sp, elt, &found);            // call search function
    if(found == false) {                            // if didn't find
        return;                                     // do nothing (remove nothing)
    }
    else {
        removeItem(sp->data[index], elt);           // if found, remove it
        sp->count--;                                // decrement counter
        return;
    }
}

/* ---------------------------------------------------------------------- */

/* Find element function, O(n^2) runtime */

void *findElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int index = search(sp, elt, &found);            // call search function
    if(found == false) {                            // if not found
        return NULL;                                // return nothing
    }
    else {                                          // if found
        return findItem(sp->data[index], elt);      // return element
    }
}

/* ---------------------------------------------------------------------- */

/* Get elements function, O(n^3) runtime */

void *getElements(SET *sp) {
    assert(sp != NULL);
    void **temp;
    void **list;
    int i, j;
    int counter = 0;
    temp = malloc(sizeof(void *)*sp->count);
    assert(temp != NULL);
    for(i = 0; i < sp->length; i++) {                           // loop through everything
        list = malloc(sizeof(void *)*numItems(sp->data[i]));    // create a secondary list array
        list = getItems(sp->data[i]);                           // call get elements on everything
        for(j = 0; j < numItems(sp->data[i]); j++) {            // loop through list size
            temp[counter] = list[j];                            // copy elements in list
            counter++;                                          // to the temp array
        }
    }
    return temp;                                                // return our copied array
}

/* ---------------------------------------------------------------------- */

/* Private search function, O(n^2) runtime */

static int search(SET *sp, void *elt, bool *found) {
    assert(sp != NULL && elt != NULL);
    int index = (*sp->hash)(elt)%sp->length;                    // use hash function for max size
    if(findItem(sp->data[index], elt) != NULL) {                // call findItem
        *found = true;                                          // if found, return location
        return index;
    }
    else {
        *found = false;                                         // if not found, still return index
        return index;
    }
}

/* ---------------------------------------------------------------------- */

