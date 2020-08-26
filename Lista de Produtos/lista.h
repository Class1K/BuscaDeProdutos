#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#define MAX 20

typedef struct {
    int codProd;       //código do produto
    char nomeProd[10]; //nome do produto
    float valor;       //valor do produto
    int qtdeEstoque;   //quantidade disponível em estoque
} Dados;

typedef struct SLista {
    Dados dados;
    struct SLista *prox;
} TLista;

TLista* CriarLista(void);
void InserirNoFim(TLista *p, Dados dados);
void InserirEmOrdem(TLista *p, Dados dados);
void ExibirLista(TLista *p);
TLista* DestruirLista(TLista *p);

#endif // LISTA_H_INCLUDED
