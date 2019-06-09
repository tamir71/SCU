#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

typedef struct NODE {
    char name[20];
    int size;
    struct NODE *next;
} NODE;

extern NODE *head;
extern NODE *tail;

void insert();
void delete();
void list();
void show();
int check_duplicate();
void read_file();
void save_file();
void free_nodes();
void reverse_list();
void reverse_name();
void *auto_save();
void read_bin();

extern pthread_mutex_t mutex;
