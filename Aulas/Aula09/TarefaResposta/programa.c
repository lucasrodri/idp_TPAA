#include <stdio.h>

// Função que realiza a busca de um elemento em um array
int busca(int arr[], int tam, int x) {
    for (int i = 0; i < tam; i++) {
        if (arr[i] == x) {
            return i;
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