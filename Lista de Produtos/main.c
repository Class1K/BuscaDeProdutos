#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void LerString(char s1[]);
int ProcurarMenor(TLista *l, Dados *d);


int main()
{
    int i, N;
    TLista *lista;
    Dados d;

    lista = CriarLista();
    printf("Quantidade de produtos: ");
    scanf("%i", &N);

    for(i=0; i<N; i++){
        printf("Codigo: ");
        scanf("%i", &d.codProd);
        printf("Nome: ");
        LerString(d.nomeProd);
        printf("Valor: ");
        scanf("%f", &d.valor);
        printf("Qt em estoque: ");
        scanf("%i", &d.qtdeEstoque);
        InserirNoFim(lista, d);
        printf("\n");
    }
    if(ProcurarMenor(lista, &d)){
        printf("Produto mais barato: ");
        printf("Codigo: %i\n", d.codProd);
        printf("Nome: %s\n", d.nomeProd);
        printf("Valor: %.2f\n", d.valor);
        printf("Estoque: %i\n", d.qtdeEstoque);
    }
    else
        printf("Lista vazia");



    return 0;
}

void LerString(char s1[])
{
    fflush(stdin);
    fgets(s1, MAX, stdin);
    if (s1[strlen(s1)-1] == '\n')
        s1[strlen(s1)-1] = '\0';

}

int ProcurarMenor(TLista *l, Dados *d)
{
    int achou = 0;
    TLista *aux = l;
    float menor = aux->prox->dados.valor;
    if (aux->prox != NULL){
        achou = 1;
        while (aux->prox != NULL){
            aux = aux->prox;
            if (aux->dados.valor < menor){
                menor = aux->dados.valor;
                *d = aux->dados;
            }
        }
    }


    return achou;
}
