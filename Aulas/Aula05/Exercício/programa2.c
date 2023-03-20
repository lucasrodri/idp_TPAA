#include <stdio.h>  
#include <stdlib.h>
#include "pilha.h"

int main() {
    Pilha *pilha = cria();
    int numero;
    printf("Informe um número: ");
    scanf("%d", &numero);
    while (numero > 0) {
        push(pilha, numero);
        printf("Informe um número: ");
        scanf("%d", &numero);
    }
    printf("Percorrendo a Pilha com POP:\n");
    percorrer_com_pop(pilha);
    pilha_libera(pilha);
    return 0;
}