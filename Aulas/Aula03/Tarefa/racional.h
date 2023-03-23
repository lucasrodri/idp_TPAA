typedef struct racional {
    int numerador;
    int denominador;
} Racional;

Racional cria (int numerador, int denominador);
Racional soma (Racional r1, Racional r2);
Racional multiplica (Racional r1, Racional r2);
int iguais (Racional r1, Racional r2);