#include <stdio.h>
#include <string.h>
#include <math.h>
#include <locale.h>
int main (){
	setlocale(LC_CTYPE, "Portuguese_Brazil");
	FILE *file1, *file2;
	int servico, continua, conta, conta_trans, meses_investidos;
	float saldo, transferencia, investimento, rendimento_bruto, rendimento_liquido, ir, emprestimo;
	char nome[50], beneficiario[50];
	printf("SEJA BEM-VINDO AO BANCO ZUBANK!\n\n");
	printf("Qual o seu nome?\n");
	gets(nome);
	printf("Qual o seu saldo bancário?\n");
	scanf("%f", &saldo);
	printf("Qual o número da sua conta bancária?\n");
	scanf("%d", &conta);
	printf("Qual o número do serviço que deseja utilizar?\n");
	do{
		printf("1 - Visualizar saldo\n2 - Realizar transferência\n3 - Rendimento da conta");
		printf("\n4 - Realizar empréstimo\n5 - Pagar conta\n6 - Renegociar dívidas\n");
		scanf("%d", &servico);
		switch (servico){
			case 1: printf("Saldo disponível: R$%f", saldo);
				break;
			case 2:
				do{
				printf("Quanto deseja transferir?\nR$");
				scanf("%f", &transferencia);
				if (transferencia > saldo){
					printf("SALDO INSUFICIENTE!\n");
				}
				} while (transferencia > saldo);
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
				printf("SALDO ATUAL: %.2f\n", saldo-transferencia);
				printf("TRANSFERÊNCIA REALIZADA COM SUCESSO, CONSULTE SEU RECIBO!\n");
				break;
			case 3: 
				do{
				printf("Quanto do saldo disponível (R$%.2f) deseja investir?\n", saldo);
				scanf("%f", &investimento);
				} while (investimento > saldo);
				do{
				printf("Por quantos meses deseja deixar o valor investido?\n");
				scanf("%d", &meses_investidos);
				} while (meses_investidos < 0);
				if (meses_investidos <= 6){
					ir = 0.225;
					} else if (meses_investidos <= 12){
						ir = 0.2;
						} else if (meses_investidos <= 24){
							ir = 0.175;
							} else {
								ir = 0.15;
								}
				rendimento_bruto = investimento*(pow(1.00892704, meses_investidos));
				rendimento_liquido = (rendimento_bruto - ((investimento*pow(1.00892704, meses_investidos) - investimento)*ir));
				file2 = fopen("RELATORIO DE RENDIMENTOS.txt", "w");
				if (file2 == NULL) {
        			printf("ERRO AO ABRIR O ARQUIVO DO RELATÓRIO DE RENDIMENTOS!\n");
       				return 1;
        			}
				fprintf(file2, "RELATÓRIO DE RENDIMENTOS\n\n\n");
				fprintf(file2, "VALOR INVESTIDO: R$%.2f\n", investimento);
				fprintf(file2, "MESES CORRIDOS: %d meses\n", meses_investidos);
				fprintf(file2, "ALÍQUOTA DO IMPOSTO DE RENDA: %.2f%%\n", ir*100);
				fprintf(file2, "RENDIMENTO BRUTO: R$%.2f\n", rendimento_bruto);
				fprintf(file2, "RENDIMENTO LÍQUIDO: R$%.2f\n", rendimento_liquido);
				fclose(file2);
				printf("CONFIRA O SEU RELATÓRIO DE RENDIMENTOS!");
				break;
		case 4: printf("Qual o valor do empréstimo que deseja?\n");
				scanf("%f", &emprestimo);
		case 5:
		case 6:
		default: printf("OPERAÇÃO INVÁLIDA!");
		}
	do{
		printf("\nDeseja continuar? Digite 0 para encerrar e 1 para continuar!\n");
		scanf("%d", &continua);
		} while (continua != 0 && continua != 1);
	} while (continua == 1);
	return 0;
}
