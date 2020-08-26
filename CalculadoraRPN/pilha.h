#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#define MAX 20
#define MAX_PILHA 10

typedef struct {
    float valor;
    char texto[MAX];
} Dados;

typedef struct {
    Dados elemento[MAX_PILHA];
    int topo;
} TPilha;


void CriarPilha(TPilha *p);
int InserirNaPilha(TPilha *p, Dados dados);
int RetirarDaPilha(TPilha *p, Dados *dados);

int PilhaVazia(TPilha p);
int PilhaCheia(TPilha p);
int QuantidadeNaPilha(TPilha p);

#endif // PILHA_H_INCLUDED
