//19.02009-0 Renan Scheidt Reschke
//19.00980-0 Diego Minharro Alves Gimenez
//19.01370-0 Felipe Freitas Villani

#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "fila.h"

int MenorFila(TFila[N_CAIXAS]);

int main()
{
    BomDia();
    TFila caixas[N_CAIXAS];
    Dados cliente;
    int frenteDeCaixa[N_CAIXAS];

    for(int i = 0; i<N_CAIXAS; i++)
    {
        CriarFila(&caixas[i]);
        frenteDeCaixa[i] = 0;
    }

    for(int h = 8; h <= 23; h++)
    {
        for(int m = 0; m <= 59; m++)
        {
            AtualizarClientes(h, m);
            while((ClientesSemFila()>0) && (MenorFila(caixas)!= -1))
            {
                cliente.valor = ProximoCliente();
                InserirNaFila(&caixas[MenorFila(caixas)], cliente);
            }
            for(int i = 0; i < N_CAIXAS; i++)
            {
                frenteDeCaixa[i] -= 8;
                if(frenteDeCaixa[i] <= 0)
                {
                    if(RetirarDaFila(&caixas[i], &cliente))
                        frenteDeCaixa[i] = (int) cliente.valor;
                    else
                        frenteDeCaixa[i] = 0;
                }
            }
            ExibirFilas(h, m, caixas, frenteDeCaixa);
        }
    }
    return 0;
}

int MenorFila(TFila caixas[N_CAIXAS])
{
    int menor = -1, n = QuantidadeNaFila(caixas[0]);
    for(int i = 0; i<N_CAIXAS; i++)
    {
        if (!FilaCheia(caixas[i]))
        {
            if (QuantidadeNaFila(caixas[i])<=n)
            {
                menor = i;
                n = QuantidadeNaFila(caixas[i]);
            }
        }
    }

    return menor;
}
