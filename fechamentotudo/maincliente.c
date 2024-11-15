// main.c

#include <stdio.h>
#include <locale.h>
#include "cliente.h"

int main() {
    setlocale(LC_CTYPE, "Portuguese_Brazil");

    // Instância da struct Cliente e inicialização de dados
    Cliente cliente;

    printf("SEJA BEM-VINDO AO BANCO ZUBANK!\n\n");
    printf("Qual o seu nome?\n");
    gets(cliente.nome);
    printf("Qual o seu saldo bancário?\n");
    scanf("%f", &cliente.saldo_inicial);
    cliente.saldo_final = cliente.saldo_inicial;
    printf("Qual o número da sua conta bancária?\n");
    scanf("%d", &cliente.conta);

    // Gera o relatório de fechamento de conta chamando a função
    gerarRelatorioFechamento(cliente);

    return 0;
}
