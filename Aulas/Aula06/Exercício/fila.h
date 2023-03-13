typedef struct lista {
    int info;
    struct lista *prox;
} Lista;

typedef struct fila {
    Lista *inicio;
    Lista *fim;
} Fila;

Fila *cria(void);
void enqueue(Fila *f, int v);
int dequeue(Fila *f);
void fila_libera(Fila *f);
void percorrer_fila(Fila *f);
void intercala(Fila *f1, Fila *f2);