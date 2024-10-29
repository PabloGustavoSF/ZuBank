// transfer.c
#include "transfer.h"
#include "transfer.h"
#include "investiment.h"
#include "emprest.h"
#include "financiament.h"
#include "extrato.h"

// Funcao que realiza a transferencia entre duas contas bancarias.
//void transfer (float transferencia, float saldo_inicial, char beneficiario[50], int conta_trans, char nome[50], int conta, float saldo_final) {
void transfer (Transferencia transfer.transferencia, Usuario usuario.usuario){
	do{
		printf("Quanto deseja transferir?\nR$");
		scanf("%f", &transferencia);
		if (transferencia > saldo_inicial){
			printf("SALDO INSUFICIENTE!\n");
			}
	} while (transferencia > saldo_inicial);
		printf("Qual o nome do beneficiário?\n");
		fflush(stdin);
		gets(beneficiario);
		printf("Qual o número da conta para qual deseja transferir o valor?\n");
		scanf("%d", &conta_trans);
		file1 = fopen("RECIBO DE TRANSFERENCIA.txt", "w");
		if (file1 == NULL) {
       		printf("ERRO AO ABRIR O ARQUIVO DO RECIBO DE TRANSFERÊNCIA!\n");
  			return 1;
		}
		fprintf(file1, "RECIBO DE TRANSFERÊNCIA\n\n\n");
		fprintf(file1, "PAGADOR: %s\n", nome);
		fprintf(file1, "CONTA BANCÁRIA: %d\n", conta);
		fprintf(file1, "BENEFICIÁRIO: %s\n", beneficiario);
		fprintf(file1, "CONTA RECEPTORA: %d\n", conta_trans);
		fprintf(file1, "VALOR RECEBIDO: R$%.2f\n", transferencia);
		fclose(file1);
		printf("SALDO ATUAL: %.2f\n", saldo_inicial - transferencia);
		saldo_final = saldo_inicial - transferencia;
		printf("TRANSFERÊNCIA REALIZADA COM SUCESSO, CONSULTE SEU RECIBO!\n");
}
