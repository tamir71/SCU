/*  Tamir Enkhjargal
    COEN 12 Term Proejct
    June 7, 2019 */
    

/* Calling necessary libraries */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"
#include <assert.h>
#include <time.h>

/* ---------------------------------------------------------------------- */

/* Main Function */

int main(void) {
    LIST *list = createDataSet();                       //  Create our list
    assert(list != NULL);
    srand(time(NULL));

    /* Part 1. Create data set. Generate 1000 student records with random age and increasing IDs */
    int i, rAge, rId, rNext, min, max;
    min = max = rAge = (rand() % 13)+18;                // Randomly make age from 18-30
    rId = (rand()%2)+1;                                 // Randomly make id from 1-2
    insert(list, rAge, rId, 0);                         // Insert the very first student
    printf("Age %d Id %d\n", rAge, rId);
    for(i = 1; i < 1000; i++) {                         // Then make 999 more students
        rAge = (rand() % 13)+18;
        rNext = list->data[i-1].id+((rand()%2)+1);      // Make id from previous + random gen 1 or 2
        if(rAge > max) {
            max = rAge;                                 // Also check for max for later
        }
        if(rAge < min) {
            min = rAge;                                 // Also check for min for later
        }
        insert(list, rAge, rNext, i);                   // Insert from new age and id
        printf("Age %d Id %d\n", rAge, rNext);    
    }
 
    /* Part 2. Randomly generate a student ID pair and check if it exists */
    int j, randId, randAge;
    randId = (rand() % 2000)+1;                         // To look for a random student, make id 1-2000
    randAge = (rand() % 13)+18;                         // To look for a random student, make age 18-30
    int x = searchId(list, randId);                     // Search for id = randId
    int y = searchAge(list, randAge);                   // Search for age = randAge
    if(x == randId && y == randAge) {                   // If both, then we can remove that student
        printf("ID %d and Age %d\n", randId, randAge);
    }
    deleteElt(list, randId);                            // Delete that student

    /* Part 3. Call maxAgeGap and destroy data set */
    int gap = maxAgeGap(max, min);                      // From previous, input maxAgeGap with max and min
    printf("Age gap: %d\n", gap);
    destroyDataSet(list);                               // Destroy data
}
/* ---------------------------------------------------------------------- */
