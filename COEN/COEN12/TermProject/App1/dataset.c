/*  Tamir Enkhjargal
    COEN 12 Term Project
    June 7, 2019

    Application 1 implementation */

/* Calling necessary libraries */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dataset.h"
#define maxStudents 3000

/* ---------------------------------------------------------------------- */

/* createDataSet function. */

LIST *createDataSet() {
    LIST *list = malloc(sizeof(LIST));                      // Create the list
    assert(list != NULL);
    list->count = 0;
    list->length = maxStudents;                             // We know how big it needs to be (3000)
    assert(list->data != NULL);
    return list;
}

/* ---------------------------------------------------------------------- */

/* destroyDataSet function. */

void destroyDataSet(LIST *list) {
    assert(list != NULL);
    free(list);                                             // We just need to delete list directly
    return;
}

/* ---------------------------------------------------------------------- */

/* searchAge function. */

int searchAge(LIST *list, int age) {
    assert(list != NULL);
    int i;
    printf("Searching for students with age %d\n", age);    
    for(i = 0; i < list->length; i++) {                     // Loop through the entire array 
        if(list->data[i].age == age) {                      // If the age matches, return it
            return age;
        }
    }
    printf("No students with that age found.\n");
    return 0;
}

/* ---------------------------------------------------------------------- */

/* insert student function. */

void insert(LIST *list, int age, int id, int index) {
    assert(list != NULL);
    list->data[index].age = age;                            // When we insert, insert to end
    list->data[index].id = id;                              // and set age and id
    list->count++;
    return;
}

/* ---------------------------------------------------------------------- */

/* delete student function. */

void deleteElt(LIST *list, int age) {
    assert(list != NULL);
    int i;
    for(i = 0; i < list->length; i++) {                     // Loop through entire array
        if(list->data[i].age == age) {                      // If we find the age in the array
            printf("Student with Age %d and ID %d deleted.\n", list->data[i].age, list->data[i]);
            list->data[i].age = '\0';                       // 'Delete' that element
            list->data[i].id = '\0';                        // 'Delete' that element
            list->count--;
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
