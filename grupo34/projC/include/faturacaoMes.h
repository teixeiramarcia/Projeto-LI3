#ifndef FATURACAOMES_H
#define FATURACAOMES_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "venda.h"
#include "types.h"

typedef struct faturacaoMes* FaturacaoMes;

FaturacaoMes make_faturacao_mes();

void update_faturacao_mes(FaturacaoMes fmes, Venda venda);

double faturacao_mes_get_faturacao_promocao(FaturacaoMes fmes);

int faturacao_mes_get_total_promocao(FaturacaoMes fmes);

double faturacao_mes_get_faturacao_normal(FaturacaoMes fmes);

int faturacao_mes_get_total_normal(FaturacaoMes fmes);

GPtrArray* faturacao_mes_get_vendas_normal(FaturacaoMes fmes);

GPtrArray* faturacao_mes_get_vendas_promocao(FaturacaoMes fmes);

bool faturacao_nao_faturou(FaturacaoMes fmes);

void destroy_faturacao_mes(FaturacaoMes fmes);

#endif
