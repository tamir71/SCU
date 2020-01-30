#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>      // fork()

main (int argc, char ** argv) {
    int child = fork();
    int x = 5;

    if (child == 0) {       // If first child
        x += 5;
        printf("My x is %d\n", x);
    }
    else {
        child = fork();
        x += 10;            // Second child and parent run this code
        if(child) {         // If true (aka Parent)
            x += 5;         // Only parent runs this last +5
        }
        printf("My x is %d\n", x);
    }
}
