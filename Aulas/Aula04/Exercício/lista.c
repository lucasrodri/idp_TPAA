#include <stdlib.h> /* malloc, free, exit */
#include <stdio.h> /* printf */
#include "lista.h"

Lista* inserir(Lista *l, int i) {
    Lista* novo = (Lista*)malloc(sizeof(Lista));
    novo->info = i;
    novo->prox = l;
    return novo;
}

Lista* remover(Lista *l, int valor) {
    Lista* anterior = NULL; //Ponteriro para o elemento anterior
    Lista* p = l; //Ponteiro para percorrer a lista
    /*procura elemento na lista, guardando o elemento anterior */
    while (p != NULL && p->info != valor) {
        anterior = p;
        p = p->prox;
    }
    /* verifica se achou o elemento*/
    if (p == NULL) {
        return l; //não achou, retorna a lista original
    }
    /*retira elemento*/
    if (anterior == NULL) {
        l = p->prox; //caso em que achou no começo
    } else {
        anterior->prox = p->prox; //caso não seja o primeiro
    }
    free(p);
    return l;
}   

Lista *buscar(Lista *lista, int valor) {
    Lista *p;
    for (p = lista; p != NULL; p = p->prox) {
        if (p->info == valor) {
            return p;
        }
    }
    return lista;
}

void percorrer(Lista *l){
    Lista *p;
    for (p = l; p != NULL; p = p->prox) {
        printf("info = %d\n", p->info);
    }
}

void liberar(Lista *l) {
    Lista *p = l;
    while (p != NULL) {
        Lista *proximo = p->prox;
        free(p);
        p = proximo;
    }
}