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
  /* Alocar grafo na memória
     Alocar nvertices nós e definí-los como NULL */
  grafo_t *G = (grafo_t *)malloc(sizeof(grafo_t));
  G->V = nvertices;
  G->adj = malloc(nvertices * sizeof(no_t*));
  for (int i = 0; i < nvertices; i++){
    G->adj[i] = NULL;
  }
  return G;
};

no_t *criarNo(int v, int peso){
  // Aloca um nó
  no_t *n = (no_t *)malloc(sizeof(no_t));
  n->V = v;
  n->peso = peso;
  n->prox = NULL;
  return n;
};

int criar_aresta(grafo_t *G, int v1, int v2, int peso){
  // Caso a aresta já exista -> erro
  if(existe_aresta(G, v1, v2)){
    return 0;
  }
  /* Se o vértice não possui nenhum adjacente:
      Alocar o vértice 1 e 2
      Conectar 1 e 2 (criar aresta)
     Vértice 1 está alocado e não possui adjacentes:
      Alocar vértice 2
      Conectar 1 e 2 (criar aresta)
     Vértice 1 está alocando e possui adjacentes:
      Alocar 2
      Criar duas auxiliares
      Percorrer lista de adjacentes do vértice 1
      Inserção no fim da lista
      Inserção no meio da lista
      Inserção no início
     Se o vértice de 2 p/ 1 ainda não foi criado, chamar a função invertendo os vértices
    */
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
  if(existe_aresta(G, v2, v1) == 0){
    return criar_aresta(G, v2, v1, peso);
  }
  return 1;
};

int existe_aresta(grafo_t *G, int v1, int v2){
  /* Caso o grafo não existe
     Caso os vértices sejam maiores que o número de vértices do grafo
     Caso os vértices sejam iguais
     Aresta não existe */
  if(G == NULL || v1 > G->V || v2 > G->V || v1 == v2){
    return 0;
  }
  /* Cria auxiliar apontando para o vértice 1
     Se auxiliar não existe ou não existir adjacentes a ele
      Aresta não existe
     CC percorrer os adjacentes */
  no_t *aux = G->adj[(v1-1)];
  if(aux == NULL || aux->prox == NULL){
    return 0;
  }else{
    aux = aux->prox;
    while(aux->V < v2 && aux->prox != NULL){
      aux = aux->prox;
    }
    if(aux->V == v2){
      return 1;
    }else if(aux->prox != NULL && aux->prox->V == v2){
      return 1;
    }else{
      return 0;
    }
  }
};

int retirar_aresta(grafo_t *G, int v1, int v2){
  /* Caso exista a aresta
      Criar duas auxiliares e percorrer a lista
      Atualizar ponteiros
      Caso exista a aresta do vértice 2 ao 1
        Chamar novamente a função de remoção invertendo os vértices */
  if(existe_aresta(G, v1, v2)){
    no_t *ant = G->adj[(v1-1)];
    no_t *aux = ant->prox;
    while(aux->V < v2){
      ant = aux;
      aux = aux->prox;
    }
    if(ant == G->adj[(v1-1)] && aux->prox == NULL){
      G->adj[(v1-1)] = NULL;
    }else if(aux->prox == NULL){
      ant->prox = NULL;
    }else{
      ant->prox = aux->prox;
    }
    free(aux);
    if(existe_aresta(G, v2, v1)){
      return retirar_aresta(G, v2, v1);
    }
    return 1;
  }else{
    return 0;
  }
};

void imprimir(grafo_t *G){
  if(G != NULL){
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
  }
};

void liberar_memoria(grafo_t *G){
  if(G != NULL){
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
  }
};
