// extrato.c
#include <stdio.h>
#include "extrato.h"

// Função para criar o arquivo de extrato bancário
void criarExtrato(FILE **file, Cliente *cliente) {
    *file = fopen("EXTRATO BANCÁRIO.txt", "w");
    if (*file == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DO EXTRATO BANCÁRIO!\n");
        return;
    }
    
    fprintf(*file, "EXTRATO BANCÁRIO - BANCO ZUBANK\n\n");
    fprintf(*file, "Nome do Cliente: %s\n", cliente->nome);
    fprintf(*file, "Número da Conta: %d\n\n", cliente->conta);
}

// Função para ler e registrar entradas no extrato (saldo inicial, rendimento, empréstimo)
void lerRelatorioEntrada(FILE *file, Extrato *extrato) {
    fprintf(file, "===== RELATÓRIO DE ENTRADA =====\n");
    fprintf(file, "Saldo Inicial: R$%.2f\n", extrato->saldo_inicial);
    fprintf(file, "Transferências Recebidas: R$%.2f\n", 0.0); // Placeholder
    fprintf(file, "Rendimento Líquido do CDB: R$%.2f\n", extrato->rendimento_liquido);
    fprintf(file, "Empréstimo Recebido: R$%.2f\n\n", extrato->emprestimo);
}

// Função para ler e registrar saídas no extrato (transferências, parcelas de empréstimo e financiamento)
void lerRelatorioSaida(FILE *file, Extrato *extrato) {
    fprintf(file, "===== RELATÓRIO DE SAÍDA =====\n");
    fprintf(file, "Transferências Realizadas: R$%.2f\n", extrato->transferencias);
    fprintf(file, "Parcelas do Empréstimo (Total): R$%.2f\n", extrato->parcelas_emprestimo);
    fprintf(file, "Parcelas do Financiamento (Total): R$%.2f\n", extrato->parcelas_financiamento);
}

// Calcula e escreve o saldo final no extrato
void calcularESalvarSaldoFinal(FILE *file, Extrato *extrato) {
    extrato->saldo_final = extrato->saldo_inicial + extrato->rendimento_liquido + extrato->emprestimo
                          - (extrato->transferencias + extrato->parcelas_emprestimo + extrato->parcelas_financiamento);
    fprintf(file, "\nSaldo Final: R$%.2f\n", extrato->saldo_final);
}

// Finaliza o arquivo do extrato
void finalizarExtrato(FILE *file) {
    fclose(file);
    printf("EXTRATO BANCÁRIO GERADO COM SUCESSO!\n");
}

// Função principal para gerar o extrato bancário
void gerarExtratoBancario(Cliente *cliente) {
    FILE *file;
    criarExtrato(&file, cliente);
    if (file != NULL) {
        lerRelatorioEntrada(file, &cliente->extrato);
        lerRelatorioSaida(file, &cliente->extrato);
        calcularESalvarSaldoFinal(file, &cliente->extrato);
        finalizarExtrato(file);
    }
}
