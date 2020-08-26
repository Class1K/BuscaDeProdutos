//19.02009-0 Renan Scheidt Reschke
//19.01370-0 Felipe Freitas Villani
//19.00980-0 Diego Minharro Alves Gimenez

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "pilha.h"




void LerString(char s1[]);
void ExibirPilha(TPilha P);
int main()
{
    char op[MAX];
    Dados C, A, B;
    TPilha P;

    CriarPilha(&P);

    do
    {

        ExibirPilha(P);
        LerString(op);

        if (strcmpi(op, "+") == 0)
        {
            if (RetirarDaPilha(&P, &B))
                if (RetirarDaPilha(&P, &A))
                {
                    C.valor = A.valor + B.valor;
                    InserirNaPilha(&P, C);
                    ExibirPilha(P);
                }
                else
                    InserirNaPilha(&P, B);


        }

        else if (strcmpi(op, "-") == 0)
        {
            if (RetirarDaPilha(&P, &B))
                if (RetirarDaPilha(&P, &A))
                {
                    C.valor = A.valor - B.valor;
                    InserirNaPilha(&P, C);
                    ExibirPilha(P);
                }
                else
                    InserirNaPilha(&P, B);

        }

        else if (strcmpi(op, "*") == 0)
        {
            if (RetirarDaPilha(&P, &B))
                if (RetirarDaPilha(&P, &A))
                {
                    C.valor = A.valor * B.valor;
                    InserirNaPilha(&P, C);
                    ExibirPilha(P);
                }
                else
                    InserirNaPilha(&P, B);

        }

        else if (strcmpi(op, "/") == 0)
        {
            if (RetirarDaPilha(&P, &B))
                if (B.valor != 0)
                    if (RetirarDaPilha(&P, &A))
                    {
                        C.valor = A.valor / B.valor;
                        InserirNaPilha(&P, C);
                        ExibirPilha(P);
                    }
                    else
                        InserirNaPilha(&P, B);

        }

        else if (strcmpi(op, "SIN") == 0)
        {
            if (RetirarDaPilha(&P, &A))
            {
                C.valor = sin(A.valor);
                InserirNaPilha(&P, C);
                ExibirPilha(P);
            }


        }

        else if (strcmpi(op, "COS") == 0)
        {
            if (RetirarDaPilha(&P, &A))
            {
                C.valor = cos(A.valor);
                InserirNaPilha(&P, C);
                ExibirPilha(P);
            }

        }


        if (strcmpi(op, "RAIZ") == 0)
        {
            if (RetirarDaPilha(&P, &A))
            {
                C.valor = sqrt(A.valor);
                InserirNaPilha(&P, C);
                ExibirPilha(P);
            }

        }

        else if (strcmpi(op, "PI") == 0)
        {
            if (RetirarDaPilha(&P, &A))
            {
                C.valor = M_PI;
                InserirNaPilha(&P, C);
                ExibirPilha(P);
            }

        }

        else if (strcmpi(op, "FIM") == 0)
        {
            printf("ACABOU");
        }

        else
        {
            C.valor = atof(op);
            InserirNaPilha(&P, C);
            ExibirPilha(P);
        }

    }
    while(strcmpi(op, "FIM") != 0);
    return 0;
}

void LerString(char s1[])
{
    fflush(stdin);
    fgets(s1, MAX, stdin);
    if (s1[strlen(s1)-1] == '\n')
        s1[strlen(s1)-1] = '\0';

}

void ExibirPilha(TPilha P)
{
    int i;
    system("cls");
    for(i=0 ; i<=P.topo ; i++)
    {
        printf("%i:\t\t %.3f\n", i, P.elemento[i].valor);
    }
    printf("Comando:\t\t");
}
