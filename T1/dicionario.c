#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dicionario.h"

#define p 0.5
//probabilidade de promoção
#define max_lvl 10
//número máximo de níveis
#define max_verb 50
//tamanho do verbete
#define max_def 140
//tamanho da definição do verbete

typedef struct verb verbete_t;

struct verb {
  char verb[max_verb];
  char def[max_def];
  int lvl;
  verbete_t  **prox;
};

struct dic {
  verbete_t *prim;
  int lvl;
};

verbete_t *busca_verbete(dic_t *d, char *arg1, int flag);
verbete_t* criar_verbete(int level, char *arg1, char *arg2);

float randomize(){
  float prob;
  prob = ((float)rand()) / (float)(RAND_MAX);
  return prob;
}

int level(){
  int lvl;
  while(randomize() < p && lvl < max_lvl){
    lvl++;
  }
  return lvl;
}

dic_t *criar(){
  dic_t *d = (dic_t *)malloc(sizeof(dic_t));
  d->prim = criar_verbete(max_lvl, " ", " ");
  d->lvl = 0;
  return d;
}

verbete_t* criar_verbete(int level, char *arg1, char *arg2){
    verbete_t *v = (verbete_t *)malloc(sizeof(verbete_t));
    v->lvl = level;
    v->prox = malloc((level + 1) * sizeof(verbete_t));

    int i = 0;
    while(i < (v->lvl + 1)){
        v->prox[i] = 0;
        i++;
    }

    strcpy(v->verb, arg1);
    strcpy(v->def, arg2);

    return v;
}

void insercao(dic_t *d, char *arg1, char *arg2){
  verbete_t *aux = d->prim;
  verbete_t **x = malloc((max_lvl + 1) * sizeof(verbete_t*));

  int lvl = aux->lvl;

  for(int i = lvl; i >= 0; i--){
    while(aux->prox[i] != 0 && strcmp(aux->prox[i]->verb, arg1) < 0){
      aux = aux->prox[i];
    }
    x[i] = aux;
  }
  aux = aux->prox[0];
  if(aux == 0 || strcmp(aux->verb, arg1) != 0){
    int newLvl = level();
    if(newLvl > lvl){
      for(int k = lvl + 1; k <= newLvl; k++){
        x[k] = d->prim;
      }
      d->lvl = newLvl;
    }
    aux = criar_verbete(newLvl, arg1, arg2);
    for (int z = 0; z <= aux->lvl; z++){
      aux->prox[z] = x[z]->prox[z];
      x[z]->prox[z] = aux;
    }
  }else if(strcmp(aux->verb, arg1) == 0){
    printf("OPERACAO INVALIDA\n");
  }
}

verbete_t *busca_verbete(dic_t *d, char *arg1, int flag){
  verbete_t *x = d->prim;
  int lvl = x->lvl;

  for(int i = lvl; i >= 0; i--){
    while(x->prox[i] != 0 && strcmp(x->prox[i]->verb, arg1) < 0){
      x = x->prox[i];
    }
  }
  if(x->prox[0] == 0){
    return NULL;
  }else if(flag == 0){
    if(strcmp(x->prox[0]->verb, arg1) == 0){
      return x->prox[0];
    }else{
      return NULL;
    }
  }else if(flag == 1){
    char c[max_verb];
    x = x->prox[0];
    if(x->verb != NULL){
      strcpy(c, x->verb);
    }
    if(c[0] == *arg1){
      return x;
    }
    return NULL;
  }
}

void impressao(dic_t *d, char *ch1){
  verbete_t *v;
  char c[max_verb];
  v = busca_verbete(d, ch1, 1);
  strcpy(c, v->verb);
  while (v->prox[0] != 0 && c[0] == *ch1){
    printf("%s %s\n", c, v->def);
    v = v->prox[0];
    if(v->verb != NULL){
      strcpy(c, v->verb);
    }
  }
}

void alteracao(dic_t *d, char *arg1, char *arg2){
  verbete_t *v;
  v = busca_verbete(d, arg1, 0);
  if(v == NULL){
    printf("OPERACAO INVALIDA\n");
  }else{
    strcpy(v->def, arg2);
  }
}

void remocao(dic_t *d, char *arg1){
  verbete_t *x = d->prim;
  verbete_t **aux;
  int lvl = x->lvl;

  aux = malloc((max_lvl + 1) * sizeof(verbete_t*));

  for(int i = lvl; i >= 0; i--){
    while(x->prox[i] != 0 && strcmp(x->prox[i]->verb, arg1) < 0){
      x = x->prox[i];
    }
    aux[i] = x;
  }

  x = x->prox[0];

  if(x != NULL){
    if(strcmp(x->verb, arg1) != 0){
        printf("OPERACAO INVALIDA\n");
    }else{
      for(int i = x->lvl; i >= 0; i--){
        if(aux[i]->prox[i] != NULL && strcmp(aux[i]->prox[i]->verb, arg1) == 0){
          aux[i]->prox[i] = x->prox[i];
        }
      }
    }
    free(aux);
  }else{
    free(aux);
    printf("OPERACAO INVALIDA\n");
  }
  //free(x);

}


void busca(dic_t *d, char *arg1){
  verbete_t *v;
  v = busca_verbete(d, arg1, 0);
  if(v == NULL){
    printf("OPERACAO INVALIDA\n");
  }else{
    printf("%s %s\n", v->verb, v->def);
  }
}
