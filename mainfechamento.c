#include <stdio.h>
#include "fechamento.h"

int main() {
    // Dados simulados para teste
    char nome[50] = "João da Silva";
    int conta = 12345;
    float saldo_inicial = 1000.00;
    float transferencia = 200.00;
    float rendimento_liquido = 50.00;
    float emprestimo = 500.00;
    float parcela_emprestimo = 50.00;
    int tempo_emprestimo = 10;
    float parcela_financiamento = 150.00;
    int parcelas = 12;
    int tipo_financiamento = 1;  // Tipo 1 para PRICE

    // Calcula o valor total das parcelas do financiamento baseado no tipo
    float val_financ = (tipo_financiamento == 1) ? parcela_financiamento : 0; // Usa PRICE como exemplo

    // Calcula o total de saída
    float saida = calcular_total_saida(transferencia, parcela_emprestimo, tempo_emprestimo, val_financ, parcelas);

    // Calcula o saldo final após todas as transações
    float saldo_final = calcular_saldo_final(saldo_inicial, rendimento_liquido, emprestimo, saida);

    // Gera o relatório de fechamento
    gerar_relatorio_fechamento(nome, conta, saldo_inicial, saldo_final, transferencia, rendimento_liquido, emprestimo, parcela_emprestimo * tempo_emprestimo, val_financ * parcelas);

    return 0;
}
