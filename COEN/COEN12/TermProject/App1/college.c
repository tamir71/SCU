/*  Tamir Enkhjargal
    COEN 12 Lab 5
    June 2, 2019
    
    */

/* Calling necessary libraries */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"
#include <assert.h>
#include <time.h>
#define maxStudents 3000

/* ---------------------------------------------------------------------- */

/* Main Function */

int main(void) {
    LIST *list = createDataSet();                           // Create list  
    assert(list != NULL);
    srand(time(NULL));

    /* Part 1. Create data set. Generate 1000 student records with random age and increasing IDs */
    int i, rAge, rId, rNext, min, max;
    min = max = rAge = (rand() % 13)+18;                    // Randomly make age from 18-30    
    rId = (rand()%2)+1;                                     // Randomly make id from 1-2
    insert(list, rAge, rId, 0);                             // Insert first student
    printf("Age %d Id %d\n", rAge, rId);
    for(i = 1; i < 1000; i++) {                             // Then for rest of students (1000 of them)
        rAge = (rand() % 13)+18;                            // Make age from 18-30
        rNext = list->data[i-1].id+((rand()%2)+1);          // The next id is previous id + 1 or 2
        if(rAge > max) {                                    // Use max for maximum from 1000 students
            max = rAge;
        }
        if(rAge < min) {                                    // Use min for minimum from 1000 students
            min = rAge;
        }
        insert(list, rAge, rNext, i);                       // Insert each student
        printf("Age %d Id %d\n", rAge, rNext);    
    }
 
    /* Part 2. Randomly generate a student age/ID pair and check if it exists */
    int j, randAge;
    randAge = (rand() % 13)+18;                             // Make age from 18-30
    deleteElt(list, randAge);                               // Delete that random age

    /* Part 3. Call maxAgeGap and destroy data set */
    int gap = maxAgeGap(max, min);                          // Declare age gap
    printf("Age gap: %d\n", gap);
    destroyDataSet(list);                                   // Destroy the list
}

/* ---------------------------------------------------------------------- */
