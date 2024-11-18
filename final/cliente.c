#include <stdio.h>
#include "cliente.h"

// Função para gerar o relatório de fechamento de conta
void gerar_relatorio_fechamento(Cliente *cliente) {
    FILE *file = fopen("RELATORIO_DE_FECHAMENTO.txt", "w");
    if (file == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DO RELATORIO DE FECHAMENTO!\n");
        return;
    }

    // Cabeçalho do relatório
    fprintf(file, "RELATORIO DE FECHAMENTO DE CONTA - BANCO ZUBANK\n\n");
    fprintf(file, "Nome do Cliente: %s\n", cliente->nome);
    fprintf(file, "Numero da Conta: %d\n\n", cliente->conta);

    // Relatório de Entrada
    fprintf(file, "===== RELATORIO DE ENTRADA =====\n");
    fprintf(file, "Saldo Inicial: R$%.2f\n", cliente->saldo_inicial);
    fprintf(file, "Rendimento Liquido de Investimento: R$%.2f\n", cliente->rendimento_liquido);
    fprintf(file, "Emprestimos Recebidos: R$%.2f\n\n", cliente->emprestimos_recebidos);

    // Relatório de Saída
    fprintf(file, "===== RELATORIO DE SAIDA =====\n");
    fprintf(file, "Transferencias Realizadas: R$%.2f\n", cliente->transferencias_realizadas);
    fprintf(file, "Parcelas de Emprestimo (Total): R$%.2f\n", cliente->parcelas_emprestimo_total);
    fprintf(file, "Parcelas de Financiamento (Total): R$%.2f\n\n", cliente->parcelas_financiamento_total);

    // Saldo Final
    fprintf(file, "Saldo Final apos todas as movimentacoes: R$%.2f\n", cliente->saldo_final);

    fclose(file);
    printf("RELATORIO DE FECHAMENTO DE CONTA GERADO COM SUCESSO!\n");
}
