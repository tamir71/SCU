//
// # Name: Tamir Enkhjargal
// # Date: 2/7/20, Fridays 2:15
// # Title: Lab5 - Producer Consumer using Semaphores
//

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>

#define NTHREADS 10
#define n 10
pthread_t threads[NTHREADS];

int in, out;
sem_t  *mutex; // = 1;
sem_t  *empty; // = n;
sem_t  *full;  // = 0;
int Buffer[n];

// Just a printing function
int produce(int item) {
    printf("Produced Item %d\n", item);
    sleep(1);   
}

// Just a printing function
int consume(int item) {
    printf("\tConsuming Item %d\n", item);
    sleep(1);
}

// Runs producer infinite while loop
void* producer(void* arg) {
    int item;
do {                                // Producer
    item = rand() % 10;             // Creates the random item
    sleep(1);
    printf("%d ", (int)arg);
    produce(item);                  // Prints out randon item
    sem_wait(empty);                // Waits for consumer to empty buffer if full
    sem_wait(mutex);                // Critical section start
    Buffer[in] = item;              // Put the product into buffer
    in = (in+1)%n;                  // increment index
    sem_post(mutex);                // Critical section end
    sem_post(full);

} while(1); }

// Runs consumer infinite while loop
void* consumer(void* arg) {
    int item;
do {                                // Consumer
    sem_wait(full);                 // Wait until buffer is full
    sem_wait(mutex);                // Critical section start
    item = Buffer[out];             // Take item from buffer
    out = (out+1)%n;                // increment index
    sem_post(mutex);                // Critical section end
    sem_post(empty);                // Wait until buffer is empty
    sleep(1);
    printf("\t%d ", (int)arg);      
    consume(item);                  // Print item we took out from buffer
} while(1); }

int main() {
    // Initialize variables
    int i;
    in = 0;
    out = 0;
    // Unlink at start to make sure mutex open works
    sem_unlink("mutex2");
    sem_unlink("empty2");
    sem_unlink("full2");
    // Initialize/Open our three shared variables
    mutex = sem_open("mutex2", O_CREAT, 0644, 1);
    empty = sem_open("empty2", O_CREAT, 0644, n);
    full = sem_open("full2", O_CREAT, 0644, 0);
    // Create producers from i = 0 to i = 4
    for(i = 0; i < NTHREADS/2; i++)
        pthread_create(&threads[i], NULL, producer, (void *)(size_t)i);
    // Create consumers from i = 5 to i = 9
    for(i = NTHREADS/2; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, consumer, (void *)(size_t)i);
    // Wait until code finished in order until we exit (doesn't happen, infinite loops)
    for(i = 0; i < NTHREADS; i++)
        pthread_join(threads[i], NULL);
    return 0;
}
