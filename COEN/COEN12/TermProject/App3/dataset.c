/*  Tamir Enkhjargal
    COEN 12 Term Project
    June 7, 2019

    Application 3 implementation */

/* Calling necessary libraries */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dataset.h"
#include <time.h>
#define baselength 1000

/* ---------------------------------------------------------------------- */

/* createDataSet function. */

LIST *createDataSet() {
    LIST *list = malloc(sizeof(LIST));                      // Create list
    assert(list != NULL);
    list->count = 0;
    list->length = baselength;                              // We don't know maximum student amount
    list->data = malloc(sizeof(DATA)*list->length);         // Create array of data structure as big
    assert(list->data != NULL);
    return list;
}

/* ---------------------------------------------------------------------- */

/* destroyDataSet function. */

void destroyDataSet(LIST *list) {                           // Destroy the data set
    assert(list != NULL);
    free(list->data);
    free(list);
    return;
}

/* ---------------------------------------------------------------------- */

/* searchAge function. */

int searchAge(LIST *list, int age) {
    assert(list != NULL);
    int i;
    printf("Searching for students with age %d\n", age);
    for(i = 0; i < list->length; i++) {                     // Loop through the entire array
        if(list->data[i].age == age) {                      // If age matches then return it
            return age;
        }
    }
    printf("No students with that age found.\n");
    return 0;
}

/* ---------------------------------------------------------------------- */

/* searchId function */ 

int searchId(LIST *list, int id) {
    assert(list != NULL);
    int i;
    printf("Searching for students with id %d\n", id);
    for(i = 0; i < list->length; i++) {                     // Loop through the entire array
        if(list->data[i].id == id) {                        // If id matches then return it
            return id;
        }
    }
    printf("No students with that id found.\n");
    return 0;
}

/* ---------------------------------------------------------------------- */

/* insert student function. */

void insert(LIST *list, int age, int id, int index) {
    assert(list != NULL);
    if(list->count == list->length) {                       // If our count = length, double array length
        list->data = realloc(list->data, sizeof(list->data)*2);
        list->length *= 2;                                  // double memory size and length
    }
    list->data[index].age = age;                            // Just insert to end of array
    list->data[index].id = id;                              // insert to end of array
    list->count++;                                          // Increment count
    return;
}

/* ---------------------------------------------------------------------- */

/* delete student function. */

void deleteElt(LIST *list, int id) {
    assert(list != NULL);
    int i;
    for(i = 0; i < list->length; i++) {                     // Loop through entire array
        if(list->data[i].id == id) {                        // If we find id we want to delete, delete it
            printf("Student with Age %d and ID %d deleted.\n", list->data[i].age, list->data[i]);
            list->data[i].age = '\0';                       // We can't set to NULL, but set to '\0'
            list->data[i].id = '\0';
            list->count--;                                  // Decrement count
        }
    }
    return;
}

/* ---------------------------------------------------------------------- */

/* maxAgeGap function. */

int maxAgeGap(int max, int min) {
    return max-min;
}

/* ---------------------------------------------------------------------- */
