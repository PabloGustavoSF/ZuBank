#ifndef FECHAMENTO_H
#define FECHAMENTO_H

// Estrutura que representa os dados para o fechamento de conta
struct FechamentoConta {
    char nome[50];               // Nome do cliente
    int conta;                   // Número da conta
    float saldo_final;           // Saldo final
    float parcela_emprestimo;    // Valor pendente de empréstimo
    float parcela_financiamento; // Valor pendente de financiamento
};

// Função que verifica pendências de empréstimo ou financiamento
int verificar_pendencias(struct FechamentoConta *fc) {
    int pendencias = 0;

    if (fc->parcela_emprestimo > 0) {
        printf("Você possui um empréstimo pendente no valor de R$%.2f.\n", fc->parcela_emprestimo);
        pendencias = 1;
    }

    if (fc->parcela_financiamento > 0) {
        printf("Você possui um financiamento pendente no valor de R$%.2f.\n", fc->parcela_financiamento);
        pendencias = 1;
    }

    if (pendencias) {
        printf("Não é possível fechar a conta com pendências financeiras.\n");
    }

    return pendencias;
}

// Função para gerar o relatório de fechamento da conta
void gerar_relatorio_fechamento(struct FechamentoConta *fc) {
    FILE *file6 = fopen("RELATORIO_DE_FECHAMENTO.txt", "w");

    if (file6 == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DO RELATÓRIO DE FECHAMENTO!\n");
        return;
    }

    fprintf(file6, "RELATÓRIO DE FECHAMENTO DE CONTA\n\n");
    fprintf(file6, "Nome do Cliente: %s\n", fc->nome);
    fprintf(file6, "Número da Conta: %d\n", fc->conta);
    fprintf(file6, "Saldo Final: R$%.2f\n", fc->saldo_final);
    fprintf(file6, "Data de Fechamento: (inserir data aqui)\n");

    fclose(file6);
    printf("Relatório de fechamento gerado com sucesso!\n");
}

// Função para realizar o fechamento de conta
void fechar_conta(struct FechamentoConta *fc) {
    int confirmar;

    // Verifica se há pendências antes de continuar
    if (verificar_pendencias(fc)) {
        return; // Interrompe se houver pendências
    }

    // Confirmação do cliente para fechar a conta
    printf("Você tem certeza que deseja fechar sua conta? Digite 1 para Sim ou 0 para Não: ");
    scanf("%d", &confirmar);

    if (confirmar == 1) {
        if (fc->saldo_final > 0) {
            printf("Seu saldo de R$%.2f será transferido para outra conta.\n", fc->saldo_final);
            fc->saldo_final = 0; // Zera o saldo
        }
        gerar_relatorio_fechamento(fc); // Gera o relatório
    } else {
        printf("Operação de fechamento de conta cancelada.\n");
    }
}

#endif // FECHAMENTO_H
