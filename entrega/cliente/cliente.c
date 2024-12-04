#include "cliente.h"

Cliente* criarCliente(const char* nome, int conta, float saldo_inicial) {
    // Alocar memória para o cliente
    Cliente* cliente = (Cliente*)malloc(sizeof(Cliente));
    if (cliente == NULL) {
        printf("Erro ao alocar memoria para o cliente.\n");
        return NULL;
    }

    // Inicializar campos do cliente
    strncpy(cliente->nome, nome, sizeof(cliente->nome) - 1);
    cliente->nome[sizeof(cliente->nome) - 1] = '\0'; // Garantir string nula
    cliente->conta = conta;
    cliente->saldo_inicial = saldo_inicial;
    cliente->saldo = saldo_inicial;
    cliente->saldo_final = saldo_inicial;

    return cliente;
}

void destruirCliente(Cliente* cliente) {
    if (cliente != NULL) {
        free(cliente);
    }
}
