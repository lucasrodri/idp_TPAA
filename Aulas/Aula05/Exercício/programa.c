#include <stdio.h>  
#include <stdlib.h>
#include "pilha.h"

int main() {
    Pilha *pilha = cria();
    //TODO: Faça o Ex1
    
    //Mostrando o número binario
    printf("\nO número digitado em binário é: ");
    printf("0b");
    mostra_binario(pilha);
    pilha_libera(pilha);
    return 0;
}