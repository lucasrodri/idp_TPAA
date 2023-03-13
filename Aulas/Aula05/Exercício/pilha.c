#include <stdlib.h> /* malloc, free, exit */
#include <stdio.h> /* printf */
#include "pilha.h"

Pilha *cria(void) {
    Pilha *p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

void push(Pilha *p, int v){
    Lista* novo = (Lista*)malloc(sizeof(Lista));
    novo->info = v;
    novo->prox = p->topo;
    p->topo = novo;
}   

int pop(Pilha *p){
    Lista* t;
    int v;
    if(p->topo == NULL){
        printf("Lista vazia!\n");
        return -1;
    }
    t = p->topo;
    v = t->info;
    p->topo = t->prox;
    free(t);
    return v;
}  

void pilha_libera(Pilha *p) {
    Lista *aux = p->topo;
    while (aux != NULL) {
        Lista *proximo = aux->prox;
        free(aux);
        aux = proximo;
    }
    free(p);
}

void percorrer_com_pop(Pilha *p){
    while (p->topo != NULL) {
        printf("info = %d\n", pop(p)); 
    }
}

void percorrer_sem_pop(Pilha *p){
    Lista *l = p->topo;
    while (l->prox != NULL) {
        printf("info = %d\n", l->info);
        l = l->prox; 
    }
    printf("info = %d\n", l->info); //Para o ultimo elemento
}

void mostra_binario(Pilha *p){
    Lista *l = p->topo;
    while (l->prox != NULL) {
        printf("%d", l->info);
        l = l->prox; 
    }
    printf("%d\n", l->info); //Para o ultimo elemento
}