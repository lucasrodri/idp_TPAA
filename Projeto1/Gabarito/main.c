#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "git.h"
#include "tools.h"

int main() {
    Branch *HEAD;
    Branch *master = cria();
    Branches *branches = (Branches *) malloc(sizeof(Branches));
    Commits *commits = (Commits *) malloc(sizeof(Commits));
    
    //Adiciona o branch master na lista de branches
    add_branch(branches, master);
    Branch *novoBranch = checkout(branches, "master");
    if (novoBranch != NULL) {
        HEAD = novoBranch;
    }

    //Adiciona o primeiro commit na lista de commits
    add_no(commits, HEAD->ponteiro);


    while(1)
    {
        char entrada[100];
        printf("$ ");
        scanf(" %[^\n]s", entrada);
        getchar(); // Limpa o buffer do teclado
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
                //git log
                gitlog(HEAD);
                break;
            }
        case 2:
            {
                //git commit -m "mensagem"
                commit(HEAD, entrada);
                add_no(commits, HEAD->ponteiro);
                break;
            }
        case 3:
            {
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
        default:
            break;
        }
    }
}