#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#define MAX 20
#define MAX_FILA 10

typedef struct {
    int valor;
    char nome[MAX];
    char bebida[MAX];
} Dados;

typedef struct {
    Dados elemento[MAX_FILA];
    int quantidade, frente, tras;
} TFila;


void CriarFila(TFila *f);
int InserirNaFila(TFila *f, Dados dados);
int RetirarDaFila(TFila *f, Dados *dados);

int FilaVazia(TFila f);
int FilaCheia(TFila f);
int QuantidadeNaFila(TFila f);

#endif // FILA_H_INCLUDED
