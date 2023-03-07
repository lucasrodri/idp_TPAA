/* Programa Exemplo.c */
#include <stdio.h>
#include "STR.h"

int main (void) {
    char str[101], str1[51], str2[51];
    printf("Entre com uma seqüência de caracteres: ");
    scanf("%50[^\n]", str1);
    printf("Primeira string lida: %s\n", str1);
    fflush(stdin); // limpa o buffer do teclado
    printf("Entre com outra seqüência de caracteres: ");
    scanf("%50[^\n]", str2);
    printf("Segunda string lida: %s\n", str2);
    copia(str, str1);
    concatena(str, str2);
    printf("Strings concatenadas: %s\n", str);
    printf("Comprimento total: %d\n",comprimento(str));
    return 0;
}
