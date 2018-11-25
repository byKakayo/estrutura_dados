#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

struct grafo{
  int V;
  int A;
  int **adj;
};

int **matriz(int l, int c, int val){
  int **m = malloc(l * sizeof(int *));
  for(int i = 0; i < l; i++){
    m[i] = malloc(c * sizeof(int));
  }
  for(int i = 0; i < l; i++){
    for(int x = 0; x < c; x++){
      m[i][x] = val;
    }
  }
  return m;
};

grafo_t *criar(int nvertices){
  grafo_t *G = (grafo_t *)malloc(sizeof(grafo_t));
  G->V = nvertices;
  G->A = 0;
  G->adj = matriz(nvertices, nvertices, -1);
  return G;
};

int criar_aresta(grafo_t *G, int v1, int v2, int peso){
  if(G != NULL && G->adj[(v1-1)][(v2-1)] == -1 && v1 <= G->V && v2 <= G->V){
    G->adj[(v1-1)][(v2-1)] = peso;
    G->adj[(v2-1)][(v1-1)] = peso;
    G->A++;
    return 1;
  }else{
    return 0;
  }
};

int existe_aresta(grafo_t *G, int v1, int v2){
  if(G->adj[(v1-1)][(v2-1)] == -1){
    return 0;
  }else{
    return 1;
  }
};

int retirar_aresta(grafo_t *G, int v1, int v2){
  if(G != NULL && G->adj[(v1-1)][(v2-1)] != -1 && v1 <= G->V && v2 <= G->V){
    G->adj[(v1-1)][(v2-1)] = -1;
    G->adj[(v2-1)][(v1-1)] = -1;
    G->A--;
    return 1;
  }else{
    return 0;
  }
};

void imprimir(grafo_t *G){
  for(int i = 1; i <= G->V; i++){
    printf("%d\n", i);
    for (int x = 1; x <= G->V; x++) {
      if(G->adj[(i-1)][(x-1)] != -1){
        printf("%d\n", x);
      }
    }
    printf("\n");
  }
};

void liberar_memoria(grafo_t *G){
  if(G != NULL){
    int **m = G->adj;
    for(int i = 0; i<G->V; i++){
      free(m[i]);
    }
    free(G);
  }
};
