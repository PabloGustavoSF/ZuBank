#include <stdio.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include "cliente.h"

 
int main (){
	setlocale(LC_CTYPE, "Portuguese_Brazil");
	FILE *file1, *file2, *file3, *file4, *file5, *file6;
	Cliente cliente;
	int servico, continua, conta, conta_trans, meses_investidos, parcelas, tipo_financiamento, i_sac, tempo_emprestimo;
	float saldo_inicial, transferencia, investimento, rendimento_bruto, rendimento_liquido, P1_sac, P_sac, juros_tot_sac=0, P_total=0, entrada, saida;
	float ir, financiamento, juros = 0.00917, parcela_financiamento, amortizacao, emprestimo, parcela_emprestimo, saldo_final, val_financ;
	char nome[50], beneficiario[50];
	printf("SEJA BEM-VINDO AO BANCO ZUBANK!\n\n");
	printf("Qual o seu nome?\n");
	gets(nome);
	printf("Qual o seu saldo bancário?\n");
	scanf("%f", &saldo_inicial);
	printf("Qual o número da sua conta bancária?\n");
	scanf("%d", &conta);
	printf("Qual o número do serviço que deseja utilizar?\n");
	do{
		printf("1 - Realizar transferência\n2 - Rendimento da conta\n3 - Realizar empréstimo");
		printf("\n4 - Realizar financiamento\n5 - Extrato\n6 - Fechar conta\n");
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
				break;
			case 2: 
					//TAXA DO CDB DE REFERÊNCIA É DE 11.45% a.a COM 102% DO CDI PELO BANCO INTER EM OUTUBRO/24
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
				break;
		case 3: //JUROS MENSAL REFERÊNCIA DE 1.46% a.m PELO EMPRÉSTIMO CONSIGNADO DO BANCO BANESTES S.A
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
				break;
		case 4:	//JUROS MENSAL REFERÊNCIA DE 0.917% a.m. DA MODALIDADE SBPE TAXA FIXA DA CAIXA ECONÔMICA FEDERAL
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
				break;
		case 5: 	
					 {
        // Calcula a saída total (transferência, parcelas de empréstimo e financiamento)
        val_financ = (tipo_financiamento == 1) ? parcela_financiamento : P1_sac;
        saida = transferencia + (parcela_emprestimo * tempo_emprestimo) + (val_financ * parcelas);

        // Cria o arquivo de extrato bancário
        file5 = fopen("EXTRATO BANCÁRIO.txt", "w");
        if (file5 == NULL) {
            printf("ERRO AO ABRIR O ARQUIVO DO EXTRATO BANCÁRIO!\n");
            return 1;
        }

        // Cabeçalho do extrato
        fprintf(file5, "EXTRATO BANCÁRIO - BANCO ZUBANK\n\n");
        fprintf(file5, "Nome do Cliente: %s\n", nome);
        fprintf(file5, "Número da Conta: %d\n\n", conta);

        // Relatório de Entrada
        fprintf(file5, "===== RELATÓRIO DE ENTRADA =====\n");
        fprintf(file5, "Saldo Inicial: R$%.2f\n", saldo_inicial);
        fprintf(file5, "Transferências Recebidas: R$%.2f\n", 0.0); // Placeholder para futuras funcionalidades
        fprintf(file5, "Rendimento Líquido do CDB: R$%.2f\n", rendimento_liquido - investimento);
        fprintf(file5, "Empréstimo Recebido: R$%.2f\n\n", emprestimo);

        // Relatório de Saída
        fprintf(file5, "===== RELATÓRIO DE SAÍDA =====\n");
        fprintf(file5, "Transferências Realizadas: R$%.2f\n", transferencia);
        fprintf(file5, "Parcelas do Empréstimo (Total): R$%.2f\n", parcela_emprestimo * tempo_emprestimo);
        fprintf(file5, "Parcelas do Financiamento (Total): R$%.2f\n", val_financ * parcelas);

        // Cálculo e exibição do saldo final após todas as movimentações
        float saldo_atualizado = saldo_inicial + rendimento_liquido + emprestimo - saida;
        fprintf(file5, "\nSaldo Final: R$%.2f\n", saldo_atualizado);

        fclose(file5);

        printf("CONFIRA SEU EXTRATO BANCÁRIO!\n");
    }
			break;
			 case 6:
        // Relatório de Fechamento de Conta usando a struct Cliente
        file6 = fopen("RELATORIO DE FECHAMENTO.txt", "w");
        if (file6 == NULL) {
            printf("ERRO AO ABRIR O ARQUIVO DO RELATÓRIO DE FECHAMENTO!\n");
            return 1;
        }
        
        // Escrevendo dados de fechamento de conta
        fprintf(file6, "RELATÓRIO DE FECHAMENTO DE CONTA\n\n");
        fprintf(file6, "Nome do Cliente: %s\n", cliente.nome);
        fprintf(file6, "Número da Conta: %d\n", cliente.conta);
        fprintf(file6, "Saldo Inicial: R$%.2f\n", cliente.saldo_inicial);
        fprintf(file6, "Saldo Final: R$%.2f\n", cliente.saldo_final);

        // Resumo das transações
        fprintf(file6, "\n===== RESUMO DAS TRANSAÇÕES =====\n");
        fprintf(file6, "Transferências Realizadas: R$%.2f\n", transferencia);
        fprintf(file6, "Rendimento Líquido de Investimento: R$%.2f\n", rendimento_liquido - investimento);
        fprintf(file6, "Empréstimo Recebido: R$%.2f\n", emprestimo);
        fprintf(file6, "Parcelas de Empréstimo (Total): R$%.2f\n", parcela_emprestimo * tempo_emprestimo);
        fprintf(file6, "Parcelas de Financiamento (Total): R$%.2f\n", (tipo_financiamento == 1 ? parcela_financiamento : P1_sac) * parcelas);

        // Exibição do saldo final após as movimentações
        fprintf(file6, "\nSaldo Final após todas as movimentações: R$%.2f\n", cliente.saldo_final);

        fclose(file6);
        printf("RELATÓRIO DE FECHAMENTO DE CONTA GERADO COM SUCESSO!\n");
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