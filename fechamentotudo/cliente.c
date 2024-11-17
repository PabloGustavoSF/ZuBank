// cliente.c
#include <stdio.h>
#include "cliente.h"

// Função para criar o arquivo de relatório de fechamento
void criarRelatorioFechamento(FILE **file, Cliente *cliente) {
    *file = fopen("RELATORIO_DE_FECHAMENTO.txt", "w");
    if (*file == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DO RELATÓRIO DE FECHAMENTO!\n");
        return;
    }

    fprintf(*file, "RELATÓRIO DE FECHAMENTO DE CONTA\n\n");
    fprintf(*file, "Nome do Cliente: %s\n", cliente->nome);
    fprintf(*file, "Número da Conta: %d\n", cliente->conta);
}

// Função para ler e registrar os dados de fechamento no relatório
void lerDadosFechamento(FILE *file, Cliente *cliente) {
    fprintf(file, "\n===== RESUMO DAS TRANSAÇÕES =====\n");
    fprintf(file, "Saldo Inicial: R$%.2f\n", cliente->saldo_inicial);
    fprintf(file, "Transferências Realizadas: R$%.2f\n", cliente->transferencias);
    fprintf(file, "Rendimento Líquido de Investimento: R$%.2f\n", cliente->rendimento_liquido);
    fprintf(file, "Empréstimo Recebido: R$%.2f\n", cliente->emprestimo);
    fprintf(file, "Parcelas de Empréstimo (Total): R$%.2f\n", cliente->parcelas_emprestimo);
    fprintf(file, "Parcelas de Financiamento (Total): R$%.2f\n", cliente->parcelas_financiamento);
}

// Função para calcular e registrar o saldo final no relatório
void atualizarSaldoFinalFechamento(FILE *file, Cliente *cliente) {
    cliente->saldo_final = cliente->saldo_inicial + cliente->rendimento_liquido + cliente->emprestimo
                          - (cliente->transferencias + cliente->parcelas_emprestimo + cliente->parcelas_financiamento);
    fprintf(file, "\nSaldo Final após todas as movimentações: R$%.2f\n", cliente->saldo_final);
}

// Função para fechar o arquivo de relatório
void finalizarRelatorioFechamento(FILE *file) {
    fclose(file);
    printf("RELATÓRIO DE FECHAMENTO DE CONTA GERADO COM SUCESSO!\n");
}

// Função principal que gera o relatório de fechamento de conta
void gerarRelatorioFechamentoConta(Cliente *cliente) {
    FILE *file;
    criarRelatorioFechamento(&file, cliente);
    if (file != NULL) {
        lerDadosFechamento(file, cliente);
        atualizarSaldoFinalFechamento(file, cliente);
        finalizarRelatorioFechamento(file);
    }
}
