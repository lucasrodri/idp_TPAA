#include <stdio.h>
#include <stdlib.h>

int len(size_t tamanho_estrutura, size_t tamanho_elemento){
  return tamanho_estrutura / tamanho_elemento;
}

int main() {
  int A[] = {57,562,24,234,2645,4,53};
  int M = A[0];
  for(int i = 0; i < len(sizeof(A), sizeof(A[0])); i++) { //sizeof(A[0]) = sizeof(int)
    if(A[i] >= M) {
      M = A[i];
    }
  }
  printf("O maior valor é: %d", M);
  return 0;
}