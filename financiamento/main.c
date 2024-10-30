// main.c

#include <stdio.h>
#include "financiamento.h"

int main() {
    struct Financiamento financiamento;

    // Criar um financiamento com valores iniciais
    createFinanciamento(&financiamento, 50000.0, 24, Jm); // R$50,000, 24 parcelas, juros mensal

    printf("Dados do financiamento inicial:\n");
    readFinanciamento(&financiamento);

    // Calcular e gerar relatório no modo Price
    printf("\nGerando relatório de financiamento no sistema Price...\n");
    Price(&financiamento);

    // Calcular e gerar relatório no modo SAC
    printf("\nGerando relatório de financiamento no sistema SAC...\n");
    Sac(&financiamento);

    // Atualizar financiamento com novos dados
    updateFinanciamento(&financiamento, 75000.0, 36, Jm); // R$75,000, 36 parcelas, juros mensal
    printf("\nDados do financiamento após atualização:\n");
    readFinanciamento(&financiamento);

    // Excluir financiamento
    deleteFinanciamento(&financiamento);
    printf("\nDados do financiamento após exclusão:\n");
    readFinanciamento(&financiamento);

    return 0;
}
