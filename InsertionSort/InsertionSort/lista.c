#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

TLista* CriarLista(void)
{
    TLista *p;   /* Ponteiro para a lista */
    p = (TLista*) malloc(sizeof(TLista));
    if (p == NULL)
    {
        printf("N�o pode criar a lista");
        exit(EXIT_FAILURE);
    }

    p->prox = NULL;   /* Atribui ponteiro nulo */
    return p;   /* Retorna endere�o da lista */
}


void InserirNoFim(TLista *p, Dados dados)
{
    TLista* novo;
    novo = (TLista*) malloc(sizeof(TLista));
    if (novo == NULL)
    {
        printf("Nao foi possivel alocar memoria!");
        exit(EXIT_FAILURE);
    }

    novo->dados = dados;

    TLista *aux;
    aux = p;
    while(aux->prox != NULL)
        aux = aux->prox;

    novo->prox = NULL;
    aux->prox = novo;
}


void InserirEmOrdem(TLista *p, Dados dados)
{
    TLista* novo;
    novo = (TLista*) malloc(sizeof(TLista));
    if (novo == NULL)
    {
        printf("Nao foi possivel alocar memoria!");
        exit(EXIT_FAILURE);
    }

    novo->dados = dados;

    TLista *aux;
    aux = p;

    if(aux->prox != NULL)
    {
        while(((aux->prox->dados).valor) < ((novo->dados).valor))
                aux = aux->prox;
        novo->prox = aux->prox;
        aux->prox = novo;
    }

    else
        InserirNoFim(p, dados);



}


TLista* DestruirLista(TLista *p)
{
    TLista* aux;
    aux = p;
    while(aux->prox != NULL)
    {
        aux = aux->prox;
        free(p);
        p = aux;
    }
    free(p);
    return NULL;
}


void ExibirLista(TLista *p)
{
    TLista* aux;
    aux = p;
    aux = aux->prox;
    while(aux != NULL)
    {
        printf("%4.2f\t%s\n",
               aux->dados.valor,
               aux->dados.texto);
        aux = aux->prox;
    }
}
