#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include "global.h"

NODE *head = NULL;
NODE *tail = NULL;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) {
    int key, input, inputSize, inputRemove;
    char inputName[20];
    pthread_t thread;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thread, NULL, auto_save, (void *)argv[2]);
    input = 1;
    if (argc != 4) {
        printf("Some of the files are missing!\n");
        return 0;
    }
    key = atoi(argv[3]);
    read_file(argv[1], key);
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
                save_file(argv[1], key);                                         /* Save (overwrite) current list to data file */
                free_nodes(head);                                           /* Then free nodes in case of memory leaks */
                return 0;
            default :                                                       /* Default Case: Anything not 0 to 4 will not be taken as anything */
                printf("Please input a number [1..4] or 0 to save.\n");
                break;
        }
    }
}
