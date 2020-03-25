#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "vendas.h"
#include "types.h"
#include "filialID.h"

Clientes make_clientes();

FiliaisCli cliente_get_filial(Cliente c, int branch);

int filiais_cli_get_quantidade(FiliaisCli fcli);

GHashTable* filiais_cli_get_mes(FiliaisCli fcli, int mes);

bool adiciona_cliente(Clientes c, char* cliente);

GHashTable* clientes_get_clientes(Clientes clientes);

Cliente clientes_get_cliente(GHashTable* clientes, char* clienteID);

void clientes_procurarCli(void* cliente, void* clienteID, void* resCli);

bool existe_cliente(Clientes c, char* cliente);

bool valida_cliente(char* l);

void update_clientes(Clientes clientes, Venda venda);

void destroy_clientes(Clientes clientes);

void destroy_cliente(Cliente cliente);

ProdutosCompradosCliente make_produtos_comprados_cliente();

int* p_c_c_get_n_produtos_comprados(ProdutosCompradosCliente p_c_c, int filial, int month);

int get_total_compras(GHashTable* mes);

#endif
