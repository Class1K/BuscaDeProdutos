#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void CriarFila(TFila* p) {
    /* define valores iniciais das propriedades da fila */
    p->quantidade = 0;
    p->frente = 0;
    p->tras = -1;
}


int InserirNaFila(TFila *p, Dados dados) {
    int fc = FilaCheia(*p);
    if (!fc) {
        p->tras = (p->tras + 1) % MAX_FILA; /* incrementa a posição "tras" no buffer circular*/
        p->elemento[p->tras] = dados;       /* insere o elemento no fim da fila */
        p->quantidade++;                    /* incrementa a quantidade */
    }
    return !fc; /* retorna se conseguiu inserir o dado */
}


int RetirarDaFila(TFila *p, Dados *dados) {
    int fv = FilaVazia(*p);
    if (!fv) {
        *dados = p->elemento[p->frente];        /* recupera o dado do início da fila */
        p->frente = (p->frente +1) % MAX_FILA;  /* incrementa a posição "frente" no buffer circular*/
        p->quantidade--;                        /* decrementa a quantidade */
    }
    return !fv; /* retorna se conseguiu remover o dado */
}


int FilaVazia(TFila p) {
    return p.quantidade == 0;
}


int FilaCheia(TFila p) {
    return p.quantidade == MAX_FILA;
}


int QuantidadeNaFila(TFila p) {
    return p.quantidade;
}
