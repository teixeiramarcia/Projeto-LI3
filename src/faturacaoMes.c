#include "faturacaoMes.h"

FaturacaoMes make_faturacao_mes(){
    FaturacaoMes fat_mes = (FaturacaoMes) malloc(sizeof(struct faturacaoMes));
    fat_mes->faturacao_promocao = 0;
    fat_mes->total_promocao = 0;
    fat_mes->faturacao_normal = 0;
    fat_mes->total_normal = 0;
    fat_mes->vendas_promocao = g_ptr_array_new();
    fat_mes->vendas_normal = g_ptr_array_new();
    return fat_mes;
}
