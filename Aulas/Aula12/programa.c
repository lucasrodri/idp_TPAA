#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main() {
    Grafo *gr = cria_grafo(10, 7, 0);
    insere_aresta(gr, 0, 1, 0, 0);
    insere_aresta(gr, 1, 3, 0, 0);
    insere_aresta(gr, 3, 2, 0, 0);
    insere_aresta(gr, 6, 1, 0, 0);
    imprime_grafo(gr);
    libera_grafo(gr);
    return 0;
}