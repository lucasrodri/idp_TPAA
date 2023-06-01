#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreb.h"


int main() {
    ArvBin* raiz = cria_ArvBin();

    insere_ArvBin(&raiz, 50);
    insere_ArvBin(&raiz, 10);
    insere_ArvBin(&raiz, 99);
    insere_ArvBin(&raiz, 5);
    insere_ArvBin(&raiz, 30);
    //insere_ArvBin(&raiz, 25);
    insere_ArvBin(&raiz, 45);
    //insere_ArvBin(&raiz, 40);

    printf("Pre Ordem (raiz, esq, dir):\n");
    preOrdem_ArvBin(raiz);
    
    printf("\nEm Ordem (esq, raiz, dir):\n");
    emOrdem_ArvBin(raiz);
    
    printf("\nPos Ordem (esq, dir, raiz):\n");
    posOrdem_ArvBin(raiz);

    printf("\nAltura da arvore: %d\n", altura_ArvBin(raiz));
    printf("Total de nos: %d\n", totalNO_ArvBin(raiz));
    
    //Removendo o nó 30
    remove_ArvBin(&raiz, 30);
    printf("\nPos Ordem (esq, dir, raiz):\n");
    posOrdem_ArvBin(raiz);
    printf("\nAltura da arvore: %d\n", altura_ArvBin(raiz));
    printf("Total de nos: %d\n", totalNO_ArvBin(raiz));

    //Contando os nos nao folha
    printf("Total de nos nao folha: %d\n", conta_nos_nao_folha(raiz));

    libera_ArvBin(&raiz);
    return 0;
}


