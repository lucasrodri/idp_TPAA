#include <stdlib.h> /* malloc, free, exit */
#include <stdio.h> /* printf */
#include "matriz.h"

void libera (Matriz* mat) {
    free(mat->v);  
    free(mat);
}

Matriz* cria (int m, int n) {
    Matriz* mat = (Matriz*) malloc(sizeof(Matriz));
    if (mat == NULL) {
        printf("Memória insuficiente!\n");  
        exit(1);
    }
    mat->lin = m;
    mat->col = n;
    mat->v = (float*) malloc(m*n*sizeof(float));
    return mat;
}

float acessa (Matriz* mat, int i, int j) {
    int k; /* índice do elemento no vetor – armazenamento por linha*/
    if (i<0 || i>=mat->lin || j<0 || j>=mat->col) {
        printf("Acesso inválido!\n");
        exit(1);
    }
    k = (i)*mat->col + (j);
    return mat->v[k];
}

int linhas (Matriz* mat) {
    return mat->lin;
}

void atribui (Matriz* mat, int i, int j, float v) {
    int k; /* índice do elemento no vetor */
    if (i<0 || i>=mat->lin || j<0 || j>=mat->col) {
        printf("Atribuição inválida!\n");  
        exit(1);
    }
    k = (i)*mat->col + (j);
    mat->v[k] = v;
}

int colunas (Matriz* mat) {
    return mat->col;
}

