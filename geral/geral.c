#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "geral.h"
#include "../hash/hash.c"

// const char data_hoje[11] = "01/01/2023";
#define ATRASO 200

#define TXT_red "\x1b[31m"
#define TXT_green "\x1b[32m"
#define TXT_yellow "\x1b[33m"
#define TXT_reset "\x1b[0m"
int alert_cod = 0;

void delay(double milissegundos)
{
    // Armazenando tempo inicial:
    clock_t tempo_inicial = clock();
    
    // looping till required time is not achieved
    while (milissegundos > clock() - tempo_inicial);
}

char *clear(void)
{    
    // Checking for windows OS with
    // _WIN32 macro
    #ifdef _WIN32
        return "cls";

    // Checking for mac OS with
    // __APPLE__ macro
    #elif __APPLE__
        return "clear";

    // Checking for linux OS with
    // __linux__ macro
    #elif __linux__
        return "clear";
    #endif
}

void cabecalho(char *pagina, char *titulo, char *num_pag)
{
    system(clear());
    printf("============================================================================================================================================\n");
    printf("\t%s\t%s\t\t%s\n", pagina, titulo, num_pag);
    printf("============================================================================================================================================\n");
}

int teste_input(void)
{
    char teste[100];
    int i = 0;

    fgets(teste, 100, stdin);
    int len = strlen(teste) - 1; // remove o '\n' do final da string

    if (len == 0)
        return '\n';
    else if(len == 1)    /* é esperado input com apenas 1 caracter */
        return toupper(teste[0]);

    return 0;       /* input invalido */
}

int teste_formato(char *str)
{
    int i;
    int negativo = 0;
    for (i = 0; str[i] != '\n'; i++)    /* verifica cada caracter */
    {
        if (!(str[i] >= '0' && str[i] <= '9'))  /* verifica se o caracter é numérico */
        {   
            if (i == 0 && str[i] == '-')
                negativo++;
            else
                return 0;   /* é string */
        }
    }
    if (negativo == 1)
    {
        return -1;          /* é número negativo */
    }
    return 1;               /* é número positivo */
}

int menu_principal(Contato *contatos) {
    int opcao, op_i;
    char dado[35];

    cabecalho("\t\t\t\t\t\t", "MENU INICIAL\t", "");
    
    printf(">>> [1] ADICIONAR\n");
    printf(">>> [2] REMOVER\n");
    printf(">>> [3] BUSCAR\n");
    printf(">>> [4] TESTE DE COLISAO\n");
    printf(">>> [5] SAIR\n");
    
    alert_msg();
    printf("\nEscolha uma opcao: ");
    opcao = teste_input();

    switch (opcao) {
        case '1': {
            printf("\nAdicionando Contato...");
            delay(ATRASO);
            preencheContato(contatos);
            break;
        }
        case '2': {
            printf("\nRemovendo Contato...");
            delay(ATRASO);

            break;
        }
        case '3': {
            printf("\nBuscando Contatos..."); delay(ATRASO);
            
            while(1) {
                //cria lista temporária, para visualização:
                char **lista;
                lista = criaCatalogo(contatos);

                cabecalho("\t\t\t\t\t\t", "BUSCAR CONTATOS\t", "");
                if (imprimeCatalogo(contatos, lista)) break;
            }

            break;
        }
        case '4': {
        
            break;
        }
        case '5': {
            printf("\nEncerrando programa...\n");
            delay(ATRASO);
            break;
        }
        default: {
            alert(1);
            break;
        }
    }
    return opcao;
}

int imprimeCatalogo(Contato *arr_contatos, char **catalogo)
{
    // variáveis usadas na impressão do catálogo:
    int inicio_pag[70] = {0};
    int id, i, j, letra, qnt_nomes;
    int linhas, colunas, count, count_ant;
    int linhas_por_letra, pagina = 0;
    char pag[10];

    // variável para o menu de opções:
    int op_lista, posicao;
    char ch_lista[100];

    while (1) {
        // imprime cabeçacho:
        sprintf(pag, "Pagina %02d", pagina+1);
        cabecalho("BUSCAR CONTATOS\t\t\t\t\t", "CATALOGO\t\t\t\t", pag);
        
        // condições iniciais:
        linhas = 0, colunas = 4, count = 0, count_ant = 0;
        letra = catalogo[inicio_pag[pagina]][0];
        // imprime página:
        while (linhas < 20) {
            if (letra <= 'Z')
                printf(TXT_green"%c\n"TXT_reset, letra);

            // contabiliza quantos nomes começam com a mesma letra inicial:
            qnt_nomes = contaNomes(catalogo, inicio_pag[pagina], letra);
            // verifica quantas linhas devem ser impressas por letra, na página:
            if (qnt_nomes > (80 - colunas*linhas))
                linhas_por_letra = (80 - colunas*linhas)/colunas;
            else
                linhas_por_letra = (qnt_nomes/colunas)+1;

            // imprime as linhas contabilizadas:
            for (i = 0; i < linhas_por_letra; i++) {
                // finaliza ciclo, caso não haja nomes, ou com todas as linhas impressas:
                if (qnt_nomes == 0 || linhas == 20) break;
                
                for (j = 0; j < colunas; j++) {
                    id = inicio_pag[pagina] + count_ant + (linhas_por_letra)*j + i;
                    if ((catalogo[id] != NULL) && (catalogo[id][0] == letra)) {
                        printf("%-35s", catalogo[id]);
                        count++;
                    }
                }
                printf("\n");
                linhas++;   
            }

            // se ciclo terminou sem completar a página, incrementa a letra e continua:
            if (linhas < 20) {
                printf("\n");
                
                linhas += 2;
                if (letra >= 'Z')
                    printf("\n");
                letra++;
                
                // nomes que já foram impressos na página:
                count_ant = count;
            }
        }
        
        // marca o início da próxima página:
        if ((pagina+1) < 70)
            inicio_pag[pagina+1] = inicio_pag[pagina] + count;
        

        // MENU DE OPÇÕES:
        printf("\n>>>[1] Pagina Anterior\n");
        printf(">>>[2] Pagina Seguinte\n");
        printf(">>>[3] Voltar\n");

        alert_msg();
        printf("\nEscolha uma opcao (ou escreva o nome completo do contato): ");
        
        fgets(ch_lista, 100, stdin);
        if (strlen(ch_lista) > 0) {                 /* verifica se está vazio */
            if (teste_formato(ch_lista) != 0) {     /* verifica se é um número */
                op_lista = atoi(ch_lista);
                switch (op_lista) {
                    case 1:
                        if (pagina > 0)
                            pagina--;
                        else
                            alert(2);
                        break;

                    case 2:
                        // verifica se todos os contatos foram impressos:
                        if ((catalogo[inicio_pag[pagina] + count]) != NULL)
                            pagina++;
                        else
                            alert(3);
                        break;

                    case 3:
                        alert(0);   /* retorna ao menu de busca */
                        return 1;

                    default:
                        alert(1);   /* opção inválida */
                        break;   
                }
            } else {                                /* buscar por nome */
                posicao = buscarContatos(arr_contatos, ch_lista);
                if (posicao != -1)
                    contatoConsulta(arr_contatos, posicao);
            }
        }
    }
    free(catalogo);
}

char **criaCatalogo(Contato *arr_contatos)
{
    char **lista_nomes;
    lista_nomes = (char**)malloc(TAM * sizeof(char*));
    if (lista_nomes == NULL) exit(1);

    int i, j, count = 0;
    for (i = 0; i < TAM; i++)
    {
        if (arr_contatos[i].tag != 0) {
            lista_nomes[count] = (char*)malloc(35 * sizeof(char));
            if (lista_nomes[count] == NULL) exit(1);

            lista_nomes[count] = arr_contatos[i].nome;
            count++;
        }
        
    }

    char *key;

    for (i = 1; i < count; i++) {
        key = lista_nomes[i];
        j = i - 1;
        while (j >= 0 && strcmp(lista_nomes[j], key) > 0) {
            lista_nomes[j + 1] = lista_nomes[j];
            j = j - 1;
        }
        lista_nomes[j + 1] = key;
    }

    return lista_nomes;
}

int contaNomes(char **lista, int origem, char inicial)
{
    int i, num_nomes = 0;
    for (i = origem; i < TAM; i++)
    {
<<<<<<< HEAD
        if (lista[i][0] == inicial) 
=======
        if (lista[i] != NULL && lista[i][0] == inicial)
>>>>>>> bae89303162196a6ef7d6fb20e82e7d8b4a51162
            num_nomes++;
    }   

    return num_nomes;
}

void alert(int cod)
{
    alert_cod = cod;
}

void alert_msg(void)
{
    // mensagem limpa, sem erro:
    if (alert_cod == 0) printf("\n\n");
    
    // alerta de formato: 
    else if (alert_cod == 1) printf(TXT_yellow"\nInsira uma opcao valida!\n"TXT_reset);
    else if (alert_cod == 2) printf(TXT_yellow"\nJa esta na pagina inicial!\n"TXT_reset);
    else if (alert_cod == 3) printf(TXT_yellow"\nJa esta na ultima pagina!\n"TXT_reset);
    else if (alert_cod == 9) printf(TXT_green"\nContato Cadastrado!\n"TXT_reset);
    // alerta de processo:
    else if (alert_cod == -1) printf(TXT_red"\nContato nao encontrado na tabela!\n"TXT_reset);

    alert(0);    /* reseta marcador */
}