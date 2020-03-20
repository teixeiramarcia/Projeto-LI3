#include <stdio.h>
#include <ctype.h>
#include "util.h"
#include "produtos.h"
#include "month.h"
#include "filialID.h"

typedef struct produto {
    char *produtoID;
    Filial filiais[sizeof(FILIAIS)];
} *Produto;

typedef struct produtos {
    GHashTable *produtos[('Z' - 'A') + 1];
} *Produtos;

Produtos make_produtos() {
    Produtos p = (Produtos) malloc(sizeof(struct produtos));
    for (int i = 0; i < (('Z' - 'A') + 1); i++) {
        p->produtos[i] = g_hash_table_new_full(g_str_hash, str_compare, free, (GDestroyNotify) destroy_produto);
    }
    return p;
}

bool valida_produto(char *l) {
    if (isupper(l[0]) && isupper(l[1])) {
        return valida_codigo(l + 2);
    }
    return false;
}

char* produto_get_poductID(Produto prod){
    return prod->produtoID;
}

Filial produto_get_filial(Produto prod, FilialID branchID){
    return prod->filiais[branchID];
}

Produto produtos_get_produto(Produtos prods, char* prodID){
    return g_hash_table_lookup(prods->produtos[prodID[0]-'A'], prodID);
}

void produtos_foreach_started_by(Produtos prods, char c, GHFunc func, gpointer user_data) {
    g_hash_table_foreach(prods->produtos[c - 'A'], func, user_data);
}

Filial produtos_get_filial(Produtos prods, char* prodID, FilialID branchID){
    return produto_get_filial(produtos_get_produto(prods, prodID), branchID);
}

typedef struct produtos_e_totais_1filial {
    FilialID branchID;
    GHashTable* produtos;
    int total;
} *ProdutosETotais1Filial;

GHashTable *produtos_e_totais_1filial_get_produtos(ProdutosETotais1Filial p_e_t_1f) {
    return p_e_t_1f->produtos;
}

int produtos_e_totais_1filial_get_total(ProdutosETotais1Filial p_e_t_1f) {
    return p_e_t_1f->total;
}

void verifica_produto_nao_comprado_1filial(void* key, void* value, void* produtos_e_totais_1filial) {
    char* key_ = (char*) key;
    Produto value_ = (Produto) value;
    ProdutosETotais1Filial produtos_e_totais_1filial_ = (ProdutosETotais1Filial) produtos_e_totais_1filial;
    for (int i = 0; i < sizeof(MONTHS); i++) {
        Filial filial = value_->filiais[(produtos_e_totais_1filial_->branchID)];
        FaturacaoMes fmes = filial_get_faturacao_mes(filial, MONTHS[i]);
        if(faturacao_nao_faturou(fmes)){
            g_hash_table_add(produtos_e_totais_1filial_->produtos, key_);
            produtos_e_totais_1filial_->total++;
        }
    }
}

typedef struct produtos_e_totais {
    GHashTable* produtos_filial[sizeof(FILIAIS)];
    int total;
} *ProdutosETotais;

int produtos_e_totais_get_total(ProdutosETotais p_e_t) {
    return p_e_t->total;
}

void verifica_produto_nao_comprado_todas(void* key, void* value, void* p_e_t){
    char* key_ = (char*) key;
    Produto value_ = (Produto) value;
    ProdutosETotais p_e_t_ = (ProdutosETotais) p_e_t;
    for (int filial = 0; filial < sizeof(FILIAIS); filial++)
        for (int month = 0; month < sizeof(MONTHS); month++) {
            int total_promocao = faturacao_mes_get_total_promocao(
                    filial_get_faturacao_mes(produto_get_filial(value_, FILIAIS[filial]), month/*MONTHS[month]*/));
            int total_normal = faturacao_get_total_normal(
                    filial_get_faturacao_mes(produto_get_filial(value_, FILIAIS[filial]), MONTHS[month]));
            if (total_promocao == 0 && total_normal == 0) {
                g_hash_table_add(p_e_t_->produtos_filial[FILIAIS[filial]], key_);
                p_e_t_->total++;
            }
        }
}

