/* # Name: Tamir Enkhjargal
 * # Date: 1/22/20 Wednesdays 2:15-5p
 * # Title: Lab3 - Part 6
 * # Description: Running 10 threads running the same function and seeing how they work concurrently
 *
 */

/**************************
*       COEN177: Threads  *
**************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10

// Define 10 threads
pthread_t threads[NTHREADS];
int main() {
    int i;
    for (i = 0; i < NTHREADS; i++)  
        // Create 10 threads to run go functionality
        pthread_create(&threads[i], NULL, go, &i);
    for (i = 0; i < NTHREADS; i++) {
	printf("Thread %d returned\n", i);
        // Actually run the 10 threads and wait for each one to finish
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}
void *go(void *arg) {
 printf("Hello from thread %d with iteration %d\n",  (int)pthread_self(), *(int *)arg);
 return 0;
}


