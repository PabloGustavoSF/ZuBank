#include "financiamento.h"

// Função para criar um financiamento
void criarFinanciamento(Financiamento **vetorFinanciamentos, int *count, int max_financiamentos) {
    if (*count >= max_financiamentos) {
        printf("Limite de financiamentos atingido!\n");
        return;
    }

    Financiamento *novo = (Financiamento *)malloc(sizeof(Financiamento));
    if (novo == NULL) {
        printf("Erro ao alocar memória para o financiamento.\n");
        return;
    }

    // Gera um novo ID
    novo->id = (*count == 0) ? 1 : vetorFinanciamentos[*count - 1]->id + 1;

    // Solicita informações do usuário
    printf("Informe o valor do financiamento: R$");
    scanf("%f", &novo->valor_financiado);

    printf("Informe o número de parcelas (meses): ");
    scanf("%d", &novo->tempo_financiamento);

    printf("Deseja usar a taxa de juros padrão (%.4f)? [1-Sim / 2-Não]: ", Jm);
    int usarPadrao;
    scanf("%d", &usarPadrao);

    if (usarPadrao == 1) {
        novo->taxa_juros = Jm;
    } else {
        printf("Informe a taxa de juros mensal (exemplo: 0.00917 para 0,917%%): ");
        scanf("%f", &novo->taxa_juros);
    }

    // Calcula parcelas e juros
    novo->valor_parcela = (novo->valor_financiado * novo->taxa_juros) /
                          (1 - pow(1 + novo->taxa_juros, -novo->tempo_financiamento));
    novo->juros_totais = (novo->valor_parcela * novo->tempo_financiamento) - novo->valor_financiado;

    // Adiciona o financiamento ao vetor
    vetorFinanciamentos[*count] = novo;
    (*count)++;

    printf("Financiamento criado com sucesso! ID: %d\n", novo->id);
}

// As demais funções permanecem inalteradas, pois a constante `Jm` só é usada durante a criação.

// Função para exibir financiamentos
void exibirFinanciamentos(Financiamento **vetorFinanciamentos, int count) {
    if (count == 0) {
        printf("Nenhum financiamento registrado.\n");
        return;
    }

    printf("ID | Valor Financiado | Parcelas | Taxa Juros | Juros Totais | Valor Parcela\n");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%d  | R$%.2f         | %d meses | %.4f      | R$%.2f      | R$%.2f\n",
               vetorFinanciamentos[i]->id,
               vetorFinanciamentos[i]->valor_financiado,
               vetorFinanciamentos[i]->tempo_financiamento,
               vetorFinanciamentos[i]->taxa_juros,
               vetorFinanciamentos[i]->juros_totais,
               vetorFinanciamentos[i]->valor_parcela);
    }
}

// Função para atualizar um financiamento
void atualizarFinanciamento(Financiamento **vetorFinanciamentos, int count) {
    int id;
    printf("Digite o ID do financiamento que deseja atualizar:\n");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (vetorFinanciamentos[i]->id == id) {
            printf("Novo valor do financiamento (atual: R$%.2f):\n", vetorFinanciamentos[i]->valor_financiado);
            scanf("%f", &vetorFinanciamentos[i]->valor_financiado);

            printf("Novo número de parcelas (atual: %d meses):\n", vetorFinanciamentos[i]->tempo_financiamento);
            scanf("%d", &vetorFinanciamentos[i]->tempo_financiamento);

            printf("Nova taxa de juros mensal (atual: %.4f):\n", vetorFinanciamentos[i]->taxa_juros);
            scanf("%f", &vetorFinanciamentos[i]->taxa_juros);

            // Recalcula valores
            vetorFinanciamentos[i]->valor_parcela = (vetorFinanciamentos[i]->valor_financiado * vetorFinanciamentos[i]->taxa_juros) /
                                                    (1 - pow(1 + vetorFinanciamentos[i]->taxa_juros, -vetorFinanciamentos[i]->tempo_financiamento));
            vetorFinanciamentos[i]->juros_totais = (vetorFinanciamentos[i]->valor_parcela * vetorFinanciamentos[i]->tempo_financiamento) -
                                                   vetorFinanciamentos[i]->valor_financiado;

            printf("Financiamento atualizado com sucesso!\n");
            return;
        }
    }
    printf("Financiamento com ID %d não encontrado.\n", id);
}

