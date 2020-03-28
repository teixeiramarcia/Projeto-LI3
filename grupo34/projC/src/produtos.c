#include <ctype.h>
#include "util.h"
#include "produtos.h"
#include "month.h"
#include "filialID.h"


typedef struct produto {
    char* produtoID;
    Filial filiais[N_FILIAIS];
} * Produto;

typedef struct produtos {
    GHashTable* produtos[('Z' - 'A') + 1];
} * Produtos;

Produtos make_produtos() {
    Produtos p = (Produtos) malloc(sizeof(struct produtos));
    for (int i = 0; i < (('Z' - 'A') + 1); i++) {
        p->produtos[i] = g_hash_table_new_full(g_str_hash, str_compare, free, (GDestroyNotify) destroy_produto);
    }
    return p;
}

GHashTable* produtos_get_produtos_letra(Produtos prods, int letra) {
    return prods->produtos[letra];
}

bool valida_produto(char* l) {
    if (isupper(l[0]) && isupper(l[1])) {
        return valida_codigo(l + 2);
    }
    return false;
}

Filial produto_get_filial(Produto prod, FilialID branchID) {
    return prod->filiais[branchID];
}

Produto produtos_get_produto(Produtos prods, char* prodID) {
    return g_hash_table_lookup(prods->produtos[prodID[0] - 'A'], prodID);
}

void produtos_foreach_started_by(Produtos prods, char c, GHFunc func, gpointer user_data) {
    g_hash_table_foreach(prods->produtos[c - 'A'], func, user_data);
}

Filial produtos_get_filial(Produtos prods, char* prodID, FilialID branchID) {
    return produto_get_filial(produtos_get_produto(prods, prodID), branchID);
}

void update_produtos(Produtos prods, Venda venda) {
    Produto prod = g_hash_table_lookup(prods->produtos[venda_get_codigo_produto(venda)[0] - 'A'],
                                       venda_get_codigo_produto(venda));
    update_filial(prod->filiais[venda_get_filial(venda)], venda);
}

char* produto_get_productID(Produto prod) {
    return prod->produtoID;
}

bool adiciona_produto(Produtos prod, char* produto, int* validos) {
    if (valida_produto(produto) && !existe_produto(prod, produto)) {
        (*validos)++;
        char l = produto[0];
        Produto p = (Produto) malloc(sizeof(struct produto));
        p->produtoID = strdup(produto);
        for (int i = 0; i < N_FILIAIS; ++i) {
            p->filiais[i] = make_filial();
        }

        return g_hash_table_insert(prod->produtos[l - 'A'], p->produtoID, p);
    }
    return false;
}

bool existe_produto(Produtos p, char* produto) {
    char l = produto[0];
    return g_hash_table_contains(p->produtos[l - 'A'], produto);
}

void destroy_produtos(Produtos produtos) {
    for (int i = 0; i < ('Z' - 'A') + 1; i++) {
        g_hash_table_destroy(produtos->produtos[i]);
    }
    free(produtos);
}

void destroy_produto(Produto produto) {
    for (int i = 0; i < N_FILIAIS; ++i) {
        destroy_filial(produto->filiais[i]);
    }
    free(produto);
}

typedef struct produtos_nunca_vendidos {
    int de_filial;
    int ate_filial;
    GHashTable* produtos_n_vendidos;
} * ProdutosNuncaVendidos;

ProdutosNuncaVendidos make_produtos_nunca_vendidos() {
    ProdutosNuncaVendidos p_n_v = malloc(sizeof(struct produtos_nunca_vendidos));
    p_n_v->produtos_n_vendidos = g_hash_table_new(g_str_hash, str_compare);
    return p_n_v;
}

GHashTable* p_n_v_get_produtos_n_vendidos(ProdutosNuncaVendidos p_n_v) {
    return p_n_v->produtos_n_vendidos;
}

void set_de_e_ate_filial_p_n_v(ProdutosNuncaVendidos p_n_v, int from_branch, int to_branch) {
    p_n_v->de_filial = from_branch;
    p_n_v->ate_filial = to_branch;
}

void guarda_se_nao_foi_vendido(void* key, void* value, void* user_data) {
    char* productID = (char*) key;
    Produto produto = (Produto) value;
    ProdutosNuncaVendidos p_n_v = (ProdutosNuncaVendidos) user_data;
    int ja_foi_vendido = 0;
    for (int i = p_n_v->de_filial; i <= p_n_v->ate_filial && ja_foi_vendido == 0; i++) {
        for (int j = 0; j < N_MONTHS && ja_foi_vendido == 0; j++) {
            FaturacaoMes fmes = filial_get_faturacao_mes(produto_get_filial(produto, i), j);
            if (!faturacao_nao_faturou(fmes)) {
                ja_foi_vendido++;
            }
        }
    }
    if (ja_foi_vendido == 0) {
        g_hash_table_add(p_n_v->produtos_n_vendidos, productID);
    }
}

