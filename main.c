#include <stdio.h>
#include <stdlib.h>
#include "./geral/geral.c"

Contato contatos[TAM];

int main(void) {
    inicializaTabela(contatos);
    recuperaTabela(contatos);
    
    int var;
    do {
        var = menu_principal(contatos);
    } while (var != '6');

    return 0;
}