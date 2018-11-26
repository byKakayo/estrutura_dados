typedef struct grafo grafo_t;

grafo_t *criar(int nvertices);
int criar_aresta(grafo_t *G, int v1, int v2, int peso);
int existe_aresta(grafo_t *G, int v1, int v2);
int retirar_aresta(grafo_t *G, int v1, int v2);
void imprimir(grafo_t *G);
void liberar_memoria(grafo_t *G);
