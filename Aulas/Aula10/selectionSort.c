#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void selectionSort(int *V, int N) {
    int i, j, menor, troca;
    for (i = 0; i < N - 1; i++) {
        menor = i;
        for (j = i + 1; j < N; j++) {
            if (V[j] < V[menor]) {
                menor = j;
            }
        }
        if (i != menor) {
            troca = V[i];
            V[i] = V[menor];
            V[menor] = troca;
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
    selectionSort(V, 30);
    printf("Vetor ordenado:\n");
    for (i = 0; i < 30; i++) {
        printf("%d ", V[i]);
    }
    printf("\n");
    return 0;
}