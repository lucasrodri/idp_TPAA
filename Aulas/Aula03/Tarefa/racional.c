#include <stdlib.h> /* malloc, free, exit */
#include <stdio.h> /* printf */
#include "racional.h"

//Calculando MMC
int mmc(int n1, int n2) {
    for(int i = 2; i <= n1*n2; i++){
        if(i % n1 == 0 && i % n2 == 0) {
            return i;
        }
    }
    return n1*n2;
}

Racional cria(int numerador, int denominador) {
    Racional r;
    if(denominador == 0) {
        printf("Denominador não pode ser 0\n");
        exit(1);
    }
    r.numerador = numerador;
    r.denominador = denominador;
    return r;
}

Racional soma(Racional r1, Racional r2) {
    Racional r;
    r.denominador = mmc(r1.denominador, r2.denominador);
    r.numerador = ((r.denominador/r1.denominador)*r1.numerador) + ((r.denominador/r2.denominador)*r2.numerador);
    return r;
}

Racional multiplica(Racional r1, Racional r2) {
    Racional r;
    r.numerador = r1.numerador * r2.numerador;
    r.denominador = r1.denominador * r2.denominador;
    return r;
}

int iguais(Racional r1, Racional r2) {
    return r1.numerador * r2.denominador == r2.numerador * r1.denominador;
}
