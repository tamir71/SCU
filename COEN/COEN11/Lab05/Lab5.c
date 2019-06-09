/* Tamir Enkhjargal
   COEN 11 Lab 5
   February 7, 2019

   Using nodes and creating linked lists for the first time */

/* Calling necessary libraries*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------------------------------------------------------------  */

/* Defining what a node contains: a name and size.
   Creating a pointer to the next structure (tail). */

typedef struct NODE {
    char name[20];
    int size;
    struct NODE *next;
} NODE;

/* --------------------------------------------------------------------  */

/* Initializing the nodes head and tail */

NODE* head = NULL;
NODE* tail = NULL;

/* ---------------------------------------------------------------------  */

/* Initializing the function prototypes before main() with the parameters */ 

void insert(char* inputName, int inputSize);
void delete(int inputRemove);
void list();
void show(int inputSize);
int check_duplicate(char* inputName);

/* ---------------------------------------------------------------------  */

/* Main function with cases 1-4, and 0 for the several functions */

int main() {
    int input, inputSize, inputRemove;
    char inputName[20];

    while(input != '0') {
        printf("Do you wish to (1) Insert, (2) Remove, (3) List, (4) Show Size, or (0) Quit?\n");
        scanf("%d", &input);

        switch(input) {
            case 1 :                                            /* Case 1: Insert */
            printf("What is the name?\n");
            scanf("%s", inputName);
            printf("How many people?\n");
            scanf("%d", &inputSize);
            if (check_duplicate(inputName) == 1) {              /* Checking for duplicates */
                insert(inputName, inputSize);                   /* If not a duplicate, then insert */
            }
            break;
            case 2 :                                            /* Case 2: Remove */
                printf("How many people are you removing?\n");
                scanf("%d", &inputRemove);
                delete(inputRemove);
                break;
            case 3 :                                            /* Case 3: List */
                list();
                break;
            case 4 :                                            /* Case 4: List based off a number */
                printf("How many people do you wish to see?\n");
                scanf("%d", &inputSize);
                show(inputSize);
                break;
            case 0 :
                return 0;
                break;
        }
    }
}

/* ---------------------------------------------------------------------  */

/* Insert function */

void insert(char* inputName, int inputSize) {
    NODE *p;
    if ((p = (NODE *)malloc(sizeof(NODE))) == NULL) {           /* Checking for allocated memory */
        printf("Memory could not be allocated\n");
        return;        
    }
    strcpy(p->name, inputName);                                 /* Uploading node p with our user-input information */
    p->size = inputSize;                                        /* Such as user name and user group size */
    if (head == NULL) {                                         /* Checking if the list is empty */
        head = tail = p;
        tail->next = NULL;
    }
    else {                                                      /* Else includes inserting if not empty (since we always insert to tail) */
        tail->next = p;
        tail = p;
    }
}

/* ---------------------------------------------------------------------  */

/* Delete function */

void delete(int inputRemove) {
    NODE *p, *q;
    if ((p = (NODE *)malloc(sizeof(NODE))) == NULL) {           /* Checking for allocated memory */
        printf("There is no memory to delete\n");
        return;
    }
    p = q = head;                                               /* Begin traversing the list from the head */
    while (p != NULL) {                                         /* While loop to traverse the list */
        if (inputRemove >= p->size) {                           /* If-statement to check if we found a node we want to delete */
            printf("Removing name %s with %d people\n", p->name, p->size);
            break;
        }
        q = p;
        p = p->next;                                            /* Traversing *magic* */
    }
    if (p == NULL || p->size != inputRemove) {                  /* Check to see if we found a node we want */
        printf("The number %d was not found\n", inputRemove);   /* If not, printing that there was not a group to delete */
        return;
    }
    if (p == head) {                                            /* Check to see if we're deleting head */
        head = p->next;                                         /* Fix the head (new) */
    }
    else {                                                      /* Else, deleting middle or tail */
        q->next = p->next;                                      /* Fix the list */
    }
    free(p);                                                    /* Delete the node we found while traversing */
    return;
}

/* ---------------------------------------------------------------------  */

/* List function */

void list() {
    NODE *p;
    p = head;
    while (p != NULL) {                                         /* While loop to traverse the list */              
        printf("Name: %s, Number of Customers: %d\n", p->name, p->size);      
        p = p->next;                                            /* Traversing *magic* */
    }
}

/* ---------------------------------------------------------------------  */

/* Show function */

void show(int inputSize) {
    NODE *p;
    p = head;
    while (p != NULL) {                                         /* While loop to traverse the list */
        if (inputSize >= p->size) {                             /* Same as list function, with a small requirement */
            printf("Name: %s, Number of Customer: %d\n", p->name, p->size);
        }
        p = p->next;                                            /* Traversing *magic* */
    }
}

/* ---------------------------------------------------------------------  */

/* Check duplicate function */

int check_duplicate(char* inputName) {
    NODE *p;
    p = head;
    while (p != NULL) {                                         /* While loop to traverse the list */
        if (strcmp(p->name, inputName) == 0) {                  /* Check if the user's name is the same as one in the list */
            printf("This user is a duplicate\n");               /* If we find someone, state that this is a duplicate */
            return 0;
        }
        p = p->next;                                            /* Traversing *magic* */
    }
    return 1;                                                   /* If we didn't find a duplicate, return 1 */
}

/* ---------------------------------------------------------------------  */
