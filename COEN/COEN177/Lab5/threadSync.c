//
// # Name: Tamir Enkhjargal
// # Date: 2/7/20, Fridays 2:15
// # Title: Lab5 - Thread Synchronization using Semaphores
//

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
sem_t *mutex; 

void* go(void* arg) { 
    sem_wait(mutex); //entry section
    printf("Thread %d Entered Critical Section..\n", (int)arg); //critical section 
    sem_post(mutex); //exit section 
    return (NULL);
} 

int main() { 
    sem_unlink("mutex2");                                       // Unlink any mutex beforehand
    mutex = sem_open("mutex2", O_CREAT, 0644, 1);               // Create mutex and initialize
    int i;
    for (i = 0; i < NTHREADS; i++)  
       pthread_create(&threads[i], NULL, go, (void *)(size_t)i);// Create nthreads and run go()
    for (i = 0; i < NTHREADS; i++) {
       pthread_join(threads[i],NULL);                           // Wait until all threads finished
       printf("\t\t\tThread %d returned \n", i);
       }
    printf("Main thread done.\n");
    sem_unlink("mutex2"); 
    return 0; 
} 
