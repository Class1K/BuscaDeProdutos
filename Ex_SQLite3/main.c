#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#define MAX 150

int main()
{
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int conexao, i;
    float v;
    char sql[MAX];

    printf("Criando conexao com o banco:\n");
    conexao = sqlite3_open("pokemonCenter.db", &db);

    if (conexao != SQLITE_OK)
    {
        printf("Erro ao conectar ao banco\n");
        exit(-1);
    }

    printf("Sucesso na conexao!\n");
    printf("Informe o valor: ");
    scanf("&f", &v);

    //Realiza pesquisa dentro do banco
    //sqlite3_prepare(db, "SELECT * FROM vendas", -1, &stmt, NULL);
    sprintf(sql, "SELECT * FROM vendas WHERE valor >% f", v);
    printf("%s\n\n", sql);

    sqlite3_prepare(db, sql, -1, &stmt, NULL);

    // escreve o cabeçalho com o nome das colunas
    for (i = 0; i < sqlite3_column_count(stmt); i++)
        printf("%s\t", sqlite3_column_name(stmt, i));
    printf("\n"); // termina a exibição do cabeçalho

    while (sqlite3_step(stmt) != SQLITE_DONE)
    {
        // para cada coluna
        for (i = 0; i < sqlite3_column_count(stmt); i++)
            printf("%s\t", sqlite3_column_text(stmt, i));
        printf("\n"); // termina a exibição de uma linha
    }
    //////////////////////////////////////////////////////////////
    sprintf(sql, "SELECT COUNT (*) FROM vendas WHERE valor > %f", v);
    sqlite3_prepare(db, sql, -1, &stmt, NULL);
    if(sqlite3_step(stmt)==SQLITE_ROW)
        printf("\nQuantidade de itens acima do valor: %i\n", sqlite3_column_int(stmt, 0));

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}
