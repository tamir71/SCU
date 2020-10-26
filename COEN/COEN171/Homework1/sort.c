// Tamir Enkhjargal
// SCU - COEN 171
// Homework 1 - sort.c

#include <stdio.h>
#include <stdlib.h>

#define high 8

typedef int numbers[high];
numbers a;

void readarray() {
    int i;
    for(i = 0; i < high; ++i) {
        scanf("%d\n", &a[i]);
    }
}

void writearray() {
    int i;
    for(i = 0; i < high; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void exchange(int *a, int *b) {
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

int partition(numbers a, int y, int z) {
	int i, j, x;
	x = a[y];
	i = y - 1;
	j = z + 1;
	while(i < j) {
		do {
			j = j - 1;
		} while(a[j] > x);
		do {
			i = i + 1;
		} while(a[i] < x);
		if(i < j)
			exchange(&a[i], &a[j]);
	}
	return j;
}

void quicksort(numbers a, int m, int n) {
    int i;
	if(n > m) {
		i = partition(a, m, n);
		printf("%d\n", i);
		writearray();
		quicksort(a, m, i);
		quicksort(a, i + 1, n);
	}
}

void main() {
	readarray();
	quicksort(a, 0, high - 1);
	writearray();
}
