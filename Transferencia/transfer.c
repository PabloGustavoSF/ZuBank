// transfer.c
#include "transfer.h"

// Fun��o que realiza a transfer�ncia entre duas contas banc�rias
void transfer(Usuario *usuario, Transferencia *transf) {
    // Solicita e verifica o valor da transfer�ncia
    do {
        printf("Quanto deseja transferir?\nR$");
        scanf("%f", &transf->transferencia);
        if (transf->transferencia > usuario->saldo_inicial) {
            printf("SALDO INSUFICIENTE!\n");
        }
    } while (transf->transferencia > usuario->saldo_inicial);

    // Solicita o nome do benefici�rio e o n�mero da conta para a transfer�ncia
    printf("Qual o nome do benefici�rio?\n");
    fflush(stdin);
    fgets(transf->beneficiario, sizeof(transf->beneficiario), stdin);
    printf("Qual o n�mero da conta para qual deseja transferir o valor?\n");
    scanf("%d", &transf->conta_trans);

    // Calcula o saldo final ap�s a transfer�ncia
    usuario->saldo_final = usuario->saldo_inicial - transf->transferencia;

    // Gera o recibo de transfer�ncia em um arquivo de texto
    FILE *file1 = fopen("RECIBO_DE_TRANSFERENCIA.txt", "w");
    if (file1 == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DO RECIBO DE TRANSFER�NCIA!\n");
        return;
    }

    fprintf(file1, "RECIBO DE TRANSFER�NCIA\n\n");
    fprintf(file1, "PAGADOR: %s\n", usuario->nome);
    fprintf(file1, "CONTA BANC�RIA: %d\n", usuario->conta);
    fprintf(file1, "SALDO INICIAL: R$%.2f\n", usuario->saldo_inicial);
    fprintf(file1, "BENEFICI�RIO: %s\n", transf->beneficiario);
    fprintf(file1, "CONTA RECEPTORA: %d\n", transf->conta_trans);
    fprintf(file1, "VALOR TRANSFERIDO: R$%.2f\n", transf->transferencia);
    fprintf(file1, "SALDO FINAL: R$%.2f\n", usuario->saldo_final);

    fclose(file1);

    printf("TRANSFER�NCIA REALIZADA COM SUCESSO. CONSULTE SEU RECIBO!\n");
    printf("SALDO ATUAL: R$%.2f\n", usuario->saldo_final);
}
