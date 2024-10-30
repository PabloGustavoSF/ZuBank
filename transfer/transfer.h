// transfer.h
#ifndef TRANSFER_H
#define TRANSFER_H

#include <stdio.h>
#include <string.h>

// Estrutura para dados do usu�rio
typedef struct {
    char nome[50];
    int conta;
    float saldo_inicial;
    float saldo_final;
} Usuario;

// Estrutura para dados da transfer�ncia
typedef struct {
    char beneficiario[50];
    float transferencia;
    int conta_trans;
} Transferencia;

// Declara��o da fun��o de transfer�ncia
void transfer(Usuario *usuario, Transferencia *transf);

#endif

