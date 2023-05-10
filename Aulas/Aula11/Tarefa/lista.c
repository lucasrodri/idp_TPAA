#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

void imprimeLista(Lista *l){
    Lista *p = l;
    while (p != NULL) {
        printf("%c ", p->letra);
        p = p->prox;
    }
    printf("\n");
}

Lista* insereFim(Lista *l, char letra){
    Lista *novo = (Lista*) malloc(sizeof(Lista));
    novo->letra = letra;
    novo->prox = NULL;
    if (l == NULL) {
        return novo;
    } else {
        Lista *p = l;
        while (p->prox != NULL) {
            p = p->prox;
        }
        p->prox = novo;
        return l;
    }
}

int removeElemento(Lista *l, char letra) {
    Lista *p = l;
    Lista *ant = NULL;
    while (p != NULL && p->letra != letra) {
        ant = p;
        p = p->prox;
    }
    if (p == NULL) {
        return 0;
    } else {
        if (ant == NULL) {
            l = p->prox;
        } else {
            ant->prox = p->prox;
        }
        free(p);
        return 1;
    }
}

int buscaElemento(Lista *l, char value, char *letra){
    Lista *p = l;
    while (p != NULL && p->letra != value) {
        p = p->prox;
    }
    if (p == NULL) {
        return 0;
    } else {
        *letra = p->letra;
        return 1;
    }
}