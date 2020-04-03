#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "vendas.h"
#include "types.h"
#include "filialID.h"

Clientes make_clientes();

char* cliente_get_cliente_id(Cliente cliente);

FiliaisCli cliente_get_filial(Cliente c, int branch);

int filiais_cli_get_quantidade(FiliaisCli fcli);

GHashTable* filiais_cli_get_mes(FiliaisCli fcli, int mes);

bool adiciona_cliente(Clientes c, char* cliente, int* validos);

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

void cliente_fez_compras_todas_filiais(void* key, void* value, void* user_data);

int clientes_comparator(void const* cli1, void const* cli2);

char* p_q_get_ID (ProdutoQuantidade p_q);

void get_produto_quantidade (void* key, void* value, void* user_data);

void adiciona_produto_quantidade (void* key, void* value, void* user_data);

int produtos_cli_comparator (void const* prod_1, void const* prod_2);

TopProdutosCliente make_top_produtos_cliente(int limite);

GPtrArray* top_produtos_cliente_get_top_produtos(TopProdutosCliente t_p_c);

void swap_produto_menor_faturacao(GPtrArray* top_produtos, int tamanho, ProdutoCli produto_novo);

void adiciona_produtos_q12(void* key, void* value, void* user_data);

int produtos_cliente_comparator(void const* prod_1, void const* prod_2);

void set_info_produtos_cliente(void* value, void* user_data);

#endif
