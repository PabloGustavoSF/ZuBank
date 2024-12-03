#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "conta/conta.h"
#include "cliente/cliente.h"
#include "transfer/transfer.h"
#include "investimento/investimento.h"
#include "emprestimo/emprestimo.h"
#include "financiamento/financiamento.h"
#include "extrato/extrato.h"

#define nTRANSFER 5
#define nINVEST 10  // Número máximo de investimentos
#define nEMPREST 5  // Número máximo de empréstimos
#define nFINANCIAMENTO 5 // Número máximo de financiamentos

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

    // Alocação e inicialização para empréstimos
    Emprestimo **emprestimos = (Emprestimo **)calloc(nEMPREST, sizeof(Emprestimo *));
    if (emprestimos == NULL)
    {
        printf("Erro ao alocar memória para empréstimos.\n");
        free(transfers);  // Liberar memória de transfers antes de sair
        free(investimentos);  // Liberar memória de investimentos antes de sair
        return 1;
    }
    int countEmprestimos = 0;  // Contador de empréstimos criados

    // Alocação e inicialização para financiamentos
    Financiamento **financiamentos = (Financiamento **)calloc(nFINANCIAMENTO, sizeof(Financiamento *));
    if (financiamentos == NULL)
    {
        printf("Erro ao alocar memória para financiamentos.\n");
        free(transfers);
        free(investimentos);
        free(emprestimos);
        return 1;
    }
    int countFinanciamentos = 0; // Contador de financiamentos criados

    printf("Nome: %s\n", user.nome);
    printf("ID da Conta: %d\n", user.conta_id);
    printf("Saldo Inicial: %.2f\n", user.saldo_Inicial);

    printf("Qual o número do serviço que deseja utilizar?\n");

    do
    {
        printf("\n1 - Realizar transferência");
        printf("\n2 - Gerenciar investimentos");
        printf("\n3 - Realizar empréstimo");
        printf("\n4 - Realizar financiamento");
        printf("\n5 - Extrato");
        printf("\n6 - Fechar conta\n");
        printf("Escolha: ");
        scanf("%d", &servico);

        switch (servico)
        {
        case 1:
            menuTransferencia(&transfers, novoCliente, nTRANSFER);
            break;
        case 2:
            menuInvestimento(investimentos, &countInvestimentos, nINVEST, &novoCliente->saldo_final);
            break;
        case 3:
            menuEmprestimo(emprestimos, &countEmprestimos, nEMPREST, &novoCliente->saldo_final);
            break;
        case 4:
            menuFinanciamento(financiamentos, &countFinanciamentos, nFINANCIAMENTO);
            break;
        case 5:
            gerarExtratoBancario(novoCliente, transfers, nTRANSFER, investimentos, countInvestimentos, emprestimos, countEmprestimos, financiamentos, countFinanciamentos);
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

    // Liberar memória alocada
    free(transfers);
    free(investimentos);
    free(emprestimos);
    free(financiamentos);
    free(novoCliente);

    return 0;
}
