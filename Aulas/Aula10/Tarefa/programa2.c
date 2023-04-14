//Crie um programa que dado uma string, coloque as letras dela em ordem crescente pelo algoritmo bubble sort. 
//Por exemplo, se a string for "cba", o programa deve imprimir "abc".

#include <stdio.h>
#include <string.h>

void bubble_sort(char str[], int n) {
    //TODO: implementar seu algoritmo de ordenação aqui
}

int main() {
    char str[100];
    printf("Digite uma string: ");
    scanf("%[^\n]s", str);
    getchar();
    int n = strlen(str);
    bubble_sort(str, n);
    printf("String ordenada: %s\n", str);
    return 0;
}
