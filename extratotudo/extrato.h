// extrato.h
#ifndef EXTRATO_H
#define EXTRATO_H

#include <stdio.h>

typedef struct {
    float saldo_inicial;
    float saldo_final;
    float transferencias;
    float rendimento_liquido;
    float emprestimo;
    float parcelas_emprestimo;
    float parcelas_financiamento;
} Extrato;

typedef struct {
    char nome[50];
    int conta;
    Extrato extrato;
} Cliente;

// Funções para manipulação do extrato bancário
void criarExtrato(FILE **file, Cliente *cliente);
void lerRelatorioEntrada(FILE *file, Extrato *extrato);
void lerRelatorioSaida(FILE *file, Extrato *extrato);
void calcularESalvarSaldoFinal(FILE *file, Extrato *extrato);
void finalizarExtrato(FILE *file);
void gerarExtratoBancario(Cliente *cliente);

#endif // EXTRATO_H
