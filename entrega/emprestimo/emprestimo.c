#include "emprestimo.h"

void criarEmprestimo(Emprestimo **vetorEmprestimos, int *count, int max_emprestimos, float *saldo_disponivel) {
    if (*count >= max_emprestimos) {
        printf("Limite de empréstimos atingido!\n");
        return;
    }

    Emprestimo *novo = (Emprestimo *)malloc(sizeof(Emprestimo));
    if (novo == NULL) {
        printf("Erro ao alocar memória para o empréstimo.\n");
        return;
    }

    // Gera um novo ID
    novo->id = (*count == 0) ? 1 : vetorEmprestimos[*count - 1]->id + 1;

    // Solicita informações do usuário
    printf("Quanto deseja receber de empréstimo? (Saldo disponível: R$%.2f)\nR$", *saldo_disponivel);
    scanf("%f", &novo->valor_emprestimo);

    // Verifica se o valor solicitado excede o saldo disponível
    if (novo->valor_emprestimo <= 0) {
        printf("Valor inválido! Empréstimo deve ser maior que zero.\n");
        free(novo);
        return;
    }

    printf("Em quantos meses deseja pagar o empréstimo?\n");
    scanf("%d", &novo->tempo_emprestimo);

    // Calcula parcelas e juros
    float taxa_juros = 0.0146;  // Taxa de juros fixa de 1.46% ao mês
    novo->valor_parcela = (novo->valor_emprestimo * taxa_juros) / (1 - pow(1 + taxa_juros, -novo->tempo_emprestimo));
    novo->juros_totais = (novo->valor_parcela * novo->tempo_emprestimo) - novo->valor_emprestimo;

    // Adiciona o empréstimo ao vetor
    vetorEmprestimos[*count] = novo;
    (*count)++;

    // Atualiza o saldo disponível
    *saldo_disponivel += novo->valor_emprestimo;

    printf("Empréstimo criado com sucesso! ID: %d\n", novo->id);
    printf("Novo saldo disponível: R$%.2f\n", *saldo_disponivel);
}

void exibirEmprestimos(Emprestimo **vetorEmprestimos, int count) {
    if (count == 0) {
        printf("Nenhum empréstimo registrado.\n");
        return;
    }

    printf("ID | Valor Emprestado | Parcelas | Juros Totais | Tempo (meses)\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%d  | R$%.2f         | R$%.2f  | R$%.2f      | %d\n",
               vetorEmprestimos[i]->id,
               vetorEmprestimos[i]->valor_emprestimo,
               vetorEmprestimos[i]->valor_parcela,
               vetorEmprestimos[i]->juros_totais,
               vetorEmprestimos[i]->tempo_emprestimo);
    }
}

void atualizarEmprestimo(Emprestimo **vetorEmprestimos, int count) {
    int id;
    printf("Digite o ID do empréstimo que deseja atualizar:\n");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (vetorEmprestimos[i]->id == id) {
            printf("Novo valor do empréstimo (atual: R$%.2f):\n", vetorEmprestimos[i]->valor_emprestimo);
            scanf("%f", &vetorEmprestimos[i]->valor_emprestimo);

            printf("Novo tempo para pagamento (atual: %d meses):\n", vetorEmprestimos[i]->tempo_emprestimo);
            scanf("%d", &vetorEmprestimos[i]->tempo_emprestimo);

            // Recalcula valores
            float taxa_juros = 0.0146;
            vetorEmprestimos[i]->valor_parcela = (vetorEmprestimos[i]->valor_emprestimo * taxa_juros) / 
                                                  (1 - pow(1 + taxa_juros, -vetorEmprestimos[i]->tempo_emprestimo));
            vetorEmprestimos[i]->juros_totais = (vetorEmprestimos[i]->valor_parcela * vetorEmprestimos[i]->tempo_emprestimo) - 
                                                vetorEmprestimos[i]->valor_emprestimo;

            printf("Empréstimo atualizado com sucesso!\n");
            return;
        }
    }
    printf("Empréstimo com ID %d não encontrado.\n", id);
}

void excluirEmprestimo(Emprestimo **vetorEmprestimos, int *count) {
    int id;
    printf("Digite o ID do empréstimo que deseja excluir:\n");
    scanf("%d", &id);

    int encontrado = 0;
    for (int i = 0; i < *count; i++) {
        if (vetorEmprestimos[i]->id == id) {
            encontrado = 1;

            // Libera a memória alocada para o empréstimo
            free(vetorEmprestimos[i]);

            // Move os elementos restantes uma posição à esquerda no vetor
            for (int j = i; j < *count - 1; j++) {
                vetorEmprestimos[j] = vetorEmprestimos[j + 1];
            }

            (*count)--;  // Reduz o número de empréstimos
            printf("Empréstimo excluído com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Empréstimo não encontrado!\n");
    }
}


void salvarEmprestimos(Emprestimo **vetorEmprestimos, int count) {
    FILE *file = fopen("emprestimos.txt", "w");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar os empréstimos.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "ID: %d\n", vetorEmprestimos[i]->id);
        fprintf(file, "VALOR DO EMPRESTIMO: R$%.2f\n", vetorEmprestimos[i]->valor_emprestimo);
        fprintf(file, "PERIODO DE PAGAMENTO: %d meses\n", vetorEmprestimos[i]->tempo_emprestimo);
        fprintf(file, "PARCELAS DO EMPRESTIMO: R$%.2f\n", vetorEmprestimos[i]->valor_parcela);
        fprintf(file, "JUROS TOTAIS DO EMPRESTIMO: R$%.2f\n", vetorEmprestimos[i]->juros_totais);
        fprintf(file, "-------------------------\n");
    }

    fclose(file);
    printf("Empréstimos salvos com sucesso!\n");
}

void carregarEmprestimos(Emprestimo **vetorEmprestimos, int *count, int max_emprestimos) {
    FILE *file = fopen("emprestimos.txt", "w");
    if (file == NULL) {
        printf("Nenhum arquivo de empréstimos encontrado.\n");
        return;
    }

    Emprestimo *emprestimo = NULL;
    char linha[256];
    int id;
    float valorEmprestimo, valorParcela, jurosTotais;
    int tempoEmprestimo;

    while (*count < max_emprestimos && fgets(linha, sizeof(linha), file) != NULL) {
        if (sscanf(linha, "ID: %d", &id) == 1) {
            emprestimo = (Emprestimo *)malloc(sizeof(Emprestimo));
            if (emprestimo == NULL) {
                printf("Erro ao alocar memória para o empréstimo.\n");
                break;
            }

            emprestimo->id = id;

            fgets(linha, sizeof(linha), file);
            sscanf(linha, "VALOR DO EMPRESTIMO: R$%f", &valorEmprestimo);
            emprestimo->valor_emprestimo = valorEmprestimo;

            fgets(linha, sizeof(linha), file);
            sscanf(linha, "PERIODO DE PAGAMENTO: %d meses", &tempoEmprestimo);
            emprestimo->tempo_emprestimo = tempoEmprestimo;

            fgets(linha, sizeof(linha), file);
            sscanf(linha, "PARCELAS DO EMPRESTIMO: R$%f", &valorParcela);
            emprestimo->valor_parcela = valorParcela;

            fgets(linha, sizeof(linha), file);
            sscanf(linha, "JUROS TOTAIS DO EMPRESTIMO: R$%f", &jurosTotais);
            emprestimo->juros_totais = jurosTotais;

            fgets(linha, sizeof(linha), file);  // Pular a linha de separação

            vetorEmprestimos[*count] = emprestimo;
            (*count)++;
        }
    }

    fclose(file);

    if (*count > 0) {
        printf("Empréstimos carregados com sucesso!\n");
    }
}


void menuEmprestimo(Emprestimo **vetorEmprestimos, int *count, int max_emprestimos, float *saldo_disponivel) {
    int opcao;

    do {
        printf("\n--- Menu Empréstimos ---\n");
        printf("1 - Criar Empréstimo\n");
        printf("2 - Listar Empréstimos\n");
        printf("3 - Atualizar Empréstimo\n");
        printf("4 - Excluir Empréstimo\n");
        printf("5 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criarEmprestimo(vetorEmprestimos, count, max_emprestimos, saldo_disponivel);
                break;
            case 2:
                exibirEmprestimos(vetorEmprestimos, *count);
                break;
            case 3:
                atualizarEmprestimo(vetorEmprestimos, *count);
                break;
            case 4:
                excluirEmprestimo(vetorEmprestimos, count);
                break;
            case 5:
                salvarEmprestimos(vetorEmprestimos, *count);  // Salva os empréstimos ao sair
                printf("Saindo do menu de empréstimos.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 5);
}
