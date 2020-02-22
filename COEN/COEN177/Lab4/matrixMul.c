//
// # Name: Tamir Enkhjargal
// # Date: Friday 2:15-5p
// # Title: Lab 4 - Matrix Multiplication
// # Description: calculate matrix multiplication using threads
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define SIZE 1024

void *matrixMultiply(void *arg);
// Create threads for each row
pthread_t threads[SIZE];
// Initialize our matrix with size x size
double matrixA[SIZE][SIZE], matrixB[SIZE][SIZE], matrixC[SIZE][SIZE];

int main() {
    static int i;
    
    // Used to initialize the seed using CPU time
    srand(time(NULL));
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            // Loop through each value in 2d array, and put in a value from 0 to 19
            matrixA[i][j] = rand() % 20;
            // Print to console afterwards
            printf(" %.2f ", matrixA[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // Same code as above, loop through and enter value into 2d array for matrixB
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            matrixB[i][j] = rand() % 20;
            printf(" %.2f ", matrixB[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    // Create threads for each row [i]
    for(i = 0; i < SIZE; i++)
        pthread_create(&threads[i], NULL, matrixMultiply, (void *)(size_t)i);
    
    // Wait for each thread to finish and close before continuing the program
    for(i = 0; i < SIZE; i++)
        pthread_join(threads[i], NULL);
    
    // After matrixC has been changed with our matrixMultiply() function, print each [r][c]
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            printf(" %.2f ", matrixC[i][j]);
        }
        printf("\n");
    }
}

void *matrixMultiply(void *arg) {
    for(int j = 0; j < SIZE; j++)
        for(int k = 0; k < SIZE; k++)
            // Loop through matrixC and use (int)(size_t) because arg is passed as (size_t)
            // but needs to be integer for indexing purposes
            matrixC[(int)(size_t)arg][j] += matrixA[(int)(size_t)arg][k]*matrixB[k][j];   
}
