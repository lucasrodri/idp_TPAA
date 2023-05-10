typedef struct lista {
    char letra;
    struct lista *prox;
} Lista;

void imprimeLista(Lista *l);
Lista* insereFim(Lista *l, char letra);
int removeElemento(Lista *l, char letra);
int buscaElemento(Lista *l, char value, char *letra);