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
    while ((teste[i] = getchar()) != '\n') i++;
    teste[i] = '\0';
    int len = strlen(teste); // remove o '\n' do final da string

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
    for (i = 0; str[i] != '\0'; i++)    /* verifica cada caracter */
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
    int opcao;
    char nome_contato[35], ch_op4[3];
    int num_contatos, num_colisoes;

    cabecalho("\t\t\t\t\t\t", "MENU INICIAL\t", "");
    
    printf(">>> [1] ADICIONAR\n");
    printf(">>> [2] BUSCAR\n");
    printf(">>> [3] REMOVER\n");
    printf(">>> [4] ANALISE DA TABELA HASH\n");
    printf(">>> [5] SAIR\n");
    
    alert_msg();
    printf("Escolha uma opcao: ");
    opcao = teste_input();

    switch (opcao) {
        case '1': {
            printf("\nAdicionando Contato...");
            delay(ATRASO);
            preencheContato(contatos);
            break;
        }
        case '2': {
            printf("\nBuscando Contatos..."); delay(ATRASO);
            
            while(1) {
                //cria lista temporária, para visualização:
                char **lista;
                lista = criaCatalogo(contatos);

                if (lista != NULL) {
                    cabecalho("\t\t\t\t\t\t", "BUSCAR CONTATOS\t", "");
                    if (imprimeCatalogo(contatos, lista)) break;
                } else {
                    alert(-4);  /* Não há contatos cadastrados. */
                    break;
                }
            }

            break;
        }
        case '3': {
            printf("\nRemovendo Contato...");
            delay(ATRASO);

            cabecalho("\t\t\t\t\t\t", "REMOVER CONTATO\t", "");
            alert_msg();
            printf("Escreva o nome completo do contato: ");

            fgets(nome_contato, 35, stdin);
            nome_contato[strlen(nome_contato)-1] = '\0';    /* buscar por nome */
            
            if (removerContato(contatos, nome_contato))
                alert(-2);
            break;
        }
        case '4': {
            while (1) {
                cabecalho("\t\t\t\t\t\t", "TABELA HASH\t", "");
                num_contatos = totalContatos(contatos);
                num_colisoes = totalColisoes(contatos);
                printf("\nPossui %d contatos registrados.\n", num_contatos);
                printf("Possui %d lacunas.\n", TAM-num_contatos);
                printf("Ocorreu um total de %d colisoes\n", num_colisoes);
                
                // MENU DE OPÇÕES:
                printf("\n>>> Voltar\n");

                alert_msg();
                printf("Aperte enter para Retornar ao Menu: ");


                int i = 0;
                while ((ch_op4[i] = getchar()) != '\n') i++;
                ch_op4[i] = '\0';
                if (strlen(ch_op4) == 0) {          /* verifica se está vazio */
                    alert(0);   /* voltando para o menu (sem mensagem de erro) */
                    break;
                }
                else
                    alert(4);   /* página não solicita entrada */
            }
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
        printf("Escolha uma opcao (ou escreva o nome completo do contato): ");
        
        fgets(ch_lista, 100, stdin);

        ch_lista[strlen(ch_lista)-1] = '\0';   /* remove '\n' */

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
            } else { 
                posicao = buscarContatos(arr_contatos, ch_lista);
                if (posicao != -1)
                    if (consultaContato(arr_contatos, posicao)) break;
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
        lista_nomes[i] = NULL;
        if (arr_contatos[i].tag != 0) {

            lista_nomes[count] = (char*)malloc(35 * sizeof(char));
            if (lista_nomes[count] == NULL) exit(1);

            lista_nomes[count] = arr_contatos[i].nome;
            count++;
        }
        
    }

    if (count > 0) {
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

    return NULL;
}

int contaNomes(char **lista, int origem, char inicial)
{
    int i, num_nomes = 0;
    for (i = origem; i < TAM; i++)
        if (lista[i] != NULL && lista[i][0] == inicial){
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
    else if (alert_cod == 4) printf(TXT_yellow"\nPagina nao solicita entrada.\n"TXT_reset);
    else if (alert_cod == 5) printf(TXT_green"\nContato Cadastrado!\n"TXT_reset);
    // alerta de processo:
    else if (alert_cod == -1) printf(TXT_red"\nContato nao encontrado na tabela!\n"TXT_reset);
    else if (alert_cod == -2) printf(TXT_green"\nContato removido com sucesso!\n"TXT_reset);
    else if (alert_cod == -3) printf(TXT_red"\nNao foi possivel adicionar contato!\n"TXT_reset);
    else if (alert_cod == -4) printf(TXT_red"\nNao ha contatos cadastrados!\n"TXT_reset);

    alert(0);    /* reseta marcador */
}

// void remove_contato(Contato *contatos){
//     char nome_remove[100];
//     int posicao;
    
//     cabecalho("\t\t\t\t\t\t\t","REMOVENDO CONTATO", "");
//     printf("\nDigite o nome do contato que deseja remover: ");

//     fgets(nome_remove, 100, stdin);  
//     nome_remove[strlen(nome_remove)-1] = '\0'; 

//     alert_msg();
//     posicao = buscarContatos(contatos, nome_remove);
//     if (posicao != -1){
//         removerContato(contatos, nome_remove);
//         alert(-2);
//     }else{
//         alert(posicao);
//     }
// }