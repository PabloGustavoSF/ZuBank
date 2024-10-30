#include "extrato.h"

void gerar_extrato_bancario(struct ExtratoBancario *eb) {
    FILE *file5;
    float val_financ, saida, saldo_atualizado;

    // Calcula o valor do financiamento com base no tipo escolhido
    val_financ = (eb->tipo_financiamento == 1) ? eb->parcela_financiamento : eb->P1_sac;

    // Calcula a saída total (transferência, parcelas de empréstimo e financiamento)
    saida = eb->transferencia + (eb->parcela_emprestimo * eb->tempo_emprestimo) + (val_financ * eb->parcelas);

    // Cria o arquivo de extrato bancário
    file5 = fopen("EXTRATO_BANCARIO.txt", "w");
    if (file5 == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DO EXTRATO BANCÁRIO!\n");
        return;
    }

    // Cabeçalho do extrato
    fprintf(file5, "EXTRATO BANCÁRIO - BANCO ZUBANK\n\n");
    fprintf(file5, "Nome do Cliente: %s\n", eb->nome);
    fprintf(file5, "Número da Conta: %d\n\n", eb->conta);

    // Relatório de Entrada
    fprintf(file5, "===== RELATÓRIO DE ENTRADA =====\n");
    fprintf(file5, "Saldo Inicial: R$%.2f\n", eb->saldo_inicial);
    fprintf(file5, "Transferências Recebidas: R$%.2f\n", 0.0); // Placeholder
    fprintf(file5, "Rendimento Líquido do CDB: R$%.2f\n", eb->rendimento_liquido - eb->investimento);
    fprintf(file5, "Empréstimo Recebido: R$%.2f\n\n", eb->emprestimo);

    // Relatório de Saída
    fprintf(file5, "===== RELATÓRIO DE SAÍDA =====\n");
    fprintf(file5, "Transferências Realizadas: R$%.2f\n", eb->transferencia);
    fprintf(file5, "Parcelas do Empréstimo (Total): R$%.2f\n", eb->parcela_emprestimo * eb->tempo_emprestimo);
    fprintf(file5, "Parcelas do Financiamento (Total): R$%.2f\n", val_financ * eb->parcelas);

    // Cálculo e exibição do saldo final após todas as movimentações
    saldo_atualizado = eb->saldo_inicial + eb->rendimento_liquido + eb->emprestimo - saida;
    fprintf(file5, "\nSaldo Final: R$%.2f\n", saldo_atualizado);

    fclose(file5);

    printf("CONFIRA SEU EXTRATO BANCÁRIO!\n");
}
