#ifndef GUSTAVO_H
#define GUSTAVO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Estruturas
typedef struct {
    char nome[50];
    int conta;
    float saldo_inicial;
    float saldo;
    float saldo_final;
} Cliente;

typedef struct {
    char beneficiario[50];
    int conta_trans;
    float valor_transferencia;
} Transferencia;

typedef struct {
    float investimento;
    int meses_investidos;
    float rendimento_bruto;
    float rendimento_liquido;
    float ir;
} Investimento;

// Fun��es para CRUD de Cliente
Cliente* criarCliente(const char* nome, int conta, float saldo_inicial);
void exibirCliente(const Cliente* cliente);
void atualizarSaldo(Cliente* cliente, float novoSaldo);
void deletarCliente(Cliente* cliente);

// Fun��es para CRUD de Transferencia
Transferencia* criarTransferencia(const char* beneficiario, int conta_trans, float valor);
void exibirTransferencia(const Transferencia** vetorTransf, int count);
void realizarTodasTransferencias(Cliente* cliente, Transferencia** vetorTransf, int* count, FILE *arquivo);
void deletarTransferencia(Transferencia** vetorTransf, int id, int* count);
void menuTransferencia(Transferencia** vetorTransf, Cliente* cliente, int max_transf);

// Fun��es para CRUD de Investimento
Investimento* criarInvestimento(float valor, int meses);
void exibirInvestimento(const Investimento* investimento);
void deletarInvestimento(Investimento* investimento);

#endif // GUSTAVO_H

