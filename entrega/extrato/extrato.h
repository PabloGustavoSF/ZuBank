#ifndef EXTRATO_H
#define EXTRATO_H

#include <stdio.h>
#include "../transfer/transfer.h"
#include "../investimento/investimento.h"
#include "../emprestimo/emprestimo.h"
#include "../financiamento/financiamento.h"
#include "../cliente/cliente.h"

// Estrutura do Extrato
typedef struct {
    float saldo_inicial;         // Saldo inicial da conta
    float saldo_final;           // Saldo final da conta
    float transferencias;        // Total das transferências realizadas
    float rendimento_liquido;    // Rendimento líquido dos investimentos
    float emprestimo;            // Valor total dos empréstimos recebidos
    float parcelas_emprestimo;   // Total das parcelas de empréstimos pagas
    float parcelas_financiamento;// Total das parcelas de financiamentos pagas
} Extrato;

// Funções para gerenciar o extrato

// Cria o arquivo do extrato com informações iniciais do cliente
void criarExtrato(FILE **file, Cliente *cliente);

// Gera o extrato completo com transferências, investimentos, empréstimos e financiamentos
void gerarExtratoBancario(Cliente *cliente, Transferencia **transfers, int nTransfers,
                          Investimento **investimentos, int countInvestimentos,
                          Emprestimo **emprestimos, int countEmprestimos,
                          Financiamento **financiamentos, int countFinanciamentos);


// Fecha o arquivo do extrato
void finalizarExtrato(FILE *file);

#endif // EXTRATO_H
