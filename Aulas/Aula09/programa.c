#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno {
    int matricula;
    char nome[50];
    float media;
    struct aluno* prox;
} Aluno;

Aluno* buscaLinear(Aluno* lista, int matricula) {
    Aluno* atual = lista;
    while (atual != NULL && atual->matricula != matricula) {
        atual = atual->prox;
    }
    return atual;
}

int main() {
    Aluno* lista = NULL;
    Aluno* resultado = NULL;
    Aluno* novo = NULL;
    int matricula;

    // Criação da lista
    novo = (Aluno*) malloc(sizeof(Aluno));
    novo->matricula = 1;
    strcpy(novo->nome, "Joao");
    novo->media = 7.5;
    novo->prox = lista;
    lista = novo;

    novo = (Aluno*) malloc(sizeof(Aluno));
    novo->matricula = 2;
    strcpy(novo->nome, "Maria");
    novo->media = 8.5;
    novo->prox = lista;
    lista = novo;

    novo = (Aluno*) malloc(sizeof(Aluno));
    novo->matricula = 3;
    strcpy(novo->nome, "Jose");
    novo->media = 9.5;
    novo->prox = lista;
    lista = novo;

    // Busca
    printf("Digite a matricula a ser buscada: ");
    scanf("%d", &matricula);
    resultado = buscaLinear(lista, matricula);
    if (resultado == NULL) {
        printf("Aluno nao encontrado\n");
    } else {
        printf("Aluno encontrado\n");
        printf("Matricula:\t%d\n", resultado->matricula);
        printf("Nome:\t\t%s\n", resultado->nome);
        printf("Media:\t\t%.2f\n", resultado->media);
    }
    return 0;
}

