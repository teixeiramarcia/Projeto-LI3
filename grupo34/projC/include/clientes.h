/**
@file clientes.h
\brief Módulo de tratamento de clientes.
*/
#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "venda.h"
#include "types.h"
#include "filialID.h"

/**
@brief Aloca memória e inicializa a estrutura de dados Clientes.

@return estrutura de dados Clientes
*/
Clientes make_clientes();

/**
@brief Obter a estrutura de dados FilialCli.
 *
 * @param c Cliente do qual se pretende obter a filial em que efetuou compras
 * @param branch int que se pretende consultar
 *
@return estrutura de dados FilialCli
*/
FilialCli cliente_get_filial(Cliente c, int branch);

/**
@brief Obter a quantidade de vendas numa FilialCli.
 *
 * @param fcli FilialCli da qual se pretende obter a quantidade de compras efetuadas
 *
@return número de vendas numa determinada filial
*/
int filiais_cli_get_quantidade(FilialCli fcli);

/**
@brief Obter os produtos vendidos num determinado mês.
 *
 * @param fcli FilialCli da qual se pretende obter o mês
 * @param mes int do qual se pretende obter a estrutura com os produtos comprados num determinado mês
 *
@return GHashTable que contém em cada posição um ProdutoCli
*/
GHashTable* filiais_cli_get_mes(FilialCli fcli, int mes);

/**
@brief Adicionar um novo cliente ao sistema.
 *
 * @param c Clientes estrutura onde vai ser adicionado o novo cliente
 * @param cliente char* identificador do cliente que se pretende adicionar caso seja válido é chamada recursivamente
 * uma função que vai inicializar uma estrutura Cliente com o código fornecido
 * @param validos int* caso o cliente seja adicionado, será incrementado o conteúdo deste parâmetro
 *
@return true se tiver sido adicionado com sucesso, false no caso contrário
*/
bool adiciona_cliente(Clientes c, char* cliente, int* validos);

/**
@brief Obter a estrutura de dados que contém todos os clientes que existe dentro da estrutura Clientes.
 *
 * @param clientes Clientes onde se pretende ir buscar a estrutura de dados
 *
@return GHashTable que contém em cada posição um Cliente
*/
GHashTable* clientes_get_clientes(Clientes clientes);

/**
@brief Obter um cliente através do seu identificador.
 *
 * @param clientes GHashTable onde se encontram armazenados todos os clientes do sistema
 * @param clienteID identificador do cliente que se pretende encontrar
 *
@return estrutura Cliente
*/
Cliente clientes_get_cliente(GHashTable* clientes, char* clienteID);

/**
@brief Função auxiliar da query 6 que consulta o cliente e verifica se este nunca efetuou compras.
 *
 * @param cliente Cliente que é consultado
 * @param clienteID char* variável inutilizada, mas exigida pela estrutura utilizada
 * @param resCli int* variável cujo conteúdo é incrementado caso o cliente em causa não tenha efetuado compras em
 * nenhuma filial
*/
void clientes_procurarCli(void* cliente, void* clienteID, void* resCli);

/**
@brief Verifica se um determinado cliente existe.
 *
 * @param c Clientes estrutura onde se encontram os clientes
 * @param cliente char* identificador do cliente a ser procurado
 *
@return true se o cliente for encontrado, false no caso contrário
*/
bool existe_cliente(Clientes c, char* cliente);

/**
@brief Verifica se o identificador de um cliente é válido.
 *
 * @param l char* identificador a ser verificado
 *
@return true se o identificador for válido, false no caso contrário
*/
bool valida_cliente(char* l);

/**
@brief Atualiza as vendas de um determinado cliente no sistema.
 *
 * @param clientes Clientes onde se encontra o cliente
 * @param venda Venda de onde é estraído o código do cliente para eventual procura do mesmo e a informação adicional
 * para atualizar a estrutura Cliente
*/
void update_clientes(Clientes clientes, Venda venda);

/**
@brief Free da estrutura Clientes.
 *
 * @param clientes Clientes a libertar
*/
void destroy_clientes(Clientes clientes);

/**
@brief Free da estrutura Cliente.
 *
 * @param cliente Cliente a libertar
*/
void destroy_cliente(Cliente cliente);

