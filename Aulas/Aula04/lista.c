#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int info;
    struct lista *prox;
} Lista;

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

int main() {
    Lista *lista = NULL;
    lista = inserir(lista, 10);
    lista = inserir(lista, 20);
    lista = inserir(lista, 30);
    printf("Percorrendo a Lista:\n");
    percorrer(lista);
    lista = remover(lista, 20);
    printf("Percorrendo a Lista após remover o elemento 20:\n");
    percorrer(lista);
    liberar(lista);
    return 0;
}