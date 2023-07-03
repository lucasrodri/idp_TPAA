#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "tools.h"

int shell(char *str) {
    // Aloca memória para uma cópia da string de entrada
    char *entrada = (char *) malloc(strlen(str) * 2 * sizeof(char));
    strcpy(entrada, str);

    if(strcmp(entrada, "exit") == 0) {
        //printf("Entrou no exit\n");
        free(entrada);
        return 0;
    } else {
        char *token = strtok(entrada, " ");
        //git <>
        token = strtok(NULL, " ");
        if(token != NULL && strcmp(token, "commit") == 0) {
            //printf("Entrou no commit\n");
            //git commit -m "mensagem"
            token = strtok(NULL, " ");
            if (token != NULL && strcmp(token, "-m") == 0) {
                token = strtok(NULL, "\"");
                if (token == NULL) {
                    //Comando inválido!
                    free(entrada);
                    return -1;
                }
                strcpy(str, token);
                free(entrada);
                return 2;
            }
            else {
                //Comando inválido!
                free(entrada);
                return -1;
            }
        } else {
            if(token != NULL && strcmp(token, "branch") == 0) {
                //printf("Entrou no branch\n");
                //git branch <nome>
                token = strtok(NULL, " ");
                if (token == NULL) {
                    //Comando inválido!
                    free(entrada);
                    return -1;
                }
                strcpy(str, token);
                free(entrada);
                return 3;
            } else {
                if(token != NULL && strcmp(token, "checkout") == 0) {
                    //printf("Entrou no checkout\n");
                    //git checkout <nome>
                    token = strtok(NULL, " ");
                    if (token == NULL) {
                        //Comando inválido!
                        free(entrada);
                        return -1;
                    }
                    strcpy(str, token);
                    free(entrada);
                    return 4;
                } else {
                    if(token != NULL && strcmp(token, "log") == 0) {
                        //printf("Entrou no log\n");
                        free(entrada);
                        return 1;
                    } else {
                        if(token != NULL && strcmp(token, "merge") == 0) {
                            //printf("Entrou no merge\n");
                            //git merge <branch>
                            token = strtok(NULL, " ");
                            if (token == NULL) {
                                //Comando inválido!
                                free(entrada);
                                return -1;
                            }
                            strcpy(str, token);
                            free(entrada);
                            return 5;
                        } else {
                            //Comando inválido!
                            //printf("Entrou no comando inválido\n");
                            free(entrada);
                            return -1;
                        }
                    }
                }
            }
        }
    }
}
