#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
#include "util.h"
#include "produtos.h"
#include "clientes.h"

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

void imprime_just_keys_clientes(void* data, void* user_data) {
    char* clienteID = (char*) data;
    printf("%s\n", (clienteID));
}

void adiciona_clientes_filial(void* data, void* user_data) {
    Venda venda = (Venda) data;
    GHashTable* clientes_filial = (GHashTable*) user_data;
    g_hash_table_add(clientes_filial, venda_get_codigo_cliente(venda));
}

void imprime_keys_for_ptr_array(void* data, void* user_data) {
    ProdutoQuantidade p_q = (ProdutoQuantidade) data;
    printf("%s\n", p_q_get_ID(p_q));
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

void imprime_info(void* value, void* user_data) {
    InformacaoProduto i_p = (InformacaoProduto) value;
    printf("Código do produto: %s\n", i_p_get_codigo_produto(i_p));
    printf("Número total de clientes envolvidos: %d\n", i_p_get_numero_compradores(i_p));
    for (int filial = 0; filial < N_FILIAIS; filial++) {
        printf("Número de unidades vendidas na filial %d: %d\n", filial+1, i_p_get_numero_vendido_filial(i_p, filial));
    }
}

