#include <stdio.h>  
#include <stdlib.h>
#include "pilha.h"

int main() {
    Pilha *pilha = cria();
    int numero, resto = 0;
    printf("Informe um número: ");
    scanf("%d", &numero);
    printf("O numero informado foi: %d ", numero);
    int n = numero;
    while (n != 0) {
        resto = n % 2;
        n = n / 2;
        push(pilha, resto);
    }
    printf("\nO número 0d%d em binário é: ", numero);
    printf("0b");
    mostra_binario(pilha);
    pilha_libera(pilha);
    return 0;
}