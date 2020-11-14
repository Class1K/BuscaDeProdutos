// 19.02009-0 Renan Scheidt Reschke
// 19.00980-0 Diego Minharro Alves Gimenez
// 19.01370-0 Felipe Freitas Villani

#include "grafo.h"

void CriarGrafo (Grafo *g, int n, int dig)
{
    int i, j;
    g->nVertices = n;
    g->digrafo = dig;
    for (i=0; i < g->nVertices; i++)
        for (j=0; j < g->nVertices; j++)
            g->Pesos[i][j] = 0;
}


void InserirAresta (Grafo *g, int de, int para, float peso)
{
    g->Pesos[de][para] = peso;
    if (!g->digrafo)
        g->Pesos[para][de] = peso;
}


void RemoverAresta (Grafo *g, int de, int para)
{
    g->Pesos[de][para] = 0;
    if (!g->digrafo)
        g->Pesos[para][de] = 0;
}


float PesoDaAresta (Grafo g, int de, int para)
{
    return g.Pesos[de][para];
}

int GrauDeEntrada (Grafo g, int v)
{
    int soma = 0;
    for(int i = 0; i<(g.nVertices); i++)
    {
        if(g.Pesos[i][v])
            soma += 1;
    }
    return soma;
}

int GrauDeSaida (Grafo g, int v)
{
    int soma = 0;
    for(int j = 0; j<(g.nVertices); j++)
    {
        if(g.Pesos[v][j])
            soma += 1;
    }
    return soma;
}

int Vertedouro (Grafo g, int v)
{
    return GrauDeEntrada (g, v) == 0;
}

int Sorvedouro (Grafo g, int v)
{
    return GrauDeSaida (g, v) == 0;
}

int Adjacente (Grafo g, int de, int para)
{
    return g.Pesos[para][de] != 0;
}

void Warshall (Grafo g, int W[MAX_VERT][MAX_VERT])
{
    for(int i = 0; i<g.nVertices; i++)
    {
        for(int j = 0; j<g.nVertices; j++)
        {
            W[i][j] = (PesoDaAresta(g, i, j) != 0);
        }
    }

    for(int k = 0; k<g.nVertices; k++)
    {
        for(int i = 0; i<g.nVertices; i++)
        {
            for(int j = 0; j<g.nVertices; j++)
            {
                W[i][j] = W[i][j] || (W[i][k] && W[k][j]);
            }
        }
    }
}

int Alcanca (Grafo g, int de, int para)
{
    int W[MAX_VERT][MAX_VERT];
    Warshall(g, W);
    return W[de][para];
}

float PesoDoPasseio (Grafo g, ListaDeVertices p)
{
    int soma = 0;
    for(int i = 0; i<(p.nVertices -1); i++)
    {
        soma += PesoDaAresta(g, p.vertices[i], p.vertices[i+1]);
    }
    return soma;
}
