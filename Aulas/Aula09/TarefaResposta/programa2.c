#include <stdio.h>

// Função que realiza a busca de um elemento em um array
int busca(int arr[], int tam, int x) {
    //Faz a busca binária
    int inicio = 0;
    int fim = tam - 1;
    int meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (arr[meio] == x) {
            return meio;
        } else if (arr[meio] < x) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

int main() {
    int arr[] = {2, 3, 5, 7, 11, 13};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 7;

    int indice = busca(arr, n, x);

    if (indice != -1) {
        printf("Elemento %d encontrado no índice %d\n", x, indice);
    } else {
        printf("Elemento %d não encontrado no array\n", x);
    }

    return 0;
}