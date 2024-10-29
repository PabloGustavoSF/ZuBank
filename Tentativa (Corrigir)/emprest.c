// emprest.c
#include "emprest.h"

// Implementacao da funcao que calcula emprestimo e gela relatorio.
void emprest(float emprestimo, int tempo_emprestimo, float parcela_emprestimo, float saldo_final) {
    printf("Quanto deseja receber de empréstimo?\nR$");
	scanf("%f", &emprestimo);
	printf("Em quantos meses deseja pagar o empréstimo?\n");
	scanf("%d", &tempo_emprestimo);
	saldo_final += emprestimo;
	file3 = fopen("RELATORIO DE EMPRESTIMO.txt", "w");
	if (file3 == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DO RELATÓRIO DE EMPRÉSTIMO!\n");
       	return 1;
        }
	parcela_emprestimo = (emprestimo*0.0146)/(1 - pow(1.0146, tempo_emprestimo*(-1)));
	fprintf(file3, "VALOR DO EMPRÉSTIMO: R$%.2f\n", emprestimo);
	fprintf(file3, "PERÍODO DE PAGAMENTO: %d meses\n", tempo_emprestimo);
	fprintf(file3, "PARCELAS DO EMPRÉSTIMO: R$%.2f\n", parcela_emprestimo);
	fprintf(file3, "Juros totais do empréstimo: R$%.2f\n", parcela_emprestimo*tempo_emprestimo - emprestimo);
	fclose(file3);
	printf("CONFIRA O SEU RELATÓRIO DE EMPRÉSTIMO!");
}
