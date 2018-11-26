#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(int argc, char** argv) {
    grafo_t *G;
    int opcao, v1, v2, aux;

    while (1) {
        printf("***OPCOES***\n");
        printf("1. Criar grafo\n");
        printf("2. Inserir aresta\n");
        printf("3. Existe aresta?\n");
        printf("4. Retirar aresta\n");
        printf("5. Imprimir grafo\n");
        printf("6. Sair\n\n");
        printf("Sua opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("\nEntre com o numero de vertices: ");
            scanf("%d", &aux);
            G = criar(aux);
            if (G == NULL)
                printf("\nErro ao criar grafo\n");
            else printf("\nGrafo criado\n");
        } else if (opcao == 2) {
            printf("\nEntre com o primeiro vertice: ");
            scanf("%d", &v1);
            printf("\nEntre com o segundo vertice: ");
            scanf("%d", &v2);
            if (criar_aresta(G, v1, v2, 1) == 0)
                printf("\nErro ao inserir aresta\n");
            else printf("\nAresta inserida\n");
        } else if (opcao == 3) {
            printf("\nEntre com o primeiro vertice: ");
            scanf("%d", &v1);
            printf("\nEntre com o segundo vertice: ");
            scanf("%d", &v2);
            if (existe_aresta(G, v1, v2) == 1)
                printf("\nAresta existe\n");
            else printf("\nAresta nao existe\n");

        } else if (opcao == 4) {
            printf("\nEntre com o primeiro vertice: ");
            scanf("%d", &v1);
            printf("\nEntre com o segundo vertice: ");
            scanf("%d", &v2);
            if (retirar_aresta(G, v1, v2) == 0)
                printf("\nErro ao retirar aresta\n");
            else printf("\nAresta retirada\n");

        } else if (opcao == 5)
            imprimir(G);
        else if (opcao == 6) {
            liberar_memoria(G);
            return 1;
        }

    }
    return (EXIT_SUCCESS);
}
