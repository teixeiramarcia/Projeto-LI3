#ifndef VENDAS_H
#define VENDAS_H

#include "sgv.h"

typedef struct venda {
    char *codigo_produto;
    double preco_unitario;
    int unidades;
    char tipo_de_compra;
    char *codigo_cliente;
    int mes;
    int filial;
} *Venda;

void adiciona_venda(char *venda, SGV sgv);

#endif
