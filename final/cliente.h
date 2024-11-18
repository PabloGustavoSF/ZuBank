#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct {
    char nome[50];
    int conta;
    float saldo_inicial;
    float saldo_final;
    float transferencias_realizadas;
    float rendimento_liquido;
    float emprestimos_recebidos;
    float parcelas_emprestimo_total;
    float parcelas_financiamento_total;
} Cliente;

// Função para gerar o relatório de fechamento de conta
void gerar_relatorio_fechamento(Cliente *cliente);

#endif
