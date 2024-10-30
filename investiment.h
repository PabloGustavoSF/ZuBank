// investiment.h
#ifndef INVESTIMENT_H
#define INVESTIMENT_H

//Estrutura que representa os dados do investimento
struct Investimento{
    float investimento;
    int meses_investidos;
    float rendimento_bruto;
    float rendimento_liquido;
    float ir;
    float saldo_final;
};

// Funcao que realiza o investimento no CDB
void investiment (struct Investimento *i){
//Do-While para evitar um investimento maior do que o saldo existente
	do{
		//Solicitacao do valor a ser investido
		printf("Quanto do saldo disponível (R$%.2f) deseja investir?\n", saldo_final);
		scanf("%f", &investimento);
	} while (investimento > saldo_final);
//Do-While para evitar um valor de meses negativo
	do{
		//Solicitacao do periodo de tempo em meses
	printf("Por quantos meses deseja deixar o valor investido?\n");
	scanf("%d", &meses_investidos);
	} while (meses_investidos < 0);
//if para selecionar a aliquota do imposto de renda baseado no periodo em que o valor ficara investido
	if (meses_investidos <= 6){
		ir = 0.225;
		} else if (meses_investidos <= 12){
			ir = 0.2;
			} else if (meses_investidos <= 24){
				ir = 0.175;
				} else {
					ir = 0.15;
				}
//Calculo do rendimento bruto, liquido e saldo apos as operacoes realizadas
	rendimento_bruto = investimento*(pow(1.009542, meses_investidos));
	rendimento_liquido = (rendimento_bruto - ((investimento*pow(1.009542, meses_investidos) - investimento)*ir));
	saldo_final += rendimento_liquido - investimento;
}
#endif // INVESTIMENT_H
