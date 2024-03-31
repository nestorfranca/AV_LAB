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

void cabecalho(char *pagina, char *titulo)
{
    system(clear());
    printf("==========================================================================================\n");
    printf("\t%s\t%s\t\t%s\n", pagina, titulo);
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

int menu_principal(void)
{
    int opcao;

    cabecalho("\t\t", "MEU INICIAL\t");
    
    printf(">>> [1] ADICIONAR\n");
    printf(">>> [2] REMOVER\n");
    printf(">>> [3] LISTAR\n");
    printf(">>> [4] TESTE DE COLISAO\n");
    printf(">>> [5] SAIR\n");
    
    alert_msg();
    printf("\nEscolha uma opcao: ");
    opcao = teste_input();

    switch (opcao) {
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
        
        case '4':
        
            break;
        
        case '5':
            printf("\nEncerrando programa...\n");
            delay(ATRASO);
            break;

        default:
            alert(1);
            break;
    }
    return opcao;
}

void imprimeCatalogo(Contato *arr_contatos, int pagina)
{
    char **lista;
    
    lista = criaCatalogo(arr_contatos, TAM);
    
    int letra = 'A';
    int inicio_pag[20] = {0, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int id, i, j/*, id_pag = 240*pagina*/;
    // while ((letra - 'A') < 26) {
    int qnt_nomes;
    int total_linhas = 0, count = 0, count_ant = 0;
    int linhas_por_letra;

    // count = inicio_pag[pagina]; 
    while (total_linhas < 40) {
        
        printf(TXT_green"\n%c\n"TXT_reset, letra);

        qnt_nomes = contaNomes(lista, inicio_pag[pagina], letra);
        // printf("%d\n", qnt_nomes);
        // printf("%d\n", total_linhas);

        if (qnt_nomes > (240 - 6*total_linhas))
            linhas_por_letra = (240 - 6*total_linhas)/6;
        else
            linhas_por_letra = (qnt_nomes/6)+1;

        // printf("%d\n", linhas_por_letra);
        // printf("%d\n", count);
        for (i = 0; i < linhas_por_letra; i++)
        {
            // printf("%d - ",  i);
            if (total_linhas == 40) break;
            
            // printf("%d - ", id);
            for (j = 0; j < 6; j++)
            {
                id = inicio_pag[pagina] + count_ant + (linhas_por_letra)*j + i;
                if ((id < TAM) && (lista[id][0] == letra)) {
                    printf("%-25s", lista[id]);
                    count++;
                }
            }
            printf("\n");
            total_linhas++;   
        }
        // printf("%d\n", i);

        if (i == linhas_por_letra) {
            total_linhas += 2;
            letra++;
            
            count_ant = count;
        }
        // printf("%d\n", total_linhas);

    }
    
    if ((pagina+1) < 20)
        inicio_pag[pagina+1] = inicio_pag[pagina] + count;

    


    // printf("%d", qnt_nomes);

    // int id;
    // int count = 0;
    // for (i = 0; i < 40; i++)
    // {
    //     if (i < total_linhas) {
    //         if (id_pag == 0 && i == 0)
    //             printf(TXT_green"\n%c\n"TXT_reset, letra);
                        
    //         // printf("%3d - ", i);
    //         for (j = 0; j < 6; j++)
    //         {   
    //             id = id_pag + total_linhas*j + i + count;

    //             if ((id < TAM) && (lista[id][0] == letra)) {
    //                 // if (id == 0 || (lista[id][0] != lista[id-1][0])) {
    //                 //     if ((id != 0) && (lista[id][0] != lista[id-1][0])) letra++;
                        
    //                 //     printf(TXT_green"\n%c\n"TXT_reset, letra);
    //                 // }
                        
    //                 printf("%-25s", lista[id]);
    //             }
    //         }
    //         printf("\n");
        
    //     } 
    //     // else {
    //     //     count = qnt_nomes;
    //     //     if (i == total_linhas) {
    //     //         letra++;
    //     //         printf(TXT_green"\n%c\n"TXT_reset, letra);
    //     //     }

    //     //     printf("\n");
            
    //     //     // printf("%3d - ", i);
    //     //     for (j = 0; j < 6; j++)
    //     //     {   
    //     //         id = count + id_pag + (40 - total_linhas)*j + i;

    //     //         if ((id < TAM) && (lista[id][0] == letra)) {
    //     //             // if (id == 0 || (lista[id][0] != lista[id-1][0])) {
    //     //             //     if ((id != 0) && (lista[id][0] != lista[id-1][0])) letra++;
                        
    //     //             //     printf(TXT_green"\n%c\n"TXT_reset, letra);
    //     //             // }
                        
    //     //             printf("%-25s", lista[id]);
    //     //         }
    //     //     }
    //     //     // printf("\n");
    //     // }


        
        
    //     printf("%d - %-25s\n",i, lista[i]);
    //     printf("%3d - %-25s %-25s %-25s %-25s\n",i, lista[id_pag + i], lista[id_pag + 40+i], lista[id_pag + 80+i], lista[id_pag + 120+i]);
    // }
    
    free(lista);
}

char **criaCatalogo(Contato *arr_contatos, int n)
{
    char **lista_nomes;
    lista_nomes = (char**)malloc(TAM * sizeof(char*));
    if (lista_nomes == NULL) exit(1);

    int i, j;
    for (i = 0; i < TAM; i++)
    {
        lista_nomes[i] = (char*)malloc(35 * sizeof(char));
        if (lista_nomes[i] == NULL) exit(1);
        
        if (arr_contatos[i].tag != 0)
            lista_nomes[i] = arr_contatos[i].nome;
    }

    char *key;

    for (i = 1; i < n; i++) {
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
        if (lista[i][0] == inicial)
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
    else if (alert_cod == 2) printf(TXT_red"\nFormato invalido!\n"TXT_reset);
    else if (alert_cod == 3) printf(TXT_red"\nErro! Tamanho maximo excedido.\n"TXT_reset);
    else if (alert_cod == 4) printf(TXT_yellow"\nTamanho invalido! O CPF deve conter 11 digitos.\n"TXT_reset);
    else if (alert_cod == 5) printf(TXT_yellow"\nO CPF deve conter apenas numeros.\n"TXT_reset);
    else if (alert_cod == 6) printf(TXT_yellow"\nTamanho invalido! O telefone deve conter 11 digitos.\n"TXT_reset);
    else if (alert_cod == 7) printf(TXT_yellow"\nO telefone deve conter apenas numeros.\n"TXT_reset);
    else if (alert_cod == 8) printf(TXT_red"\nNao e possivel selecionar uma data anterior.\n"TXT_reset);
    // alerta de processo:
    else if (alert_cod == -1) printf(TXT_green"\nData atualizada!\n"TXT_reset);
    else if (alert_cod == -2) printf(TXT_red"\nO cliente possui um aluguel ativo!\n"TXT_reset);
    else if (alert_cod == -3) printf(TXT_red"\nCadastro cancelado!\n"TXT_reset);
    else if (alert_cod == -4) printf(TXT_green"\nCadastro apagado!\n"TXT_reset);
    else if (alert_cod == -5) printf(TXT_red"\nNao ha clientes cadastrados no sistema.\n"TXT_reset);
    else if (alert_cod == -6) printf(TXT_red"\nERRO! Cliente nao encontrado.\n"TXT_reset);
    else if (alert_cod == -7) printf(TXT_red"\nArquivo nao encontrado!\n"TXT_reset);
    else if (alert_cod == -8) printf(TXT_red"\nNao foi possivel concluir o cadastro\n"TXT_reset);
    else if (alert_cod == -9) printf(TXT_red"\nData Invalida!\n"TXT_reset);
    else if (alert_cod == -10) printf(TXT_red"\nNao ha alugueis no historico.\n"TXT_reset);
    else if (alert_cod == -11) printf(TXT_green"\nAluguel criado!\n"TXT_reset);
    else if (alert_cod == -12) printf(TXT_red"\nAluguel cancelado!\n"TXT_reset);
    else if (alert_cod == -13) printf(TXT_green"\nDado(s) Atualizado(s)!\n"TXT_reset);
    else if (alert_cod == -14) printf(TXT_green"\nCarro retirado do sistema com sucesso!\n"TXT_reset);
    else if (alert_cod == -15) printf(TXT_red"\nNao ha carros cadastrados no sistema.\n"TXT_reset);
    else if (alert_cod == -16) printf(TXT_red"\nCarro Indisponivel!\n"TXT_reset);
    else if (alert_cod == -17) printf(TXT_red"\nERRO! Carro nao encotrado.\n"TXT_reset);
    else if (alert_cod == -18) printf(TXT_red"\nConflito de Data!\n"TXT_reset);

    alert(0);    /* reseta marcador */
}