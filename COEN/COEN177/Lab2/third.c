// # Name: Tamir Enkhjargal
// # Date: January 17, 2020
// # Title: Lab 2 - Third code - Making child process call ls
// # Description: To develop programs with two or more processes using fork(), exit(),
// #     wait(), and exec() system calls. To demonstrate the use of light weight processes - threads

#define _BSD_SOURCE                             // Needed to avoid usleep function warning
#include <stdio.h>                              // printf, stderr
#include <sys/types.h>                          // pid_t
#include <unistd.h>                             // fork
#include <stdlib.h>                             // atoi
#include <errno.h>                              // errno
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    // Check if all arguments exist
    if(argc != 2) {
        printf("\t\tError! Run program using ./second [microseconds]\n");
        return 0;
    }

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
    
    // Child process runs different code with execlp
    else if (pid == 0) {
        execlp("/bin/ls", "ls", NULL);          // Make child run `ls` command
    }

    // Parent process waits for child and then exits
    else {
        wait(NULL);
        printf("Child Complete");
        exit(0);
    }
    return 0;
}

