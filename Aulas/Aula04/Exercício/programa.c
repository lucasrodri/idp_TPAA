#include <stdio.h>  
#include <stdlib.h>
#include "lista.h"

int main(int argc, char *argv[]) {
    Lista *lista = NULL;
    lista = inserir(lista, 10);
    lista = inserir(lista, 20);
    lista = inserir(lista, 30);
    printf("Percorrendo a Lista:\n");
    percorrer(lista);
    printf("Procurando elemento 20:\n");
    Lista *elemento = buscar(lista, 20);
    printf("Percorrendo a Lista a partir do elemento 20:\n");
    percorrer(elemento);
    //Removendo elemento 20
    lista = remover(lista, 20);
    printf("Percorrendo a Lista após remover o elemento 20:\n");
    percorrer(lista);
    liberar(lista);
    return 0;
}
