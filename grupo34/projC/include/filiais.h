#ifndef FILIAIS_H
#define FILIAIS_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "faturacaoMes.h"
#include "vendas.h"
#include "types.h"
#include "month.h"

typedef struct filial* Filial;

Filial make_filial();

void update_filial(Filial filial, Venda venda);

FaturacaoMes filial_get_faturacao_mes(Filial filial, Month month);

void destroy_filial(Filial filial);

#endif
