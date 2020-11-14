#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void ExibirGrafo (Grafo g)
{
    int i, j;
    system("CLS");
    printf ("Numero de vertices do %s: %i\n", g.digrafo==0?"GRAFO":"DIGRAFO",g.nVertices);
    for (i=0; i <g.nVertices; i++)
    {
        for (j=0; j < g.nVertices; j++)
            printf ("%0.1f   ", PesoDaAresta (g, i, j));
        printf ("\n");
    }
    printf ("\n");
}

void ExibirArestas (Grafo g)
{
    int i, j, a;
    printf("\nPeso da Aresta:\n");
    a = 65;
    for (i=0; i<g.nVertices; i++)
        for (j=0; j<g.nVertices; j++)
            if (PesoDaAresta(g, i, j) != 0)
                printf("Aresta %c%i,%i%c: w(%c)=%.1f\n",
                       g.digrafo==0?'{':'(',
                       i, j,
                       g.digrafo==0?'}':')',
                       a++,
                       PesoDaAresta(g, i, j)
                      );
    printf ("\n");
}


int main(){
    int n, dig, i, j;
    float p;
    Grafo g;

    n=3;
    dig=1;
    CriarGrafo (&g, n, dig);

    InserirAresta (&g, 0, 1, 5);
    InserirAresta (&g, 0, 2, 1);
    InserirAresta (&g, 1, 2, 7);
    InserirAresta (&g, 1, 1, 4);
    InserirAresta (&g, 1, 0, 3);
    ExibirGrafo (g);
    ExibirArestas(g);

    printf ("Grau de Entrada e Grau de Saida:\nv\tGE\tGS\n");
    for ( i=0; i < g.nVertices; i++)
        printf ("%i\t%i\t%i\n", i, GrauDeEntrada ( g, i), GrauDeSaida (g, i));
    printf ("\n");


    printf ("Sorvedouro e Vertedouro:\n");
    for ( i=0; i < g.nVertices; i++){
        printf ("%i%seh vertedouro\n", i, Vertedouro (g,i)?" ":" nao ");
        printf ("%i%seh sorvedouro\n", i, Sorvedouro (g,i)?" ":" nao ");
    }
    printf ("\n");


    printf ("Adjacentes:\n");
    for (i=0; i < g.nVertices; i++)
        for (j=0; j < g.nVertices; j++)
            printf ("%i%seh adjacente a %i\n", i, Adjacente (g,i,j)?" ":" nao ", j);
    printf ("\n");


    printf ("Warshall:\n");
    int w [MAX_VERT][MAX_VERT];
    Warshall (g, w);
    for (i=0; i < g.nVertices; i++){
        for (j=0; j < g.nVertices; j++)
            printf ("%i\t",w[i][j]);
        printf ("\n");
    }
    printf ("\n");


    printf ("Alcance: \n");
    for (i=0; i < g.nVertices; i++)
        for (j=0; j <g.nVertices; j++)
            printf ("%i%salcanca %i\n", i,Alcanca (g,i,j)?" ":" nao ", j);

    printf ("\n");
    printf("Passeio:\n");
    ListaDeVertices passeio;
    passeio.nVertices = 5;
    passeio.vertices[0] = 0;
    passeio.vertices[1] = 1;
    passeio.vertices[2] = 1;
    passeio.vertices[3] = 0;
    passeio.vertices[4] = 2;

    for (i=0; i < passeio.nVertices-1; i++)
        printf ("%i -> ", passeio.vertices[i]);
    printf ("%i\n", passeio.vertices[passeio.nVertices-1]);
    p = PesoDoPasseio (g, passeio);
    if (p != -1)
        printf ("Peso do passeio: %.1f\n", p);
    else
        printf ("Sequencia de vertices nao eh um passeio.\n");
    printf ("\n");


    return 0;
}
