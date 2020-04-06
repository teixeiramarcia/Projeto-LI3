#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

void to_ptr_array_productID(void* key, void* value, void* user_data) {
    char* productID = (char*) key;
    GPtrArray* resultado = (GPtrArray*) user_data;
    g_ptr_array_add(resultado, productID);
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
