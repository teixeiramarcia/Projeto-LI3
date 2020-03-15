#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "filiais.h"

typedef struct produto {
    char* produtoID;
    Filial filiais[3];
} *Produto;

typedef struct produtos{
    GHashTable* produtos[('Z'-'A')+1];
} *Produtos;

Produtos make_produtos();

bool adiciona_produto (Produtos p, char* produto);

bool existe_produto (Produtos p, char *produto);

bool valida_produto (char *l);

#endif
