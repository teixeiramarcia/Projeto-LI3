#include <stdio.h>

#include "util.h"
#include "vendas.h"
#include "sgv.h"
#include "clientes.h"
#include "produtos.h"

//query 2 - WORKING
void imprime_produto(char* key, Produto prod, gpointer user_data){
    printf("%s\n", key);
}

void getProductsStartedByLetter(SGV sgv, char letter){
    printf("Produtos começados pela letra %c\n", letter);

    g_hash_table_foreach(sgv->produtos->produtos[letter-'A'], (GHFunc) imprime_produto, NULL);

}

//query 4


//query 9 - WORKING
void guarda_cliente(Venda venda, GHashTable* vendas_n){
    g_hash_table_add(vendas_n, venda->codigo_cliente);
}

void imprime_cliente(char* key, gpointer value, gpointer user_data){
    printf("%s\n", key);
}

void getProductBuyers(SGV sgv, char* prodID, int branchID){
    Produto p = g_hash_table_lookup(sgv->produtos->produtos[prodID[0]-'A'], prodID);
    GHashTable* vendas_n = g_hash_table_new(g_str_hash, str_compare);
    GHashTable* vendas_p = g_hash_table_new(g_str_hash, str_compare);
    for(int i = 0; i<12; i++){
        g_ptr_array_foreach(p ->filiais[branchID-1]->fmes[i]->vendas_normal, (GFunc) guarda_cliente, vendas_n);
        g_ptr_array_foreach(p->filiais[branchID-1]->fmes[i]->vendas_promocao, (GFunc) guarda_cliente, vendas_p);
    }
    printf("Clientes que compraram o produto %s na filial %d:\n", prodID, branchID);
    printf("Em época normal:\n");
    g_hash_table_foreach(vendas_n, (GHFunc) imprime_cliente, NULL);
    printf("Número total de clientes: %d\n", g_hash_table_size(vendas_n));
    printf("Em época promocional:\n");
    g_hash_table_foreach(vendas_p, (GHFunc) imprime_cliente, NULL);
    printf("Número total de clientes: %d\n", g_hash_table_size(vendas_p));

}




