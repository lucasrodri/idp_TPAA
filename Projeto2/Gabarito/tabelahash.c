#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelahash.h"
#include "git.h"

Hash_Branch* criaHashBranch(int table_size) {
    Hash_Branch *ha = (Hash_Branch*) malloc(sizeof(Hash_Branch));
    if (ha != NULL) {
        int i;
        ha->TABLE_SIZE = table_size;
        ha->itens = (Branch**) malloc(table_size * sizeof(Branch*));
        if (ha->itens == NULL) {
            free(ha);
            return NULL;
        }
        ha->qtd = 0;
        for (i = 0; i < ha->TABLE_SIZE; i++) {
            ha->itens[i] = NULL;
        }
    }
    return ha;
}

void liberaHashBranch(Hash_Branch *ha) {
    if (ha != NULL) {
        int i;
        for (i = 0; i < ha->TABLE_SIZE; i++) {
            if (ha->itens[i] != NULL) {
                free(ha->itens[i]);
            }
        }
        free(ha->itens);
        free(ha);
    }
}

// Funções de inserção e busca quando HÁ COLISÕES!!!
// ENDEREÇAMENTO ABERTO!!!
int insereHash_EnderAbertoBranch(Hash_Branch *ha, Branch br) {
    if (ha == NULL || ha->qtd == ha->TABLE_SIZE) {
        return 0;
    }
    int chave = valorString(br.nome);
    int i, pos, newPos;
    pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //pos = chaveDobra(chave, ha->TABLE_SIZE);
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        //newPos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);
        //newPos = duploHash(pos, chave, i, ha->TABLE_SIZE);
        if (ha->itens[newPos] == NULL) {
            Branch* novo;
            novo = (Branch*) malloc(sizeof(Branch));
            if (novo == NULL) {
                return 0;
            }
            *novo = br;
            ha->itens[newPos] = novo;
            ha->qtd++;
            return 1;
        }
    }
    return 0;
}

Branch *buscaHash_EnderAbertoBranch(Hash_Branch *ha, char *nome) {
    if (ha == NULL) {
        return 0;
    }
    int i, pos, newPos;
    int chave = valorString(nome);
    pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //pos = chaveDobra(chave, ha->TABLE_SIZE);
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        //newPos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);
        //newPos = duploHash(pos, chave, i, ha->TABLE_SIZE);
        if (ha->itens[newPos] == NULL) {
            return NULL;
        }
        if (strcmp(ha->itens[newPos]->nome, nome) == 0) {
            return (ha->itens[newPos]);
        }
    }
    return 0;
}

int removeHash_EnderAbertoBranch(Hash_Branch *ha, char *nome) {
    if (ha == NULL) {
        return 0;
    }
    int i, pos, newPos;
    int chave = valorString(nome);
    pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //pos = chaveDobra(chave, ha->TABLE_SIZE);
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        //newPos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);
        //newPos = duploHash(pos, chave, i, ha->TABLE_SIZE);
        if (ha->itens[newPos] == NULL) {
            return 0;
        }
        if (strcmp(ha->itens[newPos]->nome, nome) == 0) {
            free(ha->itens[newPos]);
            ha->itens[newPos] = NULL;
            ha->qtd--;
            return 1;
        }
    }
    return 0;
}

void imprimeHashBranch(Hash_Branch *ha) {
    if (ha == NULL) {
        return;
    }
    int i;
    printf("Tabela Hash:\n");
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        if (ha->itens[i] != NULL) {
            printf("Posição: %d. Branch: %s\n", i, ha->itens[i]->nome);
        } 
    }
    printf("\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Hash_No* criaHashNo(int table_size) {
    Hash_No *ha = (Hash_No*) malloc(sizeof(Hash_No));
    if (ha != NULL) {
        int i;
        ha->TABLE_SIZE = table_size;
        ha->itens = (No**) malloc(table_size * sizeof(No*));
        if (ha->itens == NULL) {
            free(ha);
            return NULL;
        }
        ha->qtd = 0;
        for (i = 0; i < ha->TABLE_SIZE; i++) {
            ha->itens[i] = NULL;
        }
    }
    return ha;
}

void liberaHashNo(Hash_No *ha) {
    if (ha != NULL) {
        int i;
        for (i = 0; i < ha->TABLE_SIZE; i++) {
            if (ha->itens[i] != NULL) {
                free(ha->itens[i]);
            }
        }
        free(ha->itens);
        free(ha);
    }
}

