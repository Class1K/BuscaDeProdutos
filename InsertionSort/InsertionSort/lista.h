#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#define MAX 20

typedef struct {
    float valor;
    char texto[MAX];
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
