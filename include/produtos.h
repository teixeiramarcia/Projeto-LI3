#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <stdbool.h>
#include <stddef.h>

typedef struct produtos {	
    char **validos;
    size_t num;
} Produtos;

bool existe_produto (Produtos p, char *produto);

bool valida_produto (char *l);

#endif
