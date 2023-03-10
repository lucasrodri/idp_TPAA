#include <stdio.h>  
#include <stdlib.h>
#include "matriz.h"

int main(int argc, char *argv[]) {
    float a,b,c,d;
    Matriz *M;

    // criação de uma matriz  
    M = cria(5,5);

    // inserção de valores na matriz
    atribui(M,0,0,100);
    atribui(M,0,1,200);
    atribui(M,0,2,300);
    atribui(M,0,3,400);
    atribui(M,0,4,500);
    atribui(M,1,2,40);
    atribui(M,2,3,3);
    atribui(M,3,4,15);
    atribui(M,4,1,22);

    // verificando se a inserção foi feita corretamente  
    a = acessa(M,1,2);
    b = acessa(M,2,3);
    c = acessa(M,3,4);
    d = acessa(M,4,1);

    printf ("M[0][0]: %4.2f \n", acessa(M,0,0));
    printf ("M[1][2]: %4.2f \n", a);
    printf ("M[2][3]: %4.2f \n", b);
    printf ("M[3][4]: %4.2f \n", c);
    printf ("M[4][1]: %4.2f \n", d);
    
    return 0;
}
