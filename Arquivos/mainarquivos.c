// mainarquivos.c

#include "arquivos.h"

int main() {
    const char* nomes[] = {
        "RECIBO DE TRANSFERÊNCIA.txt",
        "RELATORIO DE RENDIMENTOS.txt",
        "RELATORIO DE EMPRESTIMO.txt",
        "RELATORIO DE FINANCIAMENTO.txt",
        "EXTRATO BANCARIO.txt"
    };
    int qtdArquivos = 5;
    int i;  // Declaração do i fora do for no main também
    FILE** arquivos = abrirArquivos(nomes, qtdArquivos);

    if (arquivos == NULL) {
        printf("Falha ao abrir os arquivos.\n");
        return 1;
    }

    printf("Todos os arquivos foram abertos com sucesso para escrita.\n");

    // Fecha os arquivos abertos
    for (i = 0; i < qtdArquivos; i++) {
        fclose(arquivos[i]);
    }

    // Libera a memória alocada para os ponteiros de arquivos
    free(arquivos);

    return 0;
}
