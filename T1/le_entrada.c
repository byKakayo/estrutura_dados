#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"

int main(void) {
	char *line, *op, *arg1, *arg2;
	size_t buf_size = 210;
	dic_t *d;

	line = (char *)malloc(sizeof(char) * buf_size);
	op = (char *)malloc(sizeof(char) * buf_size);
	arg1 = (char *)malloc(sizeof(char) * buf_size);
	arg2 = (char *)malloc(sizeof(char) * buf_size);

	d = criar();

	while(getline(&line, &buf_size, stdin) != -1) {
		sscanf(line, "%s %s %[^\n]", op, arg1, arg2);
		if(strcmp(op,"insercao") == 0){
			insercao(d, arg1, arg2);
		}else if(strcmp(op,"remocao") == 0){
			remocao(d, arg1);
		}else if(strcmp(op,"alteracao") == 0){
			alteracao(d, arg1, arg2);
		}else if(strcmp(op,"busca") == 0){
			busca(d, arg1);
		}else if(strcmp(op,"impressao") == 0){
			impressao(d, &arg1[0]);
		}else{
			printf("OPERACAO INVALIDA\n");
		}
		//printf("Linha: %s\n", line);
		//printf("Operacao: %s\n", op);
		//printf("Argumento 1: %s\n", arg1);
		//printf("Argumento 2: %s\n\n", arg2);
	}

	free(line);
	free(op);
	free(arg1);
	free(arg2);
	return 0;
}
