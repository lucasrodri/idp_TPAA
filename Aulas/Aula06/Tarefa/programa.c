#include <stdio.h>  
#include <stdlib.h>
#include "fila.h"

int main() {
    Fila *f1 = cria();
    Fila *f2 = cria();
    Fila *f3 = cria();
    printf("Enfileirando os número 10, 20, 30, 40 na F1:\n");
    enqueue(f1, 10);
    enqueue(f1, 20);
    enqueue(f1, 30);
    enqueue(f1, 40);
    
    printf("Enfileirando os número 100, 200, 300, 400 na F2:\n");
    enqueue(f2, 100);
    enqueue(f2, 200);
    enqueue(f2, 300);
    enqueue(f2, 400);

    printf("Enfileirando os número 1000, 2000, 3000, 4000 na F3:\n");
    enqueue(f3, 1000);
    enqueue(f3, 2000);
    enqueue(f3, 3000);
    enqueue(f3, 4000);

    printf("Fazendo a intercalação:\n");
    intercala3(f1, f2, f3);
    
    printf("Percorrendo a Fila F1 (sem remover):\n");
    percorrer_fila(f1);

    fila_libera(f1);
    fila_libera(f2);
    fila_libera(f3);
    
    return 0;
}