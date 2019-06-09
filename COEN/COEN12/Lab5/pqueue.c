/*  Tamir Enkhjargal
    COEN 12 Lab 5
    June 2, 2019

    Creating Lab 5. Priority queue implementation */

/* Calling necessary libraries */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.h"
#include <assert.h>

/* ---------------------------------------------------------------------- */

/* Creating the structure for our Queue */

typedef struct pqueue {
    void **data;
    int length;
    int count;
    int (*compare)();
} PQ;

/* ---------------------------------------------------------------------- */

/* Create queue function. O(1) runtime. */

PQ *createQueue(int (*compare)()) {
    PQ *pq = malloc(sizeof(PQ));                    // Create a base pointer
    assert(pq != NULL);                             // Check if successful
    pq->count = 0;                                  // Start counter at 0
    pq->length = 10;                                // Length should be 10 at first
    pq->data = malloc(sizeof(void *)*pq->length);   // Create data array as long as length
    assert(pq->data != NULL);                       // Check if successful
    pq->compare = compare;
    return pq;
}

/* ---------------------------------------------------------------------- */

/* Destroy queue function. O(n) runtime */

void destroyQueue(PQ *pq) {                         
    assert(pq != NULL);                             // Check if pointer exists
    int i;
    for(i = 0; i < pq->length; i++) {               // Iterate through entire array
        free(pq->data[i]);                          // Free data per i in array
    }
    free(pq->data);                                 // Free data array
    free(pq);                                       // Free queue struct
    return;
}

/* ---------------------------------------------------------------------- */

/* Number of entries function. O(1) runtime. */

int numEntries(PQ *pq) {
    assert(pq != NULL);                             // Check if pointer exists
    return pq->count;                               // Return how many entries from counter
}

/* ---------------------------------------------------------------------- */

/* Add entry function. O(logn) runtime. */

void addEntry(PQ *pq, void *entry) {
    assert(pq != NULL);                             // Check if pointer exists
    if(pq->count == pq->length) {                   // If we reach the length cap
        pq->length *= 2;                            // Double the array length and reallocated memory
        pq->data = realloc(pq->data, sizeof(void *)*pq->length);
        assert(pq->data != NULL);
    }
    pq->data[pq->count] = entry;                    // Copy data we want to input
    int child = pq->count;                          // Set node at child
    int parent = (pq->count-1)/2;                   // Find parent of child
    while((*pq->compare)(pq->data[child],pq->data[parent]) == -1) { // Compare the value of the child to the parent
        void *temp = pq->data[parent];              // We want to save the parent's data when we swap
        pq->data[parent] = pq->data[child];         // Child's data -> Parent's data
        pq->data[child] = temp;                     // Child's data -> Parent's data (from temp)
        child = parent;                             // Then swap the indices
        parent = (parent-1)/2;                      // Keep doing this until we hit root
    }
    pq->count++;                                    // Increment the counter after adding
    return;
}

/* ---------------------------------------------------------------------- */

/* Remove entry function. O(logn) runtime. */

void *removeEntry(PQ *pq) {
    assert(pq != NULL);                             // Check if pointer exists
    PQ *pDel = malloc(sizeof(PQ));                  // Make pDel our struct to delete
    assert(pDel != NULL);                           // Check if successful
    pDel = pq->data[0];                             // We will always want to delete first
    pq->data[0] = pq->data[pq->count-1];            // Go to the last node in the tree
    int index = 0;                                  // Start at the root
    while((index*2)+1 <= pq->count-1) {             // While the index is not at/past the last node 
        int child = (index*2+1);
        if((index*2+2) <= pq->count-1) {            // If the right child exists
            if((*pq->compare)(pq->data[index*2+2], pq->data[index*2+1]) < 0) {  // If the right child is smaller than left child
                child = index*2+2;                  // Then use right child as main
            }
        }
        if((*pq->compare)(pq->data[index], pq->data[child]) < 0) { // If the parent is smaller than the children, break
            break;
        }
        else {                                      // Else (left child is smaller than parent)
            void *temp = pq->data[index];           // Save parent data into temp
            pq->data[index] = pq->data[child];      // Child's data -> Parent's data
            pq->data[child] = temp;                 // Parent's data -> Child's data
        }
        index = child;                              // Then continue down the tree
    }
    pq->count--;                                    // Decrement counter after deleting
    return pDel;                                    // Return the root node
}

/* ---------------------------------------------------------------------- */
