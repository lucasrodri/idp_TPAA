typedef struct grafo {
    int eh_ponderado;
    int nro_vertices;
    int grau_max;
    int **arestas;
    float **pesos;
    int *grau;
} Grafo;

Grafo *cria_grafo(int nro_vertices, int grau_max, int eh_ponderado);
void libera_grafo(Grafo *gr);
int insere_aresta(Grafo *gr, int orig, int dest, int eh_digrafo, float peso);
int remove_aresta(Grafo *gr, int orig, int dest, int eh_digrafo);
void imprime_grafo(Grafo *gr);
