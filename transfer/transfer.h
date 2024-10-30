// transfer.h
#ifndef TRANSFER_H
#define TRANSFER_H

#include <stdio.h>
#include <string.h>

// Estrutura para dados do usuário
typedef struct {
    char nome[50];
    int conta;
    float saldo_inicial;
    float saldo_final;
} Usuario;

// Estrutura para dados da transferência
typedef struct {
    char beneficiario[50];
    float transferencia;
    int conta_trans;
} Transferencia;

// Declaração da função de transferência
void transfer(Usuario *usuario, Transferencia *transf);

#endif

