#include <stdio.h>  
#include <stdlib.h>
#include "racional.h"

int main(int argc, char *argv[]) {
    Racional r1 = cria(2,4);
    Racional r2 = cria(4,2);
    Racional r3 = cria(1,2);

    Racional sum = soma(r1,r2);
    Racional mult = multiplica(r1,r2);
    int eq = iguais(r1,r3);

    printf("A soma é %d/%d\n", sum.numerador, sum.denominador);
    printf("A multiplicação é %d/%d\n", mult.numerador, mult.denominador);
    if(eq == 1){
        printf("Os números são iguais\n");
    } else {
        printf("Os números não são iguais\n");
    }

    return 0;
}
