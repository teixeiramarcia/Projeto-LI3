/**
@file sgv.h
\brief Módulo de tratamento do Sistema de Gestão de Vendas.
*/
#ifndef SGV_H
#define SGV_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "clientes.h"
#include "produtos.h"
#include "venda.h"
#include "types.h"

typedef struct sgv* SGV;

/**
@brief Obter a estrutura Produtos.
 *
 * @param sgv SGV estrutura onde existem as principais estruturas do sistema
 *
@return estrutura de dados Produtos
*/
Produtos sgv_get_produtos(SGV sgv);

/**
@brief Obter a estrutura Clientes.
 *
 * @param sgv SGV estrutura onde existem as principais estruturas do sistema
 *
@return estrutura de dados Clientes
*/
Clientes sgv_get_clientes(SGV sgv);

/**
@brief Aloca memória e inicializa a estrutura de dados SGV.
 *
@return estrutura de dados SGV
*/
SGV initSGV();

/**
@brief Faz o carregamento de dados para o sistema populando as estruturas criadas.
 *
@return estrutura de dados SGV
*/
SGV loadSGVFromFiles(SGV sgv, char const* filesFolderPath);

/**
@brief Liberta a memória alocada para a estrutura SGV.
 *
 * @param sgv SGV a libertar
*/
void destroySGV(SGV sgv);

/**
@brief Estrutura Query2.
*/
typedef struct query_2 {
    GHashTable* produtos_letra;
} * Query2;

/**
@brief Liberta a memória alocada para a estrutura Query2.
 *
 * @param q2 Query2 a libertar
*/
void destroy_query2(Query2 q2);

/**
@brief Estrutura Query3.
*/
typedef struct query_3 {
    double faturacao_normal[N_FILIAIS];
    double faturacao_promocao[N_FILIAIS];
    int vendas_normal[N_FILIAIS];
    int vendas_promocao[N_FILIAIS];
} * Query3;

/**
@brief Liberta a memória alocada para a estrutura Query3.
 *
 * @param q3 Query3 a libertar
*/
void destroy_query3(Query3 q3);

/**
@brief Estrutura Query4.
*/
typedef struct query_4 {
    GPtrArray* produtos_nunca_comprados[N_FILIAIS];
    GPtrArray* produtos_nunca_comprados_global;
    int total_produtos_nao_comprados[N_FILIAIS];
    int total_produtos_nao_comprados_global;
    bool e_global;
} * Query4;

/**
@brief Liberta a memória alocada para a estrutura Query4.
 *
 * @param q4 Query4 a libertar
*/
void destroy_query4(Query4 q4);

/**
@brief Estrutura Query5.
*/
typedef struct query_5 {
    GPtrArray* clientes;
} * Query5;

/**
@brief Liberta a memória alocada para a estrutura Query5.
 *
 * @param q5 Query5 a libertar
*/
void destroy_query5(Query5 q5);

/**
@brief Estrutura Query6.
*/
typedef struct query_6 {
    int total_clientes_que_nunca_compraram;
    int total_produtos_nunca_comprados;
} * Query6;

/**
@brief Liberta a memória alocada para a estrutura Query6.
 *
 * @param q6 Query6 a libertar
*/
void destroy_query6(Query6 q6);

/**
@brief Estrutura Query7.
*/
typedef struct query_7 {
    int n_produtos_comprados[N_FILIAIS][N_MONTHS];
} * Query7;

/**
@brief Liberta a memória alocada para a estrutura Query7.
 *
 * @param q7 Query7 a libertar
*/
void destroy_query7(Query7 q7);

/**
@brief Estrutura Query8.
*/
typedef struct query_8 {
    int total_vendas_meses;
    double total_faturado_meses;
} * Query8;

/**
@brief Liberta a memória alocada para a estrutura Query8.
 *
 * @param q8 Query8 a libertar
*/
void destroy_query8(Query8 q8);

/**
@brief Estrutura Query9.
*/
typedef struct query_9 {
    GHashTable* clientes_que_compraram_produto_N_filial;
    int total_clientes_N;
    GHashTable* clientes_que_compraram_produto_P_filial;
    int total_clientes_P;
} * Query9;

/**
@brief Liberta a memória alocada para a estrutura Query9.
 *
 * @param q9 Query9 a libertar
*/
void destroy_query9(Query9 q9);

/**
@brief Estrutura Query10.
*/
typedef struct query_10 {
    GPtrArray* produtos_por_quantidade;
} * Query10;

/**
@brief Liberta a memória alocada para a estrutura Query10.
 *
 * @param q10 Query10 a libertar
*/
void destroy_query10(Query10 q10);

/**
@brief Estrutura Query11.
*/
typedef struct query_11 {
    GPtrArray* top_n;
} * Query11;

