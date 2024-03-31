#include "../hash/hash.h"

/* Funções Exportadas */

/* Função delay
    Gera um atraso, em milissegundos, na resposta do programa.
*/
void delay(double milissegundos);

/* Função clear
    Limpa o terminal de acordo com o SO do usuário.
*/
char *clear(void);

/* Função cabecalho
    Adiciona o cabeçalho do menu atual.
*/
void cabecalho(char *pagina, char *titulo);

/* Função menu_principal 
    Exibe o menu principal.
*/
int menu_principal(Contato *contatos);

/* Função teste_input
    Verifica se o valor é uma string, número positivo ou negativo.
*/
int teste_input(void);

void imprimeCatalogo(Contato *arr_contatos, int pagina);

char **criaCatalogo(Contato *arr_contatos, int n);

int contaNomes(char **lista, int origem, char inicial);

void alert(int cod);

void alert_msg(void);

