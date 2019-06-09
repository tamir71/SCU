/*  Tamir Enkhjargal
    COEN 11 Lab 9
    March 11, 2019

    Adding in recursive functionality */

/* Calling necessary libraries */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/* ---------------------------------------------------------------------- */

/*  Defining what a node contains: a name and size.
    Creating a pointer to the next structure (tail). */

typedef struct NODE {
    char name[20];
    int size;
    struct NODE *next;
} NODE;

/* ---------------------------------------------------------------------- */

/* Initializing the nodes head and tail */

NODE* head = NULL;
NODE* tail = NULL;

/* ---------------------------------------------------------------------- */

/* Initializing the function prototypes before main() with the parameters */

void insert(char *inputName, int inputSize);
void delete(int inputRemove);
void list();
void show(int inputSize);
int  check_duplicate(char *inputName);
void read_file(char *name);
void save_file(char *name);
void free_nodes(NODE *p);
void reverse_list(NODE *p);
void reverse_name(NODE *p);
void *auto_save();
void read_bin(char *name);

/* ---------------------------------------------------------------------- */

/* Initiliaze thread functions */

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* ---------------------------------------------------------------------- */
int main(int argc, char *argv[]) {
    int input, inputSize, inputRemove;
    char inputName[20];
    pthread_t thread;                                                       // Initialize thread
    pthread_mutex_init(&mutex, NULL);                                       // Initialize mutex init
    pthread_create(&thread, NULL, auto_save, (void *)argv[2]);              // Open the thread and keep it open
    input = 1;
    if (argc != 3) {                                                        /* Test if two files was given as an argument */
        printf("Some of the files are missing!\n");
        return 0;
    }
    read_file(argv[1]);                                                     /* Before running the main program read in lines */
    while (input != 0) {
        printf("Do you wish to (1) Insert, (2) Remove, (3) List, (4) Show Size, (5) Reverse List, (6) Reversed Names, (7) Read Binary, or (0) Quit?\n");   
	scanf("%d", &input);
        switch (input) {
            case 1 :                                                        /* Case 1: Check duplicates, then insert() */
                printf("What is the name?\n");
                scanf("%s", inputName);
                if (check_duplicate(inputName) == 0) {                      /* Checking if user is duplicate */
                    printf("How many people?\n");
                    scanf("%d", &inputSize);
                    insert(inputName, inputSize);                           /* If not duplicate, delete */
                }
                break;
            case 2 :                                                        /* Case 2: Remove a user */
                printf("How many people are you removing?\n");
                scanf("%d", &inputRemove);
                delete(inputRemove);
                break;
            case 3 :                                                        /* Case 3: List out all users and sizes */
                list();
                break;
            case 4 :                                                        /* Case 4: List all users smaller than inputSize */
                printf("How many people do you wish to see?\n");
                scanf("%d", &inputSize);
                show(inputSize);
                break;
            case 5 :                                                        /* Case 5: Reverse print the list */
                reverse_list(head);
                break;
            case 6 :                                                        /* Case 6: Reverse the names in the list */
                reverse_name(head);
                break;
            case 7 :                                                        /* Case 7: Read the Binary file */
               read_bin(argv[2]);
                break;
            case 0 :                                                        /* Case 0: Exiting the program will cause a save, then free */
                pthread_mutex_lock(&mutex);                                 /* Lock the file to save to binary */
                pthread_cancel(thread);                                     /* Then close the file */
                pthread_mutex_unlock(&mutex);                               /* Then unlock the file */
                save_file(argv[1]);                                         /* Save (overwrite) current list to data file */
                free_nodes(head);                                           /* Then free nodes in case of memory leaks */
                return 0;
            default :                                                       /* Default Case: Anything not 0 to 4 will not be taken as anything */
                printf("Please input a number [1..4] or 0 to save.\n");
                break;
        }
    }
}

/* ---------------------------------------------------------------------- */

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

/* Read File Function */

void read_file(char *fileName) {
	char readChar[20];                                                  
        int readInt;
        FILE *fptr;
        
        if ((fptr = fopen(fileName, "r")) == NULL) {                        /* Open the file and check if null */
            printf("Cannot open the file %s\n", fileName);
        }
        else {
            fseek(fptr, 37, SEEK_SET);                                      /* Skip 37 bytes, which covers the header */
            while(fscanf(fptr, "%s\t%d\n", readChar, &readInt) == 2) {      /* Keep looking through the file and read in a readChar and readInt */
                insert(readChar, readInt);                                  /* Insert found readChar and readInt into the list */
            }
        fclose(fptr);                                                       /* Close the file-read after traversing the entire file */
        }
}

/* ---------------------------------------------------------------------- */

/* Save File Function */

void save_file(char *fileName) {
    FILE *fptr;
    NODE *p;
    fptr = fopen(fileName, "w");                                            /* Open the file for writing (overwriting) */
    fprintf(fptr, "Name\tGroup Size\n--------------------\n");              /* Write the special header and format */
    p = head;
    while (p != NULL) {                                                     /* Starting at the head, traverse the list */
        fprintf(fptr, "%s\t%d\n", p->name, p->size);                        /* and write into the file everything that we find */
        p = p->next;
    }
    fclose(fptr);                                                           /* Close the file-write after traversing the list */
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

/* ---------------------------------------------------------------------- */

/* Autosave Function */

void *auto_save(void *arg) {
    FILE *fptr;
    char *fileName = (char *)arg;
    NODE *p;
    while(1) {
        sleep(15);
        printf("Saving to File.\n");
        pthread_mutex_lock(&mutex);                                         // Lock the file
        fptr = fopen(fileName, "wb");                                       // Then open it for writing
        p = head;
        while (p != NULL) {
            fwrite(p, sizeof(NODE), 1, fptr);                               // Write the entire list to the binary file
            p = p->next;
        }
        fclose(fptr);                                                       // Close the file
        printf("Finished Saving.\n");
        pthread_mutex_unlock(&mutex);                                       // Then unlock the file
    }
}

/* ---------------------------------------------------------------------- */

/* Read Binary Function */

void read_bin(char fileName[]) {
    FILE *fptr;
    NODE p;
    pthread_mutex_lock(&mutex);                                             // Lock the file
    fptr = fopen(fileName, "rb");                                           // Then open it for reading
    if (fptr == NULL) {
        pthread_mutex_unlock(&mutex);                                       // If the file is empty, then unlock and quit
        return;
    }
    while ((fread(&p, sizeof(NODE), 1, fptr)) > 0)                          // Keep reading the binary file until it hits the end
        printf("Name: %s and Number of Customers: %d\n", p.name, p.size);   // Print contents in the binary file
    fclose(fptr);                                                           // Close the file
    pthread_mutex_unlock(&mutex);                                           // Then unlock the file
    return;
}

/* ---------------------------------------------------------------------- */
