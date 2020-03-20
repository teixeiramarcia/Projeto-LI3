#include <ctype.h>
#include "sgv.h"
#include "util.h"
#include "vendas.h"

bool is_number(char *s) {
    for (int i = 0; s[i] != '\0' && s[i] != '\n' && s[i] != '\r'; i++) {
        if (!isdigit(s[i]))
            return false;
    }
    return true;
}

bool is_price(char *s) {
    char *rest = s;

    bool res = is_number(strtok_r(rest, ".", &rest));
    res &= is_number(strtok_r(rest, ".", &rest));
    res &= (strtok_r(rest, ".", &rest) == NULL);
    return res;
}

Venda valida_venda(char *l, SGV sgv) {
    Venda venda = (Venda) malloc(sizeof(struct venda));

    int res = 0;
    l = strdup(l);
    char *token = strtok(l, " ");
    for (int i = 0; token != NULL; i++) {
        switch (i) {
            case 0:
                if (valida_produto(token) && existe_produto(sgv->produtos, token)) {
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
                if (valida_cliente(token) && existe_cliente(sgv->clientes, token)) {
                    res++;
                    venda->codigo_cliente = token;
                }
                break;
            case 5:
                if (is_number(token) && (atoi(token) >= 1 && atoi(token) <= 12)) {
                    res++;
                    venda->mes = atoi(token);
                }
                break;
            case 6:
                if (is_number(token) && (atoi(token) >= 1 && atoi(token) <= 3)) {
                    res++;
                    venda->filial = atoi(token);
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

void adiciona_venda(char *venda, SGV sgv) {
    Venda v = valida_venda(venda, sgv);

    if (v == NULL) {
        return;
    }

    Produto p = g_hash_table_lookup(sgv->produtos->produtos[v->codigo_produto[0] - 'A'], v->codigo_produto);
    FaturacaoMes fmes = p->filiais[v->filial - 1]->fmes[v->mes - 1];

    if (v->tipo_de_compra == 'P') {
        fmes->faturacao_promocao += v->preco_unitario * v->unidades;
        fmes->total_promocao += v->unidades;
        g_ptr_array_add(fmes->vendas_promocao, v);
    } else {
        fmes->faturacao_normal += v->preco_unitario * v->unidades;
        fmes->total_normal += v->unidades;
        g_ptr_array_add(fmes->vendas_normal, v);
    }

    Cliente c = g_hash_table_lookup(sgv->clientes->clientes, v->codigo_cliente);
    FiliaisCli a = c->filiaisCli[v->filial - 1];
    a->quantidade += v->unidades;
    GHashTable *b = a->produtos[v->mes - 1];
    ProdutoCli produto = g_hash_table_lookup(b, v->codigo_produto);
    if (produto == NULL) {
        produto = (ProdutoCli) malloc(sizeof(struct produtoCli));
        produto->quantidade = v->unidades;
        produto->faturacao = v->preco_unitario * v->unidades;
        produto->prodID = v->codigo_produto;
        g_hash_table_insert(b, produto->prodID, produto);
    } else {
        produto->quantidade += v->unidades;
        produto->faturacao += v->preco_unitario * v->unidades;
    }
}
