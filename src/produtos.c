#include <ctype.h>
#include "util.h"
#include "produtos.h"

Produtos make_produtos() {
    Produtos p = (Produtos) malloc(sizeof(struct produtos));
    for (int i = 0; i < (('Z' - 'A') + 1); i++) {
        p->produtos[i] = g_hash_table_new_full(g_str_hash, str_compare, free, (GDestroyNotify) destroy_produto);
    }
    return p;
}

bool valida_produto(char *l) {
    if (isupper(l[0]) && isupper(l[1])) {
        return valida_codigo(l + 2);
    }
    return false;
}

bool adiciona_produto(Produtos prod, char *produto) {
    if (valida_produto(produto) && !existe_produto(prod, produto)) {
        char l = produto[0];
        Produto p = (Produto) malloc(sizeof(struct produto));
        p->produtoID = strdup(produto);

        for (int i = 0; i < 3; ++i) {
            p->filiais[i] = make_filial();
        }

        return g_hash_table_insert(prod->produtos[l - 'A'], p->produtoID, p);
    }
    return false;
}

bool existe_produto(Produtos p, char *produto) {
    char l = produto[0];
    return g_hash_table_contains(p->produtos[l - 'A'], produto);
}

void destroy_produtos(Produtos produtos) { //FIXME
    for (int i = 0; i < 26; i++) {
        g_hash_table_destroy(produtos->produtos[i]);
    }
    free(produtos);
}

void destroy_produto(Produto produto) {
    for (int i = 0; i < 3; ++i) {
        destroy_filial(produto->filiais[i]);
    }
    free(produto);
}
