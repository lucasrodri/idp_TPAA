#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int main(int argc, char *argv[]) {
    Lista *lista = NULL;
    Produto p1 = { 1, "Produto A", 10.50, 50 };
    Produto pa;
    pa.codProd = 4;
    strcpy(pa.nomeProd, "kdjfhsldk");
    pa.qtdeEstoque = 89;
    pa.valor = 3.4;

    Produto p2 = { 2, "Produto B", 7.50, 50 };
    Produto p3 = { 3, "Produto C", 9.55, 10 };
    lista = inserir(lista, p1);
    lista = inserir(lista, p2);
    lista = inserir(lista, p3);
    printf("Percorrendo a Lista:\n");
    percorrer(lista);


    printf("Menor valor dos Produtos da Lista:\n");
    Produto *produtoMenor = buscarMenor(lista);
    printf("codProd = %d\n", produtoMenor->codProd);
    printf("nomeProd = %s\n", produtoMenor->nomeProd);
    printf("qtdeEstoque = %d\n", produtoMenor->qtdeEstoque);
    printf("valor = %.2f\n\n", produtoMenor->valor);


    printf("Procurando elemento com codProd = 2:\n");
    Lista *elemento = buscar(lista, 2);
    printf("Percorrendo a Lista a partir do elemento codProd = 2:\n");
    percorrer(elemento);
    //Removendo elemento 2
    lista = remover(lista, 2);
    printf("Percorrendo a Lista após remover o elemento codProd = 2:\n");
    percorrer(lista);
    liberar(lista);
    return 0;
}
