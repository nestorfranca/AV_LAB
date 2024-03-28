# Tabela de Dispersão para Armazenamento de Contatos
## Introdução
Este projeto consiste na implementação de uma tabela de dispersão em C para armazenamento de contatos. A tabela de dispersão, também conhecida como hash table, é uma estrutura de dados eficiente para armazenar e recuperar informações rapidamente, usando uma função de hash para mapear chaves para valores.

## Problemática
O armazenamento eficiente de uma grande quantidade de informações, como contatos, pode ser desafiador. Estruturas de dados como listas ligadas ou arrays podem não ser eficientes o suficiente para buscas rápidas. A tabela de dispersão resolve esse problema ao permitir acesso rápido aos dados por meio de uma função de hash.

## Descrição
Neste projeto, implementamos uma tabela de dispersão para armazenar contatos, cada um associado a um nome, telefone e e-mail. A tabela de dispersão é inicializada com um tamanho fixo e usa o método da multiplicação para calcular o índice onde cada contato será armazenado. Além disso, utilizamos sondagem quadrática para lidar com colisões entre as chaves.

## Vantagens
Rápido acesso aos dados: A função de hash permite acesso rápido aos dados, tornando as operações de inserção, remoção e busca eficientes.
Armazenamento otimizado: A tabela de dispersão é capaz de armazenar grandes volumes de dados de forma eficiente, sem desperdiçar espaço.
Flexibilidade: A estrutura de uma tabela de dispersão pode ser adaptada para diferentes tipos de dados e necessidades específicas do projeto.

## Desvantagens
Colisões: Em casos de colisões, onde duas chaves resultam no mesmo índice, é necessário lidar com essas situações de forma eficaz para evitar degradação do desempenho.
Tamanho fixo: O tamanho da tabela de dispersão é fixo, o que pode levar a problemas de desempenho se não for escolhido adequadamente.
Função de hash: Uma função de hash ineficiente pode resultar em distribuição desigual dos dados na tabela, prejudicando o desempenho das operações.

# Funções Implementadas
## Função inicializaTabela
* **Descrição:** Função Inicializa a tabela de dispersão.
```c
void inicializaTabela(Contato* c);
```
## Função geraChave
* **Descrição:** Gera uma chave para o contato inserido.

```c
int geraChave(Contato c);
```

## Função Hash
* **Descrição:** Gera um valor de endereço a partir de uma chave.
```c
int hash(int chave);
```
## Função contadorBit
* **Descrição:** Retorna o número mínimo par de números de bits significativos de um número.
```c
contadorBit(int num): 
```
## Função Inserir
* **Descrição:** Insere um novo contato na tabela de dispersão.
```c
void inserir(Contato *arr_contatos, Contato contato, FILE *fl);
```
## Função removerContato
* **Descrição:** Remove um contato da tabela de dispersão.
```c
void removerContato(Contato *arr_contatos, char *nome);
```
## Função sondagemQuadratica
* **Descrição:** Trata colisões entre as chaves usando sondagem quadrática.
```c
int sondagemQuadratica(int posicao, int tentativas);
```
## Função totalContatos
* **Descrição:** Retorna o total de contatos presentes na tabela de dispersão.
```c
int totalContatos(Contato *contatos);
```
## Função preencheContato
* **Descrição:** Preenche a tabela de dispersão com informações de contatos a partir de um arquivo.
```c
void preencheContato(Contato *contatos);
```
