#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define baselength 1000

typedef struct data {
    int id;
    int age;
} DATA;

typedef struct list {
    int length;
    int count;
    DATA *data;
} LIST;

LIST *createDataSet();
void destroyDataSet(LIST *list);
int searchAge(LIST *list, int age);
int searchId(LIST *list, int id);
void insert(LIST *list, int age, int id, int index);
void deleteElt(LIST *list, int index);
int maxAgeGap(int max, int min);
