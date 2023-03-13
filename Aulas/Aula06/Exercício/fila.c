#include <stdlib.h> /* malloc, free, exit */
#include <stdio.h> /* printf */
#include "fila.h"

Fila *cria(void) {
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void enqueue(Fila *f, int v){
    Lista* novo = (Lista*)malloc(sizeof(Lista));
    novo->info = v;
    novo->prox = NULL;
    if(f->fim == NULL) { // fila esta vazia
        f->inicio = novo;
    } else { // fila não estava vazia
        f->fim->prox = novo;
    }
    f->fim = novo;
}   

int dequeue(Fila *f){
    Lista* aux;
    int v;
    if(f->inicio == NULL){
        printf("Fila vazia!\n");
        return -1;
    }
    aux = f->inicio;
    v = aux->info;
    f->inicio = aux->prox;
    if(f->inicio == NULL){
        f->fim = NULL; // fila ficou vazia
    }
    free(aux);
    return v;
}  

void fila_libera(Fila *f) {
    Lista *aux = f->inicio;
    while (aux != NULL) {
        Lista *proximo = aux->prox;
        free(aux);
        aux = proximo;
    }
    free(f);
}

void percorrer_fila(Fila *f){
    Lista *l = f->inicio;
    while (l->prox != NULL) {
        printf("info = %d\n", l->info);
        l = l->prox; 
    }
    printf("info = %d\n", l->info); //Para o ultimo elemento
}

void intercala(Fila *f1, Fila *f2){
    //TODO: Faça o Ex1
}