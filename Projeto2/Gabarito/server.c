#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// Adicionando a estrutura git e a tabela hash
#include "git.h"
#include "tabelahash.h"

/* Define a porta do servidor */
#define PORT 4242

/* Tamanho do Buffer */
#define BUFFER_LENGTH 4096

#define TABLE_SIZE 1427

//Função recursiva buscaNo
No *buscaNo(int clientfd, Hash_No *commits, char *hash) {
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
        //Envia ao cliente o hash do no anterior para que o cliente possa buscar o no anterior
        char buffer[BUFFER_LENGTH];
        memset(buffer, 0x0, BUFFER_LENGTH);
        //mandar a mensagem PULL_NO + o hash
        sprintf(buffer, "PULL_NO %s", hash);
        send(clientfd, buffer, sizeof(buffer), 0);
        //Recebe o no anterior
        memset(buffer, 0x0, BUFFER_LENGTH);
        received_bytes = recv(clientfd, buffer, BUFFER_LENGTH, 0);
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
            no->ant = buscaNo(clientfd, commits, no->ant_hash);
            add_no(commits, no);
        } else {
            printf("Erro ao receber o no anterior!\n");
            exit(1);
        }
        return no;   
    }
}

int push(int clientfd, int received_bytes, char *buffer, Branch **HEAD, Hash_Branch *branches, Hash_No *commits) {
    if (received_bytes == -1) {
        perror("recv");
        return EXIT_FAILURE;
    }
    // Tentar interpretar os dados recebidos como uma estrutura Branch
    Branch branch_recv;
    Branch *branch;
    if (received_bytes == sizeof(Branch))
    {
        memcpy(&branch_recv, buffer, sizeof(Branch));
        //Procura o branch na tabela hash
        branch = checkout(branches, branch_recv.nome);
        if (branch == NULL) {
            //Branch não encontrado, cria o branch
            branch = gitbranch(NULL, branch_recv.nome);
            //Adiciona o branch na lista de branches
            add_branch(branches, branch);
            // Copia o ponteiro_hash para o ponteiro_hash do branch
            strcpy(branch->ponteiro_hash, branch_recv.ponteiro_hash);
            if (branch != NULL) {
                //Aponta o HEAD para o branch criado
                *HEAD = branch;
            }
        } else {
            //Branch encontrado, aponta o *HEAD para o branch
            *HEAD = branch;
        }
    } else {
        printf("Erro ao receber o branch!\n");
        exit(1);
    }
    //Envia ao cliente que o branch foi criado ou que o checkout foi feito
    send(clientfd, "PUSH_BRANCH_OK", sizeof("PUSH_BRANCH_OK"), 0);
    
    No no_recv;
    No *no;
    //Recebe a estrutura do No (ultimo no do branch)
    memset(buffer, 0x0, BUFFER_LENGTH);
    received_bytes = recv(clientfd, buffer, BUFFER_LENGTH, 0);
    if (received_bytes == -1) {
        perror("recv");
        return EXIT_FAILURE;
    }
    // Tentar interpretar os dados recebidos como uma estrutura No
    if (received_bytes == sizeof(No))
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
            //mostrando elementos do no
            no->ant = buscaNo(clientfd, commits, no->ant_hash);

            //Envia ao cliente que o no foi criado finaliza o push
            send(clientfd, "PUSH_NO_OK", sizeof("PUSH_NO_OK"), 0);
            
            add_no(commits, no);
            //Aponta o ponteiro do branch para o no
            branch->ponteiro = no;
        } else {
            //No encontrado, aponta o ponteiro do branch para o no
            branch->ponteiro = no;
            send(clientfd, "PUSH_NO_OK", sizeof("PUSH_NO_OK"), 0);
        }
    } else {
        printf("Erro ao receber o no!\n");
        exit(1);
    }
    printf("Push realizado com sucesso!\n\n");
    gitlog(*HEAD);
    return 1;
}

int pull(int clientfd, int received_bytes, char *buffer, Branch *branch, Hash_No *commits) {
    if (received_bytes == -1) {
        perror("recv");
        return EXIT_FAILURE;
    }
    if (strcmp(buffer, "PULL_REQUEST") == 0) {
        //Envia ao cliente a estrutura do branch
        send(clientfd, branch, sizeof(Branch), 0);
        //Recebe a resposta do cliente
        memset(buffer, 0x0, BUFFER_LENGTH);
        received_bytes = recv(clientfd, buffer, BUFFER_LENGTH, 0);
        if (received_bytes == -1) {
            perror("recv");
            return EXIT_FAILURE;
        }
        if (strcmp(buffer, "PULL_BRANCH_OK") == 0) {
            //Envia os nos para o cliente
            No *no = branch->ponteiro;
            send(clientfd, no, sizeof(No), 0);
            //Enquanto nao receber OK_PULL_NO do servidor, envia os nos
            while (strcmp(buffer, "OK_PULL_NO") != 0) {
                memset(buffer, 0x0, BUFFER_LENGTH);
                if ((received_bytes = recv(clientfd, buffer, BUFFER_LENGTH, 0)) > 0) {
                    //Se receber PULL_NO + o hash retorna o no com o hash
                    if (strncmp(buffer, "PULL_NO", 7) == 0) {
                        char *hash = strtok(buffer, " ");
                        hash = strtok(NULL, " ");
                        No *no = checkout_no(commits, hash);
                        send(clientfd, no, sizeof(No), 0);
                    }
                } 
            }
        } else {
            printf("Erro no PROTOCOLO PULL_BRANCH\n");
            return 0;
        } 
    } else {
        printf("Erro no PROTOCOLO PULL_REQUEST\n");
        return 0;
    }
    printf("Pull realizado com sucesso!\n\n");
    return 1;
}

