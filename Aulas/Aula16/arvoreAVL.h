
typedef struct NO{
    int info;
    int altura;
    struct NO *esq;
    struct NO *dir;
} ArvAVL;

ArvAVL* cria_ArvAVL();
void libera_ArvAVL(ArvAVL** raiz);
int altura_ArvAVL(ArvAVL* raiz);
int totalNO_ArvAVL(ArvAVL* raiz);
void preOrdem_ArvAVL(ArvAVL* raiz);
void emOrdem_ArvAVL(ArvAVL* raiz);
void posOrdem_ArvAVL(ArvAVL* raiz);
int insere_ArvAVL(ArvAVL** raiz, int valor);
int remove_ArvAVL(ArvAVL** raiz, int valor);
int consulta_ArvAVL(ArvAVL* raiz, int valor);

//Funções auxiliares
int alt_NO(struct NO* no);
int fatorBalanceamento_NO(struct NO* no);
int maior(int x, int y);

//Funções de rotação
void RotacaoLL(ArvAVL** raiz);
void RotacaoRR(ArvAVL** raiz);
void RotacaoLR(ArvAVL** raiz);
void RotacaoRL(ArvAVL** raiz);

//Funções de Desenho
void desenhaArvore(ArvAVL* raiz);