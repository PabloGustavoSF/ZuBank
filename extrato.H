#ifndef EXTRATO_H
#define EXTRATO_H

#include <stdio.h>

// Estrutura para armazenar os dados do extrato bancário
struct Extrato {
    char nome[50];
    int conta;
    float saldo_inicial;
    float rendimento_liquido;
    float emprestimo;
    float transferencia;
    float parcela_emprestimo;
    float parcela_financiamento;
    int tempo_emprestimo;
    int parcelas;
    float saldo_final;
};

// Função para calcular a saída total (empréstimos, transferências e financiamentos)
float calcular_saida(struct Extrato *e, int tipo_financiamento, float P1_sac) {
    float val_financ = (tipo_financiamento == 1) ? e->parcela_financiamento : P1_sac;
    return e->transferencia + (e->parcela_emprestimo * e->tempo_emprestimo) + (val_financ * e->parcelas);
}

// Função para calcular o saldo final após todas as operações
float calcular_saldo_final(struct Extrato *e, float saida) {
    return e->saldo_inicial + e->rendimento_liquido + e->emprestimo - saida;
}

// Função para gerar o relatório de extrato bancário em um arquivo .txt
void gerar_extrato(struct Extrato *e, int tipo_financiamento, float P1_sac) {
    FILE *file5 = fopen("EXTRATO BANCÁRIO.txt", "w");

    if (file5 == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DO EXTRATO BANCÁRIO!\n");
        return;
    }

    // Cabeçalho do extrato
    fprintf(file5, "EXTRATO BANCÁRIO - BANCO ZUBANK\n\n");
    fprintf(file5, "Nome do Cliente: %s\n", e->nome);
    fprintf(file5, "Número da Conta: %d\n\n", e->conta);

    // Relatório de Entrada
    fprintf(file5, "===== RELATÓRIO DE ENTRADA =====\n");
    fprintf(file5, "Saldo Inicial: R$%.2f\n", e->saldo_inicial);
    fprintf(file5, "Transferências Recebidas: R$%.2f\n", 0.0); // Placeholder
    fprintf(file5, "Rendimento Líquido do CDB: R$%.2f\n", e->rendimento_liquido);
    fprintf(file5, "Empréstimo Recebido: R$%.2f\n\n", e->emprestimo);

    // Relatório de Saída
    float saida = calcular_saida(e, tipo_financiamento, P1_sac);
    fprintf(file5, "===== RELATÓRIO DE SAÍDA =====\n");
    fprintf(file5, "Transferências Realizadas: R$%.2f\n", e->transferencia);
    fprintf(file5, "Parcelas do Empréstimo (Total): R$%.2f\n", e->parcela_emprestimo * e->tempo_emprestimo);
    fprintf(file5, "Parcelas do Financiamento (Total): R$%.2f\n", (tipo_financiamento == 1) ? 
        e->parcela_financiamento * e->parcelas : P1_sac * e->parcelas);

    // Cálculo e exibição do saldo final
    e->saldo_final = calcular_saldo_final(e, saida);
    fprintf(file5, "\nSaldo Final: R$%.2f\n", e->saldo_final);

    fclose(file5);
    printf("CONFIRA SEU EXTRATO BANCÁRIO!\n");
}

#endif // EXTRATO_H
