#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno {
    char nome[50];
    int matricula;
    float notas[3];
} Aluno;

void imprimir_aluno(Aluno *aluno) {
    printf("Nome: %s\n", aluno->nome);
    printf("Matricula: %d\n", aluno->matricula);
    printf("Nota 1: %.2f\n", aluno->notas[0]);
    printf("Nota 2: %.2f\n", aluno->notas[1]);
    printf("Nota 3: %.2f\n", aluno->notas[2]);
}

void imprimir_vetor_alunos(Aluno *alunos) {
    printf("\nImprimindo Alunos: \n\n");
    for (int i = 0; i < 3; i++)
    {
        imprimir_aluno(&alunos[i]);
        printf("\n");
    }
}

Aluno criar_aluno(char nome[], int matricula, float notas[]) {
    Aluno novo_aluno;
    strcpy(novo_aluno.nome, nome);
    novo_aluno.matricula = matricula;
    for (int i = 0; i < 3; i++) {
        novo_aluno.notas[i] = notas[i];
    }
    return novo_aluno;
}

int main(){
    Aluno aluno1;
    strcpy(aluno1.nome, "João");
    aluno1.matricula = 12345;
    aluno1.notas[0] = 7.5;
    aluno1.notas[1] = 8.0;
    aluno1.notas[2] = 6.5;
    imprimir_aluno(&aluno1);
    //Outra forma:
    float notas[3] = {7.5, 8.0, 6.5};
    //Aluno aluno2 = {"João", 12345, {notas[0], notas[1], notas[2]}};
    //ou
    Aluno aluno2 = {"João", 12345, {7.5, 8.0, 6.5}};
    imprimir_aluno(&aluno2);
    //ou
    char nome[50] = "João";
    //Aluno aluno3 = criar_aluno("João", 12345, notas);
    Aluno aluno3 = criar_aluno(nome, 12345, notas);
    imprimir_aluno(&aluno3);
    //Vetor de  estrutura
    Aluno alunos[3];
    alunos[0] = criar_aluno("João", 12345, notas);
    alunos[1] = criar_aluno("Lucas", 54321, notas);
    alunos[2] = criar_aluno("Victor", 15975, notas);
    printf("\nImprimindo Alunos: \n\n");
    for (int i = 0; i < 3; i++)
    {
        imprimir_aluno(&alunos[i]);
        printf("\n");
    }
    printf("\nImprimindo Vetor de Alunos: \n\n");
    imprimir_vetor_alunos(alunos);
    //Copiando estrutura
    Aluno a1,a2;
    a1 = criar_aluno("João", 12345, notas);
    a2 = a1;
    imprimir_aluno(&a1);
    imprimir_aluno(&a2);
    a2.matricula = 111;
    imprimir_aluno(&a1);
    imprimir_aluno(&a2);
    return 0;
}