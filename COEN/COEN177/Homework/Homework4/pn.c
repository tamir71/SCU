//
// # Name: Tamir Enkhjargal
// # Date: February 5, 2020
// # Title: Assignment 4: Software Implementation of Solving Critical Region
// # Description: Generalized software/programmers approach [Peterson's algorithm] 
// #              for n threads.
//

#include "pn.h"             // Contains all libraries and global variables

/* Posting again just for visibility purposes while implementing */
    // enum pstate {idle, want_in, in_cs}
    // enum pstate flag[N];
    // int turn
    // int j


// Create function prototypes
void leaveCS(int i);
void enterCS(int i);
void *thread(void* arg);


int main() {
    int i;
    for (i = 0; i < N; i++)
         pthread_create(&thread_id[i], NULL, thread, (void*)(size_t)i);     // Create N threads that run thread()
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);                                   // Wait for each thread to end main()
    return 0;
}

// Function that each thread runs
void *thread(void* arg) {
    int i = (int)arg;
    enterCS(i);             // Each thread enters Critical Section with its respective iteration i passed from main()
    sleep(1);
    leaveCS(i);             // Each thread leaves Critical Section with its respective iteration i passed from main()
    printf("Goodbye\n");    // Print `Goodbye` once each thread has entered and left CS
    return 0;
}

void enterCS(int i) {
    while (1) {
        flag[i] = want_in;          // Set the flag for this thread to be ready [`want_in`]
        j = turn;                   // Running thread

        while (j != i) {            // While it is not this thread's turn
            if (flag[j] != idle)    // If the running thread is not idle (AKA want_in or in_cs)
                j = turn;           // Keep the running thread running
            else                    // If the running thread is idle, then
                j = (j+1) % N;      // make the iterator j to increment the number of threads and loop around
        }
        
        flag[i] = in_cs;            // Once the thread-chooser (above while loop) exits (i.e. it is this thread's turn)
        j = 0;                      // Set iterator j to 0, and this thread is now `in_cs`

        // Loop through the entire thread list, exit when j >= N, or when (a) on this thread, (b) this thread is done
        while ( (j<N) && (j==i || flag[j] != in_cs) )
            j++;                                        // Increment j
        // When above while loop breaks, check if that j we broke on is j >= N, and we're on this thread but it has become idle
        if ( (j>=N) && (turn==i || flag[turn]==idle) )  
            break;
    }
    printf("Thread %d entered Critical Section\n", i);
}

void leaveCS(int i) {
    j = (turn+1) % N;       // Make the iterator j loop through thread list one by one
    while (flag[j]==idle)   // Keep looping to find a thread waiting or in critical section, then exit
        j = (j+1)%N;
    turn = j;               // Choose the waiting thread to be turn
    flag[i]=idle;           // Set current thread to be idle
    printf("Thread %d left Critical Section\n", i);
}

