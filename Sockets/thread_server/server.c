#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <pthread.h> // Biblioteca para threads

#include <arpa/inet.h> // Biblioteca para inet_ntoa

// Adicionado para o toupper
#include <ctype.h>

/* Define a porta do servidor */
#define PORT 4242

/* Tamanho do Buffer */
#define BUFFER_LENGTH 4096

/*
 * Estrutura para armazenar informações de cliente e servidor
 */
typedef struct
{
    int clientfd;
    struct sockaddr_in client;
} ClientInfo;

/*
 * Função executada por cada thread para lidar com um cliente
 */
void *handleClient(void *arg)
{
    ClientInfo *clientInfo = (ClientInfo *)arg;
    int clientfd = clientInfo->clientfd;
    struct sockaddr_in client = clientInfo->client;

    char buffer[BUFFER_LENGTH];

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

                send(clientfd, response, strlen(response), 0);
            }
        } while (strcmp(buffer, "bye"));

        /* Fecha a conexão do cliente */

        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client.sin_addr), clientIP, INET_ADDRSTRLEN);
        printf("Conexão do cliente  - IP: %s, Porta: %d - encerrada\n", clientIP, ntohs(client.sin_port));
        
        close(clientfd);

        /* Libera a estrutura de informações do cliente */
        free(clientInfo);
    }

    return NULL;
}

/*
 * Execução principal do programa servidor do protocolo simples
 */
int main(void)
{

    /* Estruturas de soquete do cliente e do servidor */
    struct sockaddr_in server;

    /* Descritor de arquivo do servidor */
    int serverfd;

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
    server.sin_addr.s_addr = INADDR_ANY;
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

    while (1)
    {
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        int clientfd = accept(serverfd, (struct sockaddr *)&client, &client_len);
        if (clientfd == -1)
        {
            perror("Erro ao aceitar conexão do cliente:");
            continue;
        }

        fprintf(stdout, "Cliente conectado. Criando uma nova thread...\n");

        /* Cria uma estrutura para armazenar informações do cliente */
        ClientInfo *clientInfo = (ClientInfo *)malloc(sizeof(ClientInfo));
        clientInfo->clientfd = clientfd;
        clientInfo->client = client;

        /* Cria uma nova thread para lidar com o cliente */
        pthread_t tid;
        if (pthread_create(&tid, NULL, handleClient, (void *)clientInfo) != 0)
        {
            perror("Erro ao criar uma nova thread:");
            free(clientInfo);
            close(clientfd);
        }
        else
        {
            char clientIP[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(client.sin_addr), clientIP, INET_ADDRSTRLEN);
            printf("Cliente conectado - IP: %s, Porta: %d\n", clientIP, ntohs(client.sin_port));
        }
    }
    /* Feche o soquete local */
    close(serverfd);

    printf("Conexão fechada\n\n");

    return EXIT_SUCCESS;
}