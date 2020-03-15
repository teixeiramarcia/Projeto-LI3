#ifndef FATURACAOMES_H
#define FATURACAOMES_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>

typedef struct faturacaoMes {
    double faturacao_promocao;
    int total_promocao;
    double faturacao_normal;
    int total_normal;
    GPtrArray* vendas_promocao;
    GPtrArray* vendas_normal;
} *FaturacaoMes;

FaturacaoMes make_faturacao_mes();
#endif
