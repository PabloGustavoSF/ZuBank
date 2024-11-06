//maintransfer.c
#include <stdio.h>
#include "transfer.h"

int main() {
    // Inicializa os dados do usuário
    Usuario usuario = {"João da Silva", 123456, 5000.0, 30.0};
    Transferencia transf;

    // Chama a função de transferência
    transfer(&usuario, &transf);

    return 0;
}

