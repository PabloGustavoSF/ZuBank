//maintransfer.c
#include <stdio.h>
#include "transfer.h"

int main() {
    // Inicializa os dados do usu�rio
    Usuario usuario = {"Jo�o da Silva", 123456, 5000.0, 30.0};
    Transferencia transf;

    // Chama a fun��o de transfer�ncia
    transfer(&usuario, &transf);

    return 0;
}

