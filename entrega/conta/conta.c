#include "conta.h"

void criarConta(Conta *conta){

    printf("Qual o seu nome?\n");
	fgets(conta->nome, 49, stdin);
	printf("Qual o seu saldo bancário?\n");
	scanf("%f", &conta->saldo_Inicial);
	printf("Qual o número da sua conta bancária?\n");
	scanf("%d", &conta->conta_id);
}