#include <stdlib.h> /* malloc, free, exit */
#include <stdio.h> /* printf */
#include "lista.h"

Lista* inserir(Lista *l, Produto p) {
    Lista* novo = (Lista*)malloc(sizeof(Lista));
    novo->produto = p;
    novo->prox = l;
    return novo;
}

Lista* remover(Lista *l, int codProd) {
    Lista* anterior = NULL; //Ponteriro para o elemento anterior
    Lista* p = l; //Ponteiro para percorrer a lista
    /*procura elemento na lista, guardando o elemento anterior */
    while (p != NULL && p->produto.codProd != codProd) {
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

Lista *buscar(Lista *lista, int codProd) {
    Lista *p;
    for (p = lista; p != NULL; p = p->prox) {
        if (p->produto.codProd == codProd) {
            return p;
        }
    }
    return lista;
}

void percorrer(Lista *l){
    Lista *p;
    for (p = l; p != NULL; p = p->prox) {
        printf("codProd = %d\n", p->produto.codProd);
        printf("nomeProd = %s\n", p->produto.nomeProd);
        printf("qtdeEstoque = %d\n", p->produto.qtdeEstoque);
        printf("valor = %.2f\n\n", p->produto.valor);
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

Produto* buscarMenor(Lista *lista){
    Produto *p = NULL;
    Lista *prx;
    float menor = lista->produto.valor;
    for (prx = lista; prx != NULL; prx = prx->prox) {
        if (prx->produto.valor < menor) {
            menor = prx->produto.valor;
            p = &prx->produto;
        }
    }
    if (p == NULL) {
        printf("Elemento não existe.\n");
        return NULL;
    }
    return p;
}