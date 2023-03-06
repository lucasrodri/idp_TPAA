/* Programa STR.c */
#include <stdio.h>

// Função para calcular o comprimento de uma string
int comprimento(char* str) {
    int len = 0;
    while (*str) { // enquanto o ponteiro para a string não aponta para o caractere nulo
        len++;
        str++;
    }
    return len;
}

// Função para copiar uma string
void copia(char* dest, char* orig) {
    while (*orig) { // enquanto o ponteiro para a string original não aponta para o caractere nulo
        *dest = *orig;
        dest++;
        orig++;
    }
    *dest = '\0'; // adiciona o caractere nulo no final da string copiada
}

// Função para concatenar duas strings
void concatena(char* dest, char* orig) {
    while (*dest) { // encontra o final da string destino
        dest++;
    }
    while (*orig) { // copia a string origem para o final da string destino
        *dest = *orig;
        dest++;
        orig++;
    }
    *dest = '\0'; // adiciona o caractere nulo no final da nova string
}
