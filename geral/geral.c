#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "geral.h"
#include "../hash/hash.c"

const char data_hoje[11] = "01/01/2023";
#define ATRASO 200

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

void cabecalho(char *pagina, char *titulo)
{
    system(clear());
    printf("==========================================================================================\n");
    printf("\t%s\t%s\t\t%s\n", pagina, titulo, data_hoje);
    printf("==========================================================================================\n");
}

int teste_input(void)
{
    char teste[100];
    int i = 0;
    while ((teste[i] = getchar()) != '\n') i++;
    teste[i] = '\0';
    int len = strlen(teste);

    if (len == 0)
        return '\n';
    else if(len == 1)    /* é esperado input com apenas 1 caracter */
        return toupper(teste[0]);

    return 0;       /* input invalido */
}

char *string_upper(char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper(str[i]);
    }

    return str;
}

void string_copy(char *dest, char *src)
{
    int i;
    for (i = 0; src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

int menu_principal(void){
    int opcao;

    cabecalho("\t\t", "MEU INICIAL\t");
    
    printf(">>> [1] ADICIONAR\n");
    printf(">>> [2] REMOVER\n");
    printf(">>> [1] LISTAR\n");
    
    printf("\nEscolha uma opcao: ");
    opcao = teste_input();

    switch (opcao){
        case '1':
            printf("\nAdicionando Contato...");
            delay(ATRASO);

            break;

        case '2':
            printf("\nRemovendo Contato...");
            delay(ATRASO);

            break;

        case '3':
            printf("\nListando Contatos...");
            delay(ATRASO);

            break;
        
        default:

            break;
    }
    return opcao;
}

