/* TAD: Matriz m por n (m e n >= 1) */

typedef struct matriz {
    int lin;
    int col;
    float* v;
} Matriz;


/* Funções Exportadas */

/* Função cria - Aloca e retorna matriz m por n */
Matriz* cria (int m, int n);

/* Função libera - Libera a memória de uma matriz */
void libera (Matriz* mat);

/* Função acessa - Retorna o valor do elemento [i][j] */
float acessa (Matriz* mat, int i, int j);

/* Função atribui - Atribui valor ao elemento [i][j] */
void atribui (Matriz* mat, int i, int j, float v);

/* Função linhas - Retorna o no. de linhas da matriz */
int linhas (Matriz* mat);

/* Função colunas - Retorna o no. de colunas da matriz */
int colunas (Matriz* mat);