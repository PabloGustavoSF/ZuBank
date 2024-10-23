#include <stdio.h>
#include <math.h>
#include <time.h>

#define Jm 0.00917
#define Ja 0.1898

struct Financiamento
{
    float juros;        // Taxa de Juros
    float valor;        // Valor financiado
    int parcelas;       // Número de parcelas
    float vP;           // Valor da parcela
    float amortizacao;  // Amortizaçao da divida
};

struct Relatorio
{



};

void Price(float valor, int parcelas)
{

    FILE *doc;
    float parcelaFinanciamento;

    doc = fopen("Relatorio de finciamento SAC.txt", "w");
    if (doc == NULL)
    {
        printf("Erro Ao abrir o arquivo do relatorio de financiamento");
    }
    else
    {
        parcelaFinanciamento = valor * Jm * pow(1 + Jm, parcelas) / (pow(1 + Jm, parcelas) - 1);

        fprintf(doc, "MODO DE FINANCIAMENTO: SISTEMA PRICE\n");
        fprintf(doc, "Valor das Parcelas: R$%.2f\n", parcelaFinanciamento);
        fprintf(doc, "JUROS TOTAIS: R$%.2f\n", (parcelaFinanciamento * parcelas) - valor);
        fprintf(doc, "VALOR TOTAL A SER PAGO: %.2f\n", parcelaFinanciamento * parcelas);
        fclose(doc);
    }
}

void Sac(float valor, int parcelas)
{

    FILE *doc;
    float amortizacao, p, pTotal = 0, jurosTotal;
    int i;

    time_t tempoAtual;

    struct tm *horaLocal;


    doc = fopen("Relatorio de financiamento Price.txt", "w");
    if (doc == NULL)
    {
        printf("Erro Ao abrir o arquivo do relatorio de financiamento");
    }

    amortizacao = valor / parcelas;


    fprintf(doc, "Modo de financiamento: SAC \n\n");

    for (i = 1; i <= parcelas; i++)
    {

        p = amortizacao + (valor - (i - 1) * amortizacao) * Jm;

        fprintf(doc, "Parcela %d: R$%.2f\n", i, p);

        pTotal += p;
    }

    jurosTotal = pTotal - valor;

    fprintf(doc, "\n\nJUROS TOTAIS: R$%.2f\n", jurosTotal);
    fprintf(doc, "VALOR TOTAL A SER PAGO: %.2f\n", jurosTotal + valor);

    time(&tempoAtual);
    horaLocal = localtime(&tempoAtual);

    fprintf(doc, "Hora local: %02d:%02d:%02d\n", 
            horaLocal->tm_hour, 
            horaLocal->tm_min, 
            horaLocal->tm_sec);

    fclose(doc);
    printf("CONFIRA SEU RELATÓRIO DE FINANCIAMENTO!");
}
