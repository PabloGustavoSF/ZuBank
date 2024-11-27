#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "conta/conta.h"
#include "transfer/transfer.h"
#include "investimento/investimento.h"
#include "emprestimo/emprestimo.h"

#define nTRANSFER 5
#define nINVEST 10  // Número máximo de investimentos

int main(int argc, char const *argv[])
{
    setlocale(LC_CTYPE, "Portuguese_Brazil");

    Conta user;
    int continua, servico;

    printf("SEJA BEM-VINDO AO BANCO ZUBANK!\n\n");

    criarConta(&user);
    Cliente *novoCliente = criarCliente(user.nome, user.conta_id, user.saldo_Inicial);

    // Alocação e inicialização para transferências
    Transferencia *transfers = (Transferencia *)calloc(nTRANSFER, sizeof(Transferencia));  
    if (transfers == NULL)
    {
        printf("Erro ao alocar memória para transferências.\n");
        return 1;  // Saída do programa em caso de falha na alocação
    }

    // Alocação e inicialização para investimentos
    Investimento **investimentos = (Investimento **)calloc(nINVEST, sizeof(Investimento *));
    if (investimentos == NULL)
    {
        printf("Erro ao alocar memória para investimentos.\n");
        free(transfers);  // Liberar memória de transfers antes de sair
        return 1;
    }
    int countInvestimentos = 0;  // Contador de investimentos criados

    printf("Nome: %s\n", user.nome);
    printf("ID da Conta: %d\n", user.conta_id);
    printf("Saldo Inicial: %.2f\n", user.saldo_Inicial);

    printf("Qual o número do serviço que deseja utilizar?\n");

    do
{
    printf("\n1 - Realizar transferência");
    printf("\n2 - Gerenciar investimentos"); // Atualizado: Chama o menu de investimentos
    printf("\n3 - Realizar empréstimo");
    printf("\n4 - Realizar financiamento");
    printf("\n5 - Extrato");
    printf("\n6 - Fechar conta\n");
    printf("Escolha: ");
    scanf("%d", &servico);

    switch (servico)
    {
    case 1:
        menuTransferencia(&transfers, novoCliente, nTRANSFER);  // Passando &transfers para função
        break;

    case 2:
        menuInvestimento(investimentos, &countInvestimentos, nINVEST, &novoCliente->saldo_final);  // Gerenciar investimentos
        break;

    case 3:
        printf("Funcionalidade de empréstimo ainda não implementada.\n");
        break;

    case 4:
        printf("Funcionalidade de financiamento ainda não implementada.\n");
        break;

    case 5:
        printf("Funcionalidade de extrato ainda não implementada.\n");
        break;

    case 6:
        printf("Fechando conta...\n");
        break;

    default:
        printf("Opção inválida! Tente novamente.\n");
        break;
    }

    if (servico != 6)
    {
        do
        {
            printf("\nDeseja continuar? Digite 0 para encerrar e 1 para continuar!\n");
            scanf("%d", &continua);
        } while (continua != 0 && continua != 1);
    }
    else
    {
        continua = 0;
    }
} while (continua == 1);


    printf("\nResumo da Conta:\n");
    printf("Nome: %s\n", novoCliente->nome);
    printf("ID da Conta: %d\n", novoCliente->conta);
    printf("Saldo Final: %.2f\n", novoCliente->saldo_final);

    // Liberar memória
    free(transfers);  // Liberando a memória alocada para transferências
    for (int i = 0; i < countInvestimentos; i++)  // Liberando memória dos investimentos
    {
        free(investimentos[i]);
    }
    free(investimentos);  // Liberando o vetor de ponteiros
    free(novoCliente);    // Liberando memória do cliente

    return 0;
}
