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

//FUNÇÃO PARA CRIAR O GRAFO
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

//FUNÇÃO PARA CRIAR UM NÓ
no_t *criarNo(int v, int peso){
  // Aloca um nó
  no_t *n = (no_t *)malloc(sizeof(no_t));
  n->V = v;
  n->peso = peso;
  n->prox = NULL;
  return n;
};

/*FUNÇÃO QUE RETORNA O NÓ ANTERIOR AO PROCURADO
    SE O NÓ NÃO EXISTE -> RETORNA NULL
*/
no_t *procura_aresta(grafo_t *G, int v1, int v2){
  /* Caso o grafo não existe
     Caso os vértices sejam maiores que o número de vértices do grafo
     Caso os vértices sejam iguais
     Aresta não existe */
  if(G == NULL || v1 > G->V || v2 > G->V || v1 == v2){
    return NULL;
  }
  /* Cria auxiliar apontando para o vértice 1
     Se auxiliar não existe ou não existir adjacentes a ele
      Aresta não existe */
  no_t *aux = G->adj[(v1-1)];
  if(aux == NULL || aux->prox == NULL){
    return NULL;
  }else{
  /* Vértice procurado é o primeiro da lista
      CC percorre a lista*/
    if(aux->prox->V == v2){
      return aux;
    }
    while(aux->prox->V < v2 && aux->prox->prox != NULL){
      aux = aux->prox;
    }
    if(aux->prox->V == v2){
      return aux;
    }else if(aux->prox->prox != NULL && aux->prox->prox->V == v2){
      return aux->prox;
    }else{
      return NULL;
    }
  }
}

//FUNÇÃO QUE RETORNA UM VALOR BOOLEAN P/ EXISTÊNCIA DA ARESTA
int existe_aresta(grafo_t *G, int v1, int v2){
  no_t * v = procura_aresta(G, v1, v2);
  if(v == NULL){
    return 0;
  }else{
    return 1;
  }
};


//FUNÇÃO DE INSERÇÃO DE UMA ARESTA
int inserir_aresta(grafo_t *G, int v1, int v2, int peso){
  /* Se o vértice não possui nenhum adjacente:
  Alocar o vértice 1 e 2
  Conectar 1 e 2 (criar aresta)
  Vértice 1 está alocado e não possui adjacentes:
  Conectar 1 e 2 (criar aresta)
  Alocar vértice 2
  Vértice 1 está alocando e possui adjacentes:
  Alocar 2
  Criar duas auxiliares
  Percorrer lista de adjacentes do vértice 1
  Inserção no fim da lista
  Inserção no meio da lista
  Inserção no início  */
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
  return 1;
};

//FUNÇÃO QUE RETORNA UM VALOR BOOLEAN P/ CRIAÇÃO DA ARESTA
int criar_aresta(grafo_t *G, int v1, int v2, int peso){
  /* Caso o grafo não exista
     Caso os vértices sejam maiores que o número de vértices do grafo
     Caso a aresta já exista
      ERRO */
  if(G == NULL || v1 > G->V || v2 > G->V || existe_aresta(G, v1, v2)){
    return 0;
  }
  // Se inserir a aresta de v1 -> v2 e v2 -> v1 com sucesso
  if(inserir_aresta(G, v1, v2, peso) && inserir_aresta(G, v2, v1, peso)){
    return 1;
  }
};

int delete_aresta(grafo_t *G, int v1, int v2){
  no_t *v = procura_aresta(G, v1, v2);
  if(v == NULL){
    return 0;
  }
  no_t *aux;
  aux = v->prox;
  if(v == G->adj[(v1-1)] && aux->prox == NULL){
    G->adj[(v1-1)] = NULL;
  }else if(aux->prox == NULL){
    v->prox = NULL;
  }else{
    v->prox = aux->prox;
  }
  free(aux);
  return 1;
}

//FUNÇÃO QUE RETORNA UM VALOR BOOLEAN P/ CRIAÇÃO DA ARESTA
int retirar_aresta(grafo_t *G, int v1, int v2){
  /* Caso o grafo não exista
     Caso os vértices sejam maiores que o número de vértices do grafo
      ERRO */
  if(G == NULL || v1 > G->V || v2 > G->V){
    return 0;
  }
  // Se remover a aresta de v1 -> v2 e v2 -> v1 com sucesso
  if(delete_aresta(G, v1, v2) && delete_aresta(G, v2, v1)){
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
    free(G);
  }
};
