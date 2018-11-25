typedef struct dic dic_t;

dic_t *criar();
void insercao(dic_t *d, char *arg1, char *arg2);
void alteracao(dic_t *d, char *arg1, char *arg2);
void remocao(dic_t *d, char *arg1);
void busca(dic_t *d, char *arg1);
void impressao(dic_t *d, char *ch1);
