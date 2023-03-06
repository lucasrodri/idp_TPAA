/* Programa Exemplo.c */
#include <stdio.h>
#include "STR.h"

int main (void) {
    char str[101], str1[51], str2[51];
    printf("Entre com uma seqüência de caracteres: ");
    scanf(" %50s[^\n]", str1);
    printf("Entre com outra seqüência de caracteres: ");
    scanf(" %50s[^\n]", str2);
    copia(str, str1);
    concatena(str, str2);
    printf("Comprimento total: %d\n",comprimento(str));
    return 0;
}
