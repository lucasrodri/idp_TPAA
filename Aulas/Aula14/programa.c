#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void mostra_vetor(int *vet, int tam) {
    int i;
    for (i = 0; i < tam; i++)
        printf("%d ", vet[i]);
    printf("\n");
}

void mostra_vetor2(float *vet, int tam) {
    int i;
    for (i = 0; i < tam; i++)
        printf("%.2f ", vet[i]);
    printf("\n");
}

int main() {
    int eh_digrafo = 0;
    Grafo *gr = cria_grafo(6, 6, 1);
    insere_aresta(gr, 0, 1, eh_digrafo, 6);
    insere_aresta(gr, 0, 2, eh_digrafo, 1);
    insere_aresta(gr, 0, 3, eh_digrafo, 5);
    insere_aresta(gr, 1, 2, eh_digrafo, 2);
    insere_aresta(gr, 1, 4, eh_digrafo, 5);
    insere_aresta(gr, 2, 3, eh_digrafo, 2);
    insere_aresta(gr, 2, 4, eh_digrafo, 6);
    insere_aresta(gr, 2, 5, eh_digrafo, 4);
    insere_aresta(gr, 3, 5, eh_digrafo, 4);
    insere_aresta(gr, 4, 5, eh_digrafo, 3);
    imprime_grafo(gr);
    
    //Exemplo algoritmo de Prim
    int pai[6];
    alg_prim(gr, 0, pai);
    //Mostre o vetor pai
    printf("Vetor pai (Algoritmo de Prim): ");
    mostra_vetor(pai, 6);
    
    //Exemplo algoritmo de Kruskal
    int pai2[6];
    alg_kruskal(gr, 0, pai2);
    //Mostre o vetor pai2
    printf("Vetor pai (Algoritmo de Kruskal): ");
    mostra_vetor(pai2, 6);

    libera_grafo(gr);
    return 0;
}