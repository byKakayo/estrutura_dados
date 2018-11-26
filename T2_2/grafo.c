#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

typedef struct no no_t;

struct grafo{
  int V;
  no_t **adj;
};

struct no{
  int V;
  int peso;
  no_t *prox;
};

grafo_t *criar(int nvertices){
  grafo_t *G = (grafo_t *)malloc(sizeof(grafo_t));
  G->V = nvertices;
  G->adj = malloc(nvertices * sizeof(no_t*));
  for (int i = 0; i < nvertices; i++){
    G->adj[i] = NULL;
  }
  return G;
};

no_t *criarNo(int v, int peso){
  no_t *n = (no_t *)malloc(sizeof(no_t));
  n->V = v;
  n->peso = peso;
  n->prox = NULL;
  return n;
};

int criar_aresta(grafo_t *G, int v1, int v2, int peso){
  if(v1 > G->V || v2 > G->V || v1 == v2 || existe_aresta(G, v1, v2)){
    return 0;
  }
  if(G->adj[(v1-1)] == NULL){
    no_t *v = (no_t *)malloc(sizeof(no_t));
    v->prox = criarNo(v2, peso);
    v->V = v1;
    v->peso = 0;
    G->adj[(v1-1)] = v;
  }else{
    no_t *v = G->adj[(v1-1)];
    if(v->prox == NULL){
      v->prox = criarNo(v2, peso);
    }else{
      no_t *x = criarNo(v2, peso);
      no_t *ant = v;
      no_t *aux = v->prox;
      while(aux->V < v2 && aux->prox != NULL){
        ant = aux;
        aux = aux->prox;
      }
      if(aux->prox == NULL && aux->V < v2){
        aux->prox = x;
      }else if(aux->V > v2){
        ant->prox = x;
        x->prox = aux;
      }else{
        x->prox = aux->prox;
        aux->prox = x;
      }
    }
  }

  if(G->adj[(v2-1)] == NULL){
    no_t *v = (no_t *)malloc(sizeof(no_t));
    v->prox = criarNo(v1, peso);
    v->V = v2;
    v->peso = 0;
    G->adj[(v2-1)] = v;
  }else{
    no_t *v = G->adj[(v2-1)];
    if(v->prox == NULL){
      v->prox = criarNo(v1, peso);
    }else{
      no_t *x = criarNo(v1, peso);
      no_t *ant = v;
      no_t *aux = v->prox;
      while(aux->V < v1 && aux->prox != NULL){
        ant = aux;
        aux = aux->prox;
      }
      if(aux->prox == NULL && aux->V < v1){
        aux->prox = x;
      }else if(aux->V > v1){
        ant->prox = x;
        x->prox = aux;
      }else{
        x->prox = aux->prox;
        aux->prox = x;
      }
    }
  }
  return 1;
};

int existe_aresta(grafo_t *G, int v1, int v2){
  no_t *aux = G->adj[(v1-1)];
  if(aux == NULL || aux->prox == NULL){
    return 0;
  }else{
    aux = aux->prox;
    while(aux->V < v2 && aux->prox != NULL){
      aux = aux->prox;
    }
    if(aux->prox == NULL && aux->V == v2){
      return 1;
    }else if(aux->prox != NULL && aux->prox->V == v2){
      return 1;
    }else{
      return 0;
    }
  }
};

int retirar_aresta(grafo_t *G, int v1, int v2){
  if(existe_aresta(G, v1, v2)){
    no_t *ant = G->adj[(v1-1)];
    no_t *aux = ant->prox;
    while(aux->V < v2){
      ant = aux;
      aux = aux->prox;
    }
    if(ant == G->adj[(v1-1)]){
      G->adj[(v1-1)] = NULL;
    }else if(aux->prox == NULL){
      ant->prox = NULL;
    }else{
      ant->prox = aux->prox;
    }
    free(aux);
    if(existe_aresta(G, v2, v1)){
      return retirar_aresta(G, v2, v1);
    }else{
      return 1;
    }
  }else{
    return 0;
  }
};

void imprimir(grafo_t *G){
  for(int v = 0; v < G->V; v++){
    no_t *aux = G->adj[v];
    if(aux != NULL){
      printf("%d", aux->V);
      while(aux->prox != NULL){
        aux = aux->prox;
        printf(" -> %d", aux->V);
      }
    }
    printf("\n");
  }
};

void liberar_memoria(grafo_t *G){
  for(int i = 0; i<G->V; i++){
    if(G->adj[i] != NULL){
      if(G->adj[i]->prox != NULL){
        no_t *aux = G->adj[i]->prox;
        no_t *x;
        while(aux->prox != NULL){
          x = aux;
          aux = aux->prox;
          free(x);
        }
      }
    }
  }
  free(G->adj);
};
