#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user {
    char name[20];
    int size;
} user;
user userInfo[10];
int counter = 0, STRSIZE = 20;

void insert(char* inputName, int inputSize) {
    strcpy(userInfo[counter].name, inputName);
    userInfo[counter].name[STRSIZE-1] = '\0';
    userInfo[counter].size = inputSize;
    counter++;
}

int delete(int inputRemove) {
    user *p = userInfo;
    for (int i=0; i<counter; i++) {
        if (inputRemove >= p->size) {
            printf("Removing name %s with %d people\n", p->name, p->size);
            for (int j=i; j<counter-1; j++) {
                strcpy(p->name, (p+1)->name);
                p->size = (p+1)->size;
                p++;
            }
            counter--;
            return 1;
        }
        p++;
    }
    return 0;
}

void list() {
    int i = 0;
    user *p = userInfo;
    while (i<counter) {
        printf("Name: %s, Number of Customers: %d\n", p->name, p->size);
        i++;
        p++;
    }
}

void show(int inputSize) {
    int i = 0;
    user *p = userInfo;
    while (i<counter) {
        if (inputSize >= p->size) {
            printf("Name %s and %d people\n", p->name, p->size);
        }
    i++;
    p++;
    }
}

int check_duplicate(char* inputName) {
    int i = 0;
    user *p = userInfo;
    while (i<counter) {
        if (strcmp(p->name, inputName) == 0) {
            printf("This user is a duplicate\n");        
            return 0;
        }
    i++;
    p++;
    }
    return 1;
}

int main() {
    int input, inputSize, inputRemove;
    char inputName[20];

    while(input != '0') {
        printf("Do you wish to (1) Insert, (2) Remove, (3) List, (4) Show Size, or (0) Quit?\n");
        scanf("%d", &input);

        switch(input) {
            case 1 :
            if (counter>=10) {
                printf("There are too many people reserved\n");
                break;
            }
            else {
                printf("What is the name?\n");
                scanf("%s", inputName);
                printf("How many people?\n");
                scanf("%d", &inputSize);
                if (check_duplicate(inputName) == 1) {
                    insert(inputName, inputSize);
                    break;
                }
                else {
                    break;
                }
            }
            case 2 :
                printf("How many people are you removing?\n");
                scanf("%d", &inputRemove);
                delete(inputRemove);
                break;
            case 3 :
                list();
                break;
            case 4 :
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
