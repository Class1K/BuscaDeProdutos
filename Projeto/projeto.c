// 19.02009-0 Renan Scheidt Reschke
// 19.01370-0 Felipe Freitas Villani
// 19.00980-0 Diego Minharro Alves Gimenez

#include <stdio.h>
#include <stdlib.h>
#define NP 3
#define NA 4

// protótipos das sub-rotinas
// atenção com os tipos de dados dos parâmetros
float CustokWh(int cons, int bandeira); // uso obrigatório
void DigitarConsumo(int cCond[NP][NA]);
void CustoDosPredios(int cCond[NP][NA], int bandeira, float cPredio[NP]);
float CustoTotal(float cPredio[NP]);
void ExibirResumo(float cPredio[NP], float cTotal);
void ExibirPorApartamento(int cCond[NP][NA], int bandeira, float cTotal);

// programa principal
int main()
{

    int cCond[NP][NA], bandeira;
    float cPredio[NP], cTotal;

    printf("Informe a bandeira tarifaria:\n0)Verde\n1)Amarela\n2)Vermelha - patamar 1\n3)Vermelha - patamar 2\nEscolha a opcao (0/1/2/3): ");
    scanf("%i", &bandeira);
    DigitarConsumo(cCond);
    CustoDosPredios(cCond, bandeira, cPredio);
    cTotal = CustoTotal(cPredio);
    ExibirResumo(cPredio, cTotal);
    ExibirPorApartamento(cCond, bandeira, cTotal);
    return 0;
}

// escreva as sub-rotinas aqui
float CustokWh(int cons, int bandeira)
{
    float valor[4] = {0, 1.35, 4.17, 6.28}, TUDS, TE, ICMS, C1, CustoFinal;
    TUDS = 0.25971;
    TE = 0.25588;
    ICMS = 0.12;

    C1 = cons * (TUDS + TE);
    CustoFinal = C1 * (1 + ICMS) + valor[bandeira] * (cons / 100);

    return CustoFinal;
}

void DigitarConsumo(int cCond[NP][NA])
{
    int i, j;
    for (i = 0; i < NP; i++)
    {
        for (j = 0; j < NA; j++)
        {
            printf("Digite o consumo do apartamento %i do predio %c: ", (j + 1), (65 + i));
            scanf("%i", &cCond[i][j]);
        }
    }
    printf("\n");
}

void CustoDosPredios(int cCond[][NA], int bandeira, float cPredio[NP])
{
    int i, j;
    float soma;
    for (i = 0; i < NP; i++)
    {
        soma = 0;
        for (j = 0; j < NA; j++)
        {
            soma += CustokWh(cCond[i][j], bandeira);
        }
        cPredio[i] = soma;
    }
}

float CustoTotal(float cPredio[NP])
{
    float soma = 0;
    for (int i = 0; i < NP; i++)
    {
        soma += cPredio[i];
    }
    return soma;
}

void ExibirResumo(float cPredio[NP], float cTotal)
{
    int i;
    printf("Resumo:\n");
    for (i = 0; i < NP; i++)
    {
        printf("Custo de energia do Predio %c: %4.2f\n", (65 + i), cPredio[i]);
    }
    printf("Total: R$ %.2f\n", cTotal);
    printf("\n");
}

void ExibirPorApartamento(int cCond[NP][NA], int bandeira, float cTotal)
{
    int i, j;
    float media;

    media = cTotal / (NA * NP);

    for (i = 0; i < NP; i++)
    {
        for (j = 0; j < NA; j++)
        {
            if (CustokWh(cCond[i][j], bandeira) > media)
            {
                printf("%4i%c", cCond[i][j], 33);
            }
            else
            {
                printf("%4i ", cCond[i][j]);
            }
        }
        printf("\n");
    }
}
