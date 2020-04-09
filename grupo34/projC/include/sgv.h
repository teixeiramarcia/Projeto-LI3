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

Produtos sgv_get_produtos(SGV sgv);

Clientes sgv_get_clientes(SGV sgv);

SGV initSGV();

SGV loadSGVFromFiles(SGV sgv, char const* filesFolderPath);

void destroySGV(SGV sgv);

typedef struct query_2 {
    GHashTable* produtos_letra;
} * Query2;

void destroy_query2 (Query2 q2);

typedef struct query_3 {
    double faturacao_normal[N_FILIAIS];
    double faturacao_promocao[N_FILIAIS];
    int vendas_normal[N_FILIAIS];
    int vendas_promocao[N_FILIAIS];
} * Query3;

void destroy_query3 (Query3 q3);

typedef struct query_4 {
    GPtrArray* produtos_nunca_comprados[N_FILIAIS];
    GPtrArray* produtos_nunca_comprados_global;
    int total_produtos_nao_comprados[N_FILIAIS];
    int total_produtos_nao_comprados_global;
    bool e_global;
} * Query4;

void destroy_query4 (Query4 q4);

typedef struct query_5 {
    GPtrArray* clientes;
} * Query5;

void destroy_query5 (Query5 q5);

typedef struct query_6 {
    int total_clientes_que_nunca_compraram;
    int total_produtos_nunca_comprados;
} * Query6;

void destroy_query6 (Query6 q6);

typedef struct query_7 {
    int n_produtos_comprados[N_FILIAIS][N_MONTHS];
} * Query7;

void destroy_query7 (Query7 q7);

typedef struct query_8 {
    int total_vendas_meses;
    double total_faturado_meses;
} * Query8;

void destroy_query8 (Query8 q8);

typedef struct query_9 {
    GHashTable* clientes_que_compraram_produto_N_filial;
    int total_clientes_N;
    GHashTable* clientes_que_compraram_produto_P_filial;
    int total_clientes_P;
} * Query9;

void destroy_query9 (Query9 q9);

typedef struct query_10 {
    GPtrArray* produtos_por_quantidade;
} * Query10;

void destroy_query10 (Query10 q10);

typedef struct query_11 {
    GPtrArray* top_n;
} * Query11;

void destroy_query11 (Query11 q11);

typedef struct query_12 {
    GPtrArray* top_n;
} * Query12;

void destroy_query12 (Query12 q12);

typedef struct query_13 {
    int linhas_lidas_clientes;
    int linhas_validas_clientes;
    int linhas_lidas_produtos;
    int linhas_validas_produtos;
    int linhas_lidas_vendas;
    int linhas_validas_vendas;
} * Query13;

Query13 sgv_get_query_13(SGV sgv);

//queries

Query2 getProductsStartedByLetter(SGV sgv, char letter); //query 2

Query3 getProductSalesAndProfit(SGV sgv, char* productID, int month); //query 3

Query4 getProductsNeverBought(SGV sgv, int branchID); //query 4

Query5 getClientsOfAllBranches(SGV sgv); //query 5

Query6 getClientsAndProductsNeverBoughtCount(SGV sgv); //query 6

Query7 getProductsBoughtByClient(SGV sgv, char* clientID); //query 7

Query8 getSalesAndProfit(SGV sgv, int minMonth, int maxMonth); // query 8

Query9 getProductBuyers(SGV sgv, char* prodID, int branchID); //query 9

Query10 getClientFavoriteProducts(SGV sgv, char* clientID, int month); //query 10

Query11 getTopSoldProducts(SGV sgv, int limit); //query 11

Query12 getClientTopProfitProducts(SGV sgv, char* clientID, int limit); //query 12

#endif
