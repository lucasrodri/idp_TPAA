#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int info;
    struct lista *prox;
} Lista;

typedef struct pilha {
    Lista *topo;
} Pilha;

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

int main() {
    Pilha *pilha = cria();
    push(pilha, 10);
    push(pilha, 20);
    push(pilha, 30);
    push(pilha, 40);
    printf("Fazendo um pop:\n");
    int v = pop(pilha);
    printf("O valor do topo da pilha era: %d\n", v);
    
    printf("Percorrendo a Pilha com POP:\n");
    //percorrer_com_pop(pilha);
    percorrer_sem_pop(pilha);
    printf("Mais um POP: %d\n", pop(pilha));
    pilha_libera(pilha);
    return 0;
}