#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int division(int quotient, int answer) {
    return (quotient == answer);    
}

int main() {
    int denominator, quotient, dividend, answer, result;
    int counter=0;

    srand((int) time (NULL));
    
    for (int i = 0; i<10; i++) {

        denominator = rand() % 12 + 1;
        quotient = rand() % 13;
        dividend = denominator*quotient;

        printf("What is %d divided by %d?\n", dividend, denominator);
        scanf("%d", &answer);
        
        result = division(quotient, answer);    
        
        if (result == 1) {
            printf("Correct!\n");
            counter++;
        }
        
        else {
            printf("Incorrect. The correct answer was %d\n", quotient);
        }
           
    }
    
    printf("You have answered %d out of 10 correctly\n", counter);
}