// Função para excluir um financiamento
void excluirFinanciamento(Financiamento **vetorFinanciamentos, int *count) {
    int id;
    printf("Digite o ID do financiamento que deseja excluir:\n");
    scanf("%d", &id);

    int encontrado = 0;
    for (int i = 0; i < *count; i++) {
        if (vetorFinanciamentos[i]->id == id) {
            encontrado = 1;

            free(vetorFinanciamentos[i]);

            for (int j = i; j < *count - 1; j++) {
                vetorFinanciamentos[j] = vetorFinanciamentos[j + 1];
            }

            (*count)--;
            printf("Financiamento excluído com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Financiamento não encontrado!\n");
    }
}

// Função para salvar financiamentos em arquivo
void salvarFinanciamentos(Financiamento **vetorFinanciamentos, int count) {
    FILE *file = fopen("financiamentos.txt", "w");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar os financiamentos.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "ID: %d\n", vetorFinanciamentos[i]->id);
        fprintf(file, "VALOR FINANCIADO: R$%.2f\n", vetorFinanciamentos[i]->valor_financiado);
        fprintf(file, "PERIODO: %d meses\n", vetorFinanciamentos[i]->tempo_financiamento);
        fprintf(file, "TAXA JUROS: %.4f\n", vetorFinanciamentos[i]->taxa_juros);
        fprintf(file, "VALOR PARCELA: R$%.2f\n", vetorFinanciamentos[i]->valor_parcela);
        fprintf(file, "JUROS TOTAIS: R$%.2f\n", vetorFinanciamentos[i]->juros_totais);
        fprintf(file, "-------------------------\n");
    }

    fclose(file);
    printf("Financiamentos salvos com sucesso!\n");
}

// Função para carregar financiamentos de arquivo
void carregarFinanciamentos(Financiamento **vetorFinanciamentos, int *count, int max_financiamentos) {
    FILE *file = fopen("financiamentos.txt", "r");
    if (file == NULL) {
        printf("Nenhum arquivo de financiamentos encontrado.\n");
        return;
    }

    Financiamento *financiamento = NULL;
    char linha[256];
    int id, tempo;
    float valor, taxa, parcela, juros;

    while (*count < max_financiamentos && fgets(linha, sizeof(linha), file) != NULL) {
        if (sscanf(linha, "ID: %d", &id) == 1) {
            financiamento = (Financiamento *)malloc(sizeof(Financiamento));
            if (financiamento == NULL) {
                printf("Erro ao alocar memória para o financiamento.\n");
                break;
            }

            financiamento->id = id;

            fgets(linha, sizeof(linha), file);
            sscanf(linha, "VALOR FINANCIADO: R$%f", &valor);
            financiamento->valor_financiado = valor;

            fgets(linha, sizeof(linha), file);
            sscanf(linha, "PERIODO: %d meses", &tempo);
            financiamento->tempo_financiamento = tempo;

            fgets(linha, sizeof(linha), file);
            sscanf(linha, "TAXA JUROS: %f", &taxa);
            financiamento->taxa_juros = taxa;

            fgets(linha, sizeof(linha), file);
            sscanf(linha, "VALOR PARCELA: R$%f", &parcela);
            financiamento->valor_parcela = parcela;

            fgets(linha, sizeof(linha), file);
            sscanf(linha, "JUROS TOTAIS: R$%f", &juros);
            financiamento->juros_totais = juros;

            fgets(linha, sizeof(linha), file);

            vetorFinanciamentos[*count] = financiamento;
            (*count)++;
        }
    }

    fclose(file);

    if (*count > 0) {
        printf("Financiamentos carregados com sucesso!\n");
    }
}

