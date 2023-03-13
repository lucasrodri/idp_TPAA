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
    //TODO: ex1
    printf("\nO número %d em binário é:\n", numero);
    printf("0b");
    mostra_binario(pilha);
    pilha_libera(pilha);
    return 0;
}