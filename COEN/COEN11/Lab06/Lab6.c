/* Tamir Enkhjargal
   COEN 11 Lab 6
   February 18, 2019

   Using nodes and an array of linked lists */

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

/* Initializing four head and tail nodes, used for waitlist ranges */
/* head1: Range 1-2; head2: Range 3-4; head3: Range 5-6; head4: Range 7+ */

typedef struct LIST {
    NODE *head;
    NODE *tail;
} LIST;

LIST array[4];

/* ---------------------------------------------------------------------  */

/* Initializing the function prototypes before main() with the parameters */ 

void insert(char* inputName, int inputSize);
void delete(int inputRemove);
void list();
void show(int inputSize);
int check_duplicate(char* inputName);
void quit();

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
            case 0 :                                            /* Case 0: Delete all nodes then exit */
                quit();
                return 0;
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
    if (inputSize == 1 || inputSize == 2) {                     /* If the group is of size 1-2 */
        if (array[0].head == NULL) {                            /* Checking if the first list is empty */
            array[0].head = array[0].tail = p;                  /* Change first head and tail */
            array[0].tail->next = NULL;                         /* Change first tail to be null */
        }
        else {                                                  /* Else includes inserting if not empty (since we always insert to tail) */
            array[0].tail->next = p;
            array[0].tail = p;
        }
    }
    if (inputSize == 3 || inputSize == 4) {                     /* If the group is of size 3-4 */
        if (array[1].head == NULL) {                            /* Checking if the list is empty */
            array[1].head = array[1].tail = p;
            array[1].tail->next = NULL;
        }
        else {                                                  /* Else includes inserting if not empty (since we always insert to tail) */
            array[1].tail->next = p;
            array[1].tail = p;
        }
    }
    if (inputSize == 5 || inputSize == 6) {                     /* If the group is of size 5-6 */
        if (array[2].head == NULL) {                            /* Checking if the list is empty */
            array[2].head = array[2].tail = p;
            array[2].tail->next = NULL;
        }
        else {                                                  /* Else includes inserting if not empty (since we always insert to tail) */
            array[2].tail->next = p;
            array[2].tail = p;
        }
    }
    if (inputSize > 6) {                                        /* If the group is larger than size 6 (7 or more people) */
        if (array[3].head == NULL) {                            /* Checking if the list is empty */
            array[3].head = array[3].tail = p;
            array[3].tail->next = NULL;
        }
        else {                                                  /* Else includes inserting if not empty (since we always insert to tail) */
            array[3].tail->next = p;
            array[3].tail = p;
        }
    }
}

/* ---------------------------------------------------------------------  */

/* Delete function */

void delete(int inputRemove) {
    NODE *p, *q;
    int flag = 0;
    int i;
    if ((p = (NODE *)malloc(sizeof(NODE))) == NULL) {               /* Checking for allocated memory */
        printf("There is no memory to delete\n");
        return;
    }
    for (i = 0; i < 4; i++) {                                       /* Create a for loop to traverse throug the array of lists */
        p = q = array[i].head;                                      /* Begin traversing the list from the head */
        while (p != NULL) {                                         /* While loop to traverse the list */
            if (inputRemove >= p->size) {                           /* If-statement to check if we found a node we want to delete */
                printf("Removing name %s with %d people\n", p->name, p->size);
                flag++;                                             /* Increment flag here to check if we found a node to delete */
                break;
            }
            q = p;
            p = p->next;                                            /* Traversing *magic* */
        }
        if (flag) {                                                 /* If we found a node by the end of the while loop, exit out of the for loop */
            break;
        }
    }
    if (!flag) {                                                    /* If we did not find a node, then the print and exit out of delete() */
        printf("The number %d was not found\n", inputRemove);
        return;
    }
    if (p == array[i].head) {                                       /* Check to see if we're deleting head */
        array[i].head = p->next;                                    /* Fix the head (new) */
    }
    else {                                                          /* Else, deleting middle or tail */
        q->next = p->next;                                          /* Fix the list */
    }
    free(p);                                                        /* Delete the node we found while traversing */
    return;
}

/* ---------------------------------------------------------------------  */

/* List function */

void list() {
    NODE *p;
    for (int i = 0; i < 4; i++) {                                   /* For loop to traverse through the array of lists */
        p = array[i].head;                                          /* Begin traversing at head of list index i */
        while (p != NULL) {                                         /* While loop to traverse the list */
            printf("Name: %s, Number of Customers: %d\n", p->name, p->size);      
            p = p->next;                                            /* Traversing *magic* */
        }
    }
}

/* ---------------------------------------------------------------------  */

/* Show function */

void show(int inputSize) {
    NODE *p;
    for (int i = 0; i < 4; i++) {                                   /* For loop to traverse through the array of lists */
        p = array[i].head;
        while (p != NULL) {                                         /* While loop to traverse the list */
            if (inputSize >= p->size) {
                printf("Name: %s, Number of Customers: %d\n", p->name, p->size);      
            }
            p = p->next;                                            /* Traversing *magic* */
        }
    }
}

/* ---------------------------------------------------------------------  */

/* Check duplicate function */

int check_duplicate(char* inputName) {                              /* Begin the check_duplicate from each head, beginning with head1 */
    NODE *p;                                                        /* and continue to check for duplicates throughout each list */
    for (int i = 0; i < 4; i++) {
        p = array[i].head;
        while (p != NULL) {                                         /* While loop to traverse the list */
            if (strcmp(p->name, inputName) == 0) {
                printf("This user is a duplicate\n");
                return 0;
            }
            p = p->next;                                            /* Traversing *magic* */
        }
    }
    return 1;
}

/* ---------------------------------------------------------------------  */

/* Quit function is called to delete all nodes in the lists before exiting the program */

void quit() {
    NODE *p, *q;
    for (int i = 0; i < 4; i++) {                                   /* For loop to traverse through the array of lists */
        p = q = array[i].head;      
        while (p != NULL) {                                         /* While loop to traverse the list */
            q = q->next;                                            /* Using q as a temp and always be after p */
            free(p);                                                /* After freeing p, we can't access p->next, so we use q, which is already at node p->next */
            p = q;                                                  /* Move up p */
        }
    }
}

/* ---------------------------------------------------------------------  */
