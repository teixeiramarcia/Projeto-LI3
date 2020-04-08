#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "filial.h"
#include "types.h"
#include "filialID.h"

Produtos make_produtos();

GHashTable* produtos_get_produtos_letra(Produtos prods, int letra);

bool adiciona_produto(Produtos p, char* produto, int* validos);

bool existe_produto(Produtos p, char* produto);

bool valida_produto(char* l);

void update_produtos(Produtos prods, Venda venda);

char* produto_get_productID(Produto prod);

Produto produtos_get_produto(Produtos prods, char* prodID);

Filial produto_get_filial(Produto produto, FilialID branchID);

Filial produtos_get_filial(Produtos prods, char* prodID, FilialID branchID);

void produtos_foreach_started_by(Produtos prods, char c, GHFunc func, gpointer user_data);

void guarda_se_nao_foi_vendido_global(void* key, void* value, void* user_data);

void guarda_se_nao_foi_vendido(void* key, void* value, void* user_data);

GHashTable* p_n_v_get_produtos_n_vendidos_global(ProdutosNuncaVendidos p_n_v);

GHashTable* p_n_v_get_produtos_n_vendidos(ProdutosNuncaVendidos p_n_v, int filial);

void set_de_e_ate_filial_p_n_v(ProdutosNuncaVendidos p_n_v, int from_branch, int to_branch);

void destroy_produtos(Produtos produtos);

void destroy_produto(Produto produto);

int for_each_conta_vendas(GPtrArray* vendas);

ProdutosNuncaVendidos make_produtos_nunca_vendidos();

TotaisVendasFaturacao make_totais_vendas_faturacao();

int t_v_f_get_total_vendas(TotaisVendasFaturacao t_v_f);

double t_v_f_get_total_faturacao(TotaisVendasFaturacao t_v_f);

void t_v_f_set_limites(TotaisVendasFaturacao t_v_f, int minMonth, int maxMonth);

void get_totais(void* key, void* produto, void* t_v_f);

typedef struct top_produtos* TopProdutos;

TopProdutos make_top_produtos(int limit);

GPtrArray* top_produtos_get_produtos(TopProdutos top_produtos);

int produtos_comparator(void const* p1, void const* p2);

int produtos_comparator_id(void const* prod1, void const* prod2);

void adiciona_produtos(void* key, void* value, void* user_data);

void set_info_produtos(void* value, void* user_data);

char* i_p_get_codigo_produto(InformacaoProduto i_p);

int i_p_get_numero_compradores(InformacaoProduto i_p);

int i_p_get_numero_vendido_filial(InformacaoProduto i_p, int filial);

#endif
