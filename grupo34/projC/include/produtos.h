/**
@file produtos.h
\brief Módulo de tratamento de produtos.
*/
#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "filial.h"
#include "types.h"
#include "filialID.h"

/**
@brief Aloca memória e inicializa a estrutura de dados Produtos.

@return estrutura de dados Produtos
*/
Produtos make_produtos();

/**
@brief Obter a estrutura de dados que contém todos os produtos existentes no sistema começados por uma determinada letra.
 *
 * @param prods Produtos estrutura onde se encontra um array de 26 HashTables, cada uma com os produtos de uma
 * determinada letra
 * @param branch int letra que se pretende obter
 *
@return GHashTable* com os produtos de uma determinada letra
*/
GHashTable* produtos_get_produtos_letra(Produtos prods, int letra);

/**
@brief Adiciona um produto à estrutura Produtos.
 *
 * @param p Produtos estrutura onde se pretende adicionar o novo produto
 * @param produto char* identificador do produto a adicionar
 * @param validos int* local onde ficará armazenado o número de produtos válidos até ao momento
 *
@return true se o produto for válido e ainda não existir no sistema, falso no caso contrário
*/
bool adiciona_produto(Produtos p, char* produto, int* validos);

/**
@brief Função auxiliar da função adiciona_produto.
 *
 * @param p Produtos estrutura onde se pretende verificar se já existe o produto em causa
 * @param produto char* identificador do produto que se pretende verificar se já existe
 *
@return true se o produto existir no sistema, falso no caso contrário
*/
bool existe_produto(Produtos p, char* produto);

/**
@brief Função auxiliar da função adiciona_produto.
 *
 * @param l char* identificador do produto a validar
 *
@return true se o produto for válido, falso no caso contrário
*/
bool valida_produto(char* l);

/**
@brief Atualiza a estrutura produtos com uma nova venda. Cada produto, dentro de uma estrutura adjacente armazena
 as vendas deste.
 *
 * @param l prods Produtos onde se pretende atualizar a informação de um determinado produto, ou criá-lo caso esta seja
 * a primeira venda do memso
 * @param venda Venda a ser adicionada na atualização da estrutura Produto
*/
void update_produtos(Produtos prods, Venda venda);

/**
@brief Obter o identificador de um determinado produto.
 *
 * @param prod Produto do qual se pretende obter o identificador
 *
@return identificador do Produto
*/
char* produto_get_productID(Produto prod);

/**
@brief Obter um determinado produto da estrutura Produtos.
 *
 * @param l prods Produtos onde se encontra o produto pretendido
 *
@return o Produto, se existir, NULL no caso contrário
*/
Produto produtos_get_produto(Produtos prods, char* prodID);

/**
@brief Obter uma das estruturas Filial (das 3 que existem dentro da estrutura Produto, armazenadas num array).
 *
 * @param l produto Produto que se pretende consultar
 * @param branchID FilialID que se pretende consultar dentro do produto especificado
 *
@return filial requisitada
*/
Filial produto_get_filial(Produto produto, FilialID branchID);

/**
@brief Função semelhante à produto_get_filial mas que permite obter uma filial num contexto diferene.
 *
 * @param prods Produtos onde o produto procurado se encontra
 * @param prodID char* identificador do produto procurado
 * @param branchID FilialID que se pretende consultar dentro do produto especificado
 *
@return filial requisitada
*/
Filial produtos_get_filial(Produtos prods, char* prodID, FilialID branchID);

/**
@brief Função auxiliar da Query 2.
 *
 * @param prods Produtos estrutura onde se pretende ir buscar a HashTable* que contém os produtos começados por uma
 * determinada letra.
 * @param c char letra que se pretende procurar
 * @param func GHFunc função que se aplica a cada produto, dado que apenas se pretende o identifcador para efeitos de
 * resposta à query
 * @param user_data gpointer armazenamento para o resultado da aplicação da func
*/
void produtos_foreach_started_by(Produtos prods, char c, GHFunc func, gpointer user_data);

