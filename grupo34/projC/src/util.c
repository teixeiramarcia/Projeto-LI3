#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
#include "util.h"
#include "produtos.h"

int str_compare(void const* a, void const* b) {
    char const* _a = (char const*) a;
    char const* _b = (char const*) b;
    return strcmp(_a, _b) == 0;
}

bool valida_codigo(char* codigo) {
    int i;
    for (i = 0; codigo[i] != '\0'; i++) {
        if (!isdigit(codigo[i])) {
            return false;
        }
    }
    if (i != 4) {
        return false;
    }
    return true;
}

void imprime_keys(void* key, void* value, void* user_data) {
    printf("%s\n", (char*) key);
}

void adiciona_clientes_filial(void* data, void* user_data) {
    Venda venda = (Venda) data;
    GHashTable* clientes_filial = (GHashTable*) user_data;
    g_hash_table_add(clientes_filial, venda_get_codigo_cliente(venda));
}

void imprime_keys_for_ptr_array(void* data, void* user_data) {
    Produto produto = (Produto) data;
    char* key = produto_get_productID(produto);
    printf("%s\n", (char*) key);
    for (int filial = 0; filial < N_FILIAIS; ++filial) {
        printf("    Filial %d:\n", filial + 1);
        int vendas_filial = 0;
        GHashTable* clientes_filial = g_hash_table_new(g_str_hash, str_compare);
        Filial filial_prod = produto_get_filial(produto, filial);
        for (int mes = 0; mes < N_MONTHS; ++mes) {
            FaturacaoMes fmes = filial_get_faturacao_mes(filial_prod, mes);
            vendas_filial += faturacao_mes_get_total_normal(fmes) + faturacao_mes_get_total_promocao(fmes);
            g_ptr_array_foreach(faturacao_mes_get_vendas_normal(fmes), adiciona_clientes_filial, clientes_filial);
            g_ptr_array_foreach(faturacao_mes_get_vendas_promocao(fmes), adiciona_clientes_filial, clientes_filial);
        }
        int total_clientes = g_hash_table_size(clientes_filial);
        printf("        Total de clientes que efetuaram compras: %d\n", total_clientes);
        printf("        Total de unidades vendidas: %d\n", vendas_filial);
    }
}

void add_product_id(void* prodID, void* value, void* user_data) {
    char* productID = (char*) prodID;
    GHashTable* produtos_letra = (GHashTable*) user_data;
    g_hash_table_add(produtos_letra, productID);
}

void add_client_id(void* cliID, void* value, void* user_data) {
    char* clientID = (char*) cliID;
    GHashTable* clientes_que_compraram_produto = (GHashTable*) user_data;
    g_hash_table_add(clientes_que_compraram_produto, clientID);
}

