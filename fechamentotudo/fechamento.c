#include <stdio.h>
#include "fechamento.h"

// Calcula o saldo final após todas as transações
float calcular_saldo_final(float saldo_inicial, float rendimento_liquido, float emprestimo, float saida) {
    return saldo_inicial + rendimento_liquido + emprestimo - saida;
}

// Calcula o total de saída, considerando transferências, parcelas de empréstimo e financiamento
float calcular_total_saida(float transferencia, float parcela_emprestimo, int tempo_emprestimo, float val_financ, int parcelas) {
    return transferencia + (parcela_emprestimo * tempo_emprestimo) + (val_financ * parcelas);
}

// Gera o relatório de fechamento de conta em um arquivo de texto
void gerar_relatorio_fechamento(const char *nome, int conta, float saldo_inicial, float saldo_final, float transferencia, float rendimento_liquido, float emprestimo, float parcela_emprestimo_total, float val_financ_total) {
    FILE *file = fopen("RELATORIO DE FECHAMENTO.txt", "w");
    if (file == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DO RELATÓRIO DE FECHAMENTO!\n");
        return;
    }

    // Escrevendo os dados no relatório de fechamento
    fprintf(file, "RELATÓRIO DE FECHAMENTO DE CONTA\n\n");
    fprintf(file, "Nome do Cliente: %s\n", nome);
    fprintf(file, "Número da Conta: %d\n", conta);
    fprintf(file, "Saldo Inicial: R$%.2f\n", saldo_inicial);
    fprintf(file, "Saldo Final: R$%.2f\n", saldo_final);
    
    // Resumo das transações
    fprintf(file, "\n===== RESUMO DAS TRANSAÇÕES =====\n");
    fprintf(file, "Transferências Realizadas: R$%.2f\n", transferencia);
    fprintf(file, "Rendimento Líquido de Investimento: R$%.2f\n", rendimento_liquido);
    fprintf(file, "Empréstimo Recebido: R$%.2f\n", emprestimo);
    fprintf(file, "Parcelas do Empréstimo (Total): R$%.2f\n", parcela_emprestimo_total);
    fprintf(file, "Parcelas do Financiamento (Total): R$%.2f\n", val_financ_total);

    fclose(file);
    printf("RELATÓRIO DE FECHAMENTO DE CONTA GERADO COM SUCESSO!\n");
}
