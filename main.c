#include <stdio.h>
#include <stdlib.h>

#define TAM 5000

typedef struct contato {
    char nome[35];
    char telefone[15];
    char email[50];
} Contato;


Contato* contatos[TAM];

int hash (Contato c) {
    int count = 0;
    int soma = 0;

    while (c.nome[count] != '\0') {
        soma += c.nome[count];
        count++;
    }

    return soma;
}



int main(void) {


    return 0;
}