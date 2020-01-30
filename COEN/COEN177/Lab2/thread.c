// # Name: Tamir Enkhjargal
// # Date: January 17, 2020
// # Title: Lab 2 - Third code - with two threads instead of processes.
// # Description: To develop programs with two or more processes using fork(), exit(),
// #     wait(), and exec() system calls. To demonstrate the use of light weight processes - threads

#define _BSD_SOURCE                             // usleep warning
#include <stdio.h>                              // printf, stderr
#include <sys/types.h>                          // pid_t
#include <unistd.h>                             // fork
#include <stdlib.h>                             // atoi
#include <errno.h>                              // errno
#include <pthread.h>                            // pthread functions

void* func(int n);

int main(int argc, char *argv[]) {
    
    // Check if all arguments exist
    if(argc != 2) {
        printf("\t\tError! Run program using ./third [microseconds]\n");
        return 0;
    }

    // Initialize variables
    pthread_t ptid1, ptid2;
    int i, n = atoi(argv[1]);                   // We can set how many microseconds we can sleep
    
    // Create our two threads to run func() with our n
    pthread_create(&ptid1, NULL, func,(void *)n);
    pthread_create(&ptid2, NULL, func, (void *)n);

    // Join threads side by side
    pthread_join(ptid, NULL);
    pthread_join(ptid, NULL);
    
    // Exit all threads created
    pthread_exit(NULL);
    
    return 0;
}
    
void* func(int n) {
    int i;
    
    // Simple function to just print 0-99
    for (i = 0; i < 100; i++) {
        printf("\t\t thread %d\n", i);
        usleep(n);
    }
    return NULL;
}

