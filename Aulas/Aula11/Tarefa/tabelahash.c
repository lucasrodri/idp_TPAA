#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "tabelahash.h"

Hash* criaHash(int TABLE_SIZE) {
    Hash* ha = (Hash*) malloc(sizeof(Hash));
    if (ha != NULL) {
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->itens = (char*) malloc(TABLE_SIZE * sizeof(char));
        if (ha->itens == NULL) {
            free(ha);
            return NULL;
        }
        ha->qtd = 0;
        for (i = 0; i < ha->TABLE_SIZE; i++) {
            ha->itens[i] = '\0';
        }
    }
    return ha;
}

void liberaHash(Hash *ha) {
    if (ha != NULL) {
        free(ha->itens);
        free(ha);
    }
}

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

// Funções de inserção e busca quando NÃO HÁ COLISÕES!!!
int insereHash_SemColisao(Hash *ha, char letra) {
    if (ha == NULL || ha->qtd == ha->TABLE_SIZE) {
        return 0;
    }
    int chave = (int) letra;
    int pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //int pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //int pos = chaveDobra(chave, ha->TABLE_SIZE);
    ha->itens[pos] = letra;
    ha->qtd++;
}

int buscaHash_SemColisao(Hash *ha, char value, char *letra) {
    if (ha == NULL) {
        return 0;
    }
    int chave = (int) value;
    int pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //int pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //int pos = chaveDobra(chave, ha->TABLE_SIZE);
    if (ha->itens[pos] == '\0') {
        return 0;
    }
    *letra = ha->itens[pos];
    return 1;
}

int removeHash_SemColisao(Hash *ha, char value) {
    if (ha == NULL) {
        return 0;
    }
    int chave = (int) value;
    int pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //int pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //int pos = chaveDobra(chave, ha->TABLE_SIZE);
    if (ha->itens[pos] == '\0') {
        return 0;
    }
    ha->itens[pos] = '\0';
    ha->qtd--;
    return 1;
}

// Funções de inserção e busca quando HÁ COLISÕES!!!
// ENDEREÇAMENTO ABERTO!!!
int insereHash_EnderAberto(Hash *ha, char letra) {
    if (ha == NULL || ha->qtd == ha->TABLE_SIZE) {
        return 0;
    }
    int chave = (int) letra;
    int i, pos, newPos;
    pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //pos = chaveDobra(chave, ha->TABLE_SIZE);
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        //newPos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);
        //newPos = duploHash(pos, chave, i, ha->TABLE_SIZE);
        if (ha->itens[newPos] == '\0') {
            ha->itens[newPos] = letra;
            ha->qtd++;
            return 1;
        }
    }
    return 0;
}

int buscaHash_EnderAberto(Hash *ha, char value, char *letra) {
    if (ha == NULL) {
        return 0;
    }
    int i, pos, newPos;
    int chave = (int) value;
    pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //pos = chaveDobra(chave, ha->TABLE_SIZE);
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        //newPos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);
        //newPos = duploHash(pos, chave, i, ha->TABLE_SIZE);
        if (ha->itens[newPos] == '\0') {
            return 0;
        }
        if (ha->itens[newPos] == value) {
            *letra = ha->itens[newPos];
            return 1;
        }
    }
    return 0;
}

int removeHash_EnderAberto(Hash *ha, char value) {
    if (ha == NULL) {
        return 0;
    }
    int i, pos, newPos;
    int chave = (int) value;
    pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //pos = chaveDobra(chave, ha->TABLE_SIZE);
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        //newPos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);
        //newPos = duploHash(pos, chave, i, ha->TABLE_SIZE);
        if (ha->itens[newPos] == '\0') {
            return 0;
        }
        if (ha->itens[newPos] == value) {
            ha->itens[newPos] = '\0';
            ha->qtd--;
            return 1;
        }
    }
    return 0;
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

void imprimeHash(Hash *ha) {
    if (ha == NULL) {
        return;
    }
    int i;
    printf("Tabela Hash:\n");
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        if (ha->itens[i] != '\0') {
            
            printf("Posição: %d. Chave: %d. Valor: %c\n", i, (int) ha->itens[i], ha->itens[i]);
        }
    }
    printf("\n");
}

