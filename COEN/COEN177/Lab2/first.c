// # Name: Tamir Enkhjargal
// # Date: January 17, 2020
// # Title: Lab 2 - First Code, no changes
// # Description: To develop programs with two or more processes using fork(), exit(),
// #     wait(), and exec() system calls. To demonstrate the use of light weight processes - threads

#include <stdio.h>                              // printf, stderr
#include <sys/types.h>                          // pid_t
#include <unistd.h>                             // fork
#include <stdlib.h>                             // atoi
#include <errno.h>                              // errno

int main(int argc, char *argv[]) {
    
    // Initialize variables
    pid_t pid;
    int i, n = atoi(argv[1]);                   // We can set how many microseconds we can sleep
    printf("\n Before forking.\n");
    
    // Set pid to fork(). Child process now starts after this line with parent properties
    pid = fork();
    
    // If the fork failed, fork() returns -1
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }
    
    // If fork successful, parent pid is 1
    if (pid) {                                  // If pid == 1
        for (i = 0; i < 100; i++) {
            printf("\t \t \t Parent process %d \n", i);
            usleep(n);
        }
    }
    
    // If fork successful, child pid is 0
    else {
        for (i = 0; i < 100; i++) {
            printf("Child process %d\n", i);
            usleep(n);
        }
    }

    return 0;
}

