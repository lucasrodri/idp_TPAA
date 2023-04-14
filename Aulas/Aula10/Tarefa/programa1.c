//Faça um programa que leia n nomes e ordene-os pelo tamanho utilizando o algoritmo selection sort

#include <stdio.h>
#include <string.h>

void selection_sort(char nomes[][100], int n) {
    //TODO: implementar seu algoritmo de ordenação aqui
}

int main() {
    int n;
    printf("Digite o número de nomes: ");
    scanf("%d", &n);
    getchar();
    char nomes[n][100];
    printf("Digite os nomes:\n");
    for (int i = 0; i < n; i++) {
        scanf("%[^\n]s", nomes[i]);
        getchar();
    }
    selection_sort(nomes, n);
    printf("Nomes ordenados:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", nomes[i]);
    }
    return 0;
}
    
   