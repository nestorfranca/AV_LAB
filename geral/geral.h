#include "../hash/hash.h"

/* Funções Exportadas */

/* Função delay
 - Gera um atraso, em milissegundos, na resposta do 
   programa.
*/
void delay(double milissegundos);

/* Função clear
 - Limpa o terminal de acordo com o SO do usuário.
*/
char *clear(void);

/* Função cabecalho
 - Adiciona o cabeçalho do menu atual.
*/
void cabecalho(char *pagina, char *titulo, char *num_pag);

/* Função menu_principal 
 - Exibe o menu principal.
*/
int menu_principal(Contato *arr_contatos);

/* Função teste_input
 - Verifica se o valor é uma string, número positivo ou   
   negativo.
*/
int teste_input(void);

/* Função teste_formato
    Verifica o tipo da entrada
     - inteiro (positivo ou negativo)
     - real
     - string
*/
int teste_formato(char *str);

/* Função imprimeCatalogo
 - Exibe os catálogo de nomes.
*/
int imprimeCatalogo(Contato *arr_contatos, char **catalogo);

/* Função criaCatalogo
 - Cria um catálogo com os nomes dos contatos cadastrados
   na tabela HASH, em ordem alfabética.
*/
char **criaCatalogo(Contato *arr_contatos);

/* Função contaNomes

*/
int contaNomes(char **lista, int origem, char inicial);

/* Função alert
 - Modifica o código de erro atual do sistema.
*/
void alert(int cod);

/* Função alert_msg
 - Exibe uma mensagem de erro referente ao código de 
   erro salvo no sistema.
*/
void alert_msg(void);

