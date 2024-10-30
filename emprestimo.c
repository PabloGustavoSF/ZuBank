#include <stdio.h>
#include "emprestimo.h"

int main() {
    int opcao;
    float valor_procurado;

    do {
        printf("\n---- MENU DE OPERAÇÕES ----\n");
        printf("1. Criar Emprestimo\n");
        printf("2. Ler Emprestimos\n");
        printf("3. Atualizar Emprestimo\n");
        printf("4. Excluir Emprestimo\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criar_emprestimo();
                break;

            case 2:
                ler_emprestimos();
                break;

            case 3:
                printf("Informe o valor do emprestimo a ser atualizado: R$");
                scanf("%f", &valor_procurado);
                atualizar_emprestimo(valor_procurado);
                break;

            case 4:
                printf("Informe o valor do emprestimo a ser excluido: R$");
                scanf("%f", &valor_procurado);
                excluir_emprestimo(valor_procurado);
                break;

            case 5:
                printf("Saindo...\n");
                break;

            default:
                printf("Opçao invalida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
