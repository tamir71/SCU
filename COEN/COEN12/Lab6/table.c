/*  
 *  table.c by Darren C. Atkinson
 *  Adapted by Tamir Enkhjargal
 *  COEN 12 Lab 6, Spring 2019
 */


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <stdbool.h>
# include "set.h"

# define EMPTY   0
# define FILLED  1
# define DELETED 2

struct set {
    int count;                  /* number of elements in array */
    int length;                 /* length of allocated array   */
    void **data;                /* array of allocated elements */
    char *flags;                /* state of each slot in array */
    int (*compare)();		/* comparison function         */
    unsigned (*hash)();		/* hash function               */
};

/*
 * Function:    search
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: Return the location of ELT in the set pointed to by SP.  If
 *		the element is present, then *FOUND is true.  If not
 *		present, then *FOUND is false.  The element is first hashed
 *		to its correct location.  Linear probing is used to examine
 *		subsequent locations.
 */

static int search(SET *sp, void *elt, bool *found)
{
    int available, i, locn, start;


    available = -1;
    start = (*sp->hash)(elt) % sp->length;

    for (i = 0; i < sp->length; i ++) {
        locn = (start + i) % sp->length;

        if (sp->flags[locn] == EMPTY) {
            *found = false;
            return available != -1 ? available : locn;

        } else if (sp->flags[locn] == DELETED) {
            if (available == -1)
		available = locn;

        } else if ((*sp->compare)(sp->data[locn], elt) == 0) {
            *found = true;
            return locn;
        }
    }

    *found = false;
    return available;
}


/*
 * Function:    createSet
 *
 * Complexity:  O(m)
 *
 * Description: Return a pointer to a new set with a maximum capacity of
 *		MAXELTS.
 */

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
    int i;
    SET *sp;


    assert(compare != NULL && hash != NULL);

    sp = malloc(sizeof(SET));
    assert(sp != NULL);

    sp->data = malloc(sizeof(char *) * maxElts);
    assert(sp->data != NULL);

    sp->flags = malloc(sizeof(char) * maxElts);
    assert(sp->flags != NULL);

    sp->compare = compare;
    sp->hash = hash;
    sp->length = maxElts;
    sp->count = 0;

    for (i = 0; i < maxElts; i ++)
        sp->flags[i] = EMPTY;

    return sp;
}


/*
 * Function:    destroySet
 *
 * Complexity:  O(m)
 *
 * Description: Deallocate memory associated with the set pointed to by SP.
 *		The elements themselves are not deallocated since we did not
 *		allocate them in the first place.  That's the rule: if you
 *		didn't allocate it, then you don't deallocate it.
 */

void destroySet(SET *sp)
{
    assert(sp != NULL);

    free(sp->flags);
    free(sp->data);
    free(sp);
}


/*
 * Function:    numElements
 *
 * Complexity:  O(1)
 *
 * Description: Return the number of elements in the set pointed to by SP.
 */

int numElements(SET *sp)
{
    assert(sp != NULL);
    return sp->count;
}


/*
 * Function:    addElement
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: Add ELT to the set pointed to by SP.
 */

void addElement(SET *sp, void *elt)
{
    int locn;
    bool found;


    assert(sp != NULL && elt != NULL);
    locn = search(sp, elt, &found);

    if (!found) {
	assert(sp->count < sp->length);

	sp->data[locn] = elt;
	sp->flags[locn] = FILLED;
	sp->count ++;
    }
}


/*
 * Function:    removeElement
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: Remove ELT from the set pointed to by SP.  A element is
 *		deleted by changing the state of its slot.
 */

void removeElement(SET *sp, void *elt)
{
    int locn;
    bool found;


    assert(sp != NULL && elt != NULL);
    locn = search(sp, elt, &found);

    if (found) {
	sp->flags[locn] = DELETED;
	sp->count --;
    }
}


/*
 * Function:    findElement
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: If ELT is present in the set pointed to by SP then return
 *		it, otherwise return NULL.
 */

void *findElement(SET *sp, void *elt)
{
    int locn;
    bool found;


    assert(sp != NULL && elt != NULL);

    locn = search(sp, elt, &found);
    return found ? sp->data[locn] : NULL;
}

/* Implementing the getElements function, which calls my quickSort() function. 
 *
 * Runs in O(n^3), as getElements runs with O(n) and calls quickSort(), an O(n^2) operation
 *
 * */

void *getElements(SET *sp) {
    assert(sp != NULL);
    void **array = malloc(sizeof(void *)*sp->count);                // Create secondary array with only FILLED objects
    int i, j;
    j = 0;
    for(i = 0; i < sp->length; i++) {                               // Loop through entire array
        if(sp->flags[i] == FILLED) {                                // If it is filled with an entity
            array[j] = sp->data[i];                                 // Copy that to our FILLED array
            j++;
        }
    }
    quickSort(array, 0, sp->count-1, sp->compare);                  // Call quickSort() with the new array
    return array;
}

/* Implementing the quickSort algorithm.
 *
 * Runs in O(n^2) worst-case situation. It calls the partition (O(n) runtime) function with new pivots
 * and works recursively.
 *
 */

void quickSort(void **data, int low, int high, int(*compare)()) {
    int pivot;
    if(low < high) {                                                // When low = high or low > high, we are done
        pivot = partition(data, low, high, compare);                // Partition the portion of data indicated by pivot.
        quickSort(data, low, pivot-1, compare);                     // Then quickSort everything below pivot
        quickSort(data, pivot+1, high, compare);                    // and everything above pivot
    }
    return;
}

/* Running quickSort algorithm with a separate partition function.
 *
 * O(n) runtime per call of partition.
 *
 */

int partition(void **data, int low, int high, int(*compare)()) {
    void *pivot = data[high];                                       // Make the pivot at the start
    int i, j;
    j = low;
    for(i = low; i <= high-1; i++) {                                // Within each partition, we begin our swapping
        if((*compare)(data[i], pivot) <= 0) {                       // This functionality is similar to a selection sort
            swap(data[i], data[j]);                                 // Calls our secondary swap function
            j++;
        }
    }
    swap(data[j], data[high]);                                      // Then at the end of the partition swap the pivot and last element
    return j;
}

/* A small swap function that makes the partition code look nicer.
 *
 * O(1) runtime.
 *
 */

void swap(int *y, int *z) {
    int temp;
    temp = *y;
    *y = *z;
    *z = temp;
}
