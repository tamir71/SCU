#include "global.h"

/* Read File Function */

void read_file(char *fileName, int key) {
    char readChar[20];
    int readInt;
    FILE *fptr;
    char buffer[100];
    if ((fptr = fopen(fileName, "r")) == NULL) {                        /* Open the file and check if null */
        printf("Cannot open the file %s\n", fileName);
    }
    else {
        // fseek(fptr, 37, SEEK_SET);                                      /* Skip 37 bytes, which covers the header */
        while(fgets(buffer, 100, fptr) != NULL) {       
            for (int i = 0; i < strlen(buffer); i++) {
                buffer[i]^=key;
            }
            sscanf(buffer, "%s %d", readChar, &readInt);
            insert(readChar, readInt);                                  /* Insert found readChar and readInt into the list */
        }
    }
    fclose(fptr);
}

/* ---------------------------------------------------------------------- */

/* Save File Function */

void save_file(char *fileName, int key) {
    FILE *fptr;
    NODE *p;
    char buffer[500];
    char tempChar[20];
    int tempInt;
    fptr = fopen(fileName, "w");                                            /* Open the file for writing (overwriting) */
    // fprintf(fptr, "Name\tGroup Size\n--------------------\n");              /* Write the special header and format */
    p = head;
    while (p != NULL) {                                                     /* Starting at the head, traverse the list */
        sprintf(buffer, "%s %d", p->name, p->size);                        /* and write into the file everything that we find */
        for (int i = 0; i < strlen(buffer); i++) {
            buffer[i]^=key;
        }
        fprintf(fptr, "%s\n", buffer);
        p = p->next;
    }
    fclose(fptr);                                                           /* Close the file-write after traversing the list */
}

/* ---------------------------------------------------------------------- */

/* Auto Save Function */

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
