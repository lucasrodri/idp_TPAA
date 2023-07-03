#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Adicionando a estrutura git e a tabela hash
#include "git.h"
#include "tabelahash.h"

#include "client.h"

/* Define a porta do servidor */
#define PORT 4242

/* Tamanho dos buffers dos sockets */
#define BUFFER_LENGTH 4096

/* Endereço do servidor */
#define SERVER_ADDR "127.0.0.1"


int envia_push(int sockfd, Branch *branch, char *resp, Hash_No *commits) {
    int slen;
    char buffer[BUFFER_LENGTH];
    //Envia a mensagem PUSH_BRANCH para o servidor
    send(sockfd, "PUSH_BRANCH", sizeof("PUSH_BRANCH"), 0);
    //Espera a resposta PUSH_BRANCH_OK do servidor
    memset(buffer, 0x0, BUFFER_LENGTH);
    if ((slen = recv(sockfd, buffer, BUFFER_LENGTH, 0)) > 0)
    {   
        if (strcmp(buffer, "PUSH_BRANCH_OK") == 0) {
            //Envia o branch para o servidor
            send(sockfd, branch, sizeof(Branch), 0);
            //Espera a resposta PUSH_BRANCH_OK do servidor para enviar os nos
            memset(buffer, 0x0, BUFFER_LENGTH);
            if ((slen = recv(sockfd, buffer, BUFFER_LENGTH, 0)) > 0) {
                if (strcmp(buffer, "PUSH_BRANCH_OK") == 0) {
                    //Envia os nos para o servidor
                    No *no = branch->ponteiro;
                    send(sockfd, no, sizeof(No), 0);
                    //Enquanto nao receber PUSH_NO_OK do servidor, envia os nos
                    while (strcmp(buffer, "PUSH_NO_OK") != 0) {
                        memset(buffer, 0x0, BUFFER_LENGTH);
                        if ((slen = recv(sockfd, buffer, BUFFER_LENGTH, 0)) > 0) {
                            //Se receber PULL_NO + o hash retorna o no com o hash
                            if (strncmp(buffer, "PULL_NO", 7) == 0) {
                                char *hash = strtok(buffer, " ");
                                hash = strtok(NULL, " ");
                                No *no = checkout_no(commits, hash);
                                send(sockfd, no, sizeof(No), 0);
                            }
                        } 
                    }
                } else {
                    printf("Erro no PROTOCOLO PUSH_BRANCH\n");
                    return 0;
                }
            } else {
                printf("Erro no PROTOCOLO PUSH_BRANCH\n");
                return 0;
            }
        } else {
            printf("Erro no PROTOCOLO PUSH_BRANCH\n");
            return 0;
        }
    } else {
        printf("Erro no PROTOCOLO PUSH_BRANCH\n");
        return 0;
    }
    //preenche o resp com uma resposta qualquer
    strcpy(resp, "PUSH_BRANCH_OK");
    return 1;
}

//Função recursiva buscaNo
No *buscaNo(int sockfd, Hash_No *commits, char *hash) {
    if (strcmp(hash, "") == 0) {
        return NULL;
    }
    int received_bytes;
    No no_recv;
    No *no;
    no = checkout_no(commits, hash);
    if (no != NULL) {
        return no;
    } else {
        //Envia ao servidor o hash do no anterior para que o servidor possa buscar o no anterior
        char buffer[BUFFER_LENGTH];
        memset(buffer, 0x0, BUFFER_LENGTH);
        //mandar a mensagem PULL_NO + o hash
        sprintf(buffer, "PULL_NO %s", hash);
        //print do buffer
        send(sockfd, buffer, sizeof(buffer), 0);
        //Recebe o no anterior
        memset(buffer, 0x0, BUFFER_LENGTH);
        received_bytes = recv(sockfd, buffer, BUFFER_LENGTH, 0);
        if (received_bytes == -1) {
            perror("recv");
            exit(1);
        }
        // Tentar interpretar os dados recebidos como uma estrutura No
        if (received_bytes == sizeof(No))
        {
            memcpy(&no_recv, buffer, sizeof(No));
            no = (No *) malloc(sizeof(No));
            if (no == NULL) {
                printf("Memória insuficiente!\n");
                exit(1);
            }
            strcpy(no->hash, no_recv.hash);
            strcpy(no->mensagem, no_recv.mensagem);
            strcpy(no->ant_hash, no_recv.ant_hash);
            no->ant = buscaNo(sockfd, commits, no->ant_hash);
            add_no(commits, no);
        } else {
            printf("Erro ao receber o no anterior!\n");
            exit(1);
        }
        return no;   
    }
}

