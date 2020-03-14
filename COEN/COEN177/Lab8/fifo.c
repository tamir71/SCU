/*
/ Tamir Enkhjargal
/ COEN 177L - Lab 8
/ FIFO Implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {     
        int pageno;
} ref_page;

int main(int argc, char *argv[]) {
    int C_SIZE = atoi(argv[1]);                                 // Input from program call
    ref_page cache[C_SIZE]; 
    char pageCache[100];                                        // Create character buffer 
    int cacheIndex = 0;
    int totalFaults = 0; 
    int totalRequests = 0;
    int i;  
    int page_num;
    for(i = 0; i < C_SIZE; i++)
        cache[i].pageno = -1;                                   // Initialize array with -1
    while(fgets(pageCache, 100, stdin)) {
        page_num = atoi(pageCache);
        totalRequests++;
        for(i = 0; i < C_SIZE; i++) {                           // Loop through array
            if(cache[i].pageno == page_num)                     // If we find item in array skip
                break;
            if(i == C_SIZE-1) {                                 // If we didn't find and full array
                printf("Page %d caused a fault\n", page_num);
                totalFaults++;                                  // Increment totalFaults
                cache[cacheIndex].pageno = page_num;            // Input number into array, then increment index
                cacheIndex = (cacheIndex+1) % C_SIZE;
            }
        }
    }
    double hitrate = (totalRequests - totalFaults) / (double)totalRequests;
    printf("%d Total Page Faults with %d Total Page Requests\n", totalFaults, totalRequests);
    printf("FIFO Hit rate = %f\n", hitrate);
    return 0;
}
