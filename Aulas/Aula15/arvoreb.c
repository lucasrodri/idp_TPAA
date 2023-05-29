#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreb.h"


ArvBin* cria_ArvBin() {
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if (raiz != NULL)
        raiz->raiz = NULL;
    return raiz;
}

void libera_NO(No* no){
    if (no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if (raiz == NULL)
        return;
    libera_NO(raiz->raiz);
    free(raiz);
}


int altura_ArvTemp(No* raiz) {
    if (raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(raiz->esq);
    int alt_dir = altura_ArvBin(raiz->dir);
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return (alt_dir + 1);
}

int altura_ArvBin(ArvBin* raiz) {
    if (raiz == NULL)
        return 0;
    return altura_ArvTemp(raiz->raiz);
}

int totalNO_ArvBin(ArvBin* raiz) {
    if (raiz == NULL)
        return 0;
    int alt_esq = altura_ArvTemp(raiz->raiz->esq);
    int alt_dir = altura_ArvTemp(raiz->raiz->dir);
    return (alt_esq + alt_dir + 1);
}