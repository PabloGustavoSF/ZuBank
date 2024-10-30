#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include <stdio.h>
#include <math.h>
#include <string.h>

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
    return (e->valor_emprestimo * taxa_juros) / (1 - pow(1 + taxa_juros, -e->tempo_emprestimo));
}

// Função para criar um novo empréstimo (Create)
void criar_emprestimo() {
    struct Emprestimo e;
    FILE *file = fopen("emprestimos.txt", "a");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Solicita o valor do empréstimo e o tempo de pagamento
    printf("Quanto deseja receber de empréstimo?\nR$");
    scanf("%f", &e.valor_emprestimo);

    printf("Em quantos meses deseja pagar o empréstimo?\n");
    scanf("%d", &e.tempo_emprestimo);

    // Calcula o valor das parcelas e os juros totais
    e.valor_parcela = calcular_parcela(&e);
    e.juros_totais = (e.valor_parcela * e.tempo_emprestimo) - e.valor_emprestimo;

    // Escreve os dados no arquivo de relatório
    fprintf(file, "VALOR DO EMPRÉSTIMO: R$%.2f\n", e.valor_emprestimo);
    fprintf(file, "PERÍODO DE PAGAMENTO: %d meses\n", e.tempo_emprestimo);
    fprintf(file, "PARCELAS DO EMPRÉSTIMO: R$%.2f\n", e.valor_parcela);
    fprintf(file, "JUROS TOTAIS DO EMPRÉSTIMO: R$%.2f\n", e.juros_totais);
    fprintf(file, "-------------------------\n");
    
    fclose(file);
    printf("Empréstimo criado com sucesso!\n");
}

// Função para ler todos os empréstimos (Read)
void ler_emprestimos() {
    char linha[256];
    FILE *file = fopen("emprestimos.txt", "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("\n--- Lista de Empréstimos ---\n");
    while (fgets(linha, sizeof(linha), file) != NULL) {
        printf("%s", linha);
    }

    fclose(file);
}

// Função para atualizar um empréstimo (Update)
void atualizar_emprestimo(float valor_procurado) {
    struct Emprestimo e;
    FILE *file = fopen("emprestimos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int encontrado = 0;
    char linha[256];

    if (file == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Lê os dados do arquivo original e escreve no arquivo temporário
    while (fgets(linha, sizeof(linha), file) != NULL) {
        // Verifica se a linha contém o valor procurado
        sscanf(linha, "VALOR DO EMPRÉSTIMO: R$%f", &e.valor_emprestimo);
        if (e.valor_emprestimo == valor_procurado) {
            // Solicita novos dados
            printf("Novo valor do empréstimo (atual: R$%.2f):\nR$", e.valor_emprestimo);
            scanf("%f", &e.valor_emprestimo);

            printf("Novo tempo de pagamento (atual: %d meses):\n", e.tempo_emprestimo);
            scanf("%d", &e.tempo_emprestimo);

            // Calcula os novos valores
            e.valor_parcela = calcular_parcela(&e);
            e.juros_totais = (e.valor_parcela * e.tempo_emprestimo) - e.valor_emprestimo;

            // Escreve os novos dados no arquivo temporário
            fprintf(temp, "VALOR DO EMPRÉSTIMO: R$%.2f\n", e.valor_emprestimo);
            fprintf(temp, "PERÍODO DE PAGAMENTO: %d meses\n", e.tempo_emprestimo);
            fprintf(temp, "PARCELAS DO EMPRÉSTIMO: R$%.2f\n", e.valor_parcela);
            fprintf(temp, "JUROS TOTAIS DO EMPRÉSTIMO: R$%.2f\n", e.juros_totais);
            fprintf(temp, "-------------------------\n");

            encontrado = 1;
            // Pular as linhas antigas do empréstimo no arquivo original
            fgets(linha, sizeof(linha), file);  // tempo_emprestimo
            fgets(linha, sizeof(linha), file);  // valor_parcela
            fgets(linha, sizeof(linha), file);  // juros_totais
            fgets(linha, sizeof(linha), file);  // linha separadora
        } else {
            // Mantém os dados originais no arquivo temporário
            fprintf(temp, "%s", linha);
        }
    }

    fclose(file);
    fclose(temp);

    remove("emprestimos.txt");
    rename("temp.txt", "emprestimos.txt");

    if (encontrado) {
        printf("Empréstimo atualizado com sucesso!\n");
    } else {
        printf("Empréstimo não encontrado!\n");
    }
}

// Função para excluir um empréstimo (Delete)
void excluir_emprestimo(float valor_procurado) {
    struct Emprestimo e;
    FILE *file = fopen("emprestimos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int encontrado = 0;
    char linha[256];

    if (file == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Lê os dados do arquivo original e escreve no arquivo temporário, exceto o que será excluído
    while (fgets(linha, sizeof(linha), file) != NULL) {
        sscanf(linha, "VALOR DO EMPRÉSTIMO: R$%f", &e.valor_emprestimo);
        if (e.valor_emprestimo == valor_procurado) {
            encontrado = 1;
            // Pular as próximas linhas correspondentes ao empréstimo excluído
            fgets(linha, sizeof(linha), file);  // tempo_emprestimo
            fgets(linha, sizeof(linha), file);  // valor_parcela
            fgets(linha, sizeof(linha), file);  // juros_totais
            fgets(linha, sizeof(linha), file);  // linha separadora
        } else {
            // Mantém os dados originais no arquivo temporário
            fprintf(temp, "%s", linha);
        }
    }

    fclose(file);
    fclose(temp);

    remove("emprestimos.txt");
    rename("temp.txt", "emprestimos.txt");

    if (encontrado) {
        printf("Empréstimo excluído com sucesso!\n");
    } else {
        printf("Empréstimo não encontrado!\n");
    }
}

#endif
