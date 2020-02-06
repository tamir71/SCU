//
// # Name: Tamir Enkhjargal
// # Date: February 5, 2020
// # Title: Assignment 4: Software Implementation of Solving Critical Region
// # Description: Generalized software/programmers approach [Peterson's algorithm] 
// #              for n threads.
//

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 100                           // Nthreads 

pthread_t thread_id[N];                 // Create N threads
enum pstate {idle, want_in, in_cs};     // Create different thread states: idle, ready, running
enum pstate flag[N];                    // Create flag[] to indicate readiness of thread
int turn;                               // Create turn to indicate who is running
int j;                                  // Used for iterating

