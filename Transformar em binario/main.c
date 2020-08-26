#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int main()
{
    TPilha p;
    Dados d;
    int N;
    CriarPilha(&p);

    printf("Digite um valor: ");
    scanf("%i", &N);
    // a
    while (N>1)
    {
        d.num = N%2;
        InserirNaPilha(&p, d);
        N = N / 2;
    }
    // b
    d.num = N;
    InserirNaPilha(&p, d);
    // c
    while ( QuantidadeNaPilha(p) < 8 )
    {
        d.num = 0;
        InserirNaPilha(&p, d);
    }
    // d
    while ( RetirarDaPilha(&p, &d) )
        printf("%i", d.num);
    printf("\n");

    return 0;
}
