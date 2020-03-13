#ifndef VENDAS_H
#define VENDAS_H
#include "produtos.h"
#include "clientes.h"
#include <stdbool.h>

#define LENGTH_CODIGO_P 6
#define LENGTH_CODIGO_C 5

enum tipo_venda {
    venda_normal,
    venda_promo
};

enum mes {
    janeiro,
    fevereiro,
    marco,
    abril,
    maio,
    junho,
    julho,
    agosto,
    setembro,
    outubro,
    novembro,
    dezembro
};

enum filial {
    filial_1,
    filial_2,
    filial_3,
};

typedef struct venda {
    char codigo_produto[LENGTH_CODIGO_P];
    double preco;
    int unidades_compradas;
    enum tipo_venda tipo_venda;
    char codigo_cliente[LENGTH_CODIGO_C];
    enum mes mes_venda;
    enum filial filial;
} Venda;

bool valida_venda (char *l, Produtos p, Clientes c);

/* FIXME
typedef struct vendas_ {
    //coisa para armazenar Venda
} Vendas_;
*/

typedef struct vendas {	
    char **validos;
    size_t num;
} Vendas;

#endif
