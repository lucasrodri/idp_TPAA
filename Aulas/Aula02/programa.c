#include <stdio.h>
#include <stdlib.h>

int main(){
    int teste = 10;
    printf("Valor de teste: %d\n", teste);
    printf("Endereço de teste: %p\n", &teste);
    int* pteste = &teste;
    printf("Ponteiro de pteste: %p\n", pteste);
    printf("Valor do Ponteiro de pteste: %d\n", *pteste);
    printf("Endereço do Ponteiro de pteste: %p\n", &pteste);
    return 0;
}