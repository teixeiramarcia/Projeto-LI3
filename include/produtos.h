#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>

typedef struct produto {
    char* produtoID;
    size_t n_x_comprado_f1;
    size_t n_x_comprado_f2;
    size_t n_x_comprado_f3;
} Produto;

typedef struct produtos{
    GHashTable* produtos[('Z'-'A')+1];
} Produtos;

Produtos make_produtos();

bool adiciona_produto (Produtos p, char* produto);

bool existe_produto (Produtos p, char *produto);

bool valida_produto (char *l);

#endif
