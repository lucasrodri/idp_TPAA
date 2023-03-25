typedef struct lista {
    char info;
    struct lista *prox;
} Lista;

typedef struct pilha {
    Lista *topo;
} Pilha;

Pilha *cria(void);
void push(Pilha *p, char v);
char pop(Pilha *p);
void pilha_libera(Pilha *p);
void percorrer_com_pop(Pilha *p);
void percorrer_sem_pop(Pilha *p);
void mostra_binario(Pilha *p);