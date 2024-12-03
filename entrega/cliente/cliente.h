#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura Cliente
typedef struct {
    char nome[50];
    int conta;
    float saldo_inicial;
    float saldo;
    float saldo_final;
} Cliente;

// Funções relacionadas ao Cliente
Cliente* criarCliente(const char* nome, int conta, float saldo_inicial);
void destruirCliente(Cliente* cliente);

#endif // CLIENTE_H
