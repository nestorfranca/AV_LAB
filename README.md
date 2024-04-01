# 1. Tabela de Dispersão (Hash) para Armazenamento de Contatos

## Introdução
Uma Tabela de Dispersão, ou _Hash Table_ é uma estrutura de dados eficiente para armazenar e recuperar informações rapidamente, usando uma função de hash para mapear chaves para valores. O armazenamento eficiente de uma grande quantidade de informações, como contatos, pode ser desafiador. Estruturas de dados como listas ligadas ou arrays podem não ser eficientes o suficiente para buscas rápidas. A tabela de dispersão resolve esse problema ao permitir acesso rápido aos dados por meio de uma função de hash.

## Problemática
Este projeto consiste em desenvolver um sistema de lista de contatos armazenados em uma tabela de dispersão, desenvolvendo desde a função que mapeia a posição do contato na tabela, considerando também o devido tratamento de colisões, bem como a interface para interagir com a tabela, permitindo a inserção, remoção e busca de seus dados. Toda a estrutura do sistema foi montada inteiramente em Linguagem C, e a interface foi implementada utilizando o próprio terminal.

## Descrição
Implementamos uma tabela de dispersão para armazenar contatos, cada um associado a um nome, telefone e e-mail. A tabela de dispersão é inicializada com um tamanho fixo e usa o método da multiplicação para calcular o índice onde cada contato será armazenado, utilizando o somatório dos caractéres do nome como chave. Além disso, utilizamos sondagem quadrática para lidar com colisões entre as chaves.

O sistema foi dividido em uma TAD e um módulo, a fim de organizar as funções criadas a partir de sua finalidade. Na TAD _hash.h_ foram implementadas a struct Contato e as funções relacionadas à manipulação da tabela. Já o módulo _geral.h_, consiste nas funções que gerenciam a interface e as funções disponíveis para interação. O sistema criado permite, não somente as funções básicas exigidas (inserir, remover e buscar contatos), mas também permite importar dados do arquivo inicial, fornecido pelo professor e realizar uma análise em tempo de execução das estatísticas da tabela, como percentual preenchido, número de espaços vazios e total de colisões ocorridas até o momento.

### Função Hash: Método da Multiplicação
Esse método possui algumas variações, sendo a utilizado a "Meio do quadrado". Esse método aplica uma série de passos para calcular a posição do contato, a partir da chave gerada:
1. A chave é multiplicada por ela mesma;
2. Converte para a base binária;
3. A partir disso, o endereço-base da posição é definido descartando os bits excessivos da extremidade direita e esquerda.
O tamanho máximo da cadeia de bits do endereço é definido pelo tamanho máximo da tabela, que precisa ser uma potência de dois, que esteja entre 25% a 75% do valor total de dados a serem inseridos.

### Tratamento de Colisões: Método da Sondagem Quadrática
Assim como o método de Sondagem Linear, é um método de enderaçamento simples que, ao ocorra uma colisão, percorre a tabela Hash, em busca de um espaço vazio, sendo armazenados diretamente na tabela (sem listas encadeadas). a sondagem quadrática tenta corrigir o problema de agrupamentos da sondagem linear, espalhando mais as chaves, utilizando uma função de segundo grau:

$$p_x \leftarrow p_x + c_1 (i-1) + c_2 (i-1)^2$$

onde i representa as tentativas de inserir a chave na posição $p_c$. Quando não há colisão, $p_x = p_c$.
$c_1$ e $c_2$ são coeficientes quaisquer escolhidos de forma a varrer a tabela Hash, que são definidos a partir de tentativa e erro, até obter coeficientes com bom desempenho.

<p align="center">
  <img src="https://github.com/nestorfranca/AV_LAB/assets/63437313/4bc43ebd-0732-4dba-9463-b9f8711cf3b0"/>
</p>

## Vantagens
- Tende a espalhar melhor os dadosRápido acesso aos dados: A função de hash permite acesso rápido aos dados, tornando as operações de inserção, remoção e busca eficientes.
- Armazenamento otimizado: A tabela de dispersão é capaz de armazenar grandes volumes de dados de forma eficiente, sem desperdiçar espaço.
- Flexibilidade: A estrutura de uma tabela de dispersão pode ser adaptada para diferentes tipos de dados e necessidades específicas do projeto.

## Desvantagens
- Colisões: Em casos de colisões, onde duas chaves resultam no mesmo índice, é necessário lidar com essas situações de forma eficaz para evitar degradação do desempenho.
- Tamanho fixo: O tamanho da tabela de dispersão é fixo, o que pode levar a problemas de desempenho se não for escolhido adequadamente.
- Função de hash: Uma função de hash ineficiente pode resultar em distribuição desigual dos dados na tabela, prejudicando o desempenho das operações.


