#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void insertionSort(int *V, int N) {
    int i, j, aux;
    for (i = 1; i < N; i++) {
        aux = V[i];
        for (j = i; (j > 0) && (aux < V[j - 1]); j--) {
            V[j] = V[j - 1];
        }
        V[j] = aux;
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
    insertionSort(V, 30);
    printf("Vetor ordenado:\n");
    for (i = 0; i < 30; i++) {
        printf("%d ", V[i]);
    }
    printf("\n");
    return 0;
}