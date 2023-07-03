#include <stdlib.h> /* malloc, free, exit */
#include <stdio.h> /* printf */
#include <string.h> /* strcpy */
#include "git.h"
#include <time.h>

char* hash_generator(void){
    srand(time(NULL));
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char *hash = (char*) malloc(9 * sizeof(char));
    int i;
    for(i=0;i<8;i++){
        int key = rand() % (int) (sizeof charset - 1);
        hash[i] = charset[key];
    }
    hash[i] = '\0';
    //printf("%s\n",hash);
    return hash;
}

Branch *cria(void) {
    Branch *p = (Branch *) malloc(sizeof(Branch));
    if (p == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }
    strcpy(p->nome, "master");
    No *no = (No *) malloc(sizeof(No));
    if (no == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }
    strcpy(no->hash, hash_generator());
    strcpy(no->mensagem, "first commit");
    no->ant = NULL;
    p->ponteiro = no;
    return p;
}

void libera(Branch *git) {
    No *no = git->ponteiro;
    while (no != NULL) {
        No *anterior = no->ant;
        free(no);
        no = anterior;
    }
    free(git);
}

void commit(Branch *git, char mensagem[]) {
    No *no = (No *) malloc(sizeof(No));
    if (no == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }
    strcpy(no->hash, hash_generator());
    strcpy(no->mensagem, mensagem);
    no->ant = git->ponteiro;
    git->ponteiro = no;
}

void gitlog(Branch *git) {
    No *no = git->ponteiro;
    printf("Branch: %s\n", git->nome);
    while (no != NULL) {
        printf("%s %s\n", no->hash, no->mensagem);
        no = no->ant;
    }
}

Branch *gitbranch(Branch *git, char nome[]) {
    Branch *novoBranch = (Branch *) malloc(sizeof(Branch));
    if (novoBranch == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }
    strcpy(novoBranch->nome, nome);
    novoBranch->ponteiro = git->ponteiro;
    return novoBranch;
}

void add_branch(Branches *branches, Branch *branch) {
    branches->tamanho++;
    branches->vetor = (Branch *) realloc(branches->vetor, branches->tamanho * sizeof(Branch));
    if (branches->vetor == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }
    branches->vetor[branches->tamanho - 1] = *branch;
}

Branch *checkout(Branches *branches, char nome[]) {
    int i;
    for (i = 0; i < branches->tamanho; i++) {
        if (strcmp(branches->vetor[i].nome, nome) == 0) {
            return &branches->vetor[i];
        }
    }
    return NULL;
}

void gitmerge(Branch *git) {
    No *no = (No *) malloc(sizeof(No));
    if (no == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }
    strcpy(no->hash, hash_generator());
    strcpy(no->mensagem, "Merge");
    no->ant = git->ponteiro;
    git->ponteiro = no;
}

void add_no(Commits *nos, No *no) {
    nos->tamanho++;
    nos->vetor = (No *) realloc(nos->vetor, nos->tamanho * sizeof(No));
    if (nos->vetor == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }
    nos->vetor[nos->tamanho - 1] = *no;
}

No *checkout_no(Commits *nos, char hash[]) {
    int i;
    for (i = 0; i < nos->tamanho; i++) {
        if (strcmp(nos->vetor[i].hash, hash) == 0) {
            return &nos->vetor[i];
        }
    }
    return NULL;
}