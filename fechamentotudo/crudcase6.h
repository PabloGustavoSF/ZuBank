#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    int conta;
    float saldo_inicial;
    float saldo_final;
    float transferencias;
    float rendimento_liquido;
    float emprestimo;
    float parcelas_emprestimo;
    float parcelas_financiamento;
} Cliente;

void criarRelatorioFechamento(FILE **file6, Cliente *cliente) {
    *file6 = fopen("RELATORIO DE FECHAMENTO.txt", "w");
    if (*file6 == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DO RELATÓRIO DE FECHAMENTO!\n");
        return;
    }

    fprintf(*file6, "RELATÓRIO DE FECHAMENTO DE CONTA\n\n");
    fprintf(*file6, "Nome do Cliente: %s\n", cliente->nome);
    fprintf(*file6, "Número da Conta: %d\n", cliente->conta);
}

void lerDadosFechamento(FILE *file6, Cliente *cliente) {
    fprintf(file6, "\n===== RESUMO DAS TRANSAÇÕES =====\n");
    fprintf(file6, "Saldo Inicial: R$%.2f\n", cliente->saldo_inicial);
    fprintf(file6, "Transferências Realizadas: R$%.2f\n", cliente->transferencias);
    fprintf(file6, "Rendimento Líquido de Investimento: R$%.2f\n", cliente->rendimento_liquido);
    fprintf(file6, "Empréstimo Recebido: R$%.2f\n", cliente->emprestimo);
    fprintf(file6, "Parcelas de Empréstimo (Total): R$%.2f\n", cliente->parcelas_emprestimo);
    fprintf(file6, "Parcelas de Financiamento (Total): R$%.2f\n", cliente->parcelas_financiamento);
}

void atualizarSaldoFinalFechamento(FILE *file6, Cliente *cliente) {
    cliente->saldo_final = cliente->saldo_inicial + cliente->rendimento_liquido + cliente->emprestimo
                          - (cliente->transferencias + cliente->parcelas_emprestimo + cliente->parcelas_financiamento);
    fprintf(file6, "\nSaldo Final após todas as movimentações: R$%.2f\n", cliente->saldo_final);
}

void finalizarRelatorioFechamento(FILE *file6) {
    fclose(file6);
    printf("RELATÓRIO DE FECHAMENTO DE CONTA GERADO COM SUCESSO!\n");
}

// Função principal que realiza o CRUD de fechamento
void gerarRelatorioFechamentoConta(Cliente *cliente) {
    FILE *file6;
    criarRelatorioFechamento(&file6, cliente);
    if (file6 != NULL) {
        lerDadosFechamento(file6, cliente);
        atualizarSaldoFinalFechamento(file6, cliente);
        finalizarRelatorioFechamento(file6);
    }
}
