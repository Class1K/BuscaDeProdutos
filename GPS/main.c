// 19.02009-0   Renan Scheidt Reschke
// 19.01370-0   Felipe Freitas Villani
// 19.00980-0   Diego Minharro Alves Gimenez

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 255
#define Ro 6372795.477598
#define rad(AnguloEmGraus) ((AnguloEmGraus)*M_PI / 180.0)

// **************************************
//    Criar a estrutura de dados GPS
// **************************************
typedef struct
{
    float lat, lon, alt;
    int tempo;
} GPS;
// **************************************

// **************************************
//        Prot�tipos das fun��es
// **************************************
void LerLinha(char[], FILE *);
void Trocar(char[], char, char);
void SepararDados(char[], int, char, GPS *);
float CalcularDistancia(GPS, GPS);
float Velocidade(GPS, GPS);
// **************************************

int main()
{
    // *******************************************
    //   declara��o das vari�veis
    // *******************************************
    FILE *entrada, *saida;
    GPS pat, pan;
    float distancia = 0, vel;
    char linha[MAX];

    // *******************************************

    // *******************************************
    //    abertura do arquivo de entrada
    // *******************************************
    entrada = fopen("rio_do_ouro.csv", "r");
    if (entrada == NULL)
    {
        printf("Nao conseguiu abrir ENTRADA.");
        exit(EXIT_FAILURE);
    }

    // *******************************************

    // *******************************************
    //    abertura do arquivo de saida
    // *******************************************
    saida = fopen("rio_do_ouro_novo.csv", "w");
    if (saida == NULL)
    {
        printf("Nao conseguiu abrir SAIDA.");
        exit(EXIT_FAILURE);
    }

    // *******************************************

    // *******************************************
    //    Ler o cabe�alho do arquivo
    // *******************************************
    LerLinha(linha, entrada);
    sprintf(linha, "%s; vel (km/h)\n", linha);
    fprintf(saida, "%s", linha);

    // *******************************************

    // *******************************************
    //    Ler o primeiro dado do arquivo
    //    e armazenar como um "ponto anterior"
    // *******************************************
    LerLinha(linha, entrada);
    Trocar(linha, ',', '.');
    SepararDados(linha, 4, ';', &pan);
    sprintf(linha, "%s;0\n", linha);
    Trocar(linha, '.', ',');
    printf(linha);
    fprintf(saida, "%s", linha);
    // *******************************************

    // *******************************************
    //    Ler os demais dados do arquivo
    // *******************************************
    while (!feof(entrada))
    {
        // *********************************************
        //    Ler uma linha e separar os dados do ponto
        // *********************************************
        LerLinha(linha, entrada);
        Trocar(linha, ',', '.');
        SepararDados(linha, 4, ';', &pat);
        // *******************************************

        // *****************************************************
        //   Se o "tempo atual" for igual ao "tempo anterior"
        //   OU
        //   se todas as coordenadas do "ponto atual" forem
        //    iguais as do "ponto anterior"
        //   O PONTO DEVE SER IGNORADO
        // *****************************************************
        if (!((pan.tempo == pat.tempo) || ((pan.lat == pat.lat) && (pan.lon == pat.lon) && (pan.alt == pat.alt))))
        {

            // **********************************************************************
            //  calcular a dist�ncia entre o "ponto atual" e o "ponto antrior" em m,
            //  calcular o somat�rio da dist�ncia total em m,
            //  calcular a velocidade instant�nea em km/s
            //  exibir o que foi processado
            //  acrescantar ao novo arquivo as informa��es lidas e a velocidade
            // **********************************************************************
            distancia += CalcularDistancia(pan, pat);
            vel = Velocidade(pan, pat);
            sprintf(linha, "%s;%f\n", linha, vel);
            Trocar(linha, '.', ',');
            printf(linha);
            fprintf(saida, "%s", linha);
            // *******************************************

        } // fim do if
        // *******************************************

        // *******************************************
        //    Atualizar o "ponto anterior"
        // *******************************************
        pan = pat;
        // *******************************************
    } // fim do while

    // *******************************************
    //    exibir o total percorrido
    // *******************************************
    printf("Total percorrido: %f", distancia);
    // *******************************************

    // *******************************************
    //    Fechar os arquivos
    // *******************************************
    fclose(entrada);
    fclose(saida);
    // *******************************************

    return 0;
}

// **************************************
//       Ler uma linha do arquivo
// **************************************
void LerLinha(char linha[], FILE *arq)
{
    fgets(linha, MAX, arq);
    if (linha[strlen(linha) - 1] == '\n')
        linha[strlen(linha) - 1] = '\0';
}
// **************************************

// **************************************
//  Trocar o caractere antigo pelo novo
// **************************************
void Trocar(char linha[], char antigo, char novo)
{
    int i;
    for (i = 0; i < strlen(linha); i++)
        if (linha[i] == antigo)
            linha[i] = novo;
}
// **************************************

// ********************************************
//  Divide uma string pelo caractere separador
//  nos campos da estrutura de dados GPS
// ********************************************
void SepararDados(char linha[], int quantidade,
                  char separador, GPS *valores)
{
    int i, j, c;
    char temp[80];
    char valorestxt[4][80]; /* GPS tem 4 campos*/
    c = 0;
    for (i = 0; i < quantidade; i++)
    {
        j = 0;
        while (linha[c] != separador && c < strlen(linha))
        {
            temp[j] = linha[c];
            c++;
            j++;
        }
        c++; /* pular o separador */
        temp[j] = '\0';
        strcpy(valorestxt[i], temp);

        // **************************************************
        //  fa�a convers�o das 4 strings do vetor valorestxt
        //  para os 3 campos float e 1 int da estrutura GPS
        // **************************************************
        (*valores).lat = atof(valorestxt[0]);
        (*valores).lon = atof(valorestxt[1]);
        (*valores).alt = atof(valorestxt[2]);
        (*valores).tempo = atoi(valorestxt[3]);
    }

    // ****************************************************
}
// **************************************

// *******************************************
//  Retorna a dist�ncia entre os pontos A e B
// *******************************************
float CalcularDistancia(GPS A, GPS B)
{
    float DT, dh, dv;

    dv = B.alt - A.alt;
    dh = Ro * acos(sin(rad(A.lat)) * sin(rad(B.lat)) + cos(rad(A.lat)) * cos(rad(B.lat)) * cos(rad(A.lon - B.lon)));
    DT = sqrt(pow(dh, 2) + pow(dv, 2));

    return DT;
}
// **************************************

// *******************************************
//  Retorna a velocidade entre os pontos A e B
// *******************************************
float Velocidade(GPS A, GPS B)
{
    float vel;
    vel = 3.6 * CalcularDistancia(A, B) / (B.tempo - A.tempo);

    return vel;
}
// **************************************
