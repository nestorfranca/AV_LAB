/* TAD: Contato(nome, telefone, email) */

/* Tipo Exportado */
typedef struct contato Contato;

/* Funções Exportadas */

/* Função inicializaTabela
- Preenche todos os valores de nome dos contatos
  com strings vazias
*/
void inicializaTabela(Contato* c);

/* Função geraChave:
 - Gera uma chave para o contato inserido
*/
int geraChave(char* nome);

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
void inserir(Contato *arr_contatos, Contato contato, FILE *fl);
// void inserir(Contato* contatos);

/* Função sondagemQuadratica
 - Tratamento de colisãos entre as chaves. Busca uma
   nova posição, que esteja vaga, através do cálculo:

    px <- px + c1*(i-1) + c2*(i-1)²

   onde i é o número de tentativas de inserir a chave.
*/
unsigned long long sondagemQuadratica(unsigned long long posicao, int tentativas);

/* Função totalContato
 - Retorna total de valores inseridos na tabela HASH.
*/
int totalContatos(Contato *contatos);

/* Função preencheContato
 - 
*/
void preencheContato(Contato *contatos);
// void preencheContato(Contato *contatos);

/* Função importaContato
 - Insere as informações dos contatos de um arquivo
   externo na tabela HASH.
*/
void importaContato(Contato *contatos);

/* Função buscarContato
 - busca e retorna a posição do contato com o nome
   inserido.
*/
int buscarContatos(Contato* arr_contatos, char* nome);

/* Função removerContato
 - Remove o valor inserido
*/
void removerContato(Contato *arr_contatos, char* nome);