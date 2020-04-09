#include "faturacaoMes.h"
#include "venda.h"

typedef struct faturacaoMes {
    double faturacao_promocao;
    int total_promocao;
    double faturacao_normal;
    int total_normal;
    GPtrArray* vendas_promocao;
    GPtrArray* vendas_normal;
} * FaturacaoMes;

FaturacaoMes make_faturacao_mes() {
    FaturacaoMes fat_mes = malloc(sizeof(struct faturacaoMes));
    fat_mes->faturacao_promocao = 0;
    fat_mes->total_promocao = 0;
    fat_mes->faturacao_normal = 0;
    fat_mes->total_normal = 0;
    fat_mes->vendas_promocao = g_ptr_array_new_with_free_func(destroy_venda);
    fat_mes->vendas_normal = g_ptr_array_new_with_free_func(destroy_venda);
    return fat_mes;
}

bool faturacao_nao_faturou(FaturacaoMes fmes) {
    return (fmes->faturacao_normal == 0) && (fmes->faturacao_promocao == 0);
}

void update_faturacao_mes(FaturacaoMes fmes, Venda venda) {
    if (venda_get_tipo_compra(venda) == 'P') {
        fmes->faturacao_promocao += venda_get_preco_unitario(venda) * venda_get_unidades(venda);
        fmes->total_promocao += venda_get_unidades(venda);
        g_ptr_array_add(fmes->vendas_promocao, venda);
    } else {
        fmes->faturacao_normal += venda_get_preco_unitario(venda) * venda_get_unidades(venda);
        fmes->total_normal += venda_get_unidades(venda);
        g_ptr_array_add(fmes->vendas_normal, venda);
    }
}

double faturacao_mes_get_faturacao_promocao(FaturacaoMes fmes) {
    return fmes->faturacao_promocao;
}

int faturacao_mes_get_total_promocao(FaturacaoMes fmes) {
    return fmes->total_promocao;
}

double faturacao_mes_get_faturacao_normal(FaturacaoMes fmes) {
    return fmes->faturacao_normal;
}

int faturacao_mes_get_total_normal(FaturacaoMes fmes) {
    return fmes->total_normal;
}

GPtrArray* faturacao_mes_get_vendas_normal(FaturacaoMes fmes) {
    return fmes->vendas_normal;
}

GPtrArray* faturacao_mes_get_vendas_promocao(FaturacaoMes fmes) {
    return fmes->vendas_promocao;
}

void destroy_faturacao_mes(FaturacaoMes fmes) {
    g_ptr_array_free(fmes->vendas_promocao, TRUE);
    g_ptr_array_free(fmes->vendas_normal, TRUE);
    free(fmes);
}
