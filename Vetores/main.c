#include <stdio.h>
#include <stdlib.h>

#define MAX 10



// programa principal. Não crie funções

int main()

{
    int op = 1;
    while(op==1)
    {
        int a = 11, b = 13;

        int Lx[MAX], Ly[MAX];


        // crie outras variáveis aqui

        int i = 0, n = 1, soma = 0;

        // while que preenche as listas Lx e Ly
        Lx[0] = a;
        Ly[0] = b;
        while(Lx[i]>1)
        {
            Lx[i+1] = Lx[i]/2;
            Ly[i+1] = Ly[i]*2;
            n = n+1;
            i = i+1;
        }


        // for que calcula a soma
        for(i=0; i<n; i++)
            if ((Lx[i]%2 != 0) || (Ly[i]%2 != 0))
                soma = soma + Ly[i];




        // mostra a resposta calculada

        printf("%i", soma);
        printf("\n");
        printf("\n");
        printf("Sair(0) / Continuar(1): ");
        scanf("%i", &op);
        system("cls");
    }
    return 0;

}

