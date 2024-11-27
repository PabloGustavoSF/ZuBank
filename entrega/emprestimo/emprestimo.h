#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Estrutura de Empréstimo
typedef struct {
    int id;                   // Identificador único do empréstimo
    float valor_emprestimo;   // Valor solicitado
    int tempo_emprestimo;     // Tempo para pagamento (meses)
    float valor_parcela;      // Valor das parcelas
    float juros_totais;       // Total de juros
} Emprestimo;

// Funções principais
void criarEmprestimo(Emprestimo **vetorEmprestimos, int *count, int max_emprestimos, float saldo_disponivel);
void exibirEmprestimos(Emprestimo **vetorEmprestimos, int count);
void atualizarEmprestimo(Emprestimo **vetorEmprestimos, int count);
void excluirEmprestimo(Emprestimo **vetorEmprestimos, int *count);
void salvarEmprestimos(Emprestimo **vetorEmprestimos, int count);
void carregarEmprestimos(Emprestimo **vetorEmprestimos, int *count, int max_emprestimos);

// Menu para gerenciar empréstimos
void menuEmprestimo(Emprestimo **vetorEmprestimos, int *count, int max_emprestimos, float *saldo_disponivel);

#endif // EMPRESTIMO_H
