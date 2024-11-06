// arquivos.c

#include "arquivos.h"

FILE** abrirArquivos(const char* nomes[], int qtdArquivos) {
    FILE** arquivos = (FILE**)malloc(qtdArquivos * sizeof(FILE*));
    int i, j;  // Declare i e j fora dos loops for

    if (arquivos == NULL) {
        printf("Erro ao alocar memória para os arquivos.\n");
        return NULL;
    }

    // Tenta abrir cada arquivo em modo de escrita
    for (i = 0; i < qtdArquivos; i++) {
        arquivos[i] = fopen(nomes[i], "w"); // Modo de escrita

        // Se algum arquivo não for aberto, fecha os arquivos já abertos e retorna NULL
        if (arquivos[i] == NULL) {
            printf("Erro ao abrir o arquivo %s.\n", nomes[i]);
            for (j = 0; j < i; j++) {  // Usa j aqui
                fclose(arquivos[j]);
            }
            free(arquivos);
            return NULL;
        }
    }

    return arquivos;
}
