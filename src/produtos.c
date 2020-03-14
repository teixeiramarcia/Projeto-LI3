#include <string.h>
#include <ctype.h>
#include "util.h"
#include "produtos.h"

Produtos make_produtos(){
    Produtos p;
    for(int i=0; i<(('Z'-'A')+1); i++){
        p.produtos[i] = g_hash_table_new_full(g_str_hash, str_compare, free, NULL);
    }
    return p;
}

bool valida_produto (char *l) {
    if (isupper(l[0]) && isupper(l[1])) {
        return valida_codigo(l+2);
    }
    return false;
}

bool adiciona_produto (Produtos p, char* produto){
    if(valida_produto(produto)){
        char l = produto[0];
        return g_hash_table_add(p.produtos[l - 'A'], strdup(produto));
    }
    return false;
}

bool existe_produto (Produtos p, char* produto) {
    char l = produto[0];
    return g_hash_table_contains(p.produtos[l - 'A'], produto);
}
