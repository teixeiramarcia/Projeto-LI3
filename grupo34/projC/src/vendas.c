#include <ctype.h>
#include "util.h"
#include "vendas.h"
#include "produtos.h"
#include "clientes.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct venda {
    char* codigo_produto;
    double preco_unitario;
    int unidades;
    char tipo_de_compra;
    char* codigo_cliente;
    Month mes;
    FilialID filial;
} * Venda;

char* venda_get_codigo_produto(Venda venda) {
    return venda->codigo_produto;
}

double venda_get_preco_unitario(Venda venda) {
    return venda->preco_unitario;
}

int venda_get_unidades(Venda venda) {
    return venda->unidades;
}

char venda_get_tipo_compra(Venda venda) {
    return venda->tipo_de_compra;
}

char* venda_get_codigo_cliente(Venda venda) {
    return venda->codigo_cliente;
}

Month venda_get_mes(Venda venda) {
    return venda->mes;
}

FilialID venda_get_filial(Venda venda) {
    return venda->filial;
}

void guarda_cliente(Venda venda, GHashTable* vendas_n) {
    g_hash_table_add(vendas_n, venda_get_codigo_cliente(venda));
}

bool is_number(char* s) {
    for (int i = 0; s[i] != '\0' && s[i] != '\n' && s[i] != '\r'; i++) {
        if (!isdigit(s[i]))
            return false;
    }
    return true;
}

bool is_price(char* s) {
    char* rest = strdup(s);

    bool res = is_number(strtok_r(rest, ".", &rest));
    res &= is_number(strtok_r(rest, ".", &rest));
    res &= (strtok_r(rest, ".", &rest) == NULL);
    return res;
}

Venda valida_venda(Produtos prods, Clientes clientes, char* l) {
    Venda venda = (Venda) malloc(sizeof(struct venda));

    int res = 0;
    l = strdup(l);
    char* token = strtok(l, " ");
    for (int i = 0; token != NULL; i++) {
        switch (i) {
            case 0:
                if (valida_produto(token) && existe_produto(prods, token)) {
                    res++;
                    venda->codigo_produto = token;
                }
                break;
            case 1:

                if (is_price(token)) {
                    res++;
                    venda->preco_unitario = atof(token);
                }
                break;
            case 2:
                if (is_number(token) && (atoi(token) >= 1 && atoi(token) <= 200)) {
                    res++;
                    venda->unidades = atoi(token);
                }
                break;
            case 3:
                if (token[0] == 'P' || token[0] == 'N') {
                    res++;
                    venda->tipo_de_compra = token[0];
                }
                break;
            case 4:
                if (valida_cliente(token) && existe_cliente(clientes, token)) {
                    res++;
                    venda->codigo_cliente = token;
                }
                break;
            case 5:
                if (is_number(token) && (atoi(token) >= 1 && atoi(token) <= 12)) {
                    res++;
                    venda->mes = INT_2_MONTH(atoi(token));
                }
                break;
            case 6:
                if (is_number(token) && (atoi(token) >= 1 && atoi(token) <= 3)) {
                    res++;
                    venda->filial = INT_2_FILIAL(atoi(token));
                }
                break;
            default:
                return false;
        }
        token = strtok(NULL, " ");
    }
    if (res != 7) {
        free(venda);
        return NULL;
    } else return venda;
}


