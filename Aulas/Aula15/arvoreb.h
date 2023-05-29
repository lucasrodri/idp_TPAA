//estrutura de arvore binaria

typedef struct no{
    int info;
    struct no *esq;
    struct no *dir;
} No;

typedef struct arvbin{
    No *raiz;
} ArvBin;

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin* raiz);
int altura_ArvBin(ArvBin* raiz);
int totalNO_ArvBin(ArvBin* raiz);