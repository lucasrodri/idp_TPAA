typedef struct branch Branch; // Declaração antecipada da estrutura Branch
typedef struct no No; // Declaração antecipada da estrutura No

typedef struct hashEnderAberto_Branch {
    int qtd, TABLE_SIZE;
    Branch **itens;
} Hash_Branch;

typedef struct hashEnderAberto_No {
    int qtd, TABLE_SIZE;
    No **itens;
} Hash_No;

//(Hash_Branch)

// Funcoes para manipulacao da tabela hash com enderecamento aberto 
Hash_Branch* criaHashBranch(int TABLE_SIZE);
void liberaHashBranch(Hash_Branch *ha);

// Funcoes de insercao, busca e remocao na tabela hash com colisao (enderecamento aberto) 
int insereHash_EnderAbertoBranch(Hash_Branch *ha, Branch br);
Branch *buscaHash_EnderAbertoBranch(Hash_Branch *ha, char *nome);
int removeHash_EnderAbertoBranch(Hash_Branch *ha, char *nome);

// Funcoes auxiliares
void imprimeHashBranch(Hash_Branch *ha);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//(Hash_No)

// Funcoes para manipulacao da tabela hash com enderecamento aberto 
Hash_No* criaHashNo(int TABLE_SIZE);
void liberaHashNo(Hash_No *ha);

// Funcoes de insercao, busca e remocao na tabela hash com colisao (enderecamento aberto)
int insereHash_EnderAbertoNo(Hash_No *ha, No no);
No *buscaHash_EnderAbertoNo(Hash_No *ha, char *hash);
int removeHash_EnderAbertoNo(Hash_No *ha, char *hash);

// Funcoes auxiliares
void imprimeHashNo(Hash_No *ha);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Funcoes hash
int chaveDivisao(int chave, int TABLE_SIZE);
int chaveMultiplicacao(int chave, int TABLE_SIZE);
int chaveDobra(int chave, int TABLE_SIZE);

// Converter string para int
int valorString(char *str);

// Funcoes de sondagem
int sondagemLinear(int pos, int i, int TABLE_SIZE);
int sondagemQuadratica(int pos, int i, int TABLE_SIZE);
int duploHash(int H1, int chave, int i, int TABLE_SIZE);

