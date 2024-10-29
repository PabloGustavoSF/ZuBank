// financiament.c
#include "financiament.h"

// Implementacao da funcao que escolhe o financiamento e gera o relatorio.
void financiament(int tipo_financiamento, float financiamento, int parcelas, float juros, float parcela_financiamento, float amortizacao, float P1_sac, float P_sac, int i_sac) {
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
		file4 = fopen("RELATORIO DE FINANCIAMENTO PRICE.txt", "w");
		if (file4 == NULL) {
        	printf("ERRO AO ABRIR O ARQUIVO DO RELATÓRIO DE FINANCIAMENTO!\n");
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
	printf("CONFIRA SEU RELATÓRIO DE FINANCIAMENTO!");
}
