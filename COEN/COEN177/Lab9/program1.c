#include <stdio.h>

#define SIZE 10000
int main(int argc, char *argv[]) {
    FILE *fp;
    char str[SIZE];
    char* filename = argv[1];
    
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fgets(str, SIZE, fp) != NULL)
        printf("%s", str);
    fclose(fp);
    return 0;
}
