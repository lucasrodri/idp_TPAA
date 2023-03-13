#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int info;
    struct lista *prox;
} Lista;

typedef struct fila {
    Lista *inicio;
    Lista *fim;
} Fila;

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

int main() {
    Fila *fila = cria();
    printf("Enfileirando os número 10, 20, 30, 40:\n");
    enqueue(fila, 10);
    enqueue(fila, 20);
    enqueue(fila, 30);
    enqueue(fila, 40);
    
    printf("Fazendo um desenfileiramento:\n");
    int v = dequeue(fila);
    printf("O valor no inicio da fila era: %d\n", v);
    
    printf("Percorrendo a Fila (sem remover):\n");
    percorrer_fila(fila);

    fila_libera(fila);
    
    return 0;
}