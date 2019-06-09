/*  Tamir Enkhjargal
    COEN 12 Lab 4
    May 19, 2019

    Creating Lab 4. List implementation */

/* Calling necessary libraries */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include <assert.h>
#include <stdbool.h>

/* ---------------------------------------------------------------------- */

/* Creating the structure for our Node */

typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} NODE;

/* ---------------------------------------------------------------------- */

/* Creating the structure for our List */

typedef struct list {
    int count;
    NODE *head;
    int (*compare)();
} LIST;

/* ---------------------------------------------------------------------- */

/* Create List Function. O(1) runtime */

LIST *createList(int (*compare)()) {
    LIST *pList = malloc(sizeof(LIST));             // allocate space for list pointer
    assert(pList != NULL);                          // check if successful
    pList->head = malloc(sizeof(NODE));             // allocate space for head
    assert(pList->head != NULL);                    // check if successful
    pList->count = 0;
    pList->compare = compare;                       // call compare function
    pList->head->next = pList->head;                // point next to head (dummy)
    pList->head->prev = pList->head;                // point prev to head (dummy)
    return pList;
}

/* ---------------------------------------------------------------------- */

/* Destroy Set Function. O(n) runtime */

void destroyList(LIST *lp) {
    assert(lp != NULL);
    NODE *pDel;                                     // node we want to delete
    NODE *pPrev = lp->head->prev;                   // start at the tail of list
    while(pDel != lp->head) {                       // loops through everything (stops at dummy)
        pDel = pPrev;                               // begin at tail
        pPrev = pDel->prev;                         // then begin moving backwards
        free(pDel);                                 // delete pDel
    }
    free(lp);                                       // then delete list
}

/* ---------------------------------------------------------------------- */

/* Number of Items Function. O(1) runtime */

int numItems(LIST *lp) {
    assert(lp != NULL);
    return lp->count;
}

/* ---------------------------------------------------------------------- */

/* Add First Function. O(1) runtime */

void addFirst(LIST *lp, void *item) {
    assert(lp != NULL);
    NODE *pAdd = malloc(sizeof(NODE));              // allocate memory for node we want to delete
    assert(pAdd != NULL);
    pAdd->data = item;
    lp->head->next->prev = pAdd;                    // put pAdd before first element
    pAdd->next = lp->head->next;                    // pAdd->next is first element
    pAdd->prev = lp->head;                          // pAdd->prev is the head
    lp->head->next = pAdd;                          // first element->next is now pAdd
    lp->count++;                                    // increment counter
    return;
}

/* ---------------------------------------------------------------------- */

/* Add Last Function. O(1) runtime */

void addLast(LIST *lp, void *item) {
    assert(lp != NULL);
    NODE *pAdd = malloc(sizeof(NODE));              // allocate memory for node we want to delete
    assert(pAdd != NULL);
    pAdd->data = item;
    lp->head->prev->next = pAdd;                    // put pAdd after last element
    pAdd->next = lp->head;                          // pAdd->next is head
    pAdd->prev = lp->head->prev;                    // pAdd->prev is head->prev
    lp->head->prev = pAdd;                          // head->prev is now pAdd
    lp->count++;                                    // increment counter
    return;
}

/* ---------------------------------------------------------------------- */

/* Remove First Function. O(1) runtime */

void *removeFirst(LIST *lp) {
    assert(lp != NULL);
    NODE *pDel = lp->head->next;
    void *temp = pDel->data;
    lp->head->next = pDel->next;                    // point to first node
    pDel->next->prev = lp->head;                    // first->next->prev is now head
    free(pDel);                                     // delete pDel
    lp->count--;
    return temp;
}

/* ---------------------------------------------------------------------- */

/* Remove Last Function. O(1) runtime */

void *removeLast(LIST *lp) {
    assert(lp != NULL && lp->count > 0);
    NODE *pDel = lp->head->prev;
    void *temp = pDel->data;
    lp->head->prev = pDel->prev;
    pDel->prev->next = lp->head;
    free(pDel);
    lp->count--;
    return temp;
}

/* ---------------------------------------------------------------------- */

/* Get First Function. O(1) runtime */

void *getFirst(LIST *lp) {
    assert(lp != NULL && lp->count > 0);
    return lp->head->next->data;
}

/* ---------------------------------------------------------------------- */

/* Get Last Function. O(1) runtime */

void *getLast(LIST *lp) {
    assert(lp != NULL && lp->count > 0);
    return lp->head->prev->data;
}

/* ---------------------------------------------------------------------- */

/* Remove all items Function. O(n) runtime */

void removeItem(LIST *lp, void *item) {
    assert(lp != NULL);
    if(lp->count > 0) {
        NODE *pDel = lp->head->next;
        while(pDel != lp->head) {
            if((*lp->compare)(pDel->data, item) == 0) {
                pDel->prev->next = pDel->next;
                pDel->next->prev = pDel->prev;
                free(pDel);
                lp->count--;
                break;
            }
            else {
                pDel = pDel->next;
            }
        }
    }
    return;
}

/* ---------------------------------------------------------------------- */

/* Find Item Function. O(n) runtime */

void *findItem(LIST *lp, void *item) {
    assert(lp != NULL);
    if(lp->count > 0) {
        NODE *node = lp->head->next;
        while(node != lp->head) {
            if((*lp->compare)(node->data, item) == 0) {
                return node->data;
            }
            else {
                node = node->next;
            }
        }
    }
    return NULL;
}

/* ---------------------------------------------------------------------- */

/* Return all items Function. O(n) runtime */

void *getItems(LIST *lp) {
    assert(lp != NULL);
    int i = 0;
    void **temp;
    NODE *node = lp->head->next;
    temp = malloc(sizeof(void *)*lp->count);
    assert(temp != NULL);
    while(i < lp->count && node != lp->head) {
        temp[i] = node->data;
        node = node->next;
        i++;
    }
    return temp;
}

/* ---------------------------------------------------------------------- */
