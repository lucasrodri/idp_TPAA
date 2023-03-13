typedef struct lista {
    int info;
    struct lista *prox;
} Lista;

typedef struct pilha {
    Lista *topo;
} Pilha;

Pilha *cria(void);
void push(Pilha *p, int v);
int pop(Pilha *p);
void pilha_libera(Pilha *p);
void percorrer_com_pop(Pilha *p);
void percorrer_sem_pop(Pilha *p);
void mostra_binario(Pilha *p);