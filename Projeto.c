#include <stdio.h>
#include <string.h>
#include <math.h>
#include <locale.h>
//O CÓDIGO NAO TÁ COMPLETO, CADA CASE VAI VIRAR UMA FUNÇÃO NO FINAL
int main (){
	setlocale(LC_CTYPE, "Portuguese_Brazil");
	FILE *file1, *file2, *file3;
	int servico, continua, conta, conta_trans, meses_investidos, parcelas, tipo_financiamento, i_sac;
	float saldo, transferencia, investimento, rendimento_bruto, rendimento_liquido, P1_sac, P_sac, juros_tot_sac=0, P_total=0;
	float ir, financiamento, juros = 0.0146, parcela_financiamento, amortizacao;
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
		printf("\n4 - Realizar financiamento\n5 - Extrato\n");
		scanf("%d", &servico);
		switch (servico){
			case 1: printf("Saldo disponível: R$%.2f", saldo);
				break;
			case 2:
				//COMPLETO
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
				//COMPLETO
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
				saldo += rendimento_liquido;
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
		case 4:	//JUROS MENSAL DE 1.46% a.m. E 18.98 a.a. DE REFERÊNCIA É DO BANCO BANESTES S.A.
				//PRICE COMPLETO
				printf("Qual modelo de financiamento será utilizado?\n");
				do{
					printf("1 - PRICE: Parcelas fixas\n2 - SAC: Parcelas decrescentes\n");
					scanf("%d", &tipo_financiamento);
				} while (tipo_financiamento != 1 && tipo_financiamento != 2);
				printf("Qual o valor do financiamento que deseja realizar?\n");
				scanf("%f", &financiamento);
				printf("O pagamento será realizado em quantas parcelas?\n");
				scanf("%d", &parcelas);
				if (tipo_financiamento == 1){
					file3 = fopen("RELATORIO DE FINANCIAMENTO PRICE.txt", "w");
					if (file3 == NULL) {
        				printf("ERRO AO ABRIR O ARQUIVO DO RELATÓRIO DE FINANCIAMENTO!\n");
       				return 1;
        			}
					parcela_financiamento = financiamento*juros*(pow(1 + juros, parcelas))/((pow(1 + juros, parcelas)) - 1);
					fprintf(file3, "MODO DE FINANCIAMENTO: SISTEMA PRICE\n");
					fprintf(file3, "Valor das Parcelas: R$%.2f\n", parcela_financiamento);
					fprintf(file3, "JUROS TOTAIS: R$%.2f\n", (parcela_financiamento*parcelas) - financiamento);
					fprintf(file3, "VALOR TOTAL A SER PAGO: %.2f\n", parcela_financiamento*parcelas);
					fclose(file3);
				} else {
					file3 = fopen("RELATORIO DE FINANCIAMENTO.txt", "w");
					amortizacao = financiamento/parcelas;
					P1_sac = amortizacao + (financiamento*juros);
				}
					for (i_sac=1; i_sac <= parcelas; i_sac++){
						if (i_sac == 1){
							fprintf(file3, "MODO DE FINANCIAMENTO: SISTEMA SAC\n");
							fprintf(file3, "Parcela %d: R$%.2f\n", i_sac, P1_sac);
						} else {
							for(i_sac == 3; i_sac <= parcelas; i_sac++){
								P_sac = amortizacao + (financiamento - (i_sac - 1)*amortizacao)*juros;
								//printf("\nP_sac: %.2f\nP1_sac: %.2f\ni_sac: %d\n", P_sac, P1_sac, i_sac);
							//	P_sac = amortizacao/(1 - pow(1 + juros, parcelas));
								fprintf(file3, "Parcela %d: R$%.2f\n", i_sac, P_sac);
								P_total += P_sac;
								}
								juros_tot_sac = P_sac - financiamento;
							//P1_sac += P_sac;
							fprintf(file3, "JUROS TOTAIS: R$%.2f\n", juros_tot_sac);
							fprintf(file3, "VALOR TOTAL A SER PAGO: %.2f\n", juros_tot_sac + financiamento);
							fclose(file3);
							break;
						}
					}
		case 5: 
			break;
		default: printf("OPERAÇÃO INVÁLIDA!");
	}
	do{
		printf("\nDeseja continuar? Digite 0 para encerrar e 1 para continuar!\n");
		scanf("%d", &continua);
		} while (continua != 0 && continua != 1);
	} while (continua == 1);
	return 0;
}
