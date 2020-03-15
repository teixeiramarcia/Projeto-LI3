#ifndef SGV_H
#define SGV_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "clientes.h"
#include "produtos.h"

typedef struct sgv {
    Clientes clientes;
    Produtos produtos;
} *SGV;

#endif
