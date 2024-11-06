// investiment.h
#ifndef INVESTIMENT_H
#define INVESTIMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Estrutura que representa os dados do investimento
struct Investimento {
    float investimento;
    int meses_investidos;
    float rendimento_bruto;
    float rendimento_liquido;
    float ir;
    float saldo_final;
};

// Função para criar um novo investimento e salvar no arquivo
void criar_investimento(struct Investimento *i, float saldo_atual) {
    FILE *file = fopen("investimentos.txt", "a");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Solicitação do valor a ser investido
    do {
        printf("Quanto do saldo disponível (R$%.2f) deseja investir?\n", saldo_atual);
        scanf("%f", &i->investimento);
    } while (i->investimento > saldo_atual);

    // Solicitação do período em meses
    do {
        printf("Por quantos meses deseja deixar o valor investido?\n");
        scanf("%d", &i->meses_investidos);
    } while (i->meses_investidos < 0);

    // Determinação da alíquota do IR
    if (i->meses_investidos <= 6) {
        i->ir = 0.225;
    } else if (i->meses_investidos <= 12) {
        i->ir = 0.2;
    } else if (i->meses_investidos <= 24) {
        i->ir = 0.175;
    } else {
        i->ir = 0.15;
    }

    // Cálculo do rendimento
    i->rendimento_bruto = i->investimento * pow(1.009542, i->meses_investidos);
    i->rendimento_liquido = i->rendimento_bruto - ((i->rendimento_bruto - i->investimento) * i->ir);
    i->saldo_final = saldo_atual + i->rendimento_liquido - i->investimento;

    fwrite(i, sizeof(struct Investimento), 1, file);
    fclose(file);

    printf("Investimento registrado com sucesso!\n");
}

// Função para ler todos os investimentos do arquivo
void ler_investimentos() {
    FILE *file = fopen("investimentos.txt", "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    struct Investimento i;
    printf("Investimentos Registrados:\n");

    while (fread(&i, sizeof(struct Investimento), 1, file)) {
        printf("Investimento: %.2f, Meses: %d, Rendimento Bruto: %.2f, Rendimento Líquido: %.2f, IR: %.2f, Saldo Final: %.2f\n",
               i.investimento, i.meses_investidos, i.rendimento_bruto, i.rendimento_liquido, i.ir, i.saldo_final);
    }

    fclose(file);
}

// Função para atualizar um investimento específico
void atualizar_investimento(float valor_investido) {
    FILE *file = fopen("investimentos.txt", "r+");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    struct Investimento i;
    int found = 0;

    while (fread(&i, sizeof(struct Investimento), 1, file)) {
        if (i.investimento == valor_investido) {
            printf("Digite o novo valor a ser investido: ");
            scanf("%f", &i.investimento);
            printf("Digite o novo período em meses: ");
            scanf("%d", &i.meses_investidos);

            if (i.meses_investidos <= 6) {
                i.ir = 0.225;
            } else if (i.meses_investidos <= 12) {
                i.ir = 0.2;
            } else if (i.meses_investidos <= 24) {
                i.ir = 0.175;
            } else {
                i.ir = 0.15;
            }

            i.rendimento_bruto = i.investimento * pow(1.009542, i.meses_investidos);
            i.rendimento_liquido = i.rendimento_bruto - ((i.rendimento_bruto - i.investimento) * i.ir);
            i.saldo_final += i.rendimento_liquido - i.investimento;

            fseek(file, -sizeof(struct Investimento), SEEK_CUR);
            fwrite(&i, sizeof(struct Investimento), 1, file);

            printf("Investimento atualizado com sucesso!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Investimento não encontrado.\n");
    }

    fclose(file);
}

// Função para deletar um investimento específico
void deletar_investimento(float valor_investido) {
    FILE *file = fopen("investimentos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    struct Investimento i;
    int found = 0;

    while (fread(&i, sizeof(struct Investimento), 1, file)) {
        if (i.investimento == valor_investido) {
            found = 1;
        } else {
            fwrite(&i, sizeof(struct Investimento), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove("investimentos.txt");
    rename("temp.txt", "investimentos.txt");

    if (found) {
        printf("Investimento deletado com sucesso!\n");
    } else {
        printf("Investimento não encontrado.\n");
    }
}

#endif // INVESTIMENT_H

