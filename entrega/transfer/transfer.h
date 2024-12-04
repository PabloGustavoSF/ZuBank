#ifndef TRANSFER_H
#define TRANSFER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../cliente/cliente.h"

// Estrutura da Transferência
typedef struct {
    char beneficiario[50];
    int conta_trans;
    float valor_transferencia;
} Transferencia;

// Funções para gerenciar transferências

// Cria uma nova transferência
Transferencia* criarTransferencia(const char* beneficiario, int conta_trans, float valor);

// Exibe todas as transferências no vetor
void exibirTransferencia(const Transferencia **vetorTransf, int count);

// Realiza todas as transferências pendentes e salva em arquivo
void realizarTodasTransferencias(Cliente* cliente, Transferencia** vetorTransf, int* count, FILE* arquivo);

// Deleta uma transferência específica por ID
void deletarTransferencia(Transferencia** vetorTransf, int id, int* count);

// Menu para gerenciar transferências
void menuTransferencia(Transferencia** vetorTransf, Cliente* cliente, int max_transf, int* count);

// Exclui todas as transferências pendentes
void excluirTransferenciasPendentes(Transferencia** vetorTransf, int* count);

#endif // TRANSFER_H
