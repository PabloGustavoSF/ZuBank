// investiment.c
#include "investiment.h"

// Implementacao da funcao que realiza o investimento no CDB e gera o relatorio
void investiment(float saldo_final, Investimento *investimento_data) {
    do {
        printf("Quanto do saldo disponível (R$%.2f) deseja investir?\n", saldo_final);
        scanf("%f", &investimento_data->investimento);
    } while (investimento_data->investimento > saldo_final);

    do {
        printf("Por quantos meses deseja deixar o valor investido?\n");
        scanf("%d", &investimento_data->meses_investidos);
    } while (investimento_data->meses_investidos < 0);

    // Definindo a alíquota do imposto de renda com base no tempo de investimento
    if (investimento_data->meses_investidos <= 6) {
        investimento_data->ir = 0.225;
    } else if (investimento_data->meses_investidos <= 12) {
        investimento_data->ir = 0.2;
    } else if (investimento_data->meses_investidos <= 24) {
        investimento_data->ir = 0.175;
    } else {
        investimento_data->ir = 0.15;
    }

    // Cálculo dos rendimentos
    investimento_data->rendimento_bruto = investimento_data->investimento * pow(1.009542, investimento_data->meses_investidos);
    investimento_data->rendimento_liquido = investimento_data->rendimento_bruto - ((investimento_data->rendimento_bruto - investimento_data->investimento) * investimento_data->ir);
    saldo_final += investimento_data->rendimento_liquido - investimento_data->investimento;

    // Geração do relatório de rendimentos
    FILE *file2 = fopen("RELATORIO DE RENDIMENTOS.txt", "w");
    if (file2 == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DO RELATÓRIO DE RENDIMENTOS!\n");
        return;
    }

    fprintf(file2, "RELATÓRIO DE RENDIMENTOS\n\n\n");
    fprintf(file2, "VALOR INVESTIDO: R$%.2f\n", investimento_data->investimento);
    fprintf(file2, "MESES CORRIDOS: %d meses\n", investimento_data->meses_investidos);
    fprintf(file2, "ALÍQUOTA DO IMPOSTO DE RENDA: %.2f%%\n", investimento_data->ir * 100);
    fprintf(file2, "RENDIMENTO BRUTO: R$%.2f\n", investimento_data->rendimento_bruto - investimento_data->investimento);
    fprintf(file2, "RENDIMENTO LÍQUIDO: R$%.2f\n", investimento_data->rendimento_liquido - investimento_data->investimento);

    fclose(file2);
    printf("CONFIRA O SEU RELATÓRIO DE RENDIMENTOS!\n");
}

