// cliente.h
#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>

typedef struct {
    char nome[50];
    int conta;
    float saldo_inicial;
    float saldo_final;
    float transferencias;
    float rendimento_liquido;
    float emprestimo;
    float parcelas_emprestimo;
    float parcelas_financiamento;
} Cliente;

// Funções para manipulação do relatório de fechamento de conta
void criarRelatorioFechamento(FILE **file, Cliente *cliente);
void lerDadosFechamento(FILE *file, Cliente *cliente);
void atualizarSaldoFinalFechamento(FILE *file, Cliente *cliente);
void finalizarRelatorioFechamento(FILE *file);
void gerarRelatorioFechamentoConta(Cliente *cliente);

#endif // CLIENTE_H
