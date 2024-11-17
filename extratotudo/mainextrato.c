// main.c
#include <stdio.h>
#include <string.h>
#include "fechamento.h"

int main() {
    Cliente cliente;

    // Solicita o nome do cliente e o número da conta
    printf("Digite o nome do cliente: ");
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0';  // Remove o '\n' do final

    printf("Digite o número da conta: ");
    scanf("%d", &cliente.conta);

    // Solicita os valores para o relatório de fechamento
    printf("Digite o saldo inicial: R$");
    scanf("%f", &cliente.saldo_inicial);

    printf("Digite o rendimento líquido de investimento: R$");
    scanf("%f", &cliente.rendimento_liquido);

    printf("Digite o valor do empréstimo recebido: R$");
    scanf("%f", &cliente.emprestimo);

    printf("Digite o total de transferências realizadas: R$");
    scanf("%f", &cliente.transferencias);

    printf("Digite o total das parcelas do empréstimo: R$");
    scanf("%f", &cliente.parcelas_emprestimo);

    printf("Digite o total das parcelas do financiamento: R$");
    scanf("%f", &cliente.parcelas_financiamento);

    // Gera o relatório de fechamento de conta com os dados fornecidos
    gerarRelatorioFechamentoConta(&cliente);

    return 0;
}
