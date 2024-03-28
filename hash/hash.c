#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

/* Fator de Carga = 50%
   TAM = 2^n < 5000
   TAM = 4096
*/ 
#define TAM 4096

typedef struct contato {
    int tag;
    char nome[35];
    char telefone[15];
    char email[50];
} Contato;
// Contato contatos[TAM];

void inicializaTabela(Contato* c)
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        c[i].tag = 0;
    }
}

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
    // printf("%lld\n", bits_chave);

    bits_endereco = contadorBit(TAM);
    // printf("%lld\n", bits_endereco);

    // 3. gerar o endereço, cortando os bits dos extremos,
    // para que fique do tamanho adequado ao endereço:
    endereco = quad_chave >> ((bits_chave - bits_endereco)/2);  /* corta o excesso à direita */
    endereco = endereco % (1 << (bits_endereco-1));                 /* corta o excesso à esquerda */

    return endereco;
}

int contadorBit(int num)
{
    int num_bits = 0;

    while (num != 0) {
        num_bits++;
        num = num >> 1; // Desloca os bits para a direita (divide por 2)
    }

    return num_bits;
}

void inserir(Contato *arr_contatos, Contato contato, FILE *fl)
{
    int limite = 30000;
    int chave = geraChave(contato);
    // printf("%d\n", chave);
    
    int posicao = hash(chave);
    // printf("%d\n", posicao);

    int count = 0;
    
    static int count2, i = 1;

    while (arr_contatos[posicao].tag == 1 && count < limite) 
    {   
        posicao = sondagemQuadratica(posicao, count);
        count++;
        count2++;
    }
    // if (count == limite) {
    fprintf(fl, "%d -  %s\n", i++, contato.nome);
    fprintf(fl, "%d - Tentativas: ", i++);

    fprintf(fl, "%d\n", count);
    fprintf(fl, "%d\n", count2);
    // fprintf(fl, "%d\n\n", i);
    // }

    arr_contatos[posicao] = contato;
    arr_contatos[posicao].tag = 1;

}

int sondagemQuadratica(int posicao, int tentativas)
{
    int c1 = 1, c2 = 3; // a definir

    // px  <-    px   +     c1(i)       +          c2*i²
    posicao = posicao + c1*(tentativas) + c2*(tentativas*tentativas);

    return posicao % TAM; /* caso nova posição exceda o tamanho, o modulo é usado */
}

int totalContatos(Contato *contatos)
{
    int i, count = 0;
    for (i = 0; i < TAM; i++)
    {
        if (contatos[i].tag == 1)
            count++;
    }
    
    return count;
}

void preencheContato(Contato *contatos)
{
    Contato c;


    FILE *teste = fopen("teste.txt", "wt");
    FILE *fl = fopen("todosOsContatos.txt", "rt");
    if (fl == NULL) exit(1);

    char *nome;
    char *tel;
    char *email;

    nome  = (char *)malloc(35 * sizeof(char));
    tel   = (char *)malloc(20 * sizeof(char));
    email = (char *)malloc(50 * sizeof(char));

    int i, total=0;
    for (i = 0; i < 10000; i++) {

        total = totalContatos(contatos);
        if (total == 4096) return;
        printf("%d\n", total);
        fscanf(fl, "Nome: %[A-Z. a-z]\n", nome);
        fscanf(fl, "Telefone: %[(0-9) -0-9]\n", tel);
        fscanf(fl, "Email: %s\n", email);
        fscanf(fl, "\n");

        // printf("%d\n", i);
        // printf("%s\n", nome);
        // printf("%s\n", tel);
        // printf("%s\n", email);

        strcpy(c.nome, nome);
        strcpy(c.telefone, tel);
        strcpy(c.email, email);

        // contatos[i] = c;

        inserir(contatos, c, teste);


    }
    fclose(teste);
    fclose(fl);

    
}

Contato *buscar_contatos(Contato *contatos, char *nome, char *telefone, char *email)
{
   while (contatos != NULL)
   {
      if (strcmp(contatos->nome, nome) == 0 && strcmp(contatos->telefone, telefone) == 0 && strcmp(contatos->email, email) == 0)
      {
         return contatos;
      }
      contatos = contatos->prox;
   }
   return NULL;
}