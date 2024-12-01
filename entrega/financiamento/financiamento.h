#ifndef FINANCIAMENTO_H
#define FINANCIAMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define Jm 0.00917 // Juros mensal padrão (0,917%)

typedef struct {
    int id;
    float valor_financiado;
    int tempo_financiamento;
    float taxa_juros;
    float valor_parcela;
    float juros_totais;
    float amortizacao; // Adicionado para SAC
} Financiamento;

void criarFinanciamento(Financiamento **vetorFinanciamentos, int *count, int max_financiamentos);
void exibirFinanciamentos(Financiamento **vetorFinanciamentos, int count);
void atualizarFinanciamento(Financiamento **vetorFinanciamentos, int count);
void excluirFinanciamento(Financiamento **vetorFinanciamentos, int *count);
void salvarFinanciamentos(Financiamento **vetorFinanciamentos, int count);
void carregarFinanciamentos(Financiamento **vetorFinanciamentos, int *count, int max_financiamentos);
void menuFinanciamento(Financiamento **vetorFinanciamentos, int *count, int max_financiamentos);

// Métodos de financiamento
void Price(Financiamento *f);
void Sac(Financiamento *f);

#endif // FINANCIAMENTO_H
