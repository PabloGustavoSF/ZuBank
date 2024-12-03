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
    float saldo_inicial;
    float saldo_final;
    float transferencias;
    float rendimento_liquido;
    float emprestimo;
    float parcelas_emprestimo;
    float parcelas_financiamento;
} Extrato;

// Funções para gerenciar o extrato
void criarExtrato(FILE **file, Cliente *cliente);
void lerRelatorioEntrada(FILE *file, Extrato *extrato, Transferencia *transfers, int nTransfers, Investimento **investimentos, int nInvestimentos, Emprestimo **emprestimos, int nEmprestimos);
void lerRelatorioSaida(FILE *file, Extrato *extrato, Transferencia *transfers, int nTransfers, Emprestimo **emprestimos, int nEmprestimos, Financiamento **financiamentos, int nFinanciamentos);
void calcularESalvarSaldoFinal(FILE *file, Extrato *extrato);
void finalizarExtrato(FILE *file);
void gerarExtratoBancario(Cliente *cliente, Transferencia *transfers, int nTransfers, Investimento **investimentos, int nInvestimentos, Emprestimo **emprestimos, int nEmprestimos, Financiamento **financiamentos, int nFinanciamentos);

#endif // EXTRATO_H
