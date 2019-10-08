//
//  Created by Behnam Dezfouli
//  CSEN, Santa Clara University
//
//
// This program offers two options to the user:
// -- Option 1: enables the user to copy a file to another file. 
// The user needs to enter the name of the source and destination files.
// -- Option 2: enables the user to measure the performance of file copy. 
// In addition to the name of source and destination files, the user needs to enter the maximum source file size as well as the step size to increment the source file size.
//
//
// double copier(FILE *s_file, FILE *d_file)
// Precondition: s_file is a pointer to a file opened in read mode, d_file is a file pointer opened in write mode
// Postcondition: Copies the contents of the file pointed to by s_file to the file pointed to by d_file
//


#include <stdio.h>
#include <stdlib.h> // For exit()
#include <string.h>
#include <time.h>

#define SIZE 1
#define DUM_CHAR 'A'


double copier(FILE *s_file, FILE *d_file) {
    char buffer[1];                                         // Create buffer of 1 byte
    while(fread(&buffer, 1, 1, s_file) == 1) {              // Read from source 1 byte at a time
        fwrite(&buffer, 1, 1, d_file);                      // Write into dest 1 byte at a time
    }
}

int main(int argc, char *argv[]) {
    if (strcmp(argv[3], "1") == 0) {                        // File copy
        FILE *f1;
        FILE *f2;
        f1 = fopen(argv[1], "rb");                          // Open source for read
        f2 = fopen(argv[2], "wb");                          // Open dest for write
        copier(f1, f2);                                     // Call our copier function
        return 0;
    }
    else if (strcmp(argv[4], "2") == 0) {                   // File copy with performance measure
        clock_t start, end;                                 // Initializing our variables
        double cpu_time_used;
        int maximum_file_size = atoi(argv[2]);              // String max file size -> int
        int step_size = atoi(argv[3]);                      // String step size -> int
        
        int current_size = 0;                               // Set current size to 0 at start
        while(current_size < maximum_file_size) {           // Run until current size = max size
            current_size += step_size;                      // Increment by 1 step
            FILE *f1, *f2;
            f1 = fopen(argv[1], "wb");                      // Take name and open file pointer
            fseek(f1, current_size, SEEK_SET);              // Fill with (empty) bytes * current size
            fputc("\0", f1);                                // End with EOF header
            fclose(f1);                                     // Close file pointer
            f1 = fopen(argv[1],"rb");                       // Reopen for read purposes
            f2 = fopen("dest.txt", "wb");                   // Open dummy destination file
            start = clock();                                // Start clock reading
            copier(f1, f2);                                 // Copy empty file to dest file
            end = clock();                                  // Take end clock reading
            //cpu_time_used = ((double)(end-start));  
            printf("CPU Time Used: %d\n", end-start);       // Print time taken
            fclose(f1);                                     // Close file pointers
            fclose(f2);
        }
        return 0;
    }
    
    else {
        printf("Invalid option!");
        return 0;
    }
    return 0;
}

