typedef struct no {
    char hash[9];
    char mensagem[100];
    struct no *ant;
} No;

typedef struct branch {
    char nome[100];
    No *ponteiro;
} Branch;

//Criando um vetor dinamico de Branch
typedef struct vetor {
    Branch *vetor;
    int tamanho;
} Branches;

//Criando um vetor dinamico de Nos
typedef struct vetorNo {
    No *vetor;
    int tamanho;
} Commits;

Branch *cria(void);
void libera(Branch *p);
void commit(Branch *p, char mensagem[]);
void gitlog(Branch *p);
Branch *gitbranch(Branch *p, char nome[]);
void add_branch(Branches *branches, Branch *branch);
Branch *checkout(Branches *branches, char nome[]);
void gitmerge(Branch *p);
void add_no(Commits *nos, No *no);
No *checkout_no(Commits *nos, char hash[]);