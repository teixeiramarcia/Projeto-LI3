#ifndef FILIAIS_H
#define FILIAIS_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "faturacaoMes.h"

typedef struct filial {
    FaturacaoMes fmes[12];
} *Filial;

Filial make_filial();

#endif
