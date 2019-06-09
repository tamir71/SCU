#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define maxStudents 3000

typedef struct data {
    int id;
    int age;
} DATA;

typedef struct list {
    int length;
    int count;
    DATA data[maxStudents];
} LIST;

LIST *createDataSet();
void destroyDataSet(LIST *list);
int searchAge(LIST *list, int age);
void insert(LIST *list, int age, int id, int index);
void deleteElt(LIST *list, int index);
int maxAgeGap(int max, int min);
