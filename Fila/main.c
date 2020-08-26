//19.02009-0 Renan Scheidt Reschke
//19.01370-0 Felipe Freitas Villani
//19.00980-0 Diego Minharro Alves Gimenez

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

void LerString(char s1[]);
void ExibirTabela(TFila fila);


int main()
{
    TFila fila;
    Dados pedido, entrega;
    char op;
    int n = 1;

    CriarFila(&fila);

    do
    {
        system("cls");
        printf("Opcoes:\n");
        printf("(C)adastrar novo pedido\n");
        printf("(E)ntregar bebida\n");
        printf("(A)dministrativo\n");
        printf("(S)air do programa\n");
        printf("\n");
        printf("Digite a opcao: ");
        scanf("%c", &op);
        printf("\n");

        switch (toupper(op))
        {
        case 'C':
            printf("Nome: ");
            LerString(pedido.nome);
            printf("Bebida: ");
            LerString(pedido.bebida);
            pedido.valor = n;
            if(InserirNaFila(&fila, pedido))
                n++;
            else
                printf("Nao foi possivel inserir na fila\n");
            break;

        case 'E':
            if(RetirarDaFila(&fila, &entrega))
            {
                printf("Final: %i", entrega.valor);
                printf("\n");
                printf("%s!", strupr(entrega.nome));
                printf("\n");
                printf("%s pronto!\n", strlwr(entrega.bebida));
            }
            else
                printf("Fila vazia\n");
            system("pause");
            break;

        case 'A':
            ExibirTabela(fila);
            break;

        case 'S':
            printf("Programa encerrado!");
            return 0;
            break;

        default:
            printf("Comando Invalido!\n");
            system("pause");
            break;
        }
        fflush(stdin);


    }
    while(toupper(op)!= 'S');



}

void LerString(char s1[])
{
    fflush(stdin);
    fgets(s1, MAX, stdin);
    if (s1[strlen(s1)-1] == '\n')
        s1[strlen(s1)-1] = '\0';

}


void ExibirTabela (TFila fila)
{
    int i;
    Dados pedido;

    printf("+---+--------------------+---------------+\n");
    printf("|ped|       cliente      |      item     |\n");
    printf("+---+--------------------+---------------+\n");

    while(RetirarDaFila(&fila, &pedido))
    {
        printf("|%3i|%20s|%15s|\n",pedido.valor,pedido.nome,pedido.bebida);
    }
    printf("+---+--------------------+---------------+\n");
    system("pause");
}
