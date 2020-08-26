#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 255

float Assoc_Serie(int i);
float Assoc_Paralelo();
char Opcao();

int main()
{
    float res;
do{
    system("cls");
	res = Assoc_Paralelo();
    printf("A RES equivalente eh de: %.2f ohm\n", res);
    printf("\n");
    printf("Quer fazer outra associacao? (s/n): ");    
}while (Opcao() != 'n');
return 0;
}

float Assoc_Serie(int i)
{
    float res, serie = 0;
    int n, ni;
    printf("Quantos Res estao em serie na malha %i? ", i);
    scanf("%i", &n);
    for(ni=0; ni<n; ni++)
    {
        printf("Valor da RES %i: ", ni+1);
        scanf("%f", &res);
        serie += res;
    }
    return serie;

}
float Assoc_Paralelo()
{
    int i, quant;
    float res, soma = 0;
    char op;
    printf("Quantas associacoes em PARALELO? ");
    scanf("%i", &quant);
    for(i=1; i<=quant; i++)
    {
        printf("Na malha %i exitem associacoes em serie? (s/n) ", i);
        op = Opcao();
        if (op != 'n')
            res = Assoc_Serie(i);
        else
        {
            printf("Valor da RES: ");
            scanf("%f", &res);
        }
        soma += 1.0/res;        
    }
    res = 1/soma;
    printf("\n");
    return res;
}
char Opcao()
{
    char op;
    fflush(stdin);
    scanf("%c", &op);
    tolower(op);
    return op;
}
