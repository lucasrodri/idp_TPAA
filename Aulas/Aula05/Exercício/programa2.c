#include <stdio.h>  
#include <stdlib.h>
#include "pilha.h"

int main() {
    Pilha *pilha = cria();
    //TODO: Faça o Ex2
    
    //Percorrendo a pilha
    printf("Percorrendo a Pilha com POP:\n");
    percorrer_com_pop(pilha);
    pilha_libera(pilha);
    return 0;
}