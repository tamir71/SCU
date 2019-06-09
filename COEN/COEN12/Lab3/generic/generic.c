/*  Tamir Enkhjargal
    COEN 12 Lab 3
    May 5, 2019

    Creating Lab 3, for generic pointer types. */

/* Calling necessary libraries */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <assert.h>
#include <stdbool.h>

/* ---------------------------------------------------------------------- */

/* Defining other necessary variables or function prototypes */

SET *createSet(int maxElts, int (*copmare)(), unsigned (*hash)());
void destroySet(SET *sp);
int numElements(SET *sp);
void addElement(SET *sp, void *elt);
void removeElement(SET *sp, void *elt);
void *findElement(SET *sp, void *elt);
void *getElements(SET *sp);
static int search(SET *sp, void *elt, bool *found);

#define EMPTY 0
#define DELETED 1
#define FILLED 2

/* ---------------------------------------------------------------------- */

/* Creating the structure for our SET */

struct set {
    char *flag;
    void **data;
    int length;
    int count;
    int (*compare)();
    unsigned (*hash)();
};

/* ---------------------------------------------------------------------- */

/* Create Set Function */

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    int i;
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->compare = compare;
    sp->hash = hash;
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(void*)*maxElts);
    sp->flag = malloc(sizeof(char)*maxElts);
    assert(sp->data != NULL && sp->flag != NULL);
    for(i = 0; i < sp->length; i++) {
        sp->flag[i] = EMPTY;
    }
    return sp;
}

/* ---------------------------------------------------------------------- */

/* Destroy Set Function */

void destroySet(SET *sp) {
    assert(sp != NULL);
    free(sp->data);
    free(sp->flag);
    free(sp);
    return;
}

/* ---------------------------------------------------------------------- */

/* Number of Elements Function */

int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->count;
}

/* ---------------------------------------------------------------------- */

/* Add Element Function */

void addElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL && (sp->count < sp->length));
    bool found = false;
    int index, i; 
    index = search(sp, elt, &found);
    if(found == false) {
        sp->data[index] = elt;
        assert(sp->data[index] != NULL);
        sp->flag[index] = FILLED;
        sp->count++;
    }
    if(found == true) {
        return;
    }
}

/* ---------------------------------------------------------------------- */

/* Remove Element Function */

void removeElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int index;
    index = search(sp, elt, &found);
    if(found == true) {
        assert(sp->data[index] != NULL);
        sp->flag[index] = DELETED;
        sp->count--;
        return;
    }
}

/* ---------------------------------------------------------------------- */

/* Find Element Function  */

void *findElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int index;
    index = search(sp, elt, &found);
    if(found == true) {
        return sp->data[index];
    }
    return NULL;
}

/* ---------------------------------------------------------------------- */

/* Get Elements Function */

void *getElements(SET *sp) {
    assert(sp != NULL);
    void **elts;
    elts = malloc(sizeof(void*)*(sp->count));
    int i;
    int j = 0;
    for(i = 0; i < sp->length; i++) {
        if(sp->flag[i] == FILLED) {
            elts[j] = sp->data[i];
            j++;    
        }
    }
    return elts;
}

/* ---------------------------------------------------------------------- */

/* Private Search Function */

static int search(SET *sp, void *elt, bool *found) {
    assert(sp != NULL && elt != NULL);
    int index, i, flag, temp;
    flag = 0;
    unsigned hash;
    hash = (*sp->hash)(elt)%(sp->length);
    *found = false;
    for(i = 0; i < sp->length; i++) {
        index = (hash+i) % (sp->length);
        if(sp->flag[index] == FILLED) {
            if((*sp->compare)(sp->data[index], elt) == 0) {
                *found = true;
                return index;
            }
        }
        if(sp->flag[index] == DELETED) {
            if(flag == 0) {
                temp = index;
                flag = 1;
            }
        }
        if(sp->flag[index] == EMPTY) {
            if(flag == 1) {
                return temp;
            }
            return index;
        }
    }
    return -1;
}

/* ---------------------------------------------------------------------- */
