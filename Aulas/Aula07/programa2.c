#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  time_t inicio, fim;
  unsigned long int tempo;
  inicio = time(NULL);
  //==================================
  /* coloque seu código aqui */
  //==================================
  fim = time(NULL);
  tempo = (fim - inicio)*1000;
  printf("Tempo: %lu milissengudos\n", tempo);
  return 0;
}