// transfer.h
#ifndef TRANSFER_H
#define TRANSFER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa os dados da transferência
struct Transferencia {
    char beneficiario[50];  // Nome de quem recebe o valor
    char nome[50];          // Nome de quem envia o valor
    float transferencia;     // Valor a ser transferido
    int conta;               // Conta onde sai o valor
    float saldo_inicial;     // Saldo antes de qualquer operação
    float saldo_final;       // Saldo após as operações realizadas
};

// Função para criar um novo registro de transferência e salvar em um arquivo
void criar_transferencia(struct Transferencia *t) {
    FILE *file = fopen("transferencias.txt", "a");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Digite o nome do beneficiário: ");
    scanf("%s", t->beneficiario);
    printf("Digite o seu nome: ");
    scanf("%s", t->nome);
    printf("Digite o valor a ser transferido: ");
    scanf("%f", &t->transferencia);
    printf("Digite o número da conta: ");
    scanf("%d", &t->conta);
    printf("Digite o saldo inicial: ");
    scanf("%f", &t->saldo_inicial);

    t->saldo_final = t->saldo_inicial - t->transferencia;

    fwrite(t, sizeof(struct Transferencia), 1, file);
    fclose(file);

    printf("Transferência registrada com sucesso!\n");
}

// Função para listar todas as transferências
void ler_transferencias() {
    FILE *file = fopen("transferencias.txt", "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    struct Transferencia t;
    printf("Transferências Registradas:\n");

    while (fread(&t, sizeof(struct Transferencia), 1, file)) {
        printf("Beneficiário: %s, Nome: %s, Valor: %.2f, Conta: %d, Saldo Inicial: %.2f, Saldo Final: %.2f\n",
               t.beneficiario, t.nome, t.transferencia, t.conta, t.saldo_inicial, t.saldo_final);
    }

    fclose(file);
}

// Função para atualizar uma transferência existente, identificada pelo nome do beneficiário
void atualizar_transferencia(const char *nome_beneficiario) {
    FILE *file = fopen("transferencias.txt", "r+");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    struct Transferencia t;
    int found = 0;

    while (fread(&t, sizeof(struct Transferencia), 1, file)) {
        if (strcmp(t.beneficiario, nome_beneficiario) == 0) {
            printf("Digite o novo valor de transferência: ");
            scanf("%f", &t.transferencia);
            printf("Digite o novo saldo inicial: ");
            scanf("%f", &t.saldo_inicial);

            t.saldo_final = t.saldo_inicial - t.transferencia;

            fseek(file, -sizeof(struct Transferencia), SEEK_CUR);
            fwrite(&t, sizeof(struct Transferencia), 1, file);
            printf("Transferência atualizada com sucesso!\n");

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Transferência não encontrada.\n");
    }

    fclose(file);
}

// Função para deletar uma transferência pelo nome do beneficiário
void deletar_transferencia(const char *nome_beneficiario) {
    FILE *file = fopen("transferencias.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    struct Transferencia t;
    int found = 0;

    while (fread(&t, sizeof(struct Transferencia), 1, file)) {
        if (strcmp(t.beneficiario, nome_beneficiario) == 0) {
            found = 1;
        } else {
            fwrite(&t, sizeof(struct Transferencia), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove("transferencias.txt");
    rename("temp.txt", "transferencias.txt");

    if (found) {
        printf("Transferência deletada com sucesso!\n");
    } else {
        printf("Transferência não encontrada.\n");
    }
}

#endif // TRANSFER_H

