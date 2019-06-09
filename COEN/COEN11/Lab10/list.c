#include "global.h"

/* Insert Function */

void insert(char *inputName, int inputSize) {
    pthread_mutex_lock(&mutex);
    FILE *fptr;
    NODE *p;
    if ((p = (NODE *)malloc(sizeof(NODE))) == NULL) {                       /* Check if there is enough memory to allocate for a test node */
        printf("Memory could not be allocated.\n");
        return;
    }
    strcpy(p->name, inputName);                                             /* Copy the name and size from user input to the variables */
    p->size = inputSize;
    if (head == NULL) {                                                     /* Check if list is empty */
        head = tail = p;
        tail->next = NULL;
    }
    else {                                                                  /* Otherwise, input to the end of the list */
        tail->next = p;
        tail = p;
    }
    pthread_mutex_unlock(&mutex);
}

/* ---------------------------------------------------------------------- */

/* Delete Function */

void delete (int inputRemove) {
    NODE *p, *q;
    int flag;
    p = q = head;                                                           /* Start both temp nodes at head */
    while (p != NULL) {                                                     /* Begin a while loop to traverse the list */
        if (inputRemove >= p->size) {                                       /* Find the first node that is equal-to or less-than inputRemove */
            printf("Removing name %s with %d people\n", p->name, p->size);
            flag = 1;                                                       /* Setting flag to 1 here notes we found a node to delete */
            if (p == head) {                                                /* Fixing list if found node is at head */
                head = p->next;
            }
            else {                                                          /* Fixing list if found node is at anywhere else */
                q->next = p->next;
            }
            free(p);                                                        /* Free memory / delete found node */
            return;
        }
        q = p;                                                              /* These two lines are used to */
        p = p->next;                                                        /* traverse the list and keep a current and next */
    }
    if (flag != 1) {                                                        /* If we didn't find a node to delete */
        printf("There was nothing to remove.\n");                           /* Print that we found nothing */
    }
}

/* ---------------------------------------------------------------------- */

/* List Function */

void list() {
    NODE *p;
    p = head;                                                               /* Start at head */
    while (p != NULL) {                                                     /* and keep looping */
        printf("Name: %s, Number of Customers: %d\n", p->name, p->size);    /* and print everything */
        fflush(stdout);
        p = p->next;
    }
}

/* ---------------------------------------------------------------------- */

/* Show Function */

void show(int inputSize) {                                                  /* Exact same functionality as list() with a caveat */
    NODE *p;
    p = head;
    while (p != NULL) {
        if (inputSize >= p->size) {
            printf("Name: %s, Number of Customers: %d\n", p->name, p->size);
        }
        p = p->next;
    }
}

/* ---------------------------------------------------------------------- */

/* Check Duplicate Function */

int check_duplicate(char *inputName) {
    NODE *p;
    int flag = 0;
    p = head;
    while (p != NULL) {                                                     /* While looping through the list */
        if (strcmp(p->name, inputName) == 0) {                              /* Compare each name found with what the user wants to put in */
            printf("This user is a duplicate.\n");                          /* If they are the same, found duplicate */
            flag = 1;                                                       /* Noting we found a duplicate */
            break;
        }
        else {
            p = p->next;                                                    /* If we didn't find anything yet, continue traversing the list */
        }
    }
    return flag;                                                            /* Return 0 (didn't find a duplicate) or 1 (found a duplicate) */
}

/* ---------------------------------------------------------------------- */

/* Free Nodes Function */

void free_nodes(NODE *p) {
    if (p == NULL)
        return;
    printf("Name %s and Number of Customers %d Deleted.\n", p->name, p->size);
    free(p);
    free_nodes(p->next);
}

/* ---------------------------------------------------------------------- */

/* Reverse List Function */

void reverse_list(NODE *p) {
    if (p == NULL) {                                                        /* Check if the current node is empty */
        return;
    }
    reverse_list(p->next);                                                  /* Loop through the list */
    printf("Name: %s, Number of Customers: %d\n", p->name, p->size);        /* Due to the recursive function, it waits for the last node to print */
}

/* ---------------------------------------------------------------------- */

/* Reverse Strings Function */

void reverse_name(NODE *p) {
    int i = 0;
    if (p == NULL)
        return;
    for (i = (strlen(p->name)-1); i >= 0; i--)                              // Start at end of name, then move backwords
        printf("%c", p->name[i]);                                       // Print each character one by one
    printf("\n");                                                   // Then print a new line between each name
    reverse_name(p->next);                                                  /* Move to new name after finishing name and new line */
}
