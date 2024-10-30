// financiamento.c

#include "financiamento.h"

// Função para criar um financiamento com valores iniciais
void createFinanciamento(struct Financiamento *f, float valor, int parcelas, float juros)
{
    f->valor = valor;
    f->parcelas = parcelas;
    f->juros = juros;
    f->amortizacao = valor / parcelas;
    f->vP = valor * juros * pow(1 + juros, parcelas) / (pow(1 + juros, parcelas) - 1);
}

// Função para exibir os dados de um financiamento
void readFinanciamento(struct Financiamento *f)
{
    if (f->valor == 0 && f->parcelas == 0)
    {
        printf("Nenhum dado de financiamento disponível.\n");
        return;
    }

    printf("Detalhes do Financiamento:\n");
    printf("Valor: R$%.2f\n", f->valor);
    printf("Parcelas: %d\n", f->parcelas);
    printf("Taxa de Juros: %.4f\n", f->juros);
    printf("Valor da Parcela: R$%.2f\n", f->vP);
    printf("Amortizacao: R$%.2f\n\n", f->amortizacao);
}

// Função para atualizar os dados de um financiamento
void updateFinanciamento(struct Financiamento *f, float valor, int parcelas, float juros)
{
    f->valor = valor;
    f->parcelas = parcelas;
    f->juros = juros;
    f->amortizacao = valor / parcelas;
    f->vP = valor * juros * pow(1 + juros, parcelas) / (pow(1 + juros, parcelas) - 1);
}

// Função para deletar um financiamento, redefinindo seus valores
void deleteFinanciamento(struct Financiamento *f)
{
    f->valor = 0;
    f->parcelas = 0;
    f->juros = 0;
    f->vP = 0;
    f->amortizacao = 0;
}

// Função para calcular e gravar um relatório usando o sistema Price
void Price(struct Financiamento *f)
{
    FILE *doc;
    float parcelaFinanciamento;

    // Abrir arquivo para salvar o relatório do financiamento Price
    doc = fopen("Relatorio_de_financiamento_Price.txt", "w");
    if (doc == NULL)
    {
        printf("Erro ao abrir o arquivo do relatório de financiamento\n");
        return;
    }

    // Cálculo da parcela usando sistema Price
    parcelaFinanciamento = f->valor * f->juros * pow(1 + f->juros, f->parcelas) / 
                           (pow(1 + f->juros, f->parcelas) - 1);

    // Gravar informações no arquivo
    fprintf(doc, "MODO DE FINANCIAMENTO: SISTEMA PRICE\n");
    fprintf(doc, "Valor das Parcelas: R$%.2f\n", parcelaFinanciamento);
    fprintf(doc, "JUROS TOTAIS: R$%.2f\n", (parcelaFinanciamento * f->parcelas) - f->valor);
    fprintf(doc, "VALOR TOTAL A SER PAGO: %.2f\n", parcelaFinanciamento * f->parcelas);
    fclose(doc);
}

// Função para calcular e gravar um relatório usando o sistema SAC
void Sac(struct Financiamento *f)
{
    FILE *doc;
    float p, pTotal = 0, jurosTotal;
    int i;

    time_t tempoAtual;
    struct tm *horaLocal;

    // Abrir arquivo para salvar o relatório do financiamento SAC
    doc = fopen("Relatorio_de_financiamento_SAC.txt", "w");
    if (doc == NULL)
    {
        printf("Erro ao abrir o arquivo do relatório de financiamento\n");
        return;
    }

    // Amortização fixa para cada parcela no sistema SAC
    f->amortizacao = f->valor / f->parcelas;

    fprintf(doc, "Modo de financiamento: SAC \n\n");

    // Cálculo e gravação das parcelas
    for (i = 1; i <= f->parcelas; i++)
    {
        p = f->amortizacao + (f->valor - (i - 1) * f->amortizacao) * f->juros;
        fprintf(doc, "Parcela %d: R$%.2f\n", i, p);
        pTotal += p;
    }

    // Cálculo do juros total e valor final a ser pago
    jurosTotal = pTotal - f->valor;

    fprintf(doc, "\n\nJUROS TOTAIS: R$%.2f\n", jurosTotal);
    fprintf(doc, "VALOR TOTAL A SER PAGO: %.2f\n", jurosTotal + f->valor);

    // Gravar a hora atual no relatório
    time(&tempoAtual);
    horaLocal = localtime(&tempoAtual);
    fprintf(doc, "Hora local: %02d:%02d:%02d\n", 
            horaLocal->tm_hour, 
            horaLocal->tm_min, 
            horaLocal->tm_sec);

    fclose(doc);
    printf("CONFIRA SEU RELATÓRIO DE FINANCIAMENTO!\n");
}
