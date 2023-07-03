#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "git.h"
#include "tabelahash.h"
#include "tools.h"
#include "client.h"

#define TABLE_SIZE 1427
#define LEN 4096

int main() {
    Branch *HEAD;
    // criando uma tabela hash endereçamento aberto de Branches
    Hash_Branch *branches = criaHashBranch(TABLE_SIZE);
    // criando uma tabela hash endereçamento aberto de Nos
    Hash_No *commits = criaHashNo(TABLE_SIZE);   

    int init_first = 0; 

    while(1)
    {
        char entrada[100];
        printf("$ ");
        scanf(" %[^\n]s", entrada);
        getchar(); // Limpa o buffer do teclado

        //printf("Tabela Hash de Branches:\n");
        //imprimeHashBranch(branches);
        //printf("\nTabela Hash de Commits:\n");
        //imprimeHashNo(commits);

        printf("\n");

        switch (shell(entrada))
        {
        case 0:
            {
                printf("Saindo...\n");
                libera(HEAD);
                return 0;
            }
        case -1:
            {
                printf("Comando inválido!\n");
                break;
            }
        case 1:
            {
                if(init_first == 0) {
                    printf("Git nao inicializado!\n");
                    printf("Faça um 'git init' ou 'git pull' para inicializar o git.\n");
                    break;
                }
                //git log
                gitlog(HEAD);
                break;
            }
        case 2:
            {
                if(init_first == 0) {
                    printf("Git nao inicializado!\n");
                    printf("Faça um 'git init' ou 'git pull' para inicializar o git.\n");
                    break;
                }
                //git commit -m "mensagem"
                commit(HEAD, entrada);
                add_no(commits, HEAD->ponteiro);
                break;
            }
        case 3:
            {
                if(init_first == 0) {
                    printf("Git nao inicializado!\n");
                    printf("Faça um 'git init' ou 'git pull' para inicializar o git.\n");
                    break;
                }
                //git branch <nome>
                char nomeBranch[100];
                strcpy(nomeBranch, entrada);
                Branch *novoBranch = gitbranch(HEAD, entrada);
                if (novoBranch != NULL) {
                    add_branch(branches, novoBranch);
                }
                novoBranch = checkout(branches, nomeBranch);
                if (novoBranch != NULL) {
                    HEAD = novoBranch;
                }
                break;
            }
        case 4:
            {
                if(init_first == 0) {
                    printf("Git nao inicializado!\n");
                    printf("Faça um 'git init' ou 'git pull' para inicializar o git.\n");
                    break;
                }
                //git checkout <nome>
                Branch *novoBranch = checkout(branches, entrada);
                if (novoBranch != NULL) {
                    HEAD = novoBranch;
                } else {
                    No *novoNo = checkout_no(commits, entrada);
                    if (novoNo != NULL) {
                        HEAD = (Branch *) malloc(sizeof(Branch));
                        HEAD->ponteiro = novoNo;
                        strcpy(HEAD->nome, entrada);
                    } else {
                        printf("Branch ou commit não existe!\n");
                    }
                }
                break;
            }
        case 5:
            {
                if(init_first == 0) {
                    printf("Git nao inicializado!\n");
                    printf("Faça um 'git init' ou 'git pull' para inicializar o git.\n");
                    break;
                }
                //git merge <nome>
                Branch *novoBranch = checkout(branches, entrada);
                if (novoBranch != NULL) {
                    gitmerge(HEAD);
                    add_no(commits, HEAD->ponteiro);
                } else {
                    printf("Branch não existe!\n");
                }
                break;
            }
        case 6:
            {
                if(init_first == 0) {
                    printf("Git nao inicializado!\n");
                    printf("Faça um 'git init' ou 'git pull' para inicializar o git.\n");
                    break;
                }
                //git push
                int sockfd = inicializa_socket();
                char resp[LEN];
                //Envia o branch pra onde HEAD está apontando
                if (envia_push(sockfd, HEAD, resp, commits)) {
                    printf("%s\n", resp);
                } else {
                    printf("Erro ao enviar push!\n");
                }
                fecha_socket(sockfd);
                break;
            }
        case 7:
            {
                //git pull
                init_first = 1;
                int sockfd = inicializa_socket();
                char resp[LEN];
                //Envia todas as estruturas para o client 
                if (envia_pull(sockfd, resp, &HEAD, branches, commits)) {
                    printf("%s\n", resp);
                } else {
                    printf("Erro ao enviar pull!\n");
                }
                fecha_socket(sockfd);
                break;
            }
        case 8:
            {
                //git init
                init_first = 1;
                Branch *master = cria();
                //Adiciona o branch master na lista de branches
                add_branch(branches, master);
                Branch *novoBranch = checkout(branches, "master");
                if (novoBranch != NULL) {
                    HEAD = novoBranch;
                }
                //Adiciona o primeiro commit na lista de commits
                add_no(commits, HEAD->ponteiro);
                break;
            }
        default:
            break;
        }
    }
}