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
// #define TAM 16384
#define LIMITE_TESTE 1000

typedef struct contato {
    int tag;
    char nome[35];
    char telefone[25];
    char email[50];
    int colisoes;
} Contato;
// Contato contatos[TAM];

void inicializaTabela(Contato *arr_contatos)
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        arr_contatos[i].tag = 0;
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

int inserir(Contato *arr_contatos, Contato contato)
{
    int chave = geraChave(contato.nome);
    unsigned long long posicao = hash(chave);
    
    int count = 0;
    while (arr_contatos[posicao].tag != 0 && count < LIMITE_TESTE) {   
        if (strcmp(arr_contatos[posicao].nome, contato.nome) == 0)
            return 0;
        posicao = sondagemQuadratica(posicao, count);
        count++;
    }

    if (count >= LIMITE_TESTE) return 0;

    arr_contatos[posicao] = contato;
    arr_contatos[posicao].tag = 1;
    arr_contatos[posicao].colisoes = count;

    return 1;
}

int removerContato(Contato *arr_contatos, char *nome)
{
    long long posicao;
    posicao = buscarContatos(arr_contatos, nome);
    if (posicao > 0) {
        arr_contatos[posicao].tag = 0;
        atualizaTabela(arr_contatos);
        return 1;
    }
    return 0;
    // printf("Contato '%s' não encontrado na tabela.\n", nome);
}

unsigned long long sondagemQuadratica(unsigned long long posicao, int tentativas)
{
    int c1 = 29, c2 = 8;
    
    // px  <-    px   +     c1(i)       +          c2*i²
    posicao = (posicao + c1*(tentativas) + c2*(tentativas*tentativas));
    return posicao % TAM;   /* caso nova posição exceda o tamanho, o modulo é usado */
}

int totalContatos(Contato *arr_contatos)
{
    int i, count = 0;
    for (i = 0; i < TAM; i++) {
        if (arr_contatos[i].tag == 1)
            count++;
    }
    
    return count;
}

int totalColisoes(Contato *arr_contatos)
{
    int i, count = 0;
    for (i = 0; i < TAM; i++) {
        if (arr_contatos[i].tag == 1)
            count += arr_contatos[i].colisoes;
    }
    
    return count;
}


void preencheContato(Contato *arr_contatos)
{
    Contato c;
    cabecalho("\t\t\t\t\t\t", "CADASTRO\t", "");
    
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

    if (inserir(arr_contatos, c)) {
        atualizaTabela(arr_contatos);
        
        alert(5);
        alert_msg();
        delay(1000);
    } else
        alert(-3);  /* Não foi possível adicionar contato */
    
    
    free(nome); free(tel); free(email);
}

int importaContato(Contato *arr_contatos, FILE *fl)
{
    Contato c;

    char *nome, *tel, *email;
    nome  = (char *)malloc(35 * sizeof(char));
    tel   = (char *)malloc(25 * sizeof(char));
    email = (char *)malloc(50 * sizeof(char));

    int i, count = 0;
    for (i = 0; i < 10000; i++) {
        if (totalContatos(arr_contatos) == TAM) break;

        fscanf(fl, "Nome: %34[A-Z. a-z]\n", nome);
        fscanf(fl, "Telefone: %24[(0-9) -0-9]\n", tel);
        fscanf(fl, "Email: %49s\n", email);
        fscanf(fl, "\n");

        strcpy(c.nome, nome);
        strcpy(c.telefone, tel);
        strcpy(c.email, email);

        if (inserir(arr_contatos, c))
            count++;
    }
    free(nome); free(tel); free(email);
    fclose(fl);

    if (count != 0)
        atualizaTabela(arr_contatos);

    
    return count;
}

int atualizaTabela(Contato *arr_contatos)
{
    FILE *fl = fopen("tabela_hash.txt", "wt");
    if (fl == NULL) return 0;

    int i;
    for (i = 0; i < TAM; i++) {
        if (arr_contatos[i].tag != 0) {
            fprintf(fl, "Posicao: %d\n", i);
            fprintf(fl, "Nome: %s\n", arr_contatos[i].nome);
            fprintf(fl, "Telefone: %s\n", arr_contatos[i].telefone);
            fprintf(fl, "Email: %s\n", arr_contatos[i].email);
            fprintf(fl, "Colisoes: %d\n", arr_contatos[i].colisoes);
            fprintf(fl, "\n");
        }
    }

    fclose(fl);
    return 1;
}

int recuperaTabela(Contato *arr_contatos)
{
    FILE *tabela = fopen("tabela_hash.txt", "rt");
    if (tabela == NULL) return 0;

    Contato c;

    char *nome, *tel, *email;
    nome  = (char *)malloc(35 * sizeof(char));
    tel   = (char *)malloc(25 * sizeof(char));
    email = (char *)malloc(50 * sizeof(char));

    int i, posicao, colisoes, count = 0;
    
    // ==================================================
    // move o cursor do arquivo para o fim
    // e verifica se o arquivo está vazio:
    fseek(tabela, 0, SEEK_END);

    if (ftell(tabela) != 0) {

        // retorna o cursor ao início do arquivo:
        rewind(tabela);

        printf("oi");
        while (!feof(tabela))
        {   
            fscanf(tabela, "Posicao: %d\n", &posicao);
            fscanf(tabela, "Nome: %34[A-Z. a-z]\n", nome);
            fscanf(tabela, "Telefone: %24[(0-9) -0-9]\n", tel);
            fscanf(tabela, "Email: %49s\n", email);
            fscanf(tabela, "Colisoes: %d\n", &colisoes);
            fscanf(tabela, "\n");

            strcpy(c.nome, nome);
            strcpy(c.telefone, tel);
            strcpy(c.email, email);
            c.tag = 1;
            c.colisoes = colisoes;

            if (count < TAM) {
                arr_contatos[posicao] = c;
                count++;
            }
        }
    }

    free(nome); free(tel); free(email);
    fclose(tabela);
    
    return count;
}

int buscarContatos(Contato *arr_contatos, char *nome)
{
    int chave = geraChave(nome);
    unsigned long long posicao = hash(chave);
    int count = 0;
    while (arr_contatos[posicao].tag != 0 && count < LIMITE_TESTE) {
        if (strcmp(arr_contatos[posicao].nome, nome) == 0) {
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


int consultaContato(Contato *arr_contatos, int posicao)
{
    Contato c = arr_contatos[posicao];

    int op_cons;
    while(1)
    {
        cabecalho("CATALOGO\t\t\t\t\t", "CONSULTA CONTATO\t", "");

        printf("%-7s\t%-35s\t%-20s\t%-50s\t%-8s\n", "POS", "NOME", "TELEFONE", "EMAIL", "COLISOES");
        printf("%-7d\t%-35s\t%-20s\t%-50s\t%-8d\n", posicao, c.nome, c.telefone, c.email, c.colisoes);
        printf("\n============================================================================================================================================\n");
        

        printf("\n>>>[1] Remover\n");
        printf(">>>[2] Voltar\n");
        printf(">>>[3] Voltar ao menu\n");

        alert_msg();
        printf("Escolha uma opcao: ");
        op_cons = teste_input();

        printf("%c", op_cons);
        switch (op_cons)
        {
            case '1':
                if (removerContato(arr_contatos, c.nome)) {
                    alert(-2);
                    return 1;
                }
                break;

            case '2':
                alert(0);
                return 0;

            case '3':
                alert(0);
                return 1;

            default:
                alert(1);
                break;   
        }
    }
}