// extrato.c
#include "extrato.h"

// Implementacao da funcao que gera o extrato bancario resultante de todas as operacoes realizadas.
void extrato (float val_financ, int tipo_financiamento, float parcela_financiamento, float P1_sac, float saida, float transferencia, float parcela_emprestimo, float saldo_incial, float conta_trans, float rendimento_liquido, float investimento,float emprestimo, float saldo_final) {
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
}