void Price(Financiamento *f) {
    FILE *doc;
    float parcelaFinanciamento;

    // Abrir arquivo para salvar o relatório
    doc = fopen("Relatorio_de_financiamento_Price.txt", "w");
    if (doc == NULL) {
        printf("Erro ao abrir o arquivo do relatório de financiamento\n");
        return;
    }

    // Cálculo da parcela usando sistema Price
    parcelaFinanciamento = f->valor_financiado * f->taxa_juros *
                           pow(1 + f->taxa_juros, f->tempo_financiamento) /
                           (pow(1 + f->taxa_juros, f->tempo_financiamento) - 1);

    // Gravar informações no arquivo
    fprintf(doc, "MODO DE FINANCIAMENTO: SISTEMA PRICE\n");
    fprintf(doc, "Valor das Parcelas: R$%.2f\n", parcelaFinanciamento);
    fprintf(doc, "JUROS TOTAIS: R$%.2f\n", (parcelaFinanciamento * f->tempo_financiamento) - f->valor_financiado);
    fprintf(doc, "VALOR TOTAL A SER PAGO: %.2f\n", parcelaFinanciamento * f->tempo_financiamento);
    fclose(doc);

    printf("Relatório do financiamento Price salvo com sucesso!\n");
}

void Sac(Financiamento *f) {
    FILE *doc;
    float parcela, totalPago = 0, jurosTotais = 0;
    int i;

    // Abrir arquivo para salvar o relatório
    doc = fopen("Relatorio_de_financiamento_SAC.txt", "w");
    if (doc == NULL) {
        printf("Erro ao abrir o arquivo do relatório de financiamento\n");
        return;
    }

    // Amortização fixa no sistema SAC
    f->amortizacao = f->valor_financiado / f->tempo_financiamento;

    fprintf(doc, "MODO DE FINANCIAMENTO: SISTEMA SAC\n\n");

    // Calcular e registrar cada parcela
    for (i = 1; i <= f->tempo_financiamento; i++) {
        parcela = f->amortizacao + (f->valor_financiado - (i - 1) * f->amortizacao) * f->taxa_juros;
        fprintf(doc, "Parcela %d: R$%.2f\n", i, parcela);
        totalPago += parcela;
    }

    // Calcular juros totais
    jurosTotais = totalPago - f->valor_financiado;

    // Registrar no relatório
    fprintf(doc, "\nJUROS TOTAIS: R$%.2f\n", jurosTotais);
    fprintf(doc, "VALOR TOTAL A SER PAGO: R$%.2f\n", totalPago);
    fclose(doc);

    printf("Relatório do financiamento SAC salvo com sucesso!\n");
}


// Menu de financiamento
void menuFinanciamento(Financiamento **vetorFinanciamentos, int *count, int max_financiamentos) {
    int opcao;

    do {
        printf("\n--- Menu Financiamentos ---\n");
        printf("1 - Criar Financiamento\n");
        printf("2 - Listar Financiamentos\n");
        printf("3 - Atualizar Financiamento\n");
        printf("4 - Excluir Financiamento\n");
        printf("5 - Calcular Sistema Price\n");
        printf("6 - Calcular Sistema SAC\n");
        printf("7 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criarFinanciamento(vetorFinanciamentos, count, max_financiamentos);
                break;
            case 2:
                exibirFinanciamentos(vetorFinanciamentos, *count);
                break;
            case 3:
                atualizarFinanciamento(vetorFinanciamentos, *count);
                break;
            case 4:
                excluirFinanciamento(vetorFinanciamentos, count);
                break;
            case 5: {
                int id;
                printf("Digite o ID do financiamento para calcular (Price): ");
                scanf("%d", &id);

                for (int i = 0; i < *count; i++) {
                    if (vetorFinanciamentos[i]->id == id) {
                        Price(vetorFinanciamentos[i]);
                        break;
                    }
                }
                break;
            }
            case 6: {
                int id;
                printf("Digite o ID do financiamento para calcular (SAC): ");
                scanf("%d", &id);

                for (int i = 0; i < *count; i++) {
                    if (vetorFinanciamentos[i]->id == id) {
                        Sac(vetorFinanciamentos[i]);
                        break;
                    }
                }
                break;
            }
            case 7:
                salvarFinanciamentos(vetorFinanciamentos, *count); // Salva antes de sair
                printf("Saindo do menu de financiamentos.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 7);
}
