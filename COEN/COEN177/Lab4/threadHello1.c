/**************************************************************
//
// # Name: Tamir Enkhjargal
// # Date: Friday 2:15-5p
// # Title: Lab 4 - Thread Hello 1
// # Description: Create threads with join() waiting
//
*	threadHello.c - simple multi-threaded program.            *
*   compile with: >gcc -lp threadHello.c -o threadHello       *                                              *
**************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 20

void *go(void *);
pthread_t threads[NTHREADS];

int main() {
    static int i;
    // Create NTHREADS threads and each one calls go(&i)
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, &i);

    // pthread_join each thread so we will wait for threads to finish to call "Main thread done"
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i],NULL);
	    printf("Thread %d returned \n", i);
    }
    printf("Main thread done.\n");
}

void *go(void *arg) {
    printf("Hello from thread %d with thread ID %d \n", *(int *)arg, (int)pthread_self());
    return (NULL);
}

