/* TAD: Contato(nome, telefone, email) */

/* Tipo Exportado */
typedef struct contato Contato;

/* Funções Exportadas */

/* Função geraChave:
 - Gera uma chave para o contato inserido
*/
int geraChave(Contato c);

/* Função hash:
 - Gera um valor de endereço a partir de uma chave,
   usando o método da multiplicação.
*/
int hash(int chave);

/* Função contadorBit
 - Retorna o número mínimo par de números de bits
   significativos de uma número.
*/
int contadorBit(int num);

/* Função inserir
 - Adiciona uma nova chave na tabela Hash
*/
void inserir();

/* Função sondagemQuadratica
 - Tratamento de colisãos entre as chaves. Busca uma
   nova posição, que esteja vaga, através do cálculo:

    px <- px + c1*(i-1) + c2*(i-1)²

   onde i é o número de tentativas de inserir a chave.
*/
int sondagemQuadratica(int indice);
