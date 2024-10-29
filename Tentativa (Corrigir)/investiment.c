// investimento.c
#include "investimento.h"

// Implementacao da funcao que realiza o investimento no CDB e gera o relatorio
void investiment(float saldo_final, float investimento, int meses_investidos, float ir, float rendimendo_bruto, float rendimento_liquido) {
	do{
		printf("Quanto do saldo disponível (R$%.2f) deseja investir?\n", saldo_final);
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
    	printf("ERRO AO ABRIR O ARQUIVO DO RELATÓRIO DE RENDIMENTOS!\n");
   			return 1;
      		}
	fprintf(file2, "RELATÓRIO DE RENDIMENTOS\n\n\n");
	fprintf(file2, "VALOR INVESTIDO: R$%.2f\n", investimento);
	fprintf(file2, "MESES CORRIDOS: %d meses\n", meses_investidos);
	fprintf(file2, "ALÍQUOTA DO IMPOSTO DE RENDA: %.2f%%\n", ir*100);
	fprintf(file2, "RENDIMENTO BRUTO: R$%.2f\n", rendimento_bruto - investimento);
	fprintf(file2, "RENDIMENTO LÍQUIDO: R$%.2f\n", rendimento_liquido - investimento);
	fclose(file2);
	printf("CONFIRA O SEU RELATÓRIO DE RENDIMENTOS!");
}
