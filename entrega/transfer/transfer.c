#include "transfer.h"


// Fun��es para CRUD de Transferencia
Transferencia *criarTransferencia(const char *beneficiario, int conta_trans, float valor)
{
    Transferencia *transf = (Transferencia *)malloc(sizeof(Transferencia));
    if (transf == NULL)
    {
        printf("Erro ao alocar memória para a transferência.\n");
        return NULL;
    }
    strncpy(transf->beneficiario, beneficiario, sizeof(transf->beneficiario) - 1);
    transf->beneficiario[sizeof(transf->beneficiario) - 1] = '\0'; // Garante o terminador nulo
    transf->conta_trans = conta_trans;
    transf->valor_transferencia = valor;

    return transf;
}


void exibirTransferencia(const Transferencia **vetorTransf, int count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (vetorTransf[i] == NULL)
            continue;

        printf("Transferência %zu:\n", i + 1);
        printf("  Beneficiário: %s\n", vetorTransf[i]->beneficiario);
        printf("  Conta de Destino: %d\n", vetorTransf[i]->conta_trans);
        printf("  Valor Transferido: R$%.2f\n", vetorTransf[i]->valor_transferencia);
    }
}




void deletarTransferencia(Transferencia **vetorTransf, int id, int *count)
{
    if (id < 0 || id >= *count || vetorTransf[id] == NULL)
    {
        printf("Transferência inválida.\n");
        return;
    }

    free(vetorTransf[id]);
    vetorTransf[id] = NULL;

    // Reordena o vetor removendo espaços vazios
    for (int i = id; i < *count - 1; i++)
    {
        vetorTransf[i] = vetorTransf[i + 1];
    }

    vetorTransf[*count - 1] = NULL;
    (*count)--;

    printf("Transferência excluída com sucesso.\n");
}

void realizarTodasTransferencias(Cliente *cliente, Transferencia **vetorTransf, int *count, FILE *arquivo)
{
    if (cliente == NULL || vetorTransf == NULL || arquivo == NULL)
    {
        printf("Erro: Parâmetros inválidos.\n");
        return;
    }

    for (int i = 0; i < *count; i++)
    {
        if (vetorTransf[i] == NULL)
            continue;

        // Verifica se o cliente tem saldo suficiente
        if (cliente->saldo_final >= vetorTransf[i]->valor_transferencia)
        {
            cliente->saldo_final -= vetorTransf[i]->valor_transferencia;

            // Salva a transferência no arquivo
            fprintf(arquivo, "Beneficiário: %s\nConta: %d\nValor: R$%.2f\n\n",
                    vetorTransf[i]->beneficiario, vetorTransf[i]->conta_trans, vetorTransf[i]->valor_transferencia);

            printf("Transferência de R$%.2f para %s realizada com sucesso!\n",
                   vetorTransf[i]->valor_transferencia, vetorTransf[i]->beneficiario);
        }
        else
        {
            printf("Saldo insuficiente para realizar a transferência de R$%.2f para %s.\n",
                   vetorTransf[i]->valor_transferencia, vetorTransf[i]->beneficiario);
        }

        // Libera a memória da transferência realizada
        free(vetorTransf[i]);
        vetorTransf[i] = NULL;
    }

    // Atualiza a contagem para zero, já que todas as transferências foram processadas
    *count = 0;

    printf("Todas as transferências foram processadas.\n");
}

void menuTransferencia(Transferencia **vetorTransf, Cliente *cliente, int max_transf)
{
    int op, id, count = 0;
    float valor;
    char remetente[50];
    FILE *arquivo = fopen("transferencias.txt", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de transferências.\n");
        return;
    }

    do
    {
        printf("\n| MENU Transferência |\n");
        printf("| 1 | Criar Transferência\n");
        printf("| 2 | Exibir Transferências\n");
        printf("| 3 | Deletar Transferência\n");
        printf("| 4 | Realizar Todas as Transferências\n");
        printf("| 5 | Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1: // Criar transferência
            if (count < max_transf)
            {
                do
                {
                    printf("Quanto deseja transferir? R$");
                    scanf("%f", &valor);
                    getchar(); // Limpa o buffer do scanf
                    if (valor > cliente->saldo_final)
                    {
                        printf("Saldo insuficiente! Saldo disponível: R$%.2f\n", cliente->saldo_final);
                    }
                } while (valor > cliente->saldo_final);

                printf("Qual o nome do beneficiário? ");
                fgets(remetente, sizeof(remetente), stdin);
                remetente[strcspn(remetente, "\n")] = '\0'; // Remove o '\n'

                printf("Qual o número da conta para qual deseja transferir o valor? ");
                scanf("%d", &id);

                vetorTransf[count] = criarTransferencia(remetente, id, valor);
                count++;
            }
            else
            {
                printf("Limite de transferências atingido.\n");
            }
            break;

        case 2: // Exibir transferências
            exibirTransferencia((const Transferencia **)vetorTransf, count);

            break;

        case 3: // Deletar transferência
            printf("Informe o ID da transferência que deseja deletar (1 a %d): ", count);
            scanf("%d", &id);
            deletarTransferencia(vetorTransf, id - 1, &count);
            break;

        case 4: // Realizar todas as transferências
            if (count == 0)
            {
                printf("Nenhuma transferência pendente para realizar.\n");
                break;
            }

            realizarTodasTransferencias(cliente, vetorTransf, &count, arquivo);
            break;

        case 5: // Sair
            printf("Saindo do menu de transferências...\n");
            break;

        default:
            printf("Opção inválida, tente novamente.\n");
            break;
        }
    } while (op != 5);

    fclose(arquivo);

    // Exclui transferências pendentes ao sair
    excluirTransferenciasPendentes(vetorTransf, &count);
}


void excluirTransferenciasPendentes(Transferencia **vetorTransf, int *count)
{
    for (int i = 0; i < *count; i++)
    {
        if (vetorTransf[i] != NULL)
        {
            free(vetorTransf[i]);
            vetorTransf[i] = NULL;
        }
    }
    *count = 0;
    printf("Todas as transferências pendentes foram excluídas.\n");
}