/**
@brief Função auxiliar da Query 4 caso o utilizador pretenda resultados globais.
 *
 * @param key char* identificador do produto a ser consultado, será colocado na estrutura final
 * @param value Produto a ser consultado
 * @param user_data ProdutosNuncaVendidos estrutura para armazenamento do resultado da aplicação da função
*/
void guarda_se_nao_foi_vendido_global(void* key, void* value, void* user_data);

/**
@brief Função auxiliar da Query 4 caso o utilizador pretenda resultados segregados por filiais.
 *
 * @param key char* identificador do produto a ser consultado, será colocado na estrutura final
 * @param value Produto a ser consultado
 * @param user_data ProdutosNuncaVendidos estrutura para armazenamento do resultado da aplicação da função
*/
void guarda_se_nao_foi_vendido(void* key, void* value, void* user_data);

/**
@brief Obter a estrutura que responde à Query 4 caso o cliente pretenda resultados globais.
 *
 * @param p_n_v ProdutosNuncaVendidos estrutura que contém os produtos nunca vendidos numa GHashTable*
 *
@return estrutura que contém os produtos nunca vendidos na globalidade
*/
GHashTable* p_n_v_get_produtos_n_vendidos_global(ProdutosNuncaVendidos p_n_v);

/**
@brief Obter a estrutura que responde à Query 4 caso o cliente pretenda resultados segregados por filiais.
 *
 * @param p_n_v ProdutosNuncaVendidos estrutura que contém os produtos nunca vendidos num array de 3 GHashTables*
 * @param int filial da qual se pretende obter uma GHashTable* com os produtos que nunca foram vendidos
 *
@return estrutura que contém os produtos nunca vendidos na numa determinada filial
*/
GHashTable* p_n_v_get_produtos_n_vendidos(ProdutosNuncaVendidos p_n_v, int filial);

/**
@brief Liberta a memória alocada para a estrutura ProdutosNuncaVendidos.
 *
 * @param p_n_v ProdutosNuncaVendidos estrutura que contém os produtos nunca vendidos
*/
void destroy_produtos_nunca_vendidos(ProdutosNuncaVendidos p_n_v);

/**
@brief Função auxiliar das Queries 4 e 6.
 *
 * @param p_n_v ProdutosNuncaVendidos estrutura que irá conter os produtos nunca vendidos num determinado intervalo de filiais
 * @param from_branch int filial que será o limite inferior
 * @param to_branch int filial que será o limite superior
*/
void set_de_e_ate_filial_p_n_v(ProdutosNuncaVendidos p_n_v, int from_branch, int to_branch);

/**
@brief Liberta a memória alocada para a estrutura Produtos chamando recursivamente as funções que libertam as estruturas
 internas.
 *
 * @param produtos Produtos estrutura a libertar
*/
void destroy_produtos(Produtos produtos);

/**
@brief Liberta a memória alocada para a estrutura Produto chamando recursivamente as funções que libertam as estruturas
 internas.
 *
 * @param produto Produto a libertar
*/
void destroy_produto(Produto produto);

/**
@brief Aloca memória e inicializa a estrutura ProdutosNuncaVendidos.
*/
ProdutosNuncaVendidos make_produtos_nunca_vendidos();

/**
@brief Aloca memória e inicializa a estrutura TotaisVendasFaturacao.
*/
TotaisVendasFaturacao make_totais_vendas_faturacao();

/**
@brief Auxiliar da Query 8.
 *
 * @param t_v_f TotaisVendasFaturacao estrutura a ser consultada
 *
@return total de vendas efetuadas
*/
int t_v_f_get_total_vendas(TotaisVendasFaturacao t_v_f);

/**
@brief Auxiliar da Query 8.
 *
 * @param t_v_f TotaisVendasFaturacao estrutura a ser consultada
 *
@return total de faturação adjacente das vendas efetuadas
*/
double t_v_f_get_total_faturacao(TotaisVendasFaturacao t_v_f);

