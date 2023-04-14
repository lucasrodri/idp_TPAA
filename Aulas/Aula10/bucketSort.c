#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TAM 5 //Tamanho do balde

struct balde {
    int qtd;
    int valores[TAM];
};

void bucketSort(int *V, int N) {
    int i, j, maior , menor, nroBaldes, pos;
    struct balde *bd;
    // Acha maior e menor valor
    maior = menor = V[0];
    for (i = 1; i < N; i++) {
        if (V[i] > maior) maior = V[i];
        if (V[i] < menor) menor = V[i];
    }
    //Inicializa os baldes
    nroBaldes = (maior - menor) / TAM + 1;
    bd = (struct balde *) malloc(nroBaldes * sizeof(struct balde));
    for (i = 0; i < nroBaldes; i++) {
        bd[i].qtd = 0;
    }
    //Divide os valores entre os baldes
    for (i = 0; i < N; i++) {
        pos = (V[i] - menor) / TAM;
        bd[pos].valores[bd[pos].qtd] = V[i];
        bd[pos].qtd++;
    }
    //Ordena os baldes e coloca os valores de volta no vetor
    pos = 0;
    for (i = 0; i < nroBaldes; i++) {
        //Ordena o balde usando o insertion sort
        for (j = 1; j < bd[i].qtd; j++) {
            int aux = bd[i].valores[j];
            int k = j - 1;
            while (k >= 0 && bd[i].valores[k] > aux) {
                bd[i].valores[k + 1] = bd[i].valores[k];
                k--;
            }
            bd[i].valores[k + 1] = aux;
        }
        //Coloca os valores do balde de volta no vetor
        for (j = 0; j < bd[i].qtd; j++) {
            V[pos] = bd[i].valores[j];
            pos++;
        }
    }
    free(bd);
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
    bucketSort(V, 30);
    printf("Vetor ordenado:\n");
    for (i = 0; i < 30; i++) {
        printf("%d ", V[i]);
    }
    printf("\n");
    return 0;
}