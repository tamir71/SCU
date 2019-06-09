#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char name[100][100];
int size[100];
int counter = 0, STRSIZE = 100;

int insert(char* inputName, int inputSize) {
    strncpy(name[counter], inputName, STRSIZE);
    name[counter][STRSIZE] = '\0';
    size[counter] = inputSize;
}

int removeName(int inputSize) {
    for (int i=0; i<STRSIZE; i++) {
        if (inputSize == size[i]) {
            printf("Removing name %s with %d people\n", name[i], size[i]);

            for (int j=i; j<STRSIZE; j++) {
                strcpy(name[j], name[j+1]);
                size[j] = size[j+1];
            }
        }
    }
}

int list() {
int i = -1;
while(size[++i]) {
printf("Name: %s, Number of Customers: %d\n", name[i], size[i]);
}
}

int main() {
int input, inputSize;
char inputName[100];

while(input != 4) {
printf("Do you wish to (1) Insert, (2) Remove, (3) List, or (4) Quit?\n");
scanf("%d", &input);

switch(input) {
case 1 :
printf("What is the name?\n");
scanf("%s", inputName);
printf("How many people?\n");
scanf("%d", &inputSize);
insert(inputName, inputSize);
counter++;
break;
case 2 :
printf("How many people are you removing?\n");
scanf("%d", &inputSize);
removeName(inputSize);
counter--;
break;
            case 3 :
                list();
                                break;
                                            case 4 :
                                                return 0;
                                                                break;
                                                                        }
}
}
