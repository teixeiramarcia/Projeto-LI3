#ifndef CLIENTES_H
#define CLIENTES_H
#include <stdbool.h>
#include <stddef.h>
#include <glib.h>

typedef struct clientes {
    GHashTable* clientes;
} Clientes;

Clientes make_clientes();

bool adiciona_cliente(Clientes c, char* cliente);

bool existe_cliente(Clientes c, char* cliente);

bool valida_cliente (char *l);

#endif
