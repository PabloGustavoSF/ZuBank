#include "extrato.h"

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

void lerRelatorioEntrada(FILE *file, Extrato *extrato, Transferencia *transfers, int nTransfers, Investimento **investimentos, int nInvestimentos, Emprestimo **emprestimos, int nEmprestimos) {
    fprintf(file, "===== RELATÓRIO DE ENTRADA =====\n");
    fprintf(file, "Saldo Inicial: R$%.2f\n", extrato->saldo_inicial);

    float totalTransferencias = 0.0;
    for (int i = 0; i < nTransfers; i++) {
        totalTransferencias += transfers[i].valor_transferencia;
    }
    extrato->transferencias = totalTransferencias;
    fprintf(file, "Transferências Recebidas: R$%.2f\n", totalTransferencias);

    float totalRendimentos = 0.0;
    for (int i = 0; i < nInvestimentos; i++) {
        totalRendimentos += investimentos[i]->rendimento_liquido;
    }
    extrato->rendimento_liquido = totalRendimentos;
    fprintf(file, "Rendimento Líquido do CDB: R$%.2f\n", totalRendimentos);

    float totalEmprestimos = 0.0;
    for (int i = 0; i < nEmprestimos; i++) {
        totalEmprestimos += emprestimos[i]->valor_emprestimo;
    }
    extrato->emprestimo = totalEmprestimos;
    fprintf(file, "Empréstimo Recebido: R$%.2f\n\n", totalEmprestimos);
}

void lerRelatorioSaida(FILE *file, Extrato *extrato, Transferencia *transfers, int nTransfers, Emprestimo **emprestimos, int nEmprestimos, Financiamento **financiamentos, int nFinanciamentos) {
    fprintf(file, "===== RELATÓRIO DE SAÍDA =====\n");

    float totalTransferencias = 0.0;
    for (int i = 0; i < nTransfers; i++) {
        totalTransferencias += transfers[i].valor_transferencia;
    }
    fprintf(file, "Transferências Realizadas: R$%.2f\n", totalTransferencias);

    float totalParcelasEmprestimo = 0.0;
    for (int i = 0; i < nEmprestimos; i++) {
        totalParcelasEmprestimo += emprestimos[i]->valor_parcela;
    }
    extrato->parcelas_emprestimo = totalParcelasEmprestimo;
    fprintf(file, "Parcelas do Empréstimo (Total): R$%.2f\n", totalParcelasEmprestimo);

    float totalParcelasFinanciamento = 0.0;
    for (int i = 0; i < nFinanciamentos; i++) {
        totalParcelasFinanciamento += financiamentos[i]->valor_parcela;
    }
    extrato->parcelas_financiamento = totalParcelasFinanciamento;
    fprintf(file, "Parcelas do Financiamento (Total): R$%.2f\n", totalParcelasFinanciamento);
}

void calcularESalvarSaldoFinal(FILE *file, Extrato *extrato) {
    extrato->saldo_final = extrato->saldo_inicial + extrato->rendimento_liquido + extrato->emprestimo
                          - (extrato->transferencias + extrato->parcelas_emprestimo + extrato->parcelas_financiamento);
    fprintf(file, "\nSaldo Final: R$%.2f\n", extrato->saldo_final);
}

void finalizarExtrato(FILE *file) {
    fclose(file);
    printf("EXTRATO BANCÁRIO GERADO COM SUCESSO!\n");
}

void gerarExtratoBancario(Cliente *cliente, Transferencia *transfers, int nTransfers, Investimento **investimentos, int nInvestimentos, Emprestimo **emprestimos, int nEmprestimos, Financiamento **financiamentos, int nFinanciamentos) {
    FILE *file;
    Extrato extrato = {0};
    extrato.saldo_inicial = cliente->saldo_inicial;

    criarExtrato(&file, cliente);
    if (file != NULL) {
        lerRelatorioEntrada(file, &extrato, transfers, nTransfers, investimentos, nInvestimentos, emprestimos, nEmprestimos);
        lerRelatorioSaida(file, &extrato, transfers, nTransfers, emprestimos, nEmprestimos, financiamentos, nFinanciamentos);
        calcularESalvarSaldoFinal(file, &extrato);
        finalizarExtrato(file);
    }
}
