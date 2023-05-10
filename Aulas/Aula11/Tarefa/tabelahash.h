typedef struct hashEnderAberto {
    int qtd, TABLE_SIZE;
    char *itens;
} Hash;

typedef struct hashEnderSeparado {
    int qtd, TABLE_SIZE;
    Lista **itens;
} HashSeparado;

// Funcoes para manipulacao da tabela hash com enderecamento aberto
Hash* criaHash(int TABLE_SIZE);
void liberaHash(Hash *ha);

// Funcoes para manipulacao da tabela hash com enderecamento separado
HashSeparado* criaHashSeparado(int TABLE_SIZE);
void liberaHashSeparado(HashSeparado *ha);

// Funcoes hash
int chaveDivisao(int chave, int TABLE_SIZE);
int chaveMultiplicacao(int chave, int TABLE_SIZE);
int chaveDobra(int chave, int TABLE_SIZE);

//Minha funcao hash
int hashExercicio(char letra, int TABLE_SIZE);

// Converter string para int
int valorString(char *str);

// Funcoes de sondagem
int sondagemLinear(int pos, int i, int TABLE_SIZE);
int sondagemQuadratica(int pos, int i, int TABLE_SIZE);
int duploHash(int H1, int chave, int i, int TABLE_SIZE);

// Funcoes de insercao, busca e remocao na tabela hash sem colisao
int insereHash_SemColisao(Hash *ha, char letra);
int buscaHash_SemColisao(Hash *ha, char value, char *letra);
int removeHash_SemColisao(Hash *ha, char value);

// Funcoes de insercao, busca e remocao na tabela hash com colisao (enderecamento aberto)
int insereHash_EnderAberto(Hash *ha, char letra);
int buscaHash_EnderAberto(Hash *ha, char value, char *letra);
int removeHash_EnderAberto(Hash *ha, char value);

// Funcoes de insercao, busca e remocao na tabela hash com colisao (enderecamento separado)
int insereHash_EnderSeparado(HashSeparado *ha, char letra);
int buscaHash_EnderSeparado(HashSeparado *ha, char value, char *letra);
int removeHash_EnderSeparado(HashSeparado *ha, char value);

// Funcoes auxiliares
void imprimeHash(Hash *ha);
void imprimeHashSeparado(HashSeparado *ha);



