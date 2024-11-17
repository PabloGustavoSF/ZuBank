#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>

// Definição da struct Cliente
typedef struct {
    char nome[50];
    int conta;
    float saldo_inicial;
    float saldo_final;
} Cliente;

// Protótipo da função para gerar o relatório de fechamento
void gerarRelatorioFechamento(Cliente cliente);

#endif