/*
 * Execução principal do programa servidor do protocolo simples
 */
int main(void)
{
    printf("Iniciando o servidor...\n");
    printf("Criando estruturas de dados...\n");
    
    // Criando a estrutura do git
    Branch *HEAD;
    // criando uma tabela hash endereçamento aberto de Branches
    Hash_Branch *branches = criaHashBranch(TABLE_SIZE);
    // criando uma tabela hash endereçamento aberto de Nos
    Hash_No *commits = criaHashNo(TABLE_SIZE);  

    printf("Abrindo socket do servidor...\n");

    /* Estruturas de soquete do cliente e do servidor */
    struct sockaddr_in client, server;

    /* Descritores de arquivo de cliente e servidor */
    int serverfd, clientfd;

    char buffer[BUFFER_LENGTH];

    fprintf(stdout, "Iniciando o Servidor\n");
    
    while (1)
    {

        /* Cria um soquete IPv4 TCP */
        serverfd = socket(AF_INET, SOCK_STREAM, 0);
        if (serverfd == -1)
        {
            perror("Não foi possível criar o soquete do servidor:");
            return EXIT_FAILURE;
        }
        fprintf(stdout, "Soquete do servidor criado com fd: %d\n", serverfd);

        /* Define as propriedades do soquete do servidor */
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);
        memset(server.sin_zero, 0x0, 8);

        /* Manipula o erro de porta já em uso */
        int yes = 1;
        if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR,
                       &yes, sizeof(int)) == -1)
        {
            perror("Erro nas opções do soquete:");
            return EXIT_FAILURE;
        }

        /* Associa o soquete a uma porta */
        if (bind(serverfd, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
            perror("Erro ao associar o soquete:");
            return EXIT_FAILURE;
        }

        /* Começa a esperar conexões de clientes */
        if (listen(serverfd, 1) == -1)
        {
            perror("Erro na espera de conexões:");
            return EXIT_FAILURE;
        }
        fprintf(stdout, "Ouvindo na porta %d\n", PORT);

        socklen_t client_len = sizeof(client);
        if ((clientfd = accept(serverfd,
                               (struct sockaddr *)&client, &client_len)) == -1)
        {
            perror("Erro ao aceitar conexão do cliente:");
            return EXIT_FAILURE;
        }

        /* Copia para o buffer a mensagem de boas-vindas */
        strcpy(buffer, "Hello\0");

        /* Envia a mensagem para o cliente */
        if (send(clientfd, buffer, strlen(buffer), 0))
        {
            fprintf(stdout, "Cliente conectado.\nAguardando mensagem do cliente ...\n");

            /* Zera o buffer */
            memset(buffer, 0x0, BUFFER_LENGTH);

            // Receber os dados do cliente
            int received_bytes = recv(clientfd, buffer, BUFFER_LENGTH, 0);
            if (received_bytes == -1)
            {
                perror("Falha ao receber dados do cliente");
            }

            if (received_bytes == 0)
            {
                // O cliente encerrou a conexão inesperadamente
                fprintf(stdout, "Cliente desconectado.\n");
            }

            if (strcmp(buffer, "PUSH_BRANCH") == 0)
            {
                memset(buffer, 0x0, BUFFER_LENGTH);
                printf("Recebendo push do cliente...\n");
                send(clientfd, "PUSH_BRANCH_OK", sizeof("PUSH_BRANCH_OK"), 0);
                memset(buffer, 0x0, BUFFER_LENGTH);
                //Recebe o branch
                received_bytes = recv(clientfd, buffer, BUFFER_LENGTH, 0);
                if (received_bytes == -1) {
                    perror("recv");
                    return EXIT_FAILURE;
                }
                push(clientfd, received_bytes, buffer, &HEAD, branches, commits);
            }
            else if (strcmp(buffer, "PULL_BRANCH") == 0)
            {
                memset(buffer, 0x0, BUFFER_LENGTH);
                printf("Recebendo pull do cliente...\n");
                send(clientfd, "PULL_BRANCH_OK", sizeof("PULL_BRANCH_OK"), 0);
                memset(buffer, 0x0, BUFFER_LENGTH);
                received_bytes = recv(clientfd, buffer, BUFFER_LENGTH, 0);
                pull(clientfd, received_bytes, buffer, HEAD, commits);
            }

        }

        /* Fecha a conexão do cliente */
        close(clientfd);

        /* Feche o soquete local */
        close(serverfd);

        printf("Conexão fechada\n\n");
    }
    return EXIT_SUCCESS;
}