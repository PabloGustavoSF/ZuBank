#include <stdio.h>
#include "cliente.h"

// Função para gerar o relatório de fechamento de conta
void gerarRelatorioFechamento(Cliente cliente) {
    FILE *file6 = fopen("RELATORIO_DE_FECHAMENTO.txt", "w"); // file6 é uma variável local
    if (file6 == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DO RELATÓRIO DE FECHAMENTO!\n");
        return;
    }

    // Escrevendo dados de fechamento de conta
    fprintf(file6, "RELATÓRIO DE FECHAMENTO DE CONTA\n\n");
    fprintf(file6, "Nome do Cliente: %s\n", cliente.nome);
    fprintf(file6, "Número da Conta: %d\n", cliente.conta);
    fprintf(file6, "Saldo Inicial: R$%.2f\n", cliente.saldo_inicial);
    fprintf(file6, "Saldo Final: R$%.2f\n", cliente.saldo_final);

    fclose(file6);
    printf("RELATÓRIO DE FECHAMENTO DE CONTA GERADO COM SUCESSO!\n");
}
