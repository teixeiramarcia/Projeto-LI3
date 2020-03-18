#include "filiais.h"

Filial make_filial() {
    Filial filial = (Filial) malloc(sizeof(struct filial));
    for (int i = 0; i < 12; i++) {
        filial->fmes[i] = make_faturacao_mes();
    }
    return filial;
}
