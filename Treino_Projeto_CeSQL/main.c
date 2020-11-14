#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"
#define MAX 500

void ExibirTabela(sqlite3_stmt *stmt)
{
    int i;
    // exibe o cabeçalho
    for (i = 0; i < sqlite3_column_count(stmt); i++)
        printf("%15s\t\t", sqlite3_column_name(stmt,i));
    printf("\n");

    // para cada linha da tabela
    while(sqlite3_step(stmt) != SQLITE_DONE)
    {
        // para cada coluna da linha
        for (i = 0; i < sqlite3_column_count(stmt); i++)
            if (sqlite3_column_type(stmt, i) == SQLITE_INTEGER)
                printf("%15i\t\t", sqlite3_column_int(stmt,i));
            else
                printf("%15s\t\t", sqlite3_column_text(stmt,i));
        printf("\n");
    }
    printf("\n");
}

void LerString(char s1[])
{
    fflush(stdin);
    fgets(s1, MAX, stdin);
    if (s1[strlen(s1)-1] == '\n')
        s1[strlen(s1)-1] = '\0';
}

void mostraMenu()
{
    printf("Informe a opcao:\n\n1 - Cadastro de novas Ordens de Servico\n2 - Consultar Ordens de Servico\n3 - Finalizar Ordens de Servico\n0 - Sair do Sistema\n\nOpcao: ");

}

int main()
{
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    char sql[MAX];
    int conexao;
    int opcao, op_tipo = 0, op_consulta = 0, id_os, maxid = 0;
    char setor[15], status[15], tempo[15]; //tipo str

    //Abre a conexão com o banco
    conexao = sqlite3_open("OS.db", &db);
    if (conexao != SQLITE_OK)
    {
        printf("Erro ao conectar ao banco\n");
        exit(-1);
    }

    // laço principal
    do
    {
        sqlite3_prepare(db, "SELECT MAX(id) FROM manutencao;", -1, &stmt, NULL);
        sqlite3_step(stmt);
        maxid = sqlite3_column_int(stmt, 0); //Atualiza o id maximo de OS
        // Faz a chamada do menu e a leitura da opção do usuário
        system("cls");
        mostraMenu();
        scanf("%i", &opcao);

        // se deseja fazer uma consulta
        if (opcao != 0)
        {
            // verifica a opção desejada
            switch(opcao)
            {
            case 1://Realiza Cadastro de novas Ordens de Serviço
            {
                printf("\nCadastro de OS\n\n");
                printf("Informe o Setor: ");
                LerString(setor);
                printf("\nInforme o Tipo:\n1 - Preditiva\n2 - Corretiva\n\nTipo: ");
                scanf("%i", &op_tipo);
                switch(op_tipo)
                {
                case 1://Cadastro de manutencao preditiva
                {
                    sprintf(sql,"INSERT INTO Manutencao (setor, tipo) VALUES ('%s', 'preditiva');", setor);
                    sqlite3_prepare(db, sql, -1, &stmt, NULL);
                    sqlite3_step(stmt);
                    break;
                }
                case 2://Cadastro de manutencao corretiva
                {
                    sprintf(sql,"INSERT INTO Manutencao (setor, tipo) VALUES ('%s', 'corretiva');", setor);
                    sqlite3_prepare(db, sql, -1, &stmt, NULL);
                    sqlite3_step(stmt);
                    break;
                }
                }//Fim do switch op_tipo
                break;
            } // fim do case 1

            case 2://Realiza Consulta de Ordens de Serviço
            {
                printf("\nConsulta de OS\n\n");
                printf("Informe o Tipo:\n1 - Por Setor\n2 - Status 'aberta'\n3 - Status 'Concluida'\n\nTipo: ");
                scanf("%i", &op_consulta);
                switch(op_consulta)
                {
                case 1://Consulta de OS por setor
                {
                    printf("Digite o Setor: ");
                    LerString(setor);
                    sprintf(sql,"SELECT id AS 'ID', setor AS'Setor', tipo AS 'Tipo', status AS 'Status', tempo_exec AS 'Tempo de execucao' FROM Manutencao WHERE setor = '%s';", setor);
                    sqlite3_prepare(db, sql, -1, &stmt, NULL);
                    ExibirTabela(stmt);
                    break;
                }//Fim consulta por setor
                case 2://Consulta de OS por Status 'aberta'
                {
                    sprintf(sql,"SELECT id AS 'ID', setor AS'Setor', tipo AS 'Tipo', status AS 'Status', tempo_exec AS 'Tempo de execucao' FROM Manutencao WHERE status = 'aberta';");
                    sqlite3_prepare(db, sql, -1, &stmt, NULL);
                    ExibirTabela(stmt);
                    break;
                }//Fim consulta por Status 'aberta'
                case 3://Consulta de OS por Status 'Concluida'
                {
                    sprintf(sql,"SELECT id AS 'ID', setor AS'Setor', tipo AS 'Tipo', status AS 'Status', tempo_exec AS 'Tempo de execucao' FROM Manutencao WHERE status = 'concluida';");
                    sqlite3_prepare(db, sql, -1, &stmt, NULL);
                    ExibirTabela(stmt);
                    break;
                }//Fim consulta por Status 'Concluida'
                }//Fim da analise do tipo de consulta
                break;
            } // fim do case 2

            case 3://Finaliza Ordem de Serviço
            {
                do
                {
                    printf("Digite um numero de OS valido: ");
                    scanf("%i", &id_os);
                    printf("\n");
                }
                while((id_os<=0) || (id_os>maxid)); //Testa se o numero de OS inserido é válido
                sprintf(sql,"SELECT status FROM Manutencao WHERE id = %i;", id_os);
                sqlite3_prepare(db, sql, -1, &stmt, NULL);
                sqlite3_step(stmt);
                if(strcmp(sqlite3_column_text(stmt, 0),"aberta") == 0)//Verifica se a OS está com status 'aberta'
                {
                    printf("Digite o tempo de execucao: ");
                    LerString(tempo);
                    sprintf(sql,"UPDATE Manutencao SET tempo_exec = '%s', status = 'concluida' WHERE id = %i;", tempo, id_os);
                    sqlite3_prepare(db, sql, -1, &stmt, NULL);
                    sqlite3_step(stmt);
                }
                else//Caso a OS já tenha sido finalizada
                    printf("OS ja marcada como finalizada.\n");
                break;
            } // fim do case 3
            } // fim do switch
            system("pause");
        }
    }
    while(opcao != 0);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}
