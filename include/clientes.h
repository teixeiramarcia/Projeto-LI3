#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "vendas.h"
#include "types.h"
#include "filialID.h"

Clientes make_clientes();

bool adiciona_cliente(Clientes c, char* cliente);

GHashTable* clientes_get_clientes(Clientes clientes);

void clientes_procurarCli(void* cliente, void* clienteID, void* resCli);

bool existe_cliente(Clientes c, char* cliente);

bool valida_cliente(char* l);

void update_clientes(Clientes clientes, Venda venda);

void destroy_clientes(Clientes clientes);

void destroy_cliente(Cliente cliente);

#endif
