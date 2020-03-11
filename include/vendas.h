#ifndef VENDAS_H
#define VENDAS_H
#include "produtos.h"
#include "clientes.h"
#include <stdbool.h>

typedef struct vendas {	
    char **validos;
    size_t num;
} Vendas;

bool valida_venda (char *l, Produtos p, Clientes c);

#endif