int envia_pull(int sockfd, char *resp, Branch **HEAD, Hash_Branch *branches, Hash_No *commits) {
    int slen;
    char buffer[BUFFER_LENGTH];
    //Envia a mensagem PULL_BRANCH para o servidor
    send(sockfd, "PULL_BRANCH", sizeof("PULL_BRANCH"), 0);
    //Espera a resposta PULL_BRANCH_OK do servidor
    memset(buffer, 0x0, BUFFER_LENGTH);
    if ((slen = recv(sockfd, buffer, BUFFER_LENGTH, 0)) > 0)
    {   
        if (strcmp(buffer, "PULL_BRANCH_OK") == 0) {
            //Envia PULL_REQUEST para o servidor
            send(sockfd, "PULL_REQUEST", sizeof("PULL_REQUEST"), 0);
            //Espera a estrutura branch que o HEAD do servidor aponta
            Branch branch_recv;
            Branch *branch;
            memset(buffer, 0x0, BUFFER_LENGTH);
            slen = recv(sockfd, buffer, BUFFER_LENGTH, 0);
            if (slen == -1) {
                perror("recv");
                return EXIT_FAILURE;
            }
            memcpy(&branch_recv, buffer, sizeof(Branch));
            //Procura o branch na tabela hash
            branch = checkout(branches, branch_recv.nome);
            if (branch == NULL) {
                //Branch não encontrado, cria o branch
                branch = gitbranch(NULL, branch_recv.nome);

                // Copia o ponteiro_hash para o ponteiro_hash do branch
                strcpy(branch->ponteiro_hash, branch_recv.ponteiro_hash);
                if (branch != NULL) {
                    //Aponta o HEAD para o branch criado
                    *HEAD = branch;
                }
            } else {
                //Branch encontrado, aponta o HEAD para o branch
                *HEAD = branch;
            }
            //Envia ao servidor que recebeu a branch
            send(sockfd, "PULL_BRANCH_OK", sizeof("PULL_BRANCH_OK"), 0);

            No no_recv;
            No *no;
            //Recebe a estrutura do No (ultimo no do branch)
            memset(buffer, 0x0, BUFFER_LENGTH);
            slen = recv(sockfd, buffer, BUFFER_LENGTH, 0);
            if (slen == -1) {
                perror("recv");
                return EXIT_FAILURE;
            }
            // Tentar interpretar os dados recebidos como uma estrutura No
            if (slen == sizeof(No))
            {
                memcpy(&no_recv, buffer, sizeof(No));
                // procura o no nos commits
                no = checkout_no(commits, no_recv.hash);
                if (no == NULL) {
                    //No não encontrado, cria o no
                    no = (No *) malloc(sizeof(No));
                    if (no == NULL) {
                        printf("Memória insuficiente!\n");
                        exit(1);
                    }
                    strcpy(no->hash, no_recv.hash);
                    strcpy(no->mensagem, no_recv.mensagem);
                    strcpy(no->ant_hash, no_recv.ant_hash);
                    //Busca o no anterior
                    no->ant = buscaNo(sockfd, commits, no->ant_hash);

                    //Envia ao cliente que o no foi criado finaliza o push
                    //Tive que mudar aqui e colocar o OK antes pq la eu compara as primeira 7 letras
                    send(sockfd, "OK_PULL_NO", sizeof("OK_PULL_NO"), 0);
                    
                    add_no(commits, no);
                    //Aponta o ponteiro do branch para o no
                    branch->ponteiro = no;
                } else {
                    //No encontrado, aponta o ponteiro do branch para o no
                    branch->ponteiro = no;
                    send(sockfd, "OK_PULL_NO", sizeof("OK_PULL_NO"), 0);
                }
                //Adiciona o branch na lista de branches
                add_branch(branches, branch);
            } else {
                printf("Erro ao receber o no!\n");
                exit(1);
            }
        } else {
            printf("Erro no PROTOCOLO PULL_BRANCH\n");
            return 0;
        }
    } else {
        printf("Erro no PROTOCOLO PULL_BRANCH\n");
        return 0;
    }
    //preenche o resp com uma resposta qualquer
    strcpy(resp, "PULL_BRANCH_OK");
    gitlog(*HEAD);
    return 1;
}

/*
 * Execução principal do programa cliente do nosso protocolo simples
 */
int inicializa_socket() {

    /* Socket do servidor */
    struct sockaddr_in server;
    /* Descritor de arquivo do cliente para o socket local */
    int sockfd;

    int len = sizeof(server);
    int slen;

    /* Buffer de recebimento */
    char buffer_in[BUFFER_LENGTH];
    /* Buffer de envio */
    char buffer_out[BUFFER_LENGTH];

    //fprintf(stdout, "Iniciando Cliente ...\n");

    /*
     * Cria um socket para o cliente
     */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Erro na criação do socket do cliente:");
        return EXIT_FAILURE;
    }
    //fprintf(stdout, "Socket do cliente criado com fd: %d\n", sockfd);

    /* Define as propriedades da conexão */
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    memset(server.sin_zero, 0x0, 8);

    /* Tenta se conectar ao servidor */
    if (connect(sockfd, (struct sockaddr *)&server, len) == -1)
    {
        perror("Não é possível conectar ao servidor");
        return EXIT_FAILURE;
    }

    /* Recebe a mensagem de apresentação do servidor */
    if ((slen = recv(sockfd, buffer_in, BUFFER_LENGTH, 0)) > 0)
    {
        buffer_in[slen + 1] = '\0';
        //fprintf(stdout, "O servidor diz: %s\n", buffer_in);
    }
    return sockfd;

}
    
int fecha_socket(int sockfd) {
    /* Fecha a conexão com o servidor */
    close(sockfd);
    //fprintf(stdout, "\nConexão fechada\n\n");
    return EXIT_SUCCESS;
}