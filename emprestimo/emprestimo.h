#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include <stdio.h>
#include <math.h>

// Estrutura que representa os dados do empréstimo
typedef struct Emprestimo {
    int id;                   // Identificador único do empréstimo
    float valor_emprestimo;    // Valor solicitado do empréstimo
    int tempo_emprestimo;      // Tempo para pagamento em meses
    float valor_parcela;       // Valor das parcelas do empréstimo
    float juros_totais;        // Juros totais do empréstimo
} Emprestimo; 

// Função para calcular a parcela do empréstimo com taxa fixa de 1.46% ao mês
float calcular_parcela(struct Emprestimo *e);

// Função para criar um novo empréstimo (Create)
void criar_emprestimo();

// Função para ler todos os empréstimos (Read)
void ler_emprestimos();

// Função para atualizar um empréstimo com base no ID (Update)
void atualizar_emprestimo(int id_procurado);

// Função para excluir um empréstimo com base no ID (Delete)
void excluir_emprestimo(int id_procurado);

// Função para obter o próximo ID do arquivo de empréstimos
int obter_proximo_id();

// Função genérica para abrir arquivos
FILE *abrir_arquivo(const char *nome_arquivo, const char *modo);

// Ponteiro de arquivo global
extern FILE *file;

#endif
