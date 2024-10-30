#ifndef EXTRATO_H
#define EXTRATO_H

#include <stdio.h>

// Estrutura que representa as movimentações bancárias do cliente
struct ExtratoBancario {
    char nome[50];              // Nome do cliente
    int conta;                  // Número da conta
    float saldo_inicial;        // Saldo inicial
    float transferencia;        // Valor das transferências realizadas
    float emprestimo;           // Valor do empréstimo recebido
    float parcela_emprestimo;   // Valor da parcela do empréstimo
    int tempo_emprestimo;       // Duração do empréstimo em meses
    float parcela_financiamento; // Valor da parcela do financiamento
    int parcelas;               // Quantidade de parcelas do financiamento
    int tipo_financiamento;     // Tipo de financiamento (1 ou outro)
    float P1_sac;               // Valor da parcela SAC (Sistema de Amortização Constante)
    float rendimento_liquido;   // Rendimento líquido do CDB
    float investimento;         // Valor investido
};

// Função que gera o extrato bancário
void gerar_extrato_bancario(struct ExtratoBancario *eb);

#endif // EXTRATO_H
