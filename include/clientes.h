#ifndef CLIENTES_H
#define CLIENTES_H
#include <stdbool.h>
#include <stddef.h>
#include <glib.h>

typedef struct clientes {	
    char **validos;
    size_t num;
} Clientes;

bool valida_cliente (char *l);

bool existe_cliente(Clientes c, char *cliente);

#endif
