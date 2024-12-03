#ifndef TRANSFER_H
#define TRANSFER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../cliente/cliente.h"


typedef struct {
    char beneficiario[50];
    int conta_trans;
    float valor_transferencia;
} Transferencia;


// Fun��es para CRUD de Transferencia
Transferencia* criarTransferencia(const char* beneficiario, int conta_trans, float valor);
void exibirTransferencia(const Transferencia **vetorTransf, int count);
void realizarTodasTransferencias(Cliente* cliente, Transferencia** vetorTransf, int* count, FILE* arquivo);
void deletarTransferencia(Transferencia** vetorTransf, int id, int* count);
void menuTransferencia(Transferencia** vetorTransf, Cliente* cliente, int max_transf);
void excluirTransferenciasPendentes(Transferencia** vetorTransf, int* count);


#endif // TRANSFER_H

