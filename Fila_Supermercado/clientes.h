#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include "fila.h"

int N_CAIXAS;

void BomDia();
void AtualizarClientes(int h, int m);
int ProximoCliente();
int ClientesSemFila();
void ExibirFilas(int h, int m, TFila fila[], int frenteDeCaixa[]);


#endif // CLIENTES_H_INCLUDED
