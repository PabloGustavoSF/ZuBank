#ifndef FECHAMENTO_H
#define FECHAMENTO_H

// Função para calcular o saldo final
float calcular_saldo_final(float saldo_inicial, float rendimento_liquido, float emprestimo, float saida);

// Função para calcular o total de saída
float calcular_total_saida(float transferencia, float parcela_emprestimo, int tempo_emprestimo, float val_financ, int parcelas);

// Função para gerar o relatório de fechamento de conta
void gerar_relatorio_fechamento(const char *nome, int conta, float saldo_inicial, float saldo_final, float transferencia, float rendimento_liquido, float emprestimo, float parcela_emprestimo_total, float val_financ_total);

#endif
