#ifndef SGV_H
#define SGV_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "clientes.h"
#include "produtos.h"
#include "vendas.h"
#include "types.h"

typedef struct sgv* SGV;

Produtos sgv_get_produtos(SGV sgv);

Clientes sgv_get_clientes(SGV sgv);

void sgv_adiciona_venda(SGV sgv, Venda venda, int* validos);

SGV initSGV();

SGV loadSGVFromFiles(SGV sgv, char const* filesFolderPath);

void destroySGV(SGV sgv);

typedef struct query_2 {
    GHashTable* produtos_letra;
} * Query2;

typedef struct query_3 {
    double faturacao_normal[N_FILIAIS];
    double faturacao_promocao[N_FILIAIS];
    int vendas_normal[N_FILIAIS];
    int vendas_promocao[N_FILIAIS];
} * Query3;

typedef struct query_4 {
    GHashTable* produtos_nunca_comprados[N_FILIAIS];
    GHashTable* produtos_nunca_comprados_global;
    int total_produtos_nao_comprados[N_FILIAIS];
    int total_produtos_nao_comprados_global;
} * Query4;

typedef struct query_5 {
    GPtrArray* clientes;
} * Query5;

typedef struct query_6 {
    int total_clientes_que_nunca_compraram;
    int total_produtos_nunca_comprados;
} * Query6;

typedef struct query_7 {
    int n_produtos_comprados[N_FILIAIS][N_MONTHS];
} * Query7;

typedef struct query_8 {
    int total_vendas_meses;
    double total_faturado_meses;
} * Query8;

typedef struct query_9 {
    GHashTable* clientes_que_compraram_produto_N_filial;
    int total_clientes_N;
    GHashTable* clientes_que_compraram_produto_P_filial;
    int total_clientes_P;
} * Query9;

typedef struct query_10 {

} * Query10;

typedef struct query_11 {
    GPtrArray* top_n;
} * Query11;

typedef struct query_12 {

} * Query12;

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

Query11 getTopSoldProducts(SGV sgv, int limit); //query 11

#endif
