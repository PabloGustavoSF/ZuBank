#include "extrato.h"
#include <stdio.h>
#include <stdlib.h>

// Função para criar o arquivo do extrato com informações básicas do cliente
void criarExtrato(FILE **file, Cliente *cliente) {
    *file = fopen("extrato.txt", "w");
    if (*file == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DE EXTRATO!\n");
        return;
    }

    fprintf(*file, "==================== EXTRATO BANCÁRIO ====================\n");
    fprintf(*file, "Nome do Cliente: %s\n", cliente->nome);
    fprintf(*file, "Número da Conta: %d\n", cliente->conta);
    fprintf(*file, "Saldo Inicial: R$%.2f\n", cliente->saldo_inicial);
}

// Função para gerar o extrato completo com todas as informações
void gerarExtratoBancario(Cliente *cliente, Transferencia **transfers, int nTransfers,
                          Investimento **investimentos, int countInvestimentos,
                          Emprestimo **emprestimos, int countEmprestimos,
                          Financiamento **financiamentos, int countFinanciamentos) {
    FILE *file = fopen("extrato.txt", "w");
    if (file == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DE EXTRATO!\n");
        return;
    }

    // Informações do cliente
    fprintf(file, "==================== EXTRATO BANCÁRIO ====================\n");
    fprintf(file, "Nome do Cliente: %s\n", cliente->nome);
    fprintf(file, "Número da Conta: %d\n", cliente->conta);
    fprintf(file, "Saldo Inicial: R$%.2f\n", cliente->saldo_inicial);
    fprintf(file, "Saldo Final: R$%.2f\n\n", cliente->saldo_final);

    // Transferências
    fprintf(file, "==================== TRANSFERÊNCIAS ====================\n");
    if (nTransfers > 0 && transfers != NULL) {
        for (int i = 0; i < nTransfers; i++) {
            if (transfers[i] != NULL) {
                fprintf(file, "Beneficiário: %s | Conta: %d | Valor: R$%.2f\n",
                        transfers[i]->beneficiario, transfers[i]->conta_trans, transfers[i]->valor_transferencia);
            }
        }
    } else {
        fprintf(file, "Nenhuma transferência registrada.\n");
    }

    // Investimentos
    fprintf(file, "\n==================== INVESTIMENTOS ====================\n");
    if (countInvestimentos > 0 && investimentos != NULL) {
        for (int i = 0; i < countInvestimentos; i++) {
            fprintf(file, "Valor Investido: R$%.2f | Meses: %d | Rendimento Líquido: R$%.2f\n",
                    investimentos[i]->investimento,
                    investimentos[i]->meses_investidos,
                    investimentos[i]->rendimento_liquido);
        }
    } else {
        fprintf(file, "Nenhum investimento registrado.\n");
    }

    // Empréstimos
    fprintf(file, "\n==================== EMPRÉSTIMOS ====================\n");
    if (countEmprestimos > 0 && emprestimos != NULL) {
        for (int i = 0; i < countEmprestimos; i++) {
            fprintf(file, "ID: %d | Valor: R$%.2f | Parcelas: R$%.2f | Juros Totais: R$%.2f\n",
                    emprestimos[i]->id,
                    emprestimos[i]->valor_emprestimo,
                    emprestimos[i]->valor_parcela,
                    emprestimos[i]->juros_totais);
        }
    } else {
        fprintf(file, "Nenhum empréstimo registrado.\n");
    }

    // Financiamentos
    fprintf(file, "\n==================== FINANCIAMENTOS ====================\n");
    if (countFinanciamentos > 0 && financiamentos != NULL) {
        for (int i = 0; i < countFinanciamentos; i++) {
            fprintf(file, "ID: %d | Valor Financiado: R$%.2f | Parcelas: R$%.2f | Amortização: R$%.2f | Juros Totais: R$%.2f\n",
                    financiamentos[i]->id,
                    financiamentos[i]->valor_financiado,
                    financiamentos[i]->valor_parcela,
                    financiamentos[i]->amortizacao,
                    financiamentos[i]->juros_totais);
        }
    } else {
        fprintf(file, "Nenhum financiamento registrado.\n");
    }

    // Finalização
    fprintf(file, "\n==================== FINAL DO EXTRATO ====================\n");
    fprintf(file, "Obrigado por utilizar o Banco Zubank!\n");
    fclose(file);

    printf("Extrato bancário gerado com sucesso!\n");
}


// Função para fechar o arquivo do extrato
void finalizarExtrato(FILE *file) {
    if (file != NULL) {
        fclose(file);
        printf("Extrato bancário fechado com sucesso.\n");
    } else {
        printf("ERRO: Nenhum arquivo para fechar.\n");
    }
}