typedef struct totais_vendas_faturacao {
    int total_vendas;
    double total_faturacao;
    int de_mes;
    int ate_mes;
} * TotaisVendasFaturacao;

TotaisVendasFaturacao make_totais_vendas_faturacao() {
    TotaisVendasFaturacao t_v_f = malloc(sizeof(struct totais_vendas_faturacao));
    t_v_f->total_vendas = 0;
    t_v_f->total_faturacao = 0;
    return t_v_f;
}

int t_v_f_get_total_vendas(TotaisVendasFaturacao t_v_f) {
    return t_v_f->total_vendas;
}

double t_v_f_get_total_faturacao(TotaisVendasFaturacao t_v_f) {
    return t_v_f->total_faturacao;
}

void t_v_f_set_total_vendas(TotaisVendasFaturacao t_v_f, int total_vendas) {
    t_v_f->total_vendas += total_vendas;
}

void t_v_f_set_total_faturacao(TotaisVendasFaturacao t_v_f, double total_faturacao) {
    t_v_f->total_faturacao += total_faturacao;
}

void t_v_f_set_limites(TotaisVendasFaturacao t_v_f, int minMonth, int maxMonth) {
    t_v_f->de_mes = INT_2_MONTH(minMonth);
    t_v_f->ate_mes = INT_2_MONTH(maxMonth);
}

int t_v_f_get_from_month(TotaisVendasFaturacao t_v_f) {
    return t_v_f->de_mes;
}

int t_v_f_get_to_month(TotaisVendasFaturacao t_v_f) {
    return t_v_f->ate_mes;
}

void get_totais(void* key, void* produto, void* t_v_f) {
    Produto prod = (Produto) produto;
    TotaisVendasFaturacao t_v_f_ = (TotaisVendasFaturacao) t_v_f;
    int from = t_v_f_get_from_month(t_v_f_);
    int to = t_v_f_get_to_month(t_v_f_);
    for (int filial = 1; filial <= N_FILIAIS; ++filial) {
        for (int mes = from; mes <= to; ++mes) {
            FaturacaoMes fmes = filial_get_faturacao_mes(
                    produto_get_filial(prod, INT_2_FILIAL(filial)), mes);
            int total = faturacao_mes_get_total_promocao(fmes) + faturacao_mes_get_total_normal(fmes);
            double faturacao = faturacao_mes_get_faturacao_promocao(fmes) + faturacao_mes_get_faturacao_normal(fmes);
            t_v_f_set_total_vendas(t_v_f_, total);
            t_v_f_set_total_faturacao(t_v_f_, faturacao);
        }
    }
}

typedef struct top_produtos {
    GPtrArray* produtos;
    int limite;
    int tamanho_atual;
} * TopProdutos;

TopProdutos make_top_produtos(int limit) {
    TopProdutos top_produtos = malloc(sizeof(struct top_produtos));
    top_produtos->produtos = g_ptr_array_new();
    top_produtos->limite = limit;
    top_produtos->tamanho_atual = 0;
    return top_produtos;
}

GPtrArray* top_produtos_get_produtos(TopProdutos top_produtos) {
    return top_produtos->produtos;
}

int get_vendas_produto(Produto produto) {
    int vendas = 0;
    for (int filial = 0; filial < N_FILIAIS; ++filial) {
        Filial filial_p = produto_get_filial(produto, filial);
        for (int mes = 0; mes < N_MONTHS; ++mes) {
            FaturacaoMes fmes = filial_get_faturacao_mes(filial_p, mes);
            vendas += faturacao_mes_get_total_normal(fmes) + faturacao_mes_get_total_promocao(fmes);
        }
    }
    return vendas;
}

int produtos_comparator(void const* prod_1, void const* prod_2) {
    Produto p1 = *((Produto*) prod_1);
    Produto p2 = *((Produto*) prod_2);
    int vendas_p1 = get_vendas_produto(p1);
    int vendas_p2 = get_vendas_produto(p2);
    return vendas_p2 - vendas_p1;
}

void swap_produto_menos_vendido(GPtrArray* top_produtos, int tamanho, Produto produto_novo) {
    for (int i = 0; i < tamanho; i++) {
        Produto produto = g_ptr_array_index(top_produtos, i);
        int vendas_produto = get_vendas_produto(produto);
        int vendas_novo_produto = get_vendas_produto(produto_novo);
        if (vendas_produto < vendas_novo_produto) {
            g_ptr_array_remove_index_fast(top_produtos, i);
            g_ptr_array_add(top_produtos, produto_novo);
            produto_novo = produto;
        }
    }
}

void adiciona_produtos(void* key, void* value, void* user_data) {
    Produto produto = (Produto) value;
    TopProdutos top_produtos = (TopProdutos) user_data;
    if (top_produtos->tamanho_atual < top_produtos->limite) {
        g_ptr_array_add(top_produtos->produtos, produto);
        top_produtos->tamanho_atual++;
    } else {
        swap_produto_menos_vendido(top_produtos->produtos, top_produtos->tamanho_atual, produto);
    }
}


