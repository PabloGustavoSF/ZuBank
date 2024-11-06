#include "emprestimo.h"

FILE *file = NULL; // Ponteiro global para arquivo

// Função genérica para abrir arquivos
FILE *abrir_arquivo(const char *nome_arquivo, const char *modo) {
    file = fopen(nome_arquivo, modo);
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
    }
    return file;
}

// Função para calcular a parcela do empréstimo com taxa fixa de 1.46% ao mês
float calcular_parcela(struct Emprestimo *e) {
    float taxa_juros = 0.0146;  // Taxa de juros mensal fixa
    return (e->valor_emprestimo * taxa_juros) / (1 - pow(1 + taxa_juros, -e->tempo_emprestimo));
}

// Função para obter o próximo ID com base no último empréstimo no arquivo
int obter_proximo_id() {
    struct Emprestimo e;
    FILE *file = abrir_arquivo("emprestimos.txt", "r");
    int ultimo_id = 0;
    char linha[256];

    if (file == NULL) {
        return 1; // Se o arquivo não existe, começa com ID 1
    }

    // Lê o arquivo até o final para encontrar o último ID
    while (fgets(linha, sizeof(linha), file) != NULL) {
        sscanf(linha, "ID: %d", &e.id);
        ultimo_id = e.id;
    }

    fclose(file);
    return ultimo_id + 1; // Incrementa o ID
}

// Função para criar um novo empréstimo (Create)
void criar_emprestimo() {
    Emprestimo e;
    e.id = obter_proximo_id(); // Atribui um ID único
    FILE *file = abrir_arquivo("emprestimos.txt", "a");

    if (file == NULL) {
        return;
    }

    // Solicita o valor do empréstimo e o tempo de pagamento
    printf("Quanto deseja receber de emprestimo?\nR$");
    scanf("%f", &e.valor_emprestimo);

    printf("Em quantos meses deseja pagar o emprestimo?\n");
    scanf("%d", &e.tempo_emprestimo);

    // Calcula o valor das parcelas e os juros totais
    e.valor_parcela = calcular_parcela(&e);
    e.juros_totais = (e.valor_parcela * e.tempo_emprestimo) - e.valor_emprestimo;

    // Escreve os dados no arquivo de relatório
    fprintf(file, "ID: %d\n", e.id);
    fprintf(file, "VALOR DO EMPRESTIMO: R$%.2f\n", e.valor_emprestimo);
    fprintf(file, "PERIODO DE PAGAMENTO: %d meses\n", e.tempo_emprestimo);
    fprintf(file, "PARCELAS DO EMPRESTIMO: R$%.2f\n", e.valor_parcela);
    fprintf(file, "JUROS TOTAIS DO EMPRESTIMO: R$%.2f\n", e.juros_totais);
    fprintf(file, "-------------------------\n");

    fclose(file);
    printf("Emprestimo criado com sucesso! ID: %d\n", e.id);
}

// Função para ler todos os empréstimos (Read)
void ler_emprestimos() {
    char linha[256];
    FILE *file = abrir_arquivo("emprestimos.txt", "r");

    if (file == NULL) {
        return;
    }

    printf("\n--- Lista de Emprestimos ---\n");
    while (fgets(linha, sizeof(linha), file) != NULL) {
        printf("%s", linha);
    }

    fclose(file);
}

// Função para atualizar um empréstimo com base no ID (Update)
void atualizar_emprestimo(int id_procurado) {
    Emprestimo e;
    FILE *file = abrir_arquivo("emprestimos.txt", "r");
    FILE *temp = abrir_arquivo("temp.txt", "w");
    int encontrado = 0;
    char linha[256];

    if (file == NULL || temp == NULL) {
        return;
    }

    // Lê os dados do arquivo original e escreve no arquivo temporário
    while (fgets(linha, sizeof(linha), file) != NULL) {
        if (sscanf(linha, "ID: %d", &e.id) == 1 && e.id == id_procurado) {
            encontrado = 1;

            // Lê os próximos valores do empréstimo
            fgets(linha, sizeof(linha), file);
            sscanf(linha, "VALOR DO EMPRESTIMO: R$%f", &e.valor_emprestimo);
            fgets(linha, sizeof(linha), file);
            sscanf(linha, "PERIODO DE PAGAMENTO: %d meses", &e.tempo_emprestimo);

            // Solicita os novos dados
            printf("Novo valor do emprestimo (atual: R$%.2f):\nR$", e.valor_emprestimo);
            scanf("%f", &e.valor_emprestimo);

            printf("Novo tempo de pagamento (atual: %d meses):\n", e.tempo_emprestimo);
            scanf("%d", &e.tempo_emprestimo);

            // Atualiza os valores
            e.valor_parcela = calcular_parcela(&e);
            e.juros_totais = (e.valor_parcela * e.tempo_emprestimo) - e.valor_emprestimo;

            // Escreve os novos dados no arquivo temporário
            fprintf(temp, "ID: %d\n", e.id);
            fprintf(temp, "VALOR DO EMPRESTIMO: R$%.2f\n", e.valor_emprestimo);
            fprintf(temp, "PERIODO DE PAGAMENTO: %d meses\n", e.tempo_emprestimo);
            fprintf(temp, "PARCELAS DO EMPRESTIMO: R$%.2f\n", e.valor_parcela);
            fprintf(temp, "JUROS TOTAIS DO EMPRESTIMO: R$%.2f\n", e.juros_totais);
            fprintf(temp, "-------------------------\n");

            // Pula as próximas linhas relacionadas ao empréstimo atualizado
            fgets(linha, sizeof(linha), file);
            fgets(linha, sizeof(linha), file);
            fgets(linha, sizeof(linha), file);
        } else {
            // Mantém os dados originais
            fprintf(temp, "%s", linha);
        }
    }

    fclose(file);
    fclose(temp);
    remove("emprestimos.txt");
    rename("temp.txt", "emprestimos.txt");

    if (encontrado) {
        printf("Emprestimo atualizado com sucesso!\n");
    } else {
        printf("Emprestimo nao encontrado!\n");
    }
}

// Função para excluir um empréstimo com base no ID (Delete)
void excluir_emprestimo(int id_procurado) {
    Emprestimo e;
    FILE *file = abrir_arquivo("emprestimos.txt", "r");
    FILE *temp = abrir_arquivo("temp.txt", "w");
    int encontrado = 0;
    char linha[256];

    if (file == NULL || temp == NULL) {
        return;
    }

    // Lê os dados do arquivo original e escreve no arquivo temporário, exceto o que será excluído
    while (fgets(linha, sizeof(linha), file) != NULL) {
        sscanf(linha, "ID: %d", &e.id);

        if (e.id == id_procurado && !encontrado) {
            encontrado = 1;
            // Pula as linhas do empréstimo excluído
            fgets(linha, sizeof(linha), file);
            fgets(linha, sizeof(linha), file);
            fgets(linha, sizeof(linha), file);
            fgets(linha, sizeof(linha), file);
        } else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(file);
    fclose(temp);
    remove("emprestimos.txt");
    rename("temp.txt", "emprestimos.txt");

    if (encontrado) {
        printf("Emprestimo excluido com sucesso!\n");
    } else {
        printf("Emprestimo nao encontrado!\n");
    }
}
