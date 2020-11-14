//19.02009-0 Renan Scheidt Reschke
//19.00980-0 Diego Minharro Alves Gimenez
//19.01370-0 Felipe Freitas Villani

#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#define MAX 500

void ExibirTabela(sqlite3_stmt *stmt)
{
    int i;
    // exibe o cabeçalho
    for (i = 0; i < sqlite3_column_count(stmt); i++)
        printf("%s\t\t", sqlite3_column_name(stmt,i));
    printf("\n");

    // para cada linha da tabela
    while(sqlite3_step(stmt) != SQLITE_DONE)
    {
        // para cada coluna da linha
        for (i = 0; i < sqlite3_column_count(stmt); i++)
            if (sqlite3_column_type(stmt, i) == SQLITE_FLOAT)
                printf("%.2f\t", sqlite3_column_double(stmt,i)); // formata valores reais com 2 casas
            else
                printf("%s\t", sqlite3_column_text(stmt,i));
        printf("\n");
    }
    printf("\n");
}

void mostraMenu()
{
    printf("Informe a opcao:\n\n1 - Consultar a precipitacao media no periodo\n2 - Consultar os dias com a temperatura maxima no periodo\n3 - Consultar os dias com a temperatura minima no periodo\n4 - Consultar a temperatura media no periodo\n0 - Sair do Sistema\n\nOpcao: ");

}

void formatarData(int dia, int mes, int ano, char *data)
{
    if (mes >= 10)
        sprintf(data,"%i-%i",ano,mes);
    else
        sprintf(data,"%i-0%i",ano,mes);
    if (dia >= 10)
        sprintf(data,"%s-%i",data,dia);
    else
        sprintf(data,"%s-0%i",data,dia);
}


int main()
{
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    char sql[MAX];
    int conexao;
    int dia, mes, ano, opcao;
    char dataIni[11], dataFim[11];

    //Abre a conexão com o banco
    conexao = sqlite3_open("Tempo.db", &db);
    if (conexao != SQLITE_OK)
    {
        printf("Erro ao conectar ao banco\n");
        exit(-1);
    }

    // laço principal
    do
    {
        // Faz a chamada do menu e a leitura da opção do usuário
        system("cls");
        mostraMenu();
        scanf("%i", &opcao);

        // se deseja fazer uma consulta
        if (opcao != 0)
        {
            // faz a leitura e formatação das datas inicial e final da consulta
            printf("\nDigite a data inicial\n");
            printf("Dia: ");
            scanf("%i", &dia);
            printf("Mes: ");
            scanf("%i", &mes);
            printf("Ano: ");
            scanf("%i", &ano);
            formatarData(dia, mes, ano, dataIni);

            printf("\nDigite a data final\n");
            printf("Dia: ");
            scanf("%i", &dia);
            printf("Mes: ");
            scanf("%i", &mes);
            printf("Ano: ");
            scanf("%i", &ano);
            formatarData(dia, mes, ano, dataFim);


            // verifica a opção desejada
            switch(opcao)
            {
            case 1:
            {
                //Realiza consulta para determinar a precipitação média no período
                sprintf(sql,"SELECT AVG(precipitacao) AS 'Precipitacao Media' FROM Medicoes WHERE data BETWEEN '%s' AND '%s'", dataIni, dataFim);
                printf("\n%s\n\n", sql); // POPPA
                sqlite3_prepare(db, sql, -1, &stmt, NULL);
                ExibirTabela(stmt);
                break;
            } // fim do case 1

            case 2:
            {
                //Realiza a conculta para determinar a temperatura máxima no período
                sprintf(sql,"SELECT data AS 'Data',tmax AS'Temperatura Maxima' FROM Medicoes WHERE (data BETWEEN '%s' AND '%s') AND tmax = (SELECT MAX(tmax) FROM Medicoes WHERE data BETWEEN '%s' AND '%s')", dataIni, dataFim, dataIni, dataFim);
                printf("\n%s\n\n", sql); // POPPA
                sqlite3_prepare(db, sql, -1, &stmt, NULL);
                ExibirTabela(stmt);
                break;
            } // fim do case 2

            case 3:
            {
                //Realiza a consulta para determinar a temperatura mínima no período
                sprintf(sql,"SELECT data AS 'Data',tmin AS'Temperatura Minima' FROM Medicoes WHERE (data BETWEEN '%s' AND '%s') AND tmin = (SELECT MIN(tmin) FROM Medicoes WHERE data BETWEEN '%s' AND '%s')", dataIni, dataFim, dataIni, dataFim);
                printf("\n%s\n\n", sql); // POPPA
                sqlite3_prepare(db, sql, -1, &stmt, NULL);
                ExibirTabela(stmt);
                break;
            } // fim do case 3
            case 4:
            {
                //Realiza consulta para determinar a temperatura média no período
                sprintf(sql,"SELECT AVG((tmax+tmin)/2) as 'Temperatura Media' FROM Medicoes WHERE data BETWEEN '%s' AND '%s'", dataIni, dataFim);
                printf("\n%s\n\n", sql); // POPPA
                sqlite3_prepare(db, sql, -1, &stmt, NULL);
                ExibirTabela(stmt);
                break;
            } // fim do case 4
            } // fim do switch
            system("pause");
        }
    }
    while(opcao != 0);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}