/**
@brief Liberta a memória alocada para a estrutura Query11.
 *
 * @param q11 Query11 a libertar
*/
void destroy_query11(Query11 q11);

/**
@brief Estrutura Query12.
*/
typedef struct query_12 {
    GPtrArray* top_n;
} * Query12;

/**
@brief Liberta a memória alocada para a estrutura Query12.
 *
 * @param q12 Query12 a libertar
*/
void destroy_query12(Query12 q12);

/**
@brief Estrutura Query13.
*/
typedef struct query_13 {
    int linhas_lidas_clientes;
    int linhas_validas_clientes;
    int linhas_lidas_produtos;
    int linhas_validas_produtos;
    int linhas_lidas_vendas;
    int linhas_validas_vendas;
} * Query13;

/**
@brief Getter da Query 13.
 *
 * @param sgv SGV a consultar
 *
@return Query 13
*/
Query13 sgv_get_query_13(SGV sgv);

/**
@brief Determinar a lista e o nº total de produtos cujo código se inicia por uma dada
letra (maiúscula).
 *
 * @param sgv SGV
 * @param letter char
 *
@return Query2
*/
Query2 getProductsStartedByLetter(SGV sgv, char letter);

/**
@brief Dado um mês e um código de produto, ambos válidos, determinar e apresentar
o número total de vendas (nº de registos de venda) e o total facturado com
esse produto em tal mês, distinguindo os totais em modo N e os totais em
modo P. O utilizador deverá decidir se pretende o resultado global ou os
resultados filial a filial para todas as 3 filiais.
 *
 * @param sgv SGV
 * @param productID char*
 * @param month int
 *
@return Query3
*/
Query3 getProductSalesAndProfit(SGV sgv, char* productID, int month);

/**
@brief Determinar a lista ordenada dos códigos dos produtos (e o seu número total)
que ninguém comprou, podendo o utilizador decidir igualmente se pretende
valores totais ou divididos pelas filiais.
 *
 * @param sgv SGV
 * @param branchID int
 *
@return Query4
*/
Query4 getProductsNeverBought(SGV sgv, int branchID);

/**
@brief Determinar a lista ordenada de códigos de clientes que realizaram compras em
todas as filiais.
 *
 * @param sgv SGV
 *
@return Query5
*/
Query5 getClientsOfAllBranches(SGV sgv);

/**
@brief Determinar o número de clientes registados que não realizaram compras bem
como o número de produtos que ninguém comprou.
 *
 * @param sgv SGV
 *
@return Query6
*/
Query6 getClientsAndProductsNeverBoughtCount(SGV sgv);

/**
@brief Dado um código de cliente, criar uma tabela com o número total de produtos
comprados (ou seja a soma das quantidades de todas as vendas do produto),
mês a mês (para meses em que não comprou a entrada deverá ficar a 0). A
tabela deverá ser apresentada em ecrã organizada por filial.
 *
 * @param sgv SGV
 * @param clientID char*
 *
@return Query7
*/
Query7 getProductsBoughtByClient(SGV sgv, char* clientID); //query 7

/**
@brief Dado um intervalo fechado de meses, por exemplo [1..3], determinar o total de
vendas (nº de registos de venda) registadas nesse intervalo e o total faturado.
 *
 * @param sgv SGV
 * @param minMonth int
 * @param maxMonth int
 *
@return Query8
*/
Query8 getSalesAndProfit(SGV sgv, int minMonth, int maxMonth);

/**
@brief Dado um código de produto e uma filial, determinar os códigos (e número total)
dos clientes que o compraram, distinguindo entre compra N e compra P.
 *
 * @param sgv SGV
 * @param prodID char*
 * @param branchID int
 *
@return Query9
*/
Query9 getProductBuyers(SGV sgv, char* prodID, int branchID);

/**
@brief Dado um código de cliente e um mês, determinar a lista de códigos de
produtos que mais comprou por quantidade e não por faturação), por ordem
descendente.
 *
 * @param sgv SGV
 * @param clientID char*
 * @param month int
 *
@return Query10
*/
Query10 getClientFavoriteProducts(SGV sgv, char* clientID, int month);

/**
@brief Criar uma lista dos N produtos mais vendidos ao longo do ano, indicando o número total de clientes e o número de
unidades vendidas, filial a filial.
 *
 * @param sgv SGV
 * @param limit int
 *
@return Query11
*/
Query11 getTopSoldProducts(SGV sgv, int limit);

/**
@brief Dado um código de cliente determinar quais os códigos dos N produtos em que
mais gastou dinheiro durante o ano.
 *
 * @param sgv SGV
 * @param clientID char*
 * @param limit int
 *
@return Query12
*/
Query12 getClientTopProfitProducts(SGV sgv, char* clientID, int limit);

#endif