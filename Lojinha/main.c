// 19.02009-0 Renan Scheidt Reschke
// 19.01370-0 Felipe Freitas Villani

#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#define MAX 150

int menu()
{
    int op;
    system("CLS");
    printf("1 - Nova Venda\n");
    printf("2 - Adicionar ao carrinho\n");
    printf("3 - Fechar Venda\n");
    printf("4 - Gerenciar Estoque\n");
    printf("5 - Sair\n");
    printf("\n");
    printf("Escolha a opcao: ");
    scanf("%i", &op);
    return op;
}

void ExibirTabela(sqlite3_stmt *stmt)
{
    int i;
    for (i = 0; i < sqlite3_column_count(stmt); i++)
        printf("%s\t\t", sqlite3_column_name(stmt,i));
    printf("\n");

    while(sqlite3_step(stmt) != SQLITE_DONE)
    {
        for (i = 0; i < sqlite3_column_count(stmt); i++)
            if (sqlite3_column_type(stmt, i) == SQLITE_FLOAT)
                printf("%10.2f\t", sqlite3_column_double(stmt,i));
            else
                printf("%s\t", sqlite3_column_text(stmt,i));
        printf("\n");
    }
    printf("\n");
};

void LerString(char s[])
{
    setbuf(stdin, 0);
    fgets(s, MAX, stdin);
    if (s[strlen(s)-1] == '\n')
        s[strlen(s)-1] = '\0';
}