# 2. Módulos utilizados
## hash.h
Neste módulo, implementamos o tipo estrutura _Contato_, que define as informações de interesse em seus parâmetros, bem como todas as principais funções referentes à criação e manipulação da tabela Hash.
```c
typedef struct contato {
    int tag;
    char nome[35];
    char telefone[25];
    char email[50];
    int colisoes
} Contato;
```
##  geral.h
Nesse módulo, implementamos o conjunto das funções usandas na interface do menu para a tabela Hash e nas tratativas realizadas.

## Funções em hash.h
### Função inicializaTabela
* **Descrição:** Função Inicializa a tabela de dispersão.
```c
void inicializaTabela(Contato* arr_contatos);
```
### Função geraChave
* **Descrição:** Gera uma chave para o contato inserido.
```c
int geraChave(char *nome);
```
### Função Hash
* **Descrição:** Gera um valor de endereço a partir de uma chave.
```c
int hash(int chave);
```
### Função contadorBit
* **Descrição:** Retorna o número mínimo par de números de bits significativos de um número.
```c
contadorBit(int num): 
```
### Função Inserir
* **Descrição:** Insere um novo contato na tabela de dispersão.
```c
int inserir(Contato *arr_contatos, Contato contato);
```
### Função removerContato
* **Descrição:** Remove um contato da tabela de dispersão.
```c
int removerContato(Contato *arr_contatos, char *nome);
```
### Função sondagemQuadratica
* **Descrição:** Trata colisões entre as chaves usando sondagem quadrática.
```c
unsigned long long sondagemQuadratica(unsigned long long posicao, int tentativas);
```
### Função totalContatos
* **Descrição:** Retorna o total de contatos presentes na tabela de dispersão.
```c
int totalContatos(Contato *arr_contatos);
```
### Função preencheContato
* **Descrição:** Preenche a tabela de dispersão com informações de contatos a partir de um arquivo.
```c
void preencheContato(Contato *arr_contatos);
```
### Função importaContato
* **Descrição:** Insere as informações dos contatos de um arquivo externo na tabela HASH.
```c
int importaContato(Contato *arr_contatos, FILE *fl);
```
### Função atualizaTabela
* **Descrição:** Em qualquer modificação da tabela HASH, atualiza o arquivo "tabela_hash.txt".
```c
int atualizaTabela(Contato *arr_contatos);
```
### Função recuperaTabela
* **Descrição:** - Ao iniciar a execução, retoma os dados da tabela HASH, salvos no arquivo "tabela_hash.txt".
```c
int recuperaTabela(Contato *arr_contatos);
```
### Função buscaContato
* **Descrição:** Busca e retorna a posição do contato com o nome inserido.
```c
int buscarContatos(Contato* arr_contatos, char *nome);
```
### Função consultaContato
* **Descrição:** Exibe informações individuais sobre os contatos.
```c
int consultaContato(Contato *arr_contatos, int posicao);
```

## Funções em geral.h
### Função delay
* **Descrição:** Gera um atraso, em milissegundos, na resposta do programa.
```c
void delay(double milissegundos);
```
### Função clear
* **Descrição:** Limpa o terminal de acordo com o SO do usuário.
```c
char *clear(void);
```
### Função cabecalho
* **Descrição:** Adiciona o cabeçalho do menu atual.
```c
void cabecalho(char *pagina, char *titulo, char *num_pag);
```
### Função menu_principal
* **Descrição:** Exibe o menu principal.
```c
int menu_principal(Contato *arr_contatos);
```
### Função teste_input
* **Descrição:** Verifica se o valor é uma string, número positivo ou negativo.
```c
int teste_input(void);
```
### Função teste_formato
* **Descrição:** Verifica o tipo da entrada
```c
int teste_formato(char *str);
```
### Função imprimeCatalogo
* **Descrição:** Exibe os catálogo de nomes.
```c
int imprimeCatalogo(Contato *arr_contatos, char **catalogo);
```
### Função criaCatalogo
* **Descrição:** Cria um catálogo com os nomes dos contatos cadastrados na tabela HASH, em ordem alfabética.
```c
char **criaCatalogo(Contato *arr_contatos);
```
### Função contaNomes
* **Descrição:** Conta total de nomes para determinada inicial, na página atual do catálogo.
```c
int contaNomes(char **lista, int origem, char inicial);
```
### Função alert
* **Descrição:** Modifica o código de erro atual do sistema.
```c
void alert(int cod);
```
### Função alert_msg
* **Descrição:** Exibe uma mensagem de erro referente ao código de 
   erro salvo no sistema.
```c
void alert_msg(void);
```
