typedef struct hashEnderAberto_Branch Hash_Branch; // Declaração antecipada da estrutura Hash_Branch
typedef struct hashEnderAberto_No Hash_No; // Declaração antecipada da estrutura Hash_No

typedef struct no {
    char hash[9];
    char mensagem[100];
    struct no *ant;
    char ant_hash[9]; //Representa o hash do no anterior
} No;

typedef struct branch {
    char nome[100];
    No *ponteiro;
    char ponteiro_hash[9]; //Representa o hash do no apontado pelo ponteiro
} Branch;

Branch *cria(void);
void libera(Branch *p);
void commit(Branch *p, char mensagem[]);
void gitlog(Branch *p);
Branch *gitbranch(Branch *p, char nome[]);

void add_branch(Hash_Branch *branches, Branch *branch);
Branch *checkout(Hash_Branch *branches, char nome[]);

void gitmerge(Branch *p);

void add_no(Hash_No *nos, No *no);
No *checkout_no(Hash_No *nos, char hash[]);