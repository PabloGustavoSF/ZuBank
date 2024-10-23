#include <stdio.h>
#include <string.h>
#include <math.h>
#include <locale.h>
int main (){
	setlocale(LC_CTYPE, "Portuguese_Brazil");
	FILE *file1, *file2, *file3, *file4, *file5;
	int servico, continua, conta, conta_trans, meses_investidos, parcelas, tipo_financiamento, i_sac, tempo_emprestimo;
	float saldo_inicial, transferencia, investimento, rendimento_bruto, rendimento_liquido, P1_sac, P_sac, juros_tot_sac=0, P_total=0, entrada, saida;
	float ir, financiamento, juros = 0.00917, parcela_financiamento, amortizacao, emprestimo, parcela_emprestimo, saldo_final, val_financ;
	char nome[50], beneficiario[50];
	printf("SEJA BEM-VINDO AO BANCO ZUBANK!\n\n");
	printf("Qual o seu nome?\n");
	gets(nome);
	printf("Qual o seu saldo banc�rio?\n");
	scanf("%f", &saldo_inicial);
	printf("Qual o n�mero da sua conta banc�ria?\n");
	scanf("%d", &conta);
	printf("Qual o n�mero do servi�o que deseja utilizar?\n");
	do{
		printf("1 - Realizar transfer�ncia\n2 - Rendimento da conta\n3 - Realizar empr�stimo");
		printf("\n4 - Realizar financiamento\n5 - Extrato\n");
		scanf("%d", &servico);
		switch (servico){
			case 1:
				do{
				printf("Quanto deseja transferir?\nR$");
				scanf("%f", &transferencia);
				if (transferencia > saldo_inicial){
					printf("SALDO INSUFICIENTE!\n");
				}
				} while (transferencia > saldo_inicial);
				printf("Qual o nome do benefici�rio?\n");
				fflush(stdin);
				gets(beneficiario);
				printf("Qual o n�mero da conta para qual deseja transferir o valor?\n");
				scanf("%d", &conta_trans);
				file1 = fopen("RECIBO DE TRANSFERENCIA.txt", "w");
				if (file1 == NULL) {
       			printf("ERRO AO ABRIR O ARQUIVO DO RECIBO DE TRANSFER�NCIA!\n");
       			return 1;
				}
				fprintf(file1, "RECIBO DE TRANSFER�NCIA\n\n\n");
				fprintf(file1, "PAGADOR: %s\n", nome);
				fprintf(file1, "CONTA BANC�RIA: %d\n", conta);
				fprintf(file1, "BENEFICI�RIO: %s\n", beneficiario);
				fprintf(file1, "CONTA RECEPTORA: %d\n", conta_trans);
				fprintf(file1, "VALOR RECEBIDO: R$%.2f\n", transferencia);
				fclose(file1);
				printf("SALDO ATUAL: %.2f\n", saldo_inicial - transferencia);
				saldo_final = saldo_inicial - transferencia;
				printf("TRANSFER�NCIA REALIZADA COM SUCESSO, CONSULTE SEU RECIBO!\n");
				break;
			case 2: 
					//TAXA DO CDB DE REFER�NCIA � DE 11.45% a.a COM 102% DO CDI PELO BANCO INTER EM OUTUBRO/24
				do{
				printf("Quanto do saldo dispon�vel (R$%.2f) deseja investir?\n", saldo_final);
				scanf("%f", &investimento);
				} while (investimento > saldo_final);
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
				rendimento_bruto = investimento*(pow(1.009542, meses_investidos));
				rendimento_liquido = (rendimento_bruto - ((investimento*pow(1.009542, meses_investidos) - investimento)*ir));
				saldo_final += rendimento_liquido - investimento;
				file2 = fopen("RELATORIO DE RENDIMENTOS.txt", "w");
				if (file2 == NULL) {
        			printf("ERRO AO ABRIR O ARQUIVO DO RELAT�RIO DE RENDIMENTOS!\n");
       				return 1;
        			}
				fprintf(file2, "RELAT�RIO DE RENDIMENTOS\n\n\n");
				fprintf(file2, "VALOR INVESTIDO: R$%.2f\n", investimento);
				fprintf(file2, "MESES CORRIDOS: %d meses\n", meses_investidos);
				fprintf(file2, "AL�QUOTA DO IMPOSTO DE RENDA: %.2f%%\n", ir*100);
				fprintf(file2, "RENDIMENTO BRUTO: R$%.2f\n", rendimento_bruto - investimento);
				fprintf(file2, "RENDIMENTO L�QUIDO: R$%.2f\n", rendimento_liquido - investimento);
				fclose(file2);
				printf("CONFIRA O SEU RELAT�RIO DE RENDIMENTOS!");
				break;
		case 3: //JUROS MENSAL REFER�NCIA DE 1.46% a.m PELO EMPR�STIMO CONSIGNADO DO BANCO BANESTES S.A
				printf("Quanto deseja receber de empr�stimo?\nR$");
				scanf("%f", &emprestimo);
				printf("Em quantos meses deseja pagar o empr�stimo?\n");
				scanf("%d", &tempo_emprestimo);
				saldo_final += emprestimo;
				file3 = fopen("RELATORIO DE EMPRESTIMO.txt", "w");
				if (file3 == NULL) {
        			printf("ERRO AO ABRIR O ARQUIVO DO RELAT�RIO DE EMPR�STIMO!\n");
       				return 1;
        			}
				parcela_emprestimo = (emprestimo*0.0146)/(1 - pow(1.0146, tempo_emprestimo*(-1)));
				fprintf(file3, "VALOR DO EMPR�STIMO: R$%.2f\n", emprestimo);
				fprintf(file3, "PER�ODO DE PAGAMENTO: %d meses\n", tempo_emprestimo);
				fprintf(file3, "PARCELAS DO EMPR�STIMO: R$%.2f\n", parcela_emprestimo);
				fprintf(file3, "Juros totais do empr�stimo: R$%.2f\n", parcela_emprestimo*tempo_emprestimo - emprestimo);
				fclose(file3);
				printf("CONFIRA O SEU RELAT�RIO DE EMPR�STIMO!");
				break;
		case 4:	//JUROS MENSAL REFER�NCIA DE 0.917% a.m. DA MODALIDADE SBPE TAXA FIXA DA CAIXA ECON�MICA FEDERAL
				printf("Qual modelo de financiamento ser� utilizado?\n");
				do{
					printf("1 - PRICE: Parcelas fixas\n2 - SAC: Parcelas decrescentes\n");
					scanf("%d", &tipo_financiamento);
				} while (tipo_financiamento != 1 && tipo_financiamento != 2);
				printf("Qual o valor do financiamento que deseja realizar?\n");
				scanf("%f", &financiamento);
				printf("O pagamento ser� realizado em quantas parcelas?\n");
				scanf("%d", &parcelas);
				if (tipo_financiamento == 1){
					file4 = fopen("RELATORIO DE FINANCIAMENTO PRICE.txt", "w");
					if (file4 == NULL) {
        				printf("ERRO AO ABRIR O ARQUIVO DO RELAT�RIO DE FINANCIAMENTO!\n");
       				return 1;
        			}
					parcela_financiamento = financiamento*juros*(pow(1 + juros, parcelas))/((pow(1 + juros, parcelas)) - 1);
					fprintf(file4, "MODO DE FINANCIAMENTO: SISTEMA PRICE\n");
					fprintf(file4, "Valor das Parcelas: R$%.2f\n", parcela_financiamento);
					fprintf(file4, "JUROS TOTAIS: R$%.2f\n", (parcela_financiamento*parcelas) - financiamento);
					fprintf(file4, "VALOR TOTAL A SER PAGO: %.2f\n", parcela_financiamento*parcelas);
					fclose(file4);
				} else {
					file4 = fopen("RELATORIO DE FINANCIAMENTO SAC.txt", "w");
					amortizacao = financiamento/parcelas;
					P1_sac = amortizacao + (financiamento*juros);
				}
					for (i_sac=1; i_sac <= parcelas; i_sac++){
						if (i_sac == 1){
							fprintf(file4, "MODO DE FINANCIAMENTO: SISTEMA SAC\n\n");
							fprintf(file4, "Parcela %d: R$%.2f\n", i_sac, P1_sac);
							P_total += P1_sac;
						} else {
								P_sac = amortizacao + (financiamento - (i_sac - 1)*amortizacao)*juros;
								fprintf(file4, "Parcela %d: R$%.2f\n", i_sac, P_sac);
								P_total += P_sac;
						}
					}
						juros_tot_sac = P_total - financiamento;
						fprintf(file4, "\n\nJUROS TOTAIS: R$%.2f\n", juros_tot_sac);
						fprintf(file4, "VALOR TOTAL A SER PAGO: %.2f\n", juros_tot_sac + financiamento);
						fclose(file4);
				printf("CONFIRA SEU RELAT�RIO DE FINANCIAMENTO!");
				break;
		case 5: 	
					val_financ = (tipo_financiamento == 1)?parcela_financiamento:P1_sac;
					saida = transferencia + parcela_emprestimo + val_financ;
					file5 = fopen("EXTRATO BANC�RIO.txt", "w");
					if (file5 == NULL) {
        				printf("ERRO AO ABRIR O ARQUIVO DO EXTRATO BANC�RIO!\n");
       				return 1;
        			}
					fprintf(file5, "EXTRATO BANC�RIO\n\n\n");
					fprintf(file5, "RELAT�RIO DE ENTRADA\n\n");
					fprintf(file5, "SALDO INICIAL: R$%.2f\n", saldo_inicial);
					fprintf(file5, "TRANSFER�NCIAS RECEBIDAS: %.2f\n", conta_trans);
					fprintf(file5, "RENDIMENTO L�QUIDO DO CDB: %.2f\n", rendimento_liquido - investimento);
					fprintf(file5, "EMPR�STIMO RECEBIDO: %.2f\n\n\n", emprestimo);
					fprintf(file5, "RELAT�RIO DE SA�DA\n\n");
					fprintf(file5, "TRANSFER�NCIAS REALIZADAS: %.2f\n", transferencia);
					fprintf(file5, "PARCELA DO EMPR�STIMO: %.2f\n", parcela_emprestimo);
					fprintf(file5, "PARCELA DO FINANCIAMENTO: %.2f\n", (tipo_financiamento==1)?parcela_financiamento:P1_sac);
					fprintf(file5, "SALDO FINAL: %.2lf\n", saldo_final - saida);
					fclose(file5);
					printf("CONFIRA SEU EXTRATO BANC�RIO!");
			break;
		default: printf("OPERA��O INV�LIDA!");
	}
	do{
		printf("\nDeseja continuar? Digite 0 para encerrar e 1 para continuar!\n");
		scanf("%d", &continua);
		} while (continua != 0 && continua != 1);
	} while (continua == 1);
	return 0;
}
