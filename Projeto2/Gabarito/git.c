#include <stdlib.h> /* malloc, free, exit */
#include <stdio.h> /* printf */
#include <string.h> /* strcpy */
#include "tabelahash.h"
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
    strcpy(no->ant_hash, "");
    p->ponteiro = no;
    strcpy(p->ponteiro_hash, no->hash);
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
    strcpy(no->ant_hash, git->ponteiro->hash);
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
    //se git == NULL
    if (git == NULL) {
        novoBranch->ponteiro = NULL;
        strcpy(novoBranch->ponteiro_hash, "");
    } else {
        novoBranch->ponteiro = git->ponteiro;
        strcpy(novoBranch->ponteiro_hash, git->ponteiro->hash);
    }
    return novoBranch;
}

void add_branch(Hash_Branch *branches, Branch *branch) {
    insereHash_EnderAbertoBranch(branches, *branch);
}

Branch *checkout(Hash_Branch *branches, char nome[]) {
    return buscaHash_EnderAbertoBranch(branches, nome);
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
    strcpy(no->ant_hash, git->ponteiro->hash);
    git->ponteiro = no;
    strcpy(git->ponteiro_hash, no->hash);
}

void add_no(Hash_No *nos, No *no) {
    insereHash_EnderAbertoNo(nos, *no);
}

No *checkout_no(Hash_No *nos, char hash[]) {
    return buscaHash_EnderAbertoNo(nos, hash);
}