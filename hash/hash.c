#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

/* Fator de Carga = 50%
   TAM <= 2*[número de elementos a serem inseridos]
   TAM <= 20000
   (Escolhe o valor primo mais próximo)
*/ 
#define TAM 19997

typedef struct contato {
    char nome[35];
    char telefone[15];
    char email[50];
} Contato;
Contato contatos[TAM];


int geraChave(Contato c)
{
    int count = 0, chave = 0;

    // gera uma chave, utilizando a soma dos caracteres do nome:
    while (c.nome[count] != '\0') {
        chave += c.nome[count];
        count++;
    }

    return chave;
}

int hash(int chave)
{
    long long quad_chave, bits_chave, bits_endereco;
    long long endereco;

    // MÉTODO DA MULTIPLICAÇÃO
    // 1. Elevar a chave ao quadrado:
    quad_chave = chave*chave;

    // 2. Tamanho em bits da chave e do endereço:
    bits_chave = contadorBit(quad_chave);
    bits_endereco = contadorBit(TAM);

    // 3. gerar o endereço, cortando os bits dos extremos,
    // até que fique do tamanho adequado ao endereço:
    endereco = quad_chave >> ((bits_chave/2) - (bits_endereco/2));  /* corta o excesso à direita */
    endereco = endereco % (1 >> bits_endereco);                     /* corta o excesso à direita */

    return endereco;
}


int contadorBit(int num)
{
    int num_bits = 0;

    while (num != 0) {
        num_bits++;
        num = num >> 1; // Desloca os bits para a direita (divide por 2)
    }
    if (num_bits%2 != 0) num_bits++;

    return num_bits;
}

// função para ler e retornar um contato:
Contato lerContato() {
    Contato c;
    printf("Digite a nome: ");
    fgets(c.nome, 35, stdin);
    // scanf(" %[^\n]", c.nome);
    // scanf("%*c"); // limpa o buffer do enter
    printf("\nDigite o telefone: ");
    fgets(c.telefone, 15, stdin);

    printf("\nDigite o email: ");
    fgets(c.email, 50, stdin);
}

void inserir()
{
    Contato c = lerContato();
    int chave = geraChave(c);
    int posicao = hash(chave);

    while (strcmp(contatos[posicao].nome, "") != 0)
        posicao = sondagemQuadratica(posicao);
}

int sondagemQuadrada(int indice)
{

}
