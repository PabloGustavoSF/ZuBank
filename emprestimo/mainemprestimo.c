#include <stdio.h>
#include "emprestimo.h"

int main() {
    int opcao, id;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Criar Emprestimo\n");
        printf("2. Listar Emprestimos\n");
        printf("3. Atualizar Emprestimo\n");
        printf("4. Excluir Emprestimo\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criar_emprestimo();
                break;
            case 2:
                ler_emprestimos();
                break;
            case 3:
                printf("Digite o ID do emprestimo a ser atualizado: ");
                scanf("%d", &id);
                atualizar_emprestimo(id);
                break;
            case 4:
                printf("Digite o ID do emprestimo a ser excluido: ");
                scanf("%d", &id);
                excluir_emprestimo(id);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
