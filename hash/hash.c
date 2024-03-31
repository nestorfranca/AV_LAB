#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "../geral/geral.h"

/* Fator de Carga = 50%
   TAM = 2^n < 5000
   TAM = 4096
*/ 
#define TAM 4096
#define LIMITE_TESTE 1000

typedef struct contato {
    int tag;
    char nome[35];
    char telefone[25];
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

int geraChave(char* nome)
{
    int count = 0, chave = 0;

    // gera uma chave, utilizando a soma dos caracteres do nome:
    while (nome[count] != '\0') {
        chave += nome[count];
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
    // para que fique do tamanho adequado ao endereço:
    endereco = quad_chave >> ((bits_chave - bits_endereco)/2);  /* corta o excesso à direita */
    endereco = endereco % (1 << (bits_endereco-1));             /* corta o excesso à esquerda */

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
    int chave = geraChave(contato.nome);
    unsigned long long posicao = hash(chave);
    
    static int count2 = 0, i = 1;

    int count = 0;
    while (arr_contatos[posicao].tag != 0 && count < LIMITE_TESTE) {   
        if (strcmp(arr_contatos[posicao].nome, contato.nome) == 0)
            break;
        posicao = sondagemQuadratica(posicao, count);
        count++;
        if (count == LIMITE_TESTE)
            count2++;
    }
    // if (count == limite) {
    fprintf(fl, "%s\n", contato.nome);
    fprintf(fl, "Tentativas: %d\n\n", count);
    // fprintf(fl, "%d -  %s\n", i++, contato.nome);
    // fprintf(fl, "%d - Tentativas: ", i++);

    // fprintf(fl, "%d\n", count2);
    // fprintf(fl, "%d\n\n", i);
    // }
    // printf("%d - %u\n",count, posicao);
    // printf("%d\n",count2);

    arr_contatos[posicao] = contato;
    arr_contatos[posicao].tag = 1;

}

unsigned long long sondagemQuadratica(unsigned long long posicao, int tentativas)
{
    int c1 = 29, c2 = 8;
    
    // px  <-    px   +     c1(i)       +          c2*i²
    posicao = (posicao + c1*(tentativas) + c2*(tentativas*tentativas));
    return posicao % TAM;   /* caso nova posição exceda o tamanho, o modulo é usado */
}

int totalContatos(Contato *contatos)
{
    int i, count = 0;
    for (i = 0; i < TAM; i++) {
        if (contatos[i].tag == 1)
            count++;
    }
    
    return count;
}

void preencheContato(Contato *contatos)
{
    Contato c;
    FILE* teste;
    teste = fopen("teste.txt", "rt+");
    cabecalho("\t\t", "CADASTRO\t", "");
    
    char *nome, *tel, *email;
    nome  = (char *)malloc(35 * sizeof(char));
    tel   = (char *)malloc(25 * sizeof(char));
    email = (char *)malloc(50 * sizeof(char));

    printf("Digite o nome: ");
    scanf(" %34[A-Z. a-z]", nome);
    printf("Digite o telefone (sem \"()\"): ");
    scanf(" %19[(0-9) -0-9]", tel);
    printf("Digite o email: ");
    scanf(" %49[^\n]", email);

    strcpy(c.nome, nome);
    strcpy(c.telefone, tel);
    strcpy(c.email, email);

    inserir(contatos, c, teste);

    // cabecalho("\t\t", "CADASTRO\t");
    alert(9);
    alert_msg();
    delay(1000);
}

void importaContato(Contato *contatos)
{
    Contato c;

    FILE *teste = fopen("teste.txt", "wt");
    FILE *fl = fopen("todosOsContatos.txt", "rt");
    if (fl == NULL) {
        printf("Erro ao abrir o arquivo. \n");
        exit(1);
    }

    char *nome, *tel, *email;
    nome  = (char *)malloc(35 * sizeof(char));
    tel   = (char *)malloc(25 * sizeof(char));
    email = (char *)malloc(50 * sizeof(char));

    int i;
    for (i = 0; i < 10000; i++) {
        if (totalContatos(contatos) == TAM) break;

        fscanf(fl, "Nome: %34[A-Z. a-z]\n", nome);
        fscanf(fl, "Telefone: %24[(0-9) -0-9]\n", tel);
        fscanf(fl, "Email: %49s\n", email);
        fscanf(fl, "\n");

        strcpy(c.nome, nome);
        strcpy(c.telefone, tel);
        strcpy(c.email, email);

        inserir(contatos, c, teste);
    }

    free(nome); free(tel); free(email);
    fclose(teste); fclose(fl);
}

int buscarContatos(Contato *arr_contatos, char *nome)
{
    int chave = geraChave(nome);
    unsigned long long posicao = hash(chave);

    int count = 0;
    while (arr_contatos[posicao].tag != 0 && count < LIMITE_TESTE) {
        if (strcmp(arr_contatos[posicao].nome, nome) == 0) {
            arr_contatos[posicao].tag = 0;
            return posicao;
        }

        // se não encontrar na posição, procura na próxima tentativa:
        posicao = sondagemQuadratica(posicao, count);
        count++;
    }

    alert(-1);
    // printf("Contato '%s' não encontrado na tabela.\n", nome);
    return -1;
}

void removerContato(Contato *arr_contatos, char* nome)
{
    unsigned long long posicao;
    posicao = buscarContatos(arr_contatos, nome);

    if (posicao != 0) {
        arr_contatos[posicao].tag = 0;
        return;
    }

    printf("Contato '%s' não encontrado na tabela.\n", nome);
}

int contatoConsulta(Contato *arr_contatos, int posicao)
{
    Contato c = arr_contatos[posicao];

    int op_cons;
    while(1)
    {
        cabecalho("CATALOGO\t\t\t\t\t", "CONSULTA CONTATO\t", "");

        printf("%-35s\t%-20s\t%-50s\n", "NOME", "TELEFONE", "EMAIL");
        printf("%-35s\t%-20s\t%-50s\n", c.nome, c.telefone, c.email);
        printf("\n============================================================================================================================================\n");
        

        printf(">>>[1] Excluir\n");
        printf(">>>[2] Voltar\n");
        printf(">>>[3] Voltar ao menu");

        fflush(stdin);

        alert_msg();
        printf("\nEscolha uma opcao: ");
        op_cons = teste_input();

        switch (op_cons)
        {
            case '1':
                removerContato(arr_contatos, c.nome);
                return 0;

            case '2':
                alert(0);
                return 1;

            case '3':
                alert(0);
                return 0;

            default:
                alert(1);
                break;   
        }
    }
}