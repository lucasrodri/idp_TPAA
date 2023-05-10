#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "tabelahash.h"

#define TABLE_SIZE 1427

int main() {
    // criando um vetor de chaves
    char chaves[] = {'D', 'Q', 'B', 'I', 'M', 'H', 'G', 'U', 'A', 'C', 'R', 'S'};
    int num_chaves = sizeof(chaves) / sizeof(chaves[0]);

    // criando uma tabela hash endereçamento aberto
    Hash *ha = criaHash(TABLE_SIZE);

    // inserindo as chaves na tabela hash
    for (int i = 0; i < num_chaves; i++) {
        insereHash_EnderAberto(ha, chaves[i]);
    }

    imprimeHash(ha);

    char *buscado = (char*) malloc(sizeof(char));
    if(buscaHash_EnderAberto(ha, 'R', buscado))
        printf("\n\nBuscando o letra 'R': %c\n\n", *buscado);
    else
        printf("\n\nLetra 'R' não encontrada\n\n");

    liberaHash(ha);

    printf("\n\nAgora com enderecamento separado\n\n\n");
    
    printf("Resolvendo o Exercicio do Canvas\n\n");

    //criando uma tabela hash com endereco separado
    HashSeparado *haSeparado = criaHashSeparado(TABLE_SIZE);

    // inserindo as chaves na tabela hash
    for (int i = 0; i < num_chaves; i++) {
        insereHash_EnderSeparado(haSeparado, chaves[i]);
    }

    //Inserindo a letra J
    insereHash_EnderSeparado(haSeparado, 'J');

    imprimeHashSeparado(haSeparado);

    if(buscaHash_EnderSeparado(haSeparado, 'J', buscado))
        printf("\n\nBuscando o letra 'J': %c\n\n", *buscado);
    else
        printf("\n\nLetra 'J' não encontrada\n\n");

    printf("\nA sequencia de letras na tabela hash na posição de J é: D M G A S J\n\n");

    return 0;
}