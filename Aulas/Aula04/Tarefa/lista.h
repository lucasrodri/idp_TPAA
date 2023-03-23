typedef struct produto{
    int codProd; //código do produto
    char nomeProd[10]; //nome do produto
    float valor; //valor do produto
    int qtdeEstoque; //quantidade disponível em estoque
}Produto;

typedef struct lista {
    Produto produto;
    struct lista *prox;
} Lista;

Lista* inserir(Lista *l, Produto p);
Lista* remover(Lista *l, int codProd);
void percorrer(Lista *l);
void liberar(Lista *l);
Lista *buscar(Lista *lista, int codProd);
//Função pedida no Exercício
Produto* buscarMenor(Lista *lista);