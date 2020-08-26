// 19.02009-0   Renan Scheidt Reschke
// 19.01370-0   Felipe Freitas Villani
// 19.00980-0   Diego Minharro Alves Gimenez

#include <stdio.h>
#include <stdlib.h>
#include "pokemon.h"

void Atacar(Pokemon *p1, Pokemon *p2);
int Batalha(Pokemon *p1, Pokemon *p2);
void ExibirTimes(Pokemon *p1, Pokemon *p2);

int main()
{
    int j1 = 0, j2 = 0, ganhador;
    Pokemon p1[6], p2[6];
    GerarTimes(p1, p2);
    ExibirTimes(p1, p2);
    system("pause");
    do
    {
        ganhador = Batalha(&p1[j1], &p2[j2]);
        if(ganhador == 1)
            j2 += 1;
        else
            j1 +=1;
        ExibirTimes(p1, p2);
        system("pause");
    }
    while((j1 < 6) && (j2 < 6));

    if(j1 == 6)
    {
        printf("\n");
        printf("\n");
        printf("Jogador 2 venceu!");
        printf("\n");
        printf("\n");
    }
    else
    {
        printf("\n");
        printf("\n");
        printf("Jogador 1 venceu!");
        printf("\n");
        printf("\n");
    }



    return 0;
}

void Atacar(Pokemon *p1, Pokemon *p2)
{
    if ((*p2).DF < (*p1).AT)
        (*p2).HP -= (*p1).AT - (*p2).DF;
    else
        (*p2).HP -= 1;

    if ((*p2).HP < 0)
        (*p2).HP = 0;

}

int Batalha(Pokemon *p1, Pokemon *p2)
{
    int j;
    if((*p1).SP > (*p2).SP)
        j = 1;
    else
        j = -1;
    do
    {
        if(j == 1)
            Atacar(p1, p2);
        else
            Atacar(p2, p1);
        j = -j;
    }
    while(((*p1).HP > 0) && ((*p2).HP > 0));

    if((*p1).HP > 0)
        return 1;
    else
        return 2;
}

void ExibirTimes(Pokemon p1[6], Pokemon p2[6])
{
    int i;
    system("CLS");
    printf("Jogador 1\n\n");
    printf("        Nome        \t HP\t AT\t DF\t SP\t\n");
    for(i=0; i<6; i++)
    {
        printf("%20s\t%3i\t%3i\t%3i\t%3i\n", p1[i].Nome, p1[i].HP, p1[i].AT, p1[i].DF, p1[i].SP);
    }


    printf("\n");
    printf("\n");


    printf("Jogador 2\n\n");
    printf("        Nome        \t HP\t AT\t DF\t SP\t\n");
    for(i=0; i<6; i++)
    {
        printf("%20s\t%3i\t%3i\t%3i\t%3i\n", p2[i].Nome, p2[i].HP, p2[i].AT, p2[i].DF, p2[i].SP);
    }
}
