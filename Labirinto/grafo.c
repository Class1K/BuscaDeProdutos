#include "grafo.h"
#include "fila.h"  /* Fila para busca em largura*/
#include <math.h>  /* para usar o INFINITY */


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
    int i, s = 0;
    for (i=0; i < g.nVertices; i++)
        if (PesoDaAresta (g,i,v) != 0)
            s++;
    return s;
}


int GrauDeSaida (Grafo g, int v)
{
    int i, s = 0;
    for (i=0; i < g.nVertices; i++)
        if (PesoDaAresta (g, v, i) != 0)
            s++;
    return s;
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


void Warshall (Grafo g, int w[MAX_VERT][MAX_VERT])
{
    int i, j, k;

    for (i=0; i < g.nVertices; i++)
        for ( j=0; j < g.nVertices; j++)
            w[i][j] = PesoDaAresta (g, i, j) != 0;

    for (i=0; i < g.nVertices; i++)
        for (j=0; j < g.nVertices; j++)
            for (k=0; k < g.nVertices; k++)
                w[i][j] = w[i][j] || (w[i][k] && w[k][j]);
}


int Alcanca (Grafo g, int de, int para)
{
    int w [MAX_VERT][MAX_VERT];
    Warshall (g, w);
    return w[de][para] != 0;
}


float PesoDoPasseio (Grafo g, ListaDeVertices p)
{
    float s = 0;
    int i;
    for (i=0; i<p.nVertices-1; i++)
        if (Adjacente (g, p.vertices[i+1], p.vertices[i]))
            s += PesoDaAresta (g, p.vertices[i], p.vertices[i+1]);
        else
            return -1;
    return s;
}


// *******************************************
//                  Buscas
// *******************************************


void Pre_visita_DFS(Grafo g, int v, int destino, int *achei, ListaDeVertices *caminho)
{

    caminho->vertices[caminho->nVertices] = v;
    caminho->nVertices++;
    *achei = ((v==destino)?1:0);
}

void Pos_visita_DFS(Grafo g, int v, int destino, int nExplorados, ListaDeVertices *caminho)
{
    if(nExplorados == 0 && (v != destino))
        caminho->nVertices--;
}


void Explorar (Grafo g, int v, int destino, int *visitado, ListaDeVertices *caminho, int *achei)
{
    int u, nExplorados = 0;
    visitado[v] = 1;

    Pre_visita_DFS(g, v, destino, achei, caminho);

    for (u=0; u<g.nVertices; u++)
        if (!visitado[u] && Adjacente(g,u,v) && !(*achei))
        {
            Explorar(g, u, destino, visitado, caminho, achei);
            nExplorados++;
        }

    Pos_visita_DFS(g, v, destino, nExplorados, caminho);
}


void DFS(Grafo g, int origem, int destino, ListaDeVertices *caminho)
{
    int v, achei;
    int visitado[g.nVertices];

    caminho->nVertices = 0;
    achei = 0; // se for procurar algo
    for (v=0; v<g.nVertices; v++)
        visitado[v] = 0;

    Explorar(g, origem, destino, visitado, caminho, &achei);

    /* se algum vertice ainda nao foi visitado E AINDA NÃO ACHEI!!! */
    for (v=0; v<g.nVertices; v++)
        if (!visitado[v] && !achei)
            Explorar(g, v, destino, visitado, caminho, &achei);
}


void Pre_visita_BFD(/* Parâmetros */)
{
}


void Pos_visita_BFD(Grafo g, int v, ListaDeVertices *caminho)
{
    caminho->vertices[caminho->nVertices] = v;
    caminho->nVertices++;
}


void BFS(Grafo g, int origem, int destino, float *dist, ListaDeVertices *caminho)
{
    TFila fila;
    Dados dados;

    int u, v;
    int achei = 0;

    CriarFila(&fila);
    caminho->nVertices = 0;
    for (v=0; v<g.nVertices; v++)
        dist[v] = INFINITY;

    /* Pre_visita_BFD(parâmetros); //opcional */
    dist[origem] = 0;
    dados.valor = origem;
    InserirNaFila(&fila,dados);
    /* Pos_visita_BFD(parâmetros); //opcional */
    Pos_visita_BFD(g, origem, caminho);

    while (!FilaVazia(fila) && !achei)
    {
        /* Pre_visita_BFD(parâmetros) //opcional */
        RetirarDaFila(&fila, &dados);
        v = dados.valor;

        for (u=0; u<g.nVertices; u++)
            if (dist[u]==INFINITY && Adjacente(g, u, v) && !achei)
            {
                dados.valor = u;
                InserirNaFila(&fila, dados);
                /* Pos_visita_BFD(parâmetros) //opcional */
                Pos_visita_BFD(g, u, caminho);
                dist[u] = dist[v] + 1; // ou
                /* dist[u] = dist[v] + PesoDaAresta(g, v, u); */
            }
    }
}