typedef struct produtos_e_totais_helper {
    GPtrArray* prods;
    ProdutosETotais p_e_t;
} *ProdutosETotaisHelper;

GPtrArray *produtos_e_totais_helper_get_produtos(ProdutosETotaisHelper p_e_t_h) {
    return p_e_t_h->prods;
}

ProdutosETotais produtos_e_totais_helper_get_produtos_e_totais(ProdutosETotaisHelper p_e_t_h) {
    return p_e_t_h->p_e_t;
}

void intersection(void* key, void* value, void* res){
    (void) value;
    char* key_ = (char*) key;
    ProdutosETotaisHelper res_ = (ProdutosETotaisHelper) res;
    GHashTable* prods_f2 = res_->p_e_t->produtos_filial[1];
    GHashTable* prods_f3 = res_->p_e_t->produtos_filial[2];
    if(g_hash_table_contains(prods_f2, key_) && g_hash_table_contains(prods_f3, key_)){
        g_ptr_array_add(res_->prods, key_);
    }
}

ProdutosETotaisHelper produtos_foreach_never_bought_t(Produtos prods) {
    ProdutosETotais produtos_e_totais = malloc(sizeof(struct produtos_e_totais));
    for (int filial = 0; filial < sizeof(FILIAIS); ++filial) {
        produtos_e_totais->produtos_filial[FILIAIS[filial]] = g_hash_table_new(g_str_hash, str_compare);
    }
    for (int j = 0; j < ('Z'-'A')+1; ++j) {
        g_hash_table_foreach(prods->produtos[j], verifica_produto_nao_comprado_todas, produtos_e_totais);
    }
    ProdutosETotaisHelper result = malloc(sizeof(struct produtos_e_totais_helper));
    result->prods = g_ptr_array_new();
    result->p_e_t = produtos_e_totais;
    g_hash_table_foreach(produtos_e_totais->produtos_filial[0], intersection, result);
    return result;
}

ProdutosETotais1Filial produtos_foreach_never_bought_1f(Produtos prods, FilialID branchID) {
    ProdutosETotais1Filial produtos_e_totais_1filial = malloc(sizeof(struct produtos_e_totais_1filial));
    produtos_e_totais_1filial->produtos = g_hash_table_new(g_str_hash, str_compare);
    produtos_e_totais_1filial->total = 0;
    produtos_e_totais_1filial->branchID = branchID;
    for (int i = 0; i < ('Z'-'A')+1; ++i) {
        g_hash_table_foreach(prods->produtos[i], verifica_produto_nao_comprado_1filial, produtos_e_totais_1filial);
    }
    return produtos_e_totais_1filial;
}


void update_produtos(Produtos prods, Venda venda){
    Produto prod = g_hash_table_lookup(prods->produtos[venda_get_codigo_produto(venda)[0] - 'A'], venda_get_codigo_produto(venda));
    update_filial(prod->filiais[venda_get_filial(venda)], venda);
}

bool adiciona_produto(Produtos prod, char *produto) {
    if (valida_produto(produto) && !existe_produto(prod, produto)) {
        char l = produto[0];
        Produto p = (Produto) malloc(sizeof(struct produto));
        p->produtoID = strdup(produto);
        for (int i = 0; i < sizeof(FILIAIS); ++i) {
            p->filiais[i] = make_filial();
        }

        return g_hash_table_insert(prod->produtos[l - 'A'], p->produtoID, p);
    }
    return false;
}

bool existe_produto(Produtos p, char *produto) {
    char l = produto[0];
    return g_hash_table_contains(p->produtos[l - 'A'], produto);
}

void destroy_produtos(Produtos produtos) {
    for (int i = 0; i < ('Z'-'A')+1; i++) {
        g_hash_table_destroy(produtos->produtos[i]);
    }
    free(produtos);
}

void destroy_produto(Produto produto) {
    for (int i = 0; i < sizeof(FILIAIS); ++i) {
        destroy_filial(produto->filiais[i]);
    }
    free(produto);
}
