#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct
{
    char titulo[MAX], genero[MAX];
    int quantidade;
} livro;

void Ordenar(livro[], int);
void Trocar(livro[], int);
void LerString(char s1[]);

int main()
{
    int i, n;
    livro v[MAX];
    printf("Quantos livros: ");
    scanf("%i", &n);

    for (i = 0; i < n; i++)
    {
        printf("Digite o titulo do livro %i: ", i + 1);
        LerString(v[i].titulo);
        printf("Digite o genero do livro %i: ", i + 1);
        LerString(v[i].genero);
        printf("Digite a quantidade do livro %i: ", i + 1);
        scanf("%i", &v[i].quantidade);
    }

    Ordenar(v, n);

    printf("Titulo%24c| Genero%24c| Quantidade\n", ' ', ' ');
    for (i = 0; i < n; i++)
        printf("%30s| %30s| %10i\n", v[i].titulo, v[i].genero, v[i].quantidade);

    return 0;
}

void Ordenar(livro v[], int n)
{
    int i, j;
    for (i = n - 1; i > 0; i--)
        for (j = 0; j < i; j++)
            if (strcmp(v[j].titulo, v[j + 1].titulo) == 1)
                Trocar(v, j);
}

void Trocar(livro v[], int p)
{
    livro aux;
    aux = v[p];
    v[p] = v[p + 1];
    v[p + 1] = aux;
}

void LerString(char s1[])
{
    fflush(stdin);
    fgets(s1, MAX, stdin);
    if (s1[strlen(s1) - 1] == '\n')
        s1[strlen(s1) - 1] = '\0';
}