/**
@brief Auxiliar da Query 8.
 *
 * @param t_v_f TotaisVendasFaturacao na qual se pretende estabelecer os limites
 * @param minMonth int que será o limite inferior
 * @param maxMonth int que será o limite superior
*/
void t_v_f_set_limites(TotaisVendasFaturacao t_v_f, int minMonth, int maxMonth);

/**
@brief Auxiliar da Query 8.
 *
 * @param key void* parametro inutilizado mas exigido pela função em causa da glib
 * @param produto Produto a ser consultado
 * @param t_v_f TotaisVendasFaturacao onde serão armazenados os resultados
*/
void get_totais(void* key, void* produto, void* t_v_f);

/**
@brief Aloca memória e inicializa a estrutura TopProdutos.
 *
 * @param limit int do top N de produtos
*/
TopProdutos make_top_produtos(int limit);

/**
@brief Liberta a memória alocada para a estrutura TopProdutos.
 *
 * @param t_p TopProdutos estrutura a libertar
*/
void destroy_top_produtos(TopProdutos t_p);

/**
@brief Obter o GPtrArray* onde estão armazenados os top N produtos.
 *
 * @param t_p TopProdutos estrutura que se pretende consultar
 *
@return estrutura que contém os top N produtos
*/
GPtrArray* top_produtos_get_produtos(TopProdutos top_produtos);

/**
@brief Função auxiliar das queries 4 e 11 que permite comparar as vendas de dois produtos para efeitos de ordenação numérica.
 *
 * @param p1 void const* número de vendas do produto 1
 * @param p2 void const* número de vendas do produto 2
 *
@return 0 se forem iguais, < 0 se o primeiro for antes do segundo, > 0 se o primeiro for depois do segundo
*/
int produtos_comparator(void const* p1, void const* p2);

/**
@brief Função auxiliar da query 4 que permite comparar os códigos de dois produtos para efeitos de ordenação alfabética.
 *
 * @param prod1 void const* código do produto 1
 * @param prod2 void const* código do produto 2
 *
@return 0 se forem iguais, < 0 se o primeiro for antes do segundo, > 0 se o primeiro for depois do segundo
*/
int produtos_comparator_id(void const* prod1, void const* prod2);

/**
@brief Função auxiliar das queries 11 e 12.
 *
 * @param key void* parametro inutilizado mas exigido pela função em causa da glib
 * @param value Produto que pode ser adicionado
 * @param user_data TopProdutos estrutura a que pode ser adicionado o produto
*/
void adiciona_produtos(void* key, void* value, void* user_data);

/**
@brief Função auxiliar das queries 11 e 12.
 *
 * @param value Produto de onde são retiradas as informações
 * @param user_data InformacaoProduto estrutura a que são adicionadas as informações do produto
*/
void set_info_produtos(void* value, void* user_data);

/**
@brief Obter o código do produto existente na estrutura InformacaoProduto.
 *
 * @param user_data InformacaoProduto estrutura a ser consultada
 *
@return código do InformacaoProduto consultado
*/
char* i_p_get_codigo_produto(InformacaoProduto i_p);

/**
@brief Obter o número de compradores do produto existente na estrutura InformacaoProduto.
 *
 * @param user_data InformacaoProduto estrutura a ser consultada
 *
@return número de compradores do InformacaoProduto consultado
*/
int i_p_get_numero_compradores(InformacaoProduto i_p);

/**
@brief Obter o número de vendas do produto existente na estrutura InformacaoProduto numa determinada filial.
 *
 * @param user_data InformacaoProduto estrutura a ser consultada
 * @param filial int a ser consultada
 *
@return número de vendas do produto existente na estrutura InformacaoProduto
*/
int i_p_get_numero_vendido_filial(InformacaoProduto i_p, int filial);

/**
@brief Libertar a memória alocada para a estrutura InformacaoProduto.
 *
 * @param user_data InformacaoProduto estrutura a libertar
*/
void destroy_informacao_produto(void* i_p);

#endif