// Funções de hash separado
HashSeparado* criaHashSeparado(int TABLE_SIZE) {
    HashSeparado* ha = (HashSeparado*) malloc(sizeof(HashSeparado));
    if (ha != NULL) {
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->itens = (Lista**) malloc(TABLE_SIZE * sizeof(Lista*));
        if (ha->itens == NULL) {
            free(ha);
            return NULL;
        }
        for (i = 0; i < TABLE_SIZE; i++) {
            ha->itens[i] = NULL;
        }
    }
    return ha;
}
void liberaHashSeparado(HashSeparado *ha){
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
// ENDEREÇAMENTO SEPARADO!!!
int insereHash_EnderSeparado(HashSeparado *ha, char letra) {
    if (ha == NULL || ha->qtd == ha->TABLE_SIZE) {
        return 0;
    }
    //Comentado para o exercício 
    //int chave = valorString(&letra);
    //int pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //Inserindo a função de hash para o exercício
    int pos = hashExercicio(letra, ha->TABLE_SIZE);
    //int pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //int pos = chaveDobra(chave, ha->TABLE_SIZE);
    Lista *lista = ha->itens[pos];
    if (lista == NULL) {
        lista = (Lista*) malloc(sizeof(Lista));
        if (lista == NULL) {
            return 0;
        }
        // inicializa a lista pois é a primeira inserção
        lista->letra = letra;
        lista->prox = NULL;
        ha->itens[pos] = lista;
    } else {
        // lista já existe, insere no final da lista
        insereFim(lista, letra);
    }
    return 1;
}

int buscaHash_EnderSeparado(HashSeparado *ha, char value, char *letra) {
    if (ha == NULL) {
        return 0;
    }
    //Comentado para o exercício 
    //int chave = valorString(&value);
    //int pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //Inserindo a função de hash para o exercício
    int pos = hashExercicio(value, ha->TABLE_SIZE);
    //int pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //int pos = chaveDobra(chave, ha->TABLE_SIZE);
    Lista *lista = ha->itens[pos];
    if (lista == NULL) {
        return 0;
    }
    return buscaElemento(lista, value, letra);
}

int removeHash_EnderSeparado(HashSeparado *ha, char value) {
    if (ha == NULL) {
        return 0;
    }
    //Comentado para o exercício
    //int chave = valorString(&value);
    //int pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //Inserindo a função de hash para o exercício
    int pos = hashExercicio(value, ha->TABLE_SIZE);
    //int pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //int pos = chaveDobra(chave, ha->TABLE_SIZE);
    Lista *lista = ha->itens[pos];
    if (lista == NULL) {
        return 0;
    }
    if (lista->letra == value) {
        // remove o primeiro aluno da lista
        ha->itens[pos] = lista->prox;
        free(lista);
        return 1;
    }
    return removeElemento(lista, value);
}

void imprimeHashSeparado(HashSeparado *ha) {
    if (ha == NULL) {
        return;
    }
    int i;
    printf("Tabela Hash:\n");
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        if (ha->itens[i] != NULL) {
            printf("Posição: %d. Alunos: ", i);
            imprimeLista(ha->itens[i]);
        } 
    }
    printf("\n");
}

//Função hash do Exercício 7
int hashExercicio(char letra, int TABLE_SIZE) {
    //Possiveis letras: 'D', 'Q', 'B', 'I', 'M', 'H', 'G', 'U', 'A', 'C', 'R', 'S'
    switch (letra) {
        case 'D':
            return 2;
        case 'Q':
            return 0;
        case 'B':
            return 0;
        case 'I':
            return 1;
        case 'M':
            return 2;
        case 'H':
            return 0;
        case 'G':
            return 2;
        case 'U':
            return 1;
        case 'A':
            return 2;
        case 'C':
            return 1;
        case 'R':
            return 1;
        case 'S':
            return 2;
        //Caso do J
        case 'J':
            return 2;
        default:
            return -1;
    }
}