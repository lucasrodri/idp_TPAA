#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

int main() {
    Pilha *pilha = cria();
    char frase[1000];//"ESTE EXERCICIO E MUITO FACIL."
    printf("Digite o texto (terminado por ponto): ");
    scanf("%[^\n]s", frase);
    for (int i = 0; i <= strlen(frase); i++) {
        if (frase[i] != ' ' && frase[i] != '.' && frase[i] != '\0') {
            push(pilha,frase[i]);
        } else {
            while (pilha->topo != NULL) {
                printf("%c", pop(pilha)); 
            }
            printf(" ");
        }
    }
    printf("\n");
    pilha_libera(pilha);
    return 0;
}