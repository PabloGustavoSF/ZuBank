#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include <stdio.h>
#include <math.h>

// Estrutura que representa os dados do empréstimo
struct Emprestimo {
    float valor_emprestimo;   // Valor solicitado do empréstimo
    int tempo_emprestimo;     // Tempo para pagamento em meses
    float valor_parcela;      // Valor das parcelas do empréstimo
    float juros_totais;       // Juros totais do empréstimo
};

// Função para calcular a parcela do empréstimo com taxa fixa de 1.46% ao mês
float calcular_parcela(struct Emprestimo *e) {
    float taxa_juros = 0.0146;  // Taxa de juros mensal fixa
    // Calcula o valor da parcela usando a fórmula de juros compostos
    return (e->valor_emprestimo * taxa_juros) / (1 - pow(1 + taxa_juros, -e->tempo_emprestimo));
}

// Função para gerar o relatório do empréstimo e salvar em um arquivo
void gerar_relatorio_emprestimo(struct Emprestimo *e) {
    FILE *file3;
    
    // Solicita o valor do empréstimo e o tempo de pagamento
    printf("Quanto deseja receber de empréstimo?\nR$");
    scanf("%f", &e->valor_emprestimo);

    printf("Em quantos meses deseja pagar o empréstimo?\n");
    scanf("%d", &e->tempo_emprestimo);

    // Calcula o valor das parcelas
    e->valor_parcela = calcular_parcela(e);

    // Calcula os juros totais do empréstimo
    e->juros_totais = (e->valor_parcela * e->tempo_emprestimo) - e->valor_emprestimo;

    // Abre o arquivo para escrever o relatório
    file3 = fopen("RELATORIO_DE_EMPRESTIMO.txt", "w");
    if (file3 == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DO RELATÓRIO DE EMPRÉSTIMO!\n");
        return;
    }

    // Escreve os dados do empréstimo no arquivo de relatório
    fprintf(file3, "VALOR DO EMPRÉSTIMO: R$%.2f\n", e->valor_emprestimo);
    fprintf(file3, "PERÍODO DE PAGAMENTO: %d meses\n", e->tempo_emprestimo);
    fprintf(file3, "PARCELAS DO EMPRÉSTIMO: R$%.2f\n", e->valor_parcela);
    fprintf(file3, "JUROS TOTAIS DO EMPRÉSTIMO: R$%.2f\n", e->juros_totais);
    
    // Fecha o arquivo
    fclose(file3);

    printf("CONFIRA O SEU RELATÓRIO DE EMPRÉSTIMO!\n");
}

#endif
