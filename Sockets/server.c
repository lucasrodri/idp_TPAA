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

/* Define a porta do servidor */
#define PORT 4242

/* Tamanho do Buffer */
#define BUFFER_LENGTH 4096

/*
 * Execução principal do programa servidor do protocolo simples
 */
int main(void)
{

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

                /* Recebe a mensagem do cliente */
                int message_len;
                if ((message_len = recv(clientfd, buffer, BUFFER_LENGTH, 0)) > 0)
                {
                    buffer[message_len - 1] = '\0';
                    printf("Cliente diz: %s\n", buffer);
                }

                /* 'bye' message finishes the connection */
                if (strcmp(buffer, "bye") == 0)
                {
                    send(clientfd, "bye", 3, 0);
                }
                else
                {
                    // Respondendo o cliente com a mesma mensagem recebida em caixa alta
                    for (int i = 0; i < strlen(buffer); i++)
                    {
                        buffer[i] = toupper(buffer[i]);
                    }

                    // Concatena a mensagem em caixa alta com a mensagem "yep" e uma nova linha
                    char response[strlen(buffer) + 5];
                    strcpy(response, buffer);
                    strcat(response, "\nyep\n");
                    printf("Servidor diz: %s\n", response);

                    // Como enviar um array de inteiros para o cliente, poderia ser qualquer tipo de dado ou estrutura
                    // Obs.: O Cliente deve saber como tratar os dados recebidos
                    //int arr[] = {1, 2, 3, 4, 5};
                    //send(clientfd, arr, sizeof(arr), 0);

                    send(clientfd, response, strlen(response), 0);
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