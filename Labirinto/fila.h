#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#define MAX 20
#define MAX_FILA 10

typedef struct {
    float valor;
    char texto[MAX];
} Dados;

typedef struct {
    Dados elemento[MAX_FILA];
    int quantidade, frente, tras;
} TFila;


void CriarFila(TFila *p);
int InserirNaFila(TFila *p, Dados dados);
int RetirarDaFila(TFila *p, Dados *dados);

int FilaVazia(TFila p);
int FilaCheia(TFila p);
int QuantidadeNaFila(TFila p);

#endif // FILA_H_INCLUDED
