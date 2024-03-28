#include <stdio.h>
#include <stdlib.h>
#include "./hash/hash.c"

Contato contatos[TAM];

int main(void) {
    
    inicializaTabela(contatos);
    preencheContato(contatos);

    int i;
    for (i = 0; i < TAM; i++)
    {
        printf("NOME: %s\n", contatos[i].nome);
        printf("TEL: %s\n", contatos[i].telefone);
        printf("EMAIL: %s\n\n", contatos[i].email);
    }
    
    Contato *contato_encontrado = buscar_contatos(contatos, nome, telefone, email);

    if (contato_encontrado != NULL) {
        printf("Contato encontrado: %s\n", contato_encontrado->nome);
        printf("TEL: %s\n", contato_encontrado->telefone);
        printf("EMAIL: %s\n", contato_encontrado->email);
    } else {
        printf("Contato não encontrado.\n");
    }
    
    // Contato teste_1 = ;

    // printf("%d", contadorBit(4096));
    return 0;
}