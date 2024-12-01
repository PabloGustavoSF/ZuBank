#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int id;
    float valor_emprestimo;
    int tempo_emprestimo;
    float valor_parcela;
    float juros_totais;
} Emprestimo;

// Funções relacionadas aos empréstimos
void criarEmprestimo(Emprestimo **vetorEmprestimos, int *count, int max_emprestimos, float *saldo_disponivel);
void exibirEmprestimos(Emprestimo **vetorEmprestimos, int count);
void atualizarEmprestimo(Emprestimo **vetorEmprestimos, int count);
void excluirEmprestimo(Emprestimo **vetorEmprestimos, int *count);
void salvarEmprestimos(Emprestimo **vetorEmprestimos, int count);
void carregarEmprestimos(Emprestimo **vetorEmprestimos, int *count, int max_emprestimos);
void menuEmprestimo(Emprestimo **vetorEmprestimos, int *count, int max_emprestimos, float *saldo_disponivel);

#endif // EMPRESTIMO_H
