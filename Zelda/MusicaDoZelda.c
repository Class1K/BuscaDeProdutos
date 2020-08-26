#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// C   C#  D   D#  E   F   F#  G   G#  A   A#  B
// 262,278,294,312,330,350,371,392,416,440,467,494
// DO      RE      MI  FA      SOL     LA      SI

// estrutura de dados para armazenar notas musicais
typedef struct
{

    int freq;
    int duracao;
    int oitava;

} NotaMusical;

// separa as informações lidas em uma linha do arquivo
// em uma estrutura de dados com 3 campos utilizando o
// caractere ';' como separador
void SepararDados(char linha[], NotaMusical *nota)
{

    int i, j, c;
    char temp[15];
    int valores[3];
    c = 0;
    for (i = 0; i < 3; i++)
    {

        j = 0;
        while (linha[c] != ';' && c < strlen(linha))
        {

            temp[j] = linha[c];
            c++;
            j++;
        }
        c++; /* pular o separador */
        temp[j] = '\0';
        valores[i] = atoi(temp);
    }

    // retorna, respectivamente, a frequência, a duração
    // e a oitava em uma estrutura passada por referência
    (*nota).freq = valores[0];
    (*nota).duracao = valores[1];
    (*nota).oitava = valores[2];
}

int main()
{

    char linha[15];   // uma linha do arquivo
    NotaMusical nota; // uma nota musical
    int fmin, fmax;   // limites de frequência do filtro

    // manipulação básica do arquivo

    FILE *arq;

    arq = fopen("som.txt", "r"); // abre o arquivo para leitura
    if (arq == NULL)
    {

        printf("Não consegui abrir o arquivo.");
        exit(EXIT_FAILURE);
    }

    printf("Informe a frequência minima (Hz): ");
    scanf("%i", &fmin);
    printf("Informe a frequência maxima (Hz): ");
    scanf("%i", &fmax);

    while (!feof(arq)) // verifica o arquivo até o final
    {

        fgets(linha, 15, arq); // faz a leitura de uma linha do arquivo

        SepararDados(linha, &nota);
        // separa as informações da linha em uma estrutura de dados
        if ((nota.freq > fmin) && (nota.freq < fmax))

        {

            printf("%i\t%i\t%i\n", nota.freq, nota.duracao, nota.oitava);
            Beep(nota.freq * nota.oitava, nota.duracao);
        }
    }

    fclose(arq);
    // fecha o arquivo
    return 0;
}
