#include "investimento.h"

// Função para criar o investimento
Investimento *criarInvestimento(float investimento_valor, int meses_investidos)
{
    Investimento *investimento = (Investimento *)malloc(sizeof(Investimento));
    if (investimento == NULL)
    {
        printf("Erro ao alocar memoria para o investimento.\n");
        return NULL;
    }

    // Determinar a alíquota do Imposto de Renda (IR)
    float ir;
    if (meses_investidos <= 6)
        ir = 0.225;
    else if (meses_investidos <= 12)
        ir = 0.2;
    else if (meses_investidos <= 24)
        ir = 0.175;
    else
        ir = 0.15;

    // Calcular rendimentos
    float rendimento_bruto = investimento_valor * pow(1.009542, meses_investidos);
    float rendimento_liquido = rendimento_bruto - ((rendimento_bruto - investimento_valor) * ir);

    // Preencher a estrutura
    investimento->investimento = investimento_valor;
    investimento->meses_investidos = meses_investidos;
    investimento->ir = ir;
    investimento->rendimento_bruto = rendimento_bruto - investimento_valor;
    investimento->rendimento_liquido = rendimento_liquido;

    return investimento;
}

// Função para exibir um investimento
void exibirInvestimento(const Investimento *investimento)
{
    printf("\n--- Detalhes do Investimento ---\n");
    printf("Valor investido: R$%.2f\n", investimento->investimento);
    printf("Meses corridos: %d\n", investimento->meses_investidos);
    printf("Aliquota do IR: %.2f%%\n", investimento->ir * 100);
    printf("Rendimento bruto: R$%.2f\n", investimento->rendimento_bruto);
    printf("Rendimento liquido: R$%.2f\n", investimento->rendimento_liquido);
}

// Função para salvar os investimentos no arquivo
void salvarInvestimentos(Investimento **vetorInvestimentos, int count)
{
    FILE *arquivo = fopen("investimentos.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de investimentos.\n");
        return;
    }

    // Cabeçalho do arquivo
    fprintf(arquivo, "Valor Investido | Meses Investidos | IR (%%) | Rendimento Bruto | Rendimento Líquido\n");
    fprintf(arquivo, "----------------|-----------------|--------|------------------|-------------------\n");

    for (int i = 0; i < count; i++)
    {
        if (vetorInvestimentos[i] != NULL)
        {
            fprintf(arquivo, "%.2f            | %d               | %.2f   | %.2f            | %.2f\n",
                    vetorInvestimentos[i]->investimento,
                    vetorInvestimentos[i]->meses_investidos,
                    vetorInvestimentos[i]->ir * 100, // Multiplicando por 100 para exibir como percentual
                    vetorInvestimentos[i]->rendimento_bruto,
                    vetorInvestimentos[i]->rendimento_liquido);
        }
    }

    fclose(arquivo);
    printf("Investimentos salvos com sucesso no arquivo!\n");
}

// Função para carregar investimentos do arquivo
void carregarInvestimentos(Investimento **vetorInvestimentos, int *count, int max_investimentos)
{
    FILE *arquivo = fopen("investimentos.txt", "w");
    if (arquivo == NULL)
    {
        printf("Nenhum arquivo de investimentos encontrado.\n");
        return;
    }

    while (*count < max_investimentos && !feof(arquivo))
    {
        Investimento *investimento = (Investimento *)malloc(sizeof(Investimento));
        if (investimento == NULL)
        {
            printf("Erro ao alocar memoria para o investimento.\n");
            break;
        }

        if (fscanf(arquivo, "%f %d %f %f %f",
                   &investimento->investimento,
                   &investimento->meses_investidos,
                   &investimento->ir,
                   &investimento->rendimento_bruto,
                   &investimento->rendimento_liquido) == 5)
        {
            vetorInvestimentos[*count] = investimento;
            (*count)++;
        }
        else
        {
            free(investimento);
            break;
        }
    }

    fclose(arquivo);
    printf("Investimentos carregados com sucesso!\n");
}

// Função para deletar um investimento
void deletarInvestimento(Investimento **vetorInvestimentos, int id, int *count)
{
    if (id < 0 || id >= *count || vetorInvestimentos[id] == NULL)
    {
        printf("Investimento invalido.\n");
        return;
    }

    free(vetorInvestimentos[id]);
    vetorInvestimentos[id] = NULL;

    for (int i = id; i < *count - 1; i++)
    {
        vetorInvestimentos[i] = vetorInvestimentos[i + 1];
    }

    vetorInvestimentos[*count - 1] = NULL;
    (*count)--;

    printf("Investimento excluido com sucesso.\n");
}

// Menu de gerenciamento de investimentos
void menuInvestimento(Investimento **vetorInvestimentos, int *count, int max_investimentos, float *saldo_final)
{
    int op, id, meses;
    float valor;

    carregarInvestimentos(vetorInvestimentos, count, max_investimentos);

    do
    {
        printf("| Seu saldo e ( R$%.2f )\n", *saldo_final);
        printf("\n| MENU Investimento |\n");
        printf("| 1 | Criar Investimento\n");
        printf("| 2 | Exibir Investimentos\n");
        printf("| 3 | Deletar Investimento\n");
        printf("| 4 | Salvar e Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1: // Criar investimento
            if (*count < max_investimentos)
            {
                printf("Quanto deseja investir? R$");
                scanf("%f", &valor);

                if (valor > *saldo_final)
                {
                    printf("Saldo insuficiente! Seu saldo atual e R$%.2f.\n", *saldo_final);
                }
                else
                {
                    printf("Por quantos meses deseja investir? ");
                    scanf("%d", &meses);

                    vetorInvestimentos[*count] = criarInvestimento(valor, meses);
                    if (vetorInvestimentos[*count] != NULL)
                    {
                        (*count)++;
                        *saldo_final -= valor; // Deduz o valor investido do saldo final
                        printf("Investimento criado com sucesso! Seu novo saldo e R$%.2f.\n", *saldo_final);
                    }
                }
            }
            else
            {
                printf("Limite de investimentos atingido.\n");
            }
            break;

        case 2: // Exibir investimentos
            if (*count == 0)
            {
                printf("Nenhum investimento cadastrado.\n");
            }
            else
            {
                for (int i = 0; i < *count; i++)
                {
                    printf("\nID: %d\n", i + 1);
                    exibirInvestimento(vetorInvestimentos[i]);
                }
            }
            break;

        case 3: // Deletar investimento
            printf("Informe o ID do investimento que deseja deletar (1 a %d): ", *count);
            scanf("%d", &id);
            if (id > 0 && id <= *count)
            {
                *saldo_final += vetorInvestimentos[id - 1]->investimento; // Reembolsa o valor investido
                deletarInvestimento(vetorInvestimentos, id - 1, count);
                printf("Investimento deletado com sucesso! Seu novo saldo e R$%.2f.\n", *saldo_final);
            }
            else
            {
                printf("ID invalido.\n");
            }
            break;

        case 4: // Salvar e sair
            salvarInvestimentos(vetorInvestimentos, *count);
            printf("Saindo do menu de investimentos...\n");
            break;

        default:
            printf("Opção invalida, tente novamente.\n");
            break;
        }
    } while (op != 4);
}
