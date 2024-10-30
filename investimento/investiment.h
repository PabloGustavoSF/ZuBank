// investiment.h
#ifndef INVESTIMENT_H
#define INVESTIMENT_H

#include <stdio.h>
#include <math.h>

// Definição da struct Investimento
typedef struct {
    float investimento;
    int meses_investidos;
    float rendimento_bruto;
    float rendimento_liquido;
    float ir;
} Investimento;

// Declaração da função de investimento
void investiment(float saldo_final, Investimento *investimento_data);

#endif

