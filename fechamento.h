#ifndef FECHAMENTO_H
#define FECHAMENTO_H

#include <stdio.h>

// Estrutura que representa os dados do cliente para fechamento de conta
struct FechamentoConta {
    char nome[50];               // Nome do cliente
    int conta;                   // Número da conta
    float saldo_final;           // Saldo final
    float parcela_emprestimo;    // Valor do empréstimo pendente
    float parcela_financiamento; // Valor do financiamento pendente
};

// Função que verifica se há pendências financeiras
int verificar_pendencias(struct FechamentoConta *fc);

// Função que realiza o fechamento da conta
int fechar_conta(struct FechamentoConta *fc, FILE *file6, int *continua);

#endif // FECHAMENTO_H
