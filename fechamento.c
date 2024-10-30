#include "fechamento.h"

int verificar_pendencias(struct FechamentoConta *fc) {
    int pendencias = 0;

    if (fc->parcela_emprestimo > 0) {
        printf("Você possui um empréstimo pendente no valor de R$%.2f.\n", fc->parcela_emprestimo);
        printf("Por favor, liquide o empréstimo antes de fechar a conta.\n");
        pendencias = 1;
    }

    if (fc->parcela_financiamento > 0) {
        printf("Você possui um financiamento pendente no valor de R$%.2f.\n", fc->parcela_financiamento);
        printf("Por favor, liquide o financiamento antes de fechar a conta.\n");
        pendencias = 1;
    }

    if (pendencias) {
        printf("Não é possível fechar a conta com pendências financeiras.\n");
    }

    return pendencias;
}

int fechar_conta(struct FechamentoConta *fc, FILE *file6, int *continua) {
    int confirmar;

    // Verifica se há pendências antes de prosseguir
    if (verificar_pendencias(fc)) {
        return 0; // Sai se houver pendências
    }

    // Confirmação do fechamento da conta
    printf("Você tem certeza que deseja fechar sua conta? Digite 1 para Sim ou 0 para Não:\n");
    scanf("%d", &confirmar);

    if (confirmar == 1) {
        // Transferência de saldo, se houver
        if (fc->saldo_final > 0) {
            printf("Seu saldo de R$%.2f será transferido para outra conta.\n", fc->saldo_final);
            fc->saldo_final = 0; // Zera o saldo
        }

        // Geração do relatório de fechamento
        file6 = fopen("RELATORIO_DE_FECHAMENTO_DE_CONTA.txt", "w");
        if (file6 == NULL) {
            printf("ERRO AO ABRIR O ARQUIVO DO RELATÓRIO DE FECHAMENTO DE CONTA!\n");
            return 1;
        }

        fprintf(file6, "RELATÓRIO DE FECHAMENTO DE CONTA\n\n");
        fprintf(file6, "Nome do Cliente: %s\n", fc->nome);
        fprintf(file6, "Número da Conta: %d\n", fc->conta);
        fprintf(file6, "Saldo Final: R$%.2f\n", fc->saldo_final);
        fprintf(file6, "Data de Fechamento: (inserir data aqui)\n");
        fclose(file6);

        printf("Sua conta foi fechada com sucesso. Confira o relatório de fechamento de conta.\n");
        *continua = 0; // Encerra o loop principal
    } else {
        printf("Operação de fechamento de conta cancelada.\n");
    }

    return 0;
}