// Funções de inserção e busca quando HÁ COLISÕES!!!
// ENDEREÇAMENTO ABERTO!!!
int insereHash_EnderAbertoNo(Hash_No *ha, No no) {
    if (ha == NULL || ha->qtd == ha->TABLE_SIZE) {
        return 0;
    }
    int chave = valorString(no.hash);
    int i, pos, newPos;
    pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //pos = chaveDobra(chave, ha->TABLE_SIZE);
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        //newPos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);
        //newPos = duploHash(pos, chave, i, ha->TABLE_SIZE);
        if (ha->itens[newPos] == NULL) {
            No* novo;
            novo = (No*) malloc(sizeof(No));
            if (novo == NULL) {
                return 0;
            }
            *novo = no;
            ha->itens[newPos] = novo;
            ha->qtd++;
            return 1;
        }
    }
    return 0;
}

No *buscaHash_EnderAbertoNo(Hash_No *ha, char *hash) {
    if (ha == NULL) {
        return 0;
    }
    int i, pos, newPos;
    int chave = valorString(hash);
    pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //pos = chaveDobra(chave, ha->TABLE_SIZE);
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        //newPos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);
        //newPos = duploHash(pos, chave, i, ha->TABLE_SIZE);
        if (ha->itens[newPos] == NULL) {
            return NULL;
        }
        if (strcmp(ha->itens[newPos]->hash, hash) == 0) {
            return (ha->itens[newPos]);
        }
    }
    return 0;
}

int removeHash_EnderAbertoNo(Hash_No *ha, char *hash) {
    if (ha == NULL) {
        return 0;
    }
    int i, pos, newPos;
    int chave = valorString(hash);
    pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //pos = chaveDobra(chave, ha->TABLE_SIZE);
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        //newPos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);
        //newPos = duploHash(pos, chave, i, ha->TABLE_SIZE);
        if (ha->itens[newPos] == NULL) {
            return 0;
        }
        if (strcmp(ha->itens[newPos]->hash, hash) == 0) {
            free(ha->itens[newPos]);
            ha->itens[newPos] = NULL;
            ha->qtd--;
            return 1;
        }
    }
    return 0;
}

void imprimeHashNo(Hash_No *ha) {
    if (ha == NULL) {
        return;
    }
    int i;
    printf("Tabela Hash:\n");
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        if (ha->itens[i] != NULL) {
            printf("Posição: %d. No: %s\n", i, ha->itens[i]->hash);
        } 
    }
    printf("\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int chaveDivisao(int chave, int TABLE_SIZE) {
    return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}

int chaveMultiplicacao(int chave, int TABLE_SIZE) {
    float A = 0.6180339887; // constante qualquer: 0 < A < 1
    float val = chave * A;
    val = val - (int) val;
    return (int) (TABLE_SIZE * val);
}

int chaveDobra(int chave, int TABLE_SIZE) {
    int num_bits = 10; // depende da chave e da TABLE_SIZE. É recomendado que seja um número de bits que seja um divisor do tamanho da chave, para que todas as partes da chave sejam usadas de forma equilibrada
    int parte1 = chave >> num_bits;
    int parte2 = chave & (TABLE_SIZE-1);
    return (parte1 ^ parte2);
}

int valorString(char *str) {
    int i, valor = 7; // valor primo qualquer para evitar que a string seja nula
    int tam = strlen(str);
    for (i = 0; i < tam; i++) {
        valor = 31 * valor + (int) str[i]; // 31 é um número primo qualquer, frequentemente utilizado em funções de hashing
    }
    return valor;
}

int sondagemLinear(int pos, int i, int TABLE_SIZE) {
    return ((pos + i) & 0x7FFFFFFF) % TABLE_SIZE;
}

int sondagemQuadratica(int pos, int i, int TABLE_SIZE) {
    pos = pos + 2*i + 5*i*i; // função quadrática c1 = 2, c2 = 5
    return (pos & 0x7FFFFFFF) % TABLE_SIZE;
}

int duploHash(int H1, int chave, int i, int TABLE_SIZE) {
    int H2 = chaveDivisao(chave, TABLE_SIZE-1) + 1;
    //int H2 = chaveMultiplicacao(chave, TABLE_SIZE-1) + 1;
    //int H2 = chaveDobra(chave, TABLE_SIZE-1) + 1;
    return ((H1 + i*H2) & 0x7FFFFFFF) % TABLE_SIZE;
}