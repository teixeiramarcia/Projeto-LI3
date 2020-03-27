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

void sgv_adiciona_venda(SGV sgv, Venda venda);

SGV initSGV();

SGV loadSGVFromFiles(SGV sgv, char const* filesFolderPath);

void destroySGV(SGV sgv);

typedef struct query_2 {
    GHashTable* produtos_letra;
} * Query2;

typedef struct query_3 {

} * Query3;

typedef struct query_4 {
    GHashTable* produtos_nunca_comprados;
    int total_produtos_nao_comprados;
} * Query4;

typedef struct query_5 {

} * Query5;

typedef struct query_6 {
    int total_clientes_que_nunca_compraram;
    int total_produtos_nunca_comprados;
} * Query6;

typedef struct query_7 { //FIXME ainda com void return

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

//queries

Query2 getProductsStartedByLetter(SGV sgv, char letter); //query 2

Query4 getProductsNeverBought(SGV sgv, int branchID); //query 4

Query6 getClientsAndProductsNeverBoughtCount(SGV sgv); //query 6

void getProductsBoughtByClient(SGV sgv, char* clientID); //query 7

Query8 getSalesAndProfit(SGV sgv, int minMonth, int maxMonth); // query 8

Query9 getProductBuyers(SGV sgv, char* prodID, int branchID); //query 9

Query11 getTopSoldProducts(SGV sgv, int limit); //query 11

#endif
