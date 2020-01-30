#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void first();
void second();

int main() {
    pthread_t threads[2];
    int i;

    pthread_create(&threads[0], NULL, first, NULL);
    pthread_create(&threads[1], NULL, second, NULL);

    pthread_join(threads[1], NULL);
    pthread_join(threads[0], NULL);

    printf("Main thread done.\n");
    return 0;
}

void first() {
    int i = 0;
    while(1) {
        i++;
        if((i % 10000000) == 0) {
            printf(".");
        }
    }
}

void second() {
    while(getchar() != 0) {
        printf("Thank you for your input.\n");
    }
}
