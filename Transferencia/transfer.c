// transfer.c
#include "transfer.h"

// Função que realiza a transferência entre duas contas bancárias
void transfer(Usuario *usuario, Transferencia *transf) {
    // Solicita e verifica o valor da transferência
    do {
        printf("Quanto deseja transferir?\nR$");
        scanf("%f", &transf->transferencia);
        if (transf->transferencia > usuario->saldo_inicial) {
            printf("SALDO INSUFICIENTE!\n");
        }
    } while (transf->transferencia > usuario->saldo_inicial);

    // Solicita o nome do beneficiário e o número da conta para a transferência
    printf("Qual o nome do beneficiário?\n");
    fflush(stdin);
    fgets(transf->beneficiario, sizeof(transf->beneficiario), stdin);
    printf("Qual o número da conta para qual deseja transferir o valor?\n");
    scanf("%d", &transf->conta_trans);

    // Calcula o saldo final após a transferência
    usuario->saldo_final = usuario->saldo_inicial - transf->transferencia;

    // Gera o recibo de transferência em um arquivo de texto
    FILE *file1 = fopen("RECIBO_DE_TRANSFERENCIA.txt", "w");
    if (file1 == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DO RECIBO DE TRANSFERÊNCIA!\n");
        return;
    }

    fprintf(file1, "RECIBO DE TRANSFERÊNCIA\n\n");
    fprintf(file1, "PAGADOR: %s\n", usuario->nome);
    fprintf(file1, "CONTA BANCÁRIA: %d\n", usuario->conta);
    fprintf(file1, "SALDO INICIAL: R$%.2f\n", usuario->saldo_inicial);
    fprintf(file1, "BENEFICIÁRIO: %s\n", transf->beneficiario);
    fprintf(file1, "CONTA RECEPTORA: %d\n", transf->conta_trans);
    fprintf(file1, "VALOR TRANSFERIDO: R$%.2f\n", transf->transferencia);
    fprintf(file1, "SALDO FINAL: R$%.2f\n", usuario->saldo_final);

    fclose(file1);

    printf("TRANSFERÊNCIA REALIZADA COM SUCESSO. CONSULTE SEU RECIBO!\n");
    printf("SALDO ATUAL: R$%.2f\n", usuario->saldo_final);
}
