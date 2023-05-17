#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// Adicionado para o toupper
#include <ctype.h>

// Adicionando a estrutura de aluno
#include "aluno.h"

/* Define a porta do servidor */
#define PORT 4242

/* Tamanho do Buffer */
#define BUFFER_LENGTH 4096

/*
 * Execução principal do programa servidor do protocolo simples
 */
int main(void)
{

    // Criando uma lista encadeada de alunos
    ListaAlunos *lista = NULL;

    // Criando alunos
    printf("Criando alunos...\n");
    Aluno *al1 = criaAluno(1, "Aluno 1", 10, 10, 10);
    Aluno *al2 = criaAluno(2, "Aluno 2", 9, 9, 9);

    // Inserindo alunos na lista
    printf("Inserindo alunos na lista...\n");
    inserirAlunoLista(&lista, *al1);
    inserirAlunoLista(&lista, *al2);

    // Imprimindo a lista de alunos
    printf("Lista de alunos:\n");
    imprimeListaAlunos(lista);

    printf("Abrindo socket do servidor...\n");

    /* Estruturas de soquete do cliente e do servidor */
    struct sockaddr_in client, server;

    /* Descritores de arquivo de cliente e servidor */
    int serverfd, clientfd;

    char buffer[BUFFER_LENGTH];

    while (1)
    {

        fprintf(stdout, "Iniciando o Servidor\n");

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
        strcpy(buffer, "Olá, cliente!\n\0");

        /* Envia a mensagem para o cliente */
        if (send(clientfd, buffer, strlen(buffer), 0))
        {
            fprintf(stdout, "Cliente conectado.\nAguardando mensagem do cliente ...\n");

            /* Comunica com o cliente até receber a mensagem "bye" */
            do
            {

                /* Zera o buffer */
                memset(buffer, 0x0, BUFFER_LENGTH);

                // Receber os dados do cliente
                int received_bytes = recv(clientfd, buffer, BUFFER_LENGTH, 0);
                if (received_bytes == -1)
                {
                    perror("Falha ao receber dados do cliente");
                    break;
                }

                if (received_bytes == 0)
                {
                    // O cliente encerrou a conexão inesperadamente
                    fprintf(stdout, "Cliente desconectado.\n");
                    break;
                }

                if (strcmp(buffer, "list") == 0)
                {
                    // Envia lista de alunos para o cliente
                    memset(buffer, 0x0, BUFFER_LENGTH);
                    strcpy(buffer, "Lista de alunos atual:\n\n");
                    gravaListaAlunos(lista, buffer);
                    send(clientfd, buffer, strlen(buffer), 0);
                }
                else if (strcmp(buffer, "bye") == 0) {
                    // Mensagem "bye" recebida
                    send(clientfd, "bye", 3, 0);
                }
                else
                {

                    // Tentar interpretar os dados recebidos como uma estrutura Aluno
                    Aluno aluno;
                    if (received_bytes == sizeof(Aluno))
                    {
                        memcpy(&aluno, buffer, sizeof(Aluno));
                        // Imprimir os dados do aluno
                        printf("Dados do aluno recebido:\n");
                        imprimeAluno(&aluno);

                        // Inserir o aluno na lista
                        inserirAlunoLista(&lista, aluno);

                        fprintf(stdout, "Aluno recebido e inserido na lista.\n");
                    }
                    else
                    {
                        // Os dados recebidos não correspondem a uma estrutura Aluno
                        fprintf(stdout, "Dados recebidos não correspondem a uma estrutura Aluno: %s\n", buffer);
                    }

                    // Responder o cliente com a lista de alunos armazenada no servidor
                    memset(buffer, 0x0, BUFFER_LENGTH);
                    strcpy(buffer, "Lista de alunos atual:\n\n");
                    gravaListaAlunos(lista, buffer);

                    // Enviar a resposta para o cliente
                    if (send(clientfd, buffer, strlen(buffer), 0) == -1)
                    {
                        perror("Falha ao enviar resposta para o cliente");
                        break;
                    }
                }

            } while (strcmp(buffer, "bye"));
        }

        /* Fecha a conexão do cliente */
        close(clientfd);

        /* Feche o soquete local */
        close(serverfd);

        printf("Conexão fechada\n\n");
    }
    return EXIT_SUCCESS;
}