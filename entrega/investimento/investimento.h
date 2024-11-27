#ifndef INVESTIMENTO_H
#define INVESTIMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definição da estrutura de investimento
typedef struct {
    float investimento;       // Valor investido
    int meses_investidos;     // Quantidade de meses
    float ir;                 // Alíquota do imposto de renda
    float rendimento_bruto;   // Rendimento bruto do investimento
    float rendimento_liquido; // Rendimento líquido após imposto
} Investimento;

// Protótipos das funções

// Cria um novo investimento baseado no valor e meses informados
Investimento *criarInvestimento(float investimento_valor, int meses_investidos);

// Exibe os detalhes de um investimento no console
void exibirInvestimento(const Investimento *investimento);

// Salva todos os investimentos no arquivo "investimentos.txt"
void salvarInvestimentos(Investimento **vetorInvestimentos, int count);

// Carrega os investimentos do arquivo "investimentos.txt"
void carregarInvestimentos(Investimento **vetorInvestimentos, int *count, int max_investimentos);

// Deleta um investimento específico da lista
void deletarInvestimento(Investimento **vetorInvestimentos, int id, int *count);

// Menu para gerenciar uma lista de investimentos
void menuInvestimento(Investimento **vetorInvestimentos, int *count, int max_investimentos, float* saldo_final);

#endif // INVESTIMENTO_H