int main()
{
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int conexao, op, novavenda, codProd, quant, quant_dig;
    float preco;
    char sql[MAX], nomeItem[MAX];

    // criar a conexão
    conexao = sqlite3_open("Lojinha.db", &db);
    if (conexao != SQLITE_OK)
    {
        printf("Erro ao conectar ao banco\n");
        exit(-1);
    }
    sqlite3_prepare(db, "SELECT MAX(idVenda) FROM vendas;", -1, &stmt, NULL);
    sqlite3_step(stmt);
    novavenda = sqlite3_column_int(stmt, 0);

    do
    {
        op = menu();

        switch (op)
        {
        case 1:
            sqlite3_prepare(db, "SELECT MAX(idVenda) FROM vendas;", -1, &stmt, NULL);
            sqlite3_step(stmt);
            novavenda = sqlite3_column_int(stmt, 0);
            if(novavenda == NULL)
                novavenda = 1;
            else
                novavenda += 1;
            printf("ID da venda nova: %i\n", novavenda);
            break;
        //Termina a determinação do idVenda

        case 2://Adicionar produto ao carrinho
            printf("\n");
            sqlite3_prepare(db, "SELECT * FROM estoque;", -1, &stmt, NULL);
            ExibirTabela(stmt); //Exibe a tabela do estoque
            printf("\n");
            printf("Adicionar Item ao Carrinho\n");
            printf("\n");
            printf("Digite o codigo do produto: ");
            scanf("%i", &codProd);
            sqlite3_prepare(db, "SELECT MAX(codigo) FROM estoque;", -1, &stmt, NULL);
            sqlite3_step(stmt);
            if((codProd >= 1) && (codProd <= sqlite3_column_int(stmt, 0)))//Caso o código seja válido
            {
                printf("Digite a quantidade: ");
                scanf("%i", &quant);
                quant_dig = quant;
                sprintf(sql, "SELECT quant FROM estoque WHERE codigo = %i;", codProd);
                sqlite3_prepare(db, sql, -1, &stmt, NULL);
                sqlite3_step(stmt);
                if((quant >= 1) && (quant <= sqlite3_column_int(stmt, 0)))
                {
                    sprintf(sql, "SELECT COUNT(*) FROM vendas WHERE codigo = %i AND idVenda = %i;", codProd, novavenda);
                    sqlite3_prepare(db, sql, -1, &stmt, NULL);
                    sqlite3_step(stmt);
                    if(sqlite3_column_int(stmt, 0) != 0)//Caso o item já esteja na venda atual
                    {
                        sprintf(sql, "SELECT quant FROM vendas WHERE codigo = %i AND idVenda = %i;", codProd, novavenda);
                        sqlite3_prepare(db, sql, -1, &stmt, NULL);
                        sqlite3_step(stmt);
                        quant += sqlite3_column_int(stmt, 0); //Soma as quantidades

                        sprintf(sql, "SELECT preco FROM estoque WHERE codigo = %i;", codProd);
                        sqlite3_prepare(db, sql, -1, &stmt, NULL);
                        sqlite3_step(stmt);
                        preco = quant*sqlite3_column_double(stmt, 0); //Atualiza o preço

                        sprintf(sql, "UPDATE vendas SET quant = %i, preco = %f WHERE codigo = %i AND idVenda = %i;", quant, preco, codProd, novavenda);
                        sqlite3_prepare(db, sql, -1, &stmt, NULL);
                        sqlite3_step(stmt);
                    }
                    else//Caso o item não esteja na venda atual
                    {
                        sprintf(sql, "SELECT preco FROM estoque WHERE codigo = %i;", codProd);
                        sqlite3_prepare(db, sql, -1, &stmt, NULL);
                        sqlite3_step(stmt);
                        preco = quant*sqlite3_column_double(stmt, 0);

                        sprintf(sql, "INSERT INTO vendas (idVenda, codigo, quant, preco) VALUES(%i, %i, %i, %f);", novavenda, codProd, quant, preco);
                        sqlite3_prepare(db, sql, -1, &stmt, NULL);
                        sqlite3_step(stmt);
                    }
                    sprintf(sql, "SELECT quant FROM estoque WHERE codigo = %i;", codProd);
                    sqlite3_prepare(db, sql, -1, &stmt, NULL);
                    sqlite3_step(stmt);
                    quant = sqlite3_column_int(stmt, 0) - quant_dig;

                    sprintf(sql, "UPDATE estoque SET quant = %i WHERE codigo = %i;", quant, codProd);
                    sqlite3_prepare(db, sql, -1, &stmt, NULL);
                    sqlite3_step(stmt);//Atualiza a quantidade do produto no estoque

                    sprintf(sql, "SELECT codigo, quant, preco FROM vendas WHERE idVenda = %i;", novavenda);
                    sqlite3_prepare(db, sql, -1, &stmt, NULL);
                    system("cls");
                    printf("\n");
                    printf("Venda Atual\n");
                    printf("\n");
                    ExibirTabela(stmt);//Exibe o codigo dos itens, quantidade e preço da venda atual

                    sqlite3_prepare(db, "SELECT * FROM estoque", -1, &stmt, NULL);
                    printf("\n");
                    printf("Estoque atualizado\n");
                    printf("\n");
                    ExibirTabela(stmt);//Exibe o estoque aqtualizado
                }
                else//caso a quantidade não esteja disponível em estoque
                {
                    printf("Quantidade indisponivel em estoque.\n");
                    printf("\n");
                }
            }
            else//Caso o código seja inválido
            {
                printf("Produto nao cadastrado.\n");
                printf("\n");
            }
            break;
            //Termina adição de produto ao carrinho

        case 3://Fechar venda atual
            sprintf(sql, "SELECT codigo, quant, preco FROM vendas WHERE idVenda = %i;", novavenda);
            sqlite3_prepare(db, sql, -1, &stmt, NULL);
            system("cls");
            printf("\n");
            printf("Venda Atual\n");
            printf("\n");
            ExibirTabela(stmt);//Exibe o codigo dos itens, quantidade e preço da venda atual
            printf("\n");

            sprintf(sql, "SELECT SUM(preco) FROM vendas WHERE idVenda = %i;", novavenda);
            sqlite3_prepare(db, sql, -1, &stmt, NULL);
            sqlite3_step(stmt);
            printf("Valor total: R$ %.2f\n", sqlite3_column_double(stmt, 0));//Exibe o preço total da compra
            break;
            //Fim fechar venda atual

        case 4://Atualizar estoque
            sqlite3_prepare(db, "SELECT * FROM estoque", -1, &stmt, NULL);
            printf("\n");
            printf("Estoque atualizado\n");
            printf("\n");
            ExibirTabela(stmt);//Exibe o estoque aqtualizado

            printf("Digite o codigo do produto a ser adicionado: ");
            scanf("%i", &codProd);

            sprintf(sql, "SELECT COUNT(*) FROM estoque WHERE codigo = %i;", codProd);
            sqlite3_prepare(db, sql, -1, &stmt, NULL);
            sqlite3_step(stmt);

            if(sqlite3_column_int(stmt, 0) != 0)//O produto já existe no estoque
            {
                printf("Digite a quantidade a ser adicionada: ");
                scanf("%i", &quant);

                sprintf(sql, "SELECT quant FROM estoque WHERE codigo = %i;", codProd);
                sqlite3_prepare(db, sql, -1, &stmt, NULL);
                sqlite3_step(stmt);
                quant += sqlite3_column_int(stmt, 0); //Soma as quantidades

                sprintf(sql, "UPDATE estoque SET quant = %i WHERE codigo = %i;", quant, codProd);
                sqlite3_prepare(db, sql, -1, &stmt, NULL);
                sqlite3_step(stmt);

                sqlite3_prepare(db, "SELECT * FROM estoque", -1, &stmt, NULL);
                printf("\n");
                printf("Estoque atualizado\n");
                printf("\n");
                ExibirTabela(stmt);//Exibe o estoque aqtualizado

            }
            else//Novo produto
            {
                printf("Cadastro de novo produto\n");
                printf("\n");

                printf("Digite o nome do produto: ");
                LerString(nomeItem);

                printf("Quantidade: ");
                scanf("%i", &quant);

                printf("Preco: ");
                scanf("%f", &preco);

                sprintf(sql, "INSERT INTO estoque (nome, quant, preco) VALUES('%s', %i, %f);", nomeItem, quant, preco);
                sqlite3_prepare(db, sql, -1, &stmt, NULL);
                sqlite3_step(stmt);

                sqlite3_prepare(db, "SELECT * FROM estoque", -1, &stmt, NULL);
                printf("\n");
                printf("Estoque atualizado\n");
                printf("\n");
                ExibirTabela(stmt);//Exibe o estoque aqtualizado
            }
            break;
            //Finaliza atualização do estoque
        }
        system("pause");
    }
    while (op != 5);

    // liberar memória e fehcar a conexão
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}