/**
@brief Aloca memória e inicializa a estrutura auxiliar da query 7, ProdutosCompradosCliente.
 *
@return estrutura ProdutosCompradosCliente
*/
ProdutosCompradosCliente make_produtos_comprados_cliente();

/**
@brief Função auxiliar da query 7.
 *
 * @param p_c_c ProdutosCompradosCliente estrutura que vai ser consultada para obtenção do total de produtos comprados
 * numa determinada filial e num determinado mês
 * @param filial int a ser consultada
 * @param month int  a ser consultado
 *
@return total de produtos comprados
*/
int* p_c_c_get_n_produtos_comprados(ProdutosCompradosCliente p_c_c, int filial, int month);

/**
@brief Função auxiliar da query 7.
 *
 * @param mes GHashTable a ser consultada para obtenção do total de compras
 *
@return total de compras efetuadas
*/
int get_total_compras(GHashTable* mes);

/**
@brief Função auxiliar da query 5.
 *
 * @param key void* identificador de um determinado cliente
 * @param value void* Cliente que se pretende consultar
 * @param user_data void* estrutura de armazenamento dos identificadores dos clientes que efetuaram compras em todas
 * as filiais
*/
void cliente_fez_compras_todas_filiais(void* key, void* value, void* user_data);

/**
@brief Função auxiliar da query 5 que permite comparar dois códigos de cliente para efeitos de ordenação alfabética.
 *
 * @param cli1 void const* identificador do cliente 1
 * @param cli2 void const* identificador do cliente 2
 *
@return 0 se forem iguais, < 0 se o primeiro for antes do segundo, > 0 se o primeiro for depois do segundo
*/
int clientes_comparator(void const* cli1, void const* cli2);

/**
@brief Função auxiliar da query 10.
 *
 * @param p_q ProdutoQuantidade estrutura da aqual se pretende obter o identificador do produto
 *
@return identificador de um ProdutoQuantidade
*/
char* p_q_get_ID(ProdutoQuantidade p_q);

/**
@brief Função auxiliar da query 10.
 *
 * @param key void* identificador de um ProdutoQuantidade
 * @param value void* produto ProdutoCli
 * @param user_data void* GHashTable onde será guardada a estrutura ProdutoQuantidade de um dos top produtos comprados
 * por um determinado cliente
*/
void get_produto_quantidade(void* key, void* value, void* user_data);

/**
@brief Função auxiliar da query 10.
 *
 * @param key void* identificador de um ProdutoQuantidade
 * @param value void* produto ProdutoCli
 * @param user_data void* GHashTable onde será guardada a estrutura ProdutoQuantidade de um dos top produtos comprados
 * por um determinado cliente
*/
void adiciona_produto_quantidade(void* key, void* value, void* user_data);

/**
@brief Função auxiliar da query 10 que permite comparar dois ProdutoCli para efeitos de ordenação pelas unidades compradas.
 *
 * @param prod_1 void const* primeiro produto
 * @param prod_2 void const* segundo produto
 *
@return 0 se forem iguais, < 0 se o primeiro for antes do segundo, > 0 se o primeiro for depois do segundo
*/
int produtos_cli_comparator(void const* prod_1, void const* prod_2);

/**
@brief Função auxiliar da query 12 cujo objetivo é adicionar produtos a uma HashTable sob a forma de união (sem repetições).
 *
 * @param key void* identificador de um ProdutoCli
 * @param value void* produto ProdutoCli
 * @param user_data void* GHashTable onde será adicionado o identificador do produto
*/
void adiciona_produtos_q12(void* key, void* value, void* user_data);

/**
@brief Função auxiliar da query 12.
 *
 * @param value void* identificador de um ProdutoFaturacao
 * @param user_data void* GPtrArray(ordenado pela faturação) que vai guardar o identificador do ProdutoFaturação
*/
void set_info_produtos_cliente(void* value, void* user_data);

/**
@brief Função auxiliar da query 12 cujo objetivo é encontrar o maior elemento e eliminá-lo da GList para que não seja
 enontrado em passagens seguintes.
 *
 * @param lista GList* onde irá ser procurado o maior elemento
 *
@return produto com a maior faturação encontrado
*/
ProdutoFaturacao get_maior(GList* lista);

#endif
