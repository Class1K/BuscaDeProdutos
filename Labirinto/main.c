// 19.02009-0 Renan Scheidt Reschke
// 19.00980-0 Diego Minharro Alves Gimenez
// 19.01370-0 Felipe Freitas Villani

#include <stdio.h>
#include <stdlib.h>
#include <math.h>  /* para usar o INFINITY */
#include "grafo.h"

void ExibirGrafo (Grafo g)
{
    int i, j;
    system("CLS");
    printf ("Numero de vertices do %s: %i\n", g.digrafo==0?"GRAFO":"DIGRAFO",g.nVertices);

    // primeira linha com nomes dos vértices
    printf("    ");
    for (i=0; i <g.nVertices; i++)
        printf("%c   ", 65+i);
    printf("%\n");

    for (i=0; i <g.nVertices; i++)
    {
        // primeira coluna com nomes dos vértices
        printf("%c   ", 65+i);
        for (j=0; j < g.nVertices; j++)
            printf ("%0.0f   ", PesoDaAresta (g, i, j));
        printf ("\n");
    }
    printf ("\n");
}


int main ()
{
    int n, dig, i;
    Grafo g;
    ListaDeVertices caminho;

	/* **********************************************
	           crie seu labirinto aqui
    ********************************************** */
    n = 17;
    dig = 0;
    int origem = 0;
    int destino = 12;
    CriarGrafo (&g, n, dig);
    InserirAresta (&g, 0, 1, 1);
    InserirAresta (&g, 1, 2, 1);
    InserirAresta (&g, 1, 3, 1);
    InserirAresta (&g, 1, 5, 1);
    InserirAresta (&g, 5, 4, 1);
    InserirAresta (&g, 5, 6, 1);
    InserirAresta (&g, 6, 11, 1);
    InserirAresta (&g, 6, 7, 1);
    InserirAresta (&g, 6, 8, 1);
    InserirAresta (&g, 11, 12, 1);
    InserirAresta (&g, 7, 9, 1);
    InserirAresta (&g, 8, 9, 1);
    InserirAresta (&g, 9, 10, 1);
    InserirAresta (&g, 9, 11, 1);
    InserirAresta (&g, 10, 13, 1);
    InserirAresta (&g, 13, 14, 1);
    InserirAresta (&g, 13, 16, 1);
    InserirAresta (&g, 10, 15, 1);
    InserirAresta (&g, 15, 16, 1);
    InserirAresta (&g, 16, 12, 1);

	/* **********************************************
	           crie seu labirinto aqui
    ********************************************** */

    ExibirGrafo (g);

    printf ("Busca em profundidade: \n");
    DFS(g, origem, destino, &caminho);
    for (i=0; i < caminho.nVertices-1; i++)
        printf("%c -> ",caminho.vertices[i]+65);
    printf ("%c\n\n",caminho.vertices[i]+65);


    return 0;
}
