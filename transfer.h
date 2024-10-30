// transfer.h
#ifndef TRANSFER_H
#define TRANSFER_H

//Estrutura que representa os dados da transferencia
struct Transferencia{
    char beneficiario[50]; //Nome de quem recebe o valor
    char nome[50]; //Nome de quem envia o valor
    float transferencia; //Valor a ser transferido
    int conta; //Conta onde sai o valor
    float saldo_inicial; //Valor referente ao saldo antes de qualquer operacao
	float saldo_final; //Valor referente ao saldo apos as operacoes realizadas
};

//Funcao que realiza a transferencia entre as contas
void transfer (struct Transferencia *t){
	//Do-While para evitar transferencias de saldos negativos
	do{
		//Solicita a quantia a ser transferida
		printf("Quanto deseja transferir?\nR$");
		scanf("%f", &transferencia);
		if (transferencia > saldo_inicial){
			printf("SALDO INSUFICIENTE!\n");
		}
	} while (transferencia > saldo_inicial);
	//Solicita o nome do recebedor
	printf("Qual o nome do beneficiário?\n");
	fflush(stdin);
	gets(beneficiario);
	//Solicita o numero da conta do recebedor
	printf("Qual o número da conta para qual deseja transferir o valor?\n");
	scanf("%d", &conta_trans);
	saldo_final = saldo_inicial - transferencia;
	//Impressao do saldo apos a transferencia
	printf("SALDO ATUAL: %.2f\n", saldo_inicial - transferencia);
}
//Funcao para gerar o relatorio de transferencia em aquivo .txt
void gerar_relatorio_transferencia (struct Transferencia *t){
	FILE *file1;
	//Abertura do arquivo do relatorio de transferencia
	file1 = fopen("RECIBO DE TRANSFERENCIA.txt", "w");
	//Checagem de erro ao abrir o arquivo
	if (file1 == NULL) {
       	printf("ERRO AO ABRIR O ARQUIVO DO RECIBO DE TRANSFERÊNCIA!\n");
       	return 1;
	}
	//Impressao dos dados no relatorio
	fprintf(file1, "RECIBO DE TRANSFERÊNCIA\n\n\n");
	fprintf(file1, "PAGADOR: %s\n", nome);
	fprintf(file1, "CONTA BANCÁRIA: %d\n", conta);
	fprintf(file1, "BENEFICIÁRIO: %s\n", beneficiario);
	fprintf(file1, "CONTA RECEPTORA: %d\n", conta_trans);
	fprintf(file1, "VALOR RECEBIDO: R$%.2f\n", transferencia);
	fclose(file1);
	//Mensagem informando a conclusao com exito do relatorio
	printf("TRANSFERÊNCIA REALIZADA COM SUCESSO, CONSULTE SEU RECIBO!\n");
}
#endif // TRANSFER_H
