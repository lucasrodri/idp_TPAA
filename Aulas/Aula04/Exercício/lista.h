typedef struct lista {
    int info;
    struct lista *prox;
} Lista;

Lista* inserir(Lista *l, int i);
Lista* remover(Lista *l, int valor);
void percorrer(Lista *l);
void liberar(Lista *l);
//Função pedida no Exercício
Lista *buscar(Lista *lista, int valor);