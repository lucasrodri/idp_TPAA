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
    Lista *l1 = f1->inicio;
    Lista *l2 = f2->inicio;

    // Verificar se ambas as filas estão vazias
    if (l1 == NULL && l2 == NULL) {
        return;
    }

    // Se uma das filas estiver vazia, basta copiar a outra para a fila final f1
    if (l1 == NULL) {
        f1->inicio = f2->inicio;
        f1->fim = f2->fim;
        f2->inicio = NULL;
        f2->fim = NULL;
        return;
    } else if (l2 == NULL) {
        return;
    }

    // Intercale os elementos das filas
    while (l1 != NULL && l2 != NULL) {
        Lista *prox1 = l1->prox;
        Lista *prox2 = l2->prox;

        l1->prox = l2;
        l2->prox = prox1;

        f1->fim = l2;

        l1 = prox1;
        l2 = prox2;
    }

    // Se a segunda fila for maior que a primeira
    // anexa o restante da segunda fila na final da primeira.
    if (l2 != NULL) {
        f1->fim->prox = l2;
        f1->fim = f2->fim;
    }

    f2->inicio = NULL;
    f2->fim = NULL;
}

void intercala3(Fila *f1, Fila *f2, Fila *f3){
    Lista *l1 = f1->inicio;
    Lista *l2 = f2->inicio;
    Lista *l3 = f3->inicio;

    // Verificar se as filas estão vazias
    if (l1 == NULL && l2 == NULL && l3 == NULL) {
        return;
    }

    // Se uma das filas estiver vazia, basta intercalar as outras duas
    if (l1 == NULL) {
        intercala(f2,f3);
        f1->inicio = f2->inicio;
        f1->fim = f2->fim;
        return;
    } else {
        if (l2 == NULL) {
            intercala(f1,f3);
            return;
        } else {
            if (l3 == NULL) {
                intercala(f1,f2);
                return;
            }
        }
    }

    // Intercale os elementos das filas
    while (l1 != NULL && l2 != NULL && l3 != NULL) {
        Lista *prox1 = l1->prox;
        Lista *prox2 = l2->prox;
        Lista *prox3 = l3->prox;

        l1->prox = l2;
        l2->prox = l3;
        l3->prox = prox1;

        f1->fim = l3;

        l1 = prox1;
        l2 = prox2;
        l3 = prox3;
    }

    // Se uma das filas for maior que a primeira
    if (l1 != NULL || l2 != NULL || l3 != NULL) {
        //uma delas é null, descobri qual:
        if (l1 == NULL) {
            f2->inicio = l2;
            f3->inicio = l3;
            intercala(f2,f3);
            f1->fim->prox = f2->inicio;
            f1->fim = f2->fim;
        } else {
            if (l2 == NULL) {
                Lista *auxInicio = f1->inicio;
                Lista *auxFim = f1->fim;
                f1->inicio = l1;
                f3->inicio = l3;
                intercala(f1,f3);
                auxFim->prox = f1->inicio;
                f1->inicio = auxInicio;
            } else {//l3 == NULL
                Lista *auxInicio = f1->inicio;
                Lista *auxFim = f1->fim;
                f1->inicio = l1;
                f2->inicio = l2;
                intercala(f1,f2);
                auxFim->prox = f1->inicio;
                f1->inicio = auxInicio;
            }
        }
    }

    f2->inicio = NULL;
    f2->fim = NULL;

    f3->inicio = NULL;
    f3->fim = NULL;
}