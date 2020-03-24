#include "types.h"
#include "filiais.h"
#include "vendas.h"
#include "month.h"

typedef struct filial {
    FaturacaoMes fmes[12];
} * Filial;

Filial make_filial() {
    Filial filial = (Filial) malloc(sizeof(struct filial));
    for (int i = 0; i < 12; i++) {
        filial->fmes[i] = make_faturacao_mes();
    }
    return filial;
}

void update_filial(Filial filial, Venda venda) {
    update_faturacao_mes(filial->fmes[venda_get_mes(venda)], venda);
}

FaturacaoMes filial_get_faturacao_mes(Filial filial, Month month) {
    return filial->fmes[month];
}

void destroy_filial(Filial filial) {
    for (int i = 0; i < 12; ++i) {
        destroy_faturacao_mes(filial->fmes[i]);
    }
    free(filial);
}
