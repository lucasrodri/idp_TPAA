#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define K 100

void countingSort(int *V, int N) {
    int i, j, k;
    int baldes[K];
    for (i = 0; i < K; i++) {
        baldes[i] = 0;
    }
    for (i = 0; i < N; i++) {
        baldes[V[i]]++;
    }
    //Reconstruindo o vetor
    for (i = 0, j = 0; i < K; i++) {
        for (k = 0; k < baldes[i]; k++) {
            V[j++] = i;
        }
    }
}

int main() {
    srand(time(NULL));
    int V[30];
    int i;
    for (i = 0; i < 30; i++) {
        V[i] = rand() % 100;
    }
    for (i = 0; i < 30; i++) {
        printf("%d ", V[i]);
    } 
    printf("\n");
    countingSort(V, 30);
    printf("Vetor ordenado:\n");
    for (i = 0; i < 30; i++) {
        printf("%d ", V[i]);
    }
    printf("\n");
    return 0;
}