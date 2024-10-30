// financiamento.h

#ifndef FINANCIAMENTO_H
#define FINANCIAMENTO_H

#include <stdio.h>
#include <math.h>
#include <time.h>

#define Jm 0.00917  // Juros mensal padrão para financiamento

// Estrutura para armazenar dados de um financiamento
struct Financiamento
{
    float juros;        // Taxa de Juros
    float valor;        // Valor financiado
    int parcelas;       // Número de parcelas
    float vP;           // Valor da parcela
    float amortizacao;  // Amortização da dívida
};

// Funções CRUD para a estrutura Financiamento
void createFinanciamento(struct Financiamento *f, float valor, int parcelas, float juros);
void readFinanciamento(struct Financiamento *f);
void updateFinanciamento(struct Financiamento *f, float valor, int parcelas, float juros);
void deleteFinanciamento(struct Financiamento *f);

// Funções para cálculos de financiamento usando sistema Price e SAC
void Price(struct Financiamento *f);
void Sac(struct Financiamento *f);

#endif // FINANCIAMENTO_H
