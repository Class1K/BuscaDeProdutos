#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

void CriarPilha(TPilha *p){
    /* define valores iniciais das propriedades da pilha */
    p->topo = -1;
}


int InserirNaPilha(TPilha *p, Dados dados) {
    int pc = PilhaCheia(*p);
    if (!pc) {
        p->topo++;                      /* incrementa posi��o do topo */
        p->elemento[p->topo] = dados;   /* insere elemento no topo da pilha */
    }
    return !pc; /* retorna se conseguiu inserir o dado */
}


int RetirarDaPilha(TPilha *p, Dados *dados) {
    int pv;
    pv = PilhaVazia(*p);
    if (!pv) {
        *dados = p->elemento[p->topo];  /* recupera informa��o do topo da pilha */
        p->topo--;                      /* decrementa posi��o do topo */
    }
    return !pv; /* retorna se conseguiu remover o dado */
}


int PilhaVazia(TPilha p) {
    return p.topo == -1;
}


int PilhaCheia(TPilha p) {
    return p.topo == MAX_PILHA - 1;
}


int QuantidadeNaPilha(TPilha p) {
    return p.topo + 1;
}
