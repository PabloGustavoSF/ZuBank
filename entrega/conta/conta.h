#ifndef CONTA_H
#define CONTA_H

#include <stdio.h>


typedef struct
{
    char nome[50];
    float saldo_Inicial;
    int conta_id;
} Conta;

void criarConta(Conta *conta);


#endif // CONTA_H
