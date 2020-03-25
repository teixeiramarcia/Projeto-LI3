#ifndef VENDAS_H
#define VENDAS_H

#include "produtos.h"
#include "types.h"
#include "month.h"
#include "filialID.h"

char* venda_get_codigo_produto(Venda venda);

double venda_get_preco_unitario(Venda venda);

int venda_get_unidades(Venda venda);

char venda_get_tipo_compra(Venda venda);

char* venda_get_codigo_cliente(Venda venda);

Month venda_get_mes(Venda venda);

void guarda_cliente(Venda venda, GHashTable* vendas_n);

FilialID venda_get_filial(Venda venda);

Venda valida_venda(Produtos prods, Clientes clientes, char* l);

#endif
