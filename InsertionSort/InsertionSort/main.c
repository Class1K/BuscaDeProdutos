// 19.02009-0 Renan Scheidt Reschke
// 19.01370-0 Felipe Freitas Villani

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void LerString(char s[])
{
  setbuf(stdin, 0);
  // ou fflush(stdin);
  fgets(s, MAX, stdin);
  if (s[strlen(s)-1] == '\n')
      s[strlen(s)-1] = '\0';
}

int main() {
    char op;
    Dados dados;
    TLista *lista;
    lista = CriarLista();
    do {
        printf("valor: ");
        scanf("%f",&dados.valor);
        printf("texto: ");
        LerString(dados.texto);
        InserirEmOrdem(lista, dados);
        printf("Mais itens (S/N)? ");
        scanf("%c", &op);
    } while (toupper(op) != 'N');
    ExibirLista(lista);
    lista = DestruirLista(lista);
    return 0;
}
