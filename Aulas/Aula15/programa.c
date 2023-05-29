#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreb.h"


int main() {
    ArvBin* raiz = cria_ArvBin();
    
    libera_ArvBin(raiz);
    return 0;
}


