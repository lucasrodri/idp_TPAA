#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreAVL.h"


int main() {
    ArvAVL* raiz = cria_ArvAVL();

    insere_ArvAVL(&raiz, 1);
    insere_ArvAVL(&raiz, 2);
    insere_ArvAVL(&raiz, 3);
    insere_ArvAVL(&raiz, 10);
    insere_ArvAVL(&raiz, 4);
    insere_ArvAVL(&raiz, 5);
    insere_ArvAVL(&raiz, 9);

    printf("\nAltura da arvore: %d\n", altura_ArvAVL(raiz));
    printf("Total de nos: %d\n", totalNO_ArvAVL(raiz));
    
    desenhaArvore(raiz);

    libera_ArvAVL(&raiz);

    ///////////////

    raiz = cria_ArvAVL();

    insere_ArvAVL(&raiz, 4);
    insere_ArvAVL(&raiz, 2);
    insere_ArvAVL(&raiz, 7);
    insere_ArvAVL(&raiz, 1);
    insere_ArvAVL(&raiz, 3);

    desenhaArvore(raiz);

    //Remove o 2
    remove_ArvAVL(&raiz, 2);
    desenhaArvore(raiz);
    //Remove o 7
    remove_ArvAVL(&raiz, 7);
    desenhaArvore(raiz);

    libera_ArvAVL(&raiz);
    return 0;
}


