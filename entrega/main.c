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
#define nINVEST 10       // Número máximo de investimentos
#define nEMPREST 5       // Número máximo de empréstimos
#define nFINANCIAMENTO 5 // Número máximo de financiamentos

void exibirTitulo(const char *titulo) {
    printf("\n=========================================\n");
    printf("   %s\n", titulo);
    printf("=========================================\n");
}

void exibirLinha() {
    printf("-----------------------------------------\n");
}

int main(int argc, char const *argv[])
{
    setlocale(LC_CTYPE, "Portuguese_Brazil");

    Conta user;
    int continua, servico;

    exibirTitulo("BEM-VINDO AO BANCO ZUBANK");

    criarConta(&user);
    Cliente *novoCliente = criarCliente(user.nome, user.conta_id, user.saldo_Inicial);

    // Alocação de vetor de ponteiros para Transferencia
    Transferencia **transfers = (Transferencia **)calloc(nTRANSFER, sizeof(Transferencia *));
    if (transfers == NULL)
    {
        printf("Erro ao alocar memoria para transferencias.\n");
        return 1;
    }
    int countTransferencias = 0;

    // Alocação e inicialização para investimentos
    Investimento **investimentos = (Investimento **)calloc(nINVEST, sizeof(Investimento *));
    if (investimentos == NULL)
    {
        printf("Erro ao alocar memoria para investimentos.\n");
        free(transfers);
        return 1;
    }
    int countInvestimentos = 0;

    // Alocação e inicialização para empréstimos
    Emprestimo **emprestimos = (Emprestimo **)calloc(nEMPREST, sizeof(Emprestimo *));
    if (emprestimos == NULL)
    {
        printf("Erro ao alocar memoria para emprestimos.\n");
        free(transfers);
        free(investimentos);
        return 1;
    }
    int countEmprestimos = 0;

    // Alocação e inicialização para financiamentos
    Financiamento **financiamentos = (Financiamento **)calloc(nFINANCIAMENTO, sizeof(Financiamento *));
    if (financiamentos == NULL)
    {
        printf("Erro ao alocar memoria para financiamentos.\n");
        free(transfers);
        free(investimentos);
        free(emprestimos);
        return 1;
    }
    int countFinanciamentos = 0;

    exibirLinha();
    printf("Dados da Conta:\n");
    printf("Nome: %s\n", user.nome);
    printf("ID da Conta: %d\n", user.conta_id);
    printf("Saldo Inicial: R$%.2f\n", user.saldo_Inicial);
    exibirLinha();

    do
    {
        exibirTitulo("MENU PRINCIPAL");
        printf("1 - Realizar Transferencia\n");
        printf("2 - Gerenciar Investimentos\n");
        printf("3 - Realizar Emprestimo\n");
        printf("4 - Realizar Financiamento\n");
        printf("5 - Gerar Extrato\n");
        printf("6 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &servico);

        switch (servico)
        {
        case 1:
            exibirTitulo("TRANSFERENCIAS");
            menuTransferencia(transfers, novoCliente, nTRANSFER, &countTransferencias);
            break;
        case 2:
            exibirTitulo("INVESTIMENTOS");
            menuInvestimento(investimentos, &countInvestimentos, nINVEST, &novoCliente->saldo_final);
            break;
        case 3:
            exibirTitulo("EMPRESTIMOS");
            menuEmprestimo(emprestimos, &countEmprestimos, nEMPREST, &novoCliente->saldo_final);
            break;
        case 4:
            exibirTitulo("FINANCIAMENTOS");
            menuFinanciamento(financiamentos, &countFinanciamentos, nFINANCIAMENTO);
            break;
        case 5:
            exibirTitulo("EXTRATO");
            gerarExtratoBancario(novoCliente, transfers, countTransferencias, investimentos, countInvestimentos, emprestimos, countEmprestimos, financiamentos, countFinanciamentos);
            break;
        case 6:
            exibirTitulo("ENCERRANDO O PROGRAMA");
            printf("Obrigado por utilizar o Banco ZUBANK. Ate logo!\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
            break;
        }

        if (servico != 6)
        {
            do
            {
                printf("\nDeseja realizar outra operacao? (1 - Sim / 0 - Nao): ");
                scanf("%d", &continua);
            } while (continua != 0 && continua != 1);
        }
        else
        {
            continua = 0;
        }
    } while (continua == 1);

    // Liberar memória alocada
    for (int i = 0; i < countTransferencias; i++)
        free(transfers[i]);
    free(transfers);

    for (int i = 0; i < countInvestimentos; i++)
        free(investimentos[i]);
    free(investimentos);

    for (int i = 0; i < countEmprestimos; i++)
        free(emprestimos[i]);
    free(emprestimos);

    for (int i = 0; i < countFinanciamentos; i++)
        free(financiamentos[i]);
    free(financiamentos);

    free(novoCliente);

    return 0;
}
