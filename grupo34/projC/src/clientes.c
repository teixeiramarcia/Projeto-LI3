#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "clientes.h"
#include "vendas.h"

typedef struct produtoCli {
    char* prodID;
    int quantidade;
    double faturacao;
} * ProdutoCli;

typedef struct filiaisCli {
    int quantidade;
    GHashTable* produtos[12];
} * FiliaisCli;

typedef struct cliente {
    char* clienteID;
    FiliaisCli filiaisCli[N_FILIAIS];
} * Cliente;

typedef struct clientes {
    GHashTable* clientes;
} * Clientes;

Clientes make_clientes() {
    Clientes clientes = (Clientes) malloc(sizeof(struct clientes));
    clientes->clientes = g_hash_table_new_full(g_str_hash, str_compare, free, (GDestroyNotify) destroy_cliente);
    return clientes;
}

char* cliente_get_cliente_id(Cliente cliente) {
    return cliente->clienteID;
}

FiliaisCli cliente_get_filial(Cliente c, int branch) {
    return c->filiaisCli[branch];
}

int filiais_cli_get_quantidade(FiliaisCli fcli) {
    return fcli->quantidade;
}

void filiais_cli_set_quantidade(FiliaisCli fcli, int qtd) {
    int a = filiais_cli_get_quantidade(fcli);
    fcli->quantidade = a + qtd;
}

GHashTable* filiais_cli_get_mes(FiliaisCli fcli, int mes) {
    return fcli->produtos[mes];
}

bool valida_cliente(char* l) {
    if (isupper(l[0])) {
        return valida_codigo(l + 1) && (atoi(l + 1) >= 1000 && atoi(l + 1) <= 5000);
    }
    return false;
}

bool existe_cliente(Clientes c, char* cliente) {
    return g_hash_table_contains(c->clientes, cliente);
}

bool adiciona_cliente(Clientes clis, char* cliID, int* validos) {
    if (valida_cliente(cliID) && !existe_cliente(clis, cliID)) {
        (*validos)++;
        Cliente cliente = (Cliente) malloc(sizeof(struct cliente));
        cliente->clienteID = strdup(cliID);
        for (int j = 0; j < N_FILIAIS; ++j) {
            cliente->filiaisCli[j] = (FiliaisCli) malloc(sizeof(struct filiaisCli));
            cliente->filiaisCli[j]->quantidade = 0;
            for (int i = 0; i < 12; i++) {
                cliente->filiaisCli[j]->produtos[i] = g_hash_table_new_full(g_str_hash, str_compare, free, free);

            }
        }
        return g_hash_table_insert(clis->clientes, cliente->clienteID, cliente);
    }
    return false;
}

GHashTable* clientes_get_clientes(Clientes clientes) {
    return clientes->clientes;
}

Cliente clientes_get_cliente(GHashTable* clientes, char* clienteID) {
    return g_hash_table_lookup(clientes, clienteID);
}

void clientes_procurarCli(void* clienteID, void* cliente, void* resCli) {
    (void) clienteID;
    Cliente cliente_ = (Cliente) cliente;
    int* resCli_ = (int*) resCli;
    int count = 0;
    for (int i = 0; i < N_FILIAIS; i++) {
        if (cliente_->filiaisCli[i]->quantidade == 0) {
            count++;
        }
    }
    if (count == N_FILIAIS) {
        (*resCli_)++;
    }
}

void update_clientes(Clientes clientes, Venda venda) {
    char* codigo_cliente = venda_get_codigo_cliente(venda);
    Cliente cliente = g_hash_table_lookup(clientes->clientes, codigo_cliente);
    int qtd = filiais_cli_get_quantidade(cliente->filiaisCli[venda_get_filial(venda)]);
    int qtd_new = qtd + venda_get_unidades(venda);
    filiais_cli_set_quantidade(cliente->filiaisCli[venda_get_filial(venda)], qtd_new);
    ProdutoCli pcli = g_hash_table_lookup(cliente->filiaisCli[venda_get_filial(venda)]->produtos[venda_get_mes(venda)],
                                          venda_get_codigo_produto(venda));
    if (pcli == NULL) {
        pcli = (ProdutoCli) malloc(sizeof(struct produtoCli));
        pcli->prodID = venda_get_codigo_produto(venda);
        pcli->quantidade = venda_get_unidades(venda);
        pcli->faturacao = venda_get_preco_unitario(venda) * venda_get_unidades(venda);
        g_hash_table_insert(cliente->filiaisCli[venda_get_filial(venda)]->produtos[venda_get_mes(venda)], pcli->prodID,
                            pcli);
    } else {
        pcli->quantidade += venda_get_unidades(venda);
        pcli->faturacao += venda_get_preco_unitario(venda) * venda_get_unidades(venda);
    }
}

void destroy_clientes(Clientes clientes) {
    g_hash_table_destroy(clientes->clientes);
    free(clientes);
}

void destroy_filiais_cli(FiliaisCli fcli) {
    for (int i = 0; i < 12; ++i) {
        g_hash_table_destroy(fcli->produtos[i]);
    }
    free(fcli);
}

void destroy_cliente(Cliente cliente) {
    for (int i = 0; i < N_FILIAIS; ++i) {
        destroy_filiais_cli(cliente->filiaisCli[i]);
    }
    free(cliente);
}

typedef struct produtos_comprados_cliente {
    int n_produtos_comprados[N_FILIAIS][N_MONTHS];
} * ProdutosCompradosCliente;

ProdutosCompradosCliente make_produtos_comprados_cliente() {
    return malloc(sizeof(struct produtos_comprados_cliente));
}

int* p_c_c_get_n_produtos_comprados(ProdutosCompradosCliente p_c_c, int filial, int month) {
    return &p_c_c->n_produtos_comprados[filial][month];
}

void get_quantidade(void* key, void* produto, void* result) {
    ProdutoCli pcli = (ProdutoCli) produto;
    int* res = (int*) result;
    *res += pcli->quantidade;
}

int get_total_compras(GHashTable* mes) {
    int result = 0;
    g_hash_table_foreach(mes, get_quantidade, &result);
    return result;
}

void cliente_fez_compras_todas_filiais(void* key, void* value, void* user_data) {
    char* clienteID = (char*) key;
    Cliente cliente = (Cliente) value;
    GPtrArray* clientes_resultado = (GPtrArray*) user_data;
    int r = 0;
    for (int i = 0; i < N_FILIAIS; i++) {
        FiliaisCli fcli = cliente_get_filial(cliente, i);
        if (filiais_cli_get_quantidade(fcli) != 0) {
            r++;
        }
    }
    if (r == 3) {
        g_ptr_array_add(clientes_resultado, clienteID);
    }
}

int clientes_comparator(void const* cli1, void const* cli2) {
    char* clienteID1 = *((char**) cli1);
    char* clienteID2 = *((char**) cli2);
    for (int i = 0; i < 5; ++i) {
        int dif = clienteID1[i] - clienteID2[i];
        if (dif != 0) {
            return dif;
        }
    }
    return 0;
}

typedef struct produto_quantidade {
    char* productID;
    int quantidade;
} * ProdutoQuantidade;

char* p_q_get_ID(ProdutoQuantidade p_q) {
    return p_q->productID;
}

void get_produto_quantidade(void* key, void* value, void* user_data) {
    char* productID = (char*) key;
    ProdutoCli produto = (ProdutoCli) value;
    GHashTable* resultado = (GHashTable*) user_data;
    if (!g_hash_table_contains(resultado, productID)) {
        ProdutoQuantidade p_q = malloc(sizeof(struct produto_quantidade));
        p_q->productID = productID;
        p_q->quantidade = produto->quantidade;
        g_hash_table_insert(resultado, productID, p_q);
    } else {
        ProdutoQuantidade p_q = g_hash_table_lookup(resultado, productID);
        p_q->quantidade += produto->quantidade;
    }
}

void adiciona_produto_quantidade(void* key, void* value, void* user_data) {
    ProdutoQuantidade p_q = (ProdutoQuantidade) value;
    GPtrArray* resultado = (GPtrArray*) user_data;
    g_ptr_array_add(resultado, p_q);
}

int produtos_cli_comparator(void const* prod_1, void const* prod_2) {
    ProdutoQuantidade produto_1 = *((ProdutoQuantidade*) prod_1);
    ProdutoQuantidade produto_2 = *((ProdutoQuantidade*) prod_2);
    int quantidade_1 = produto_1->quantidade;
    int quantidade_2 = produto_2->quantidade;
    return quantidade_2 - quantidade_1;
}

typedef struct produto_faturacao {
    char* prodID;
    double faturacao;
} * ProdutoFaturacao;

void adiciona_produtos_q12(void* key, void* value, void* user_data) {
    char* productID = (char*) key;
    ProdutoCli prod_cli = (ProdutoCli) value;
    GHashTable* resultado = (GHashTable*) user_data;
    if (g_hash_table_contains(resultado, prod_cli->prodID)) {
        ProdutoFaturacao produto_faturacao = g_hash_table_lookup(resultado, prod_cli->prodID);
        produto_faturacao->faturacao += prod_cli->faturacao;
    } else {
        ProdutoFaturacao produto_faturacao = malloc(sizeof(struct produto_faturacao));
        produto_faturacao->prodID = productID;
        produto_faturacao->faturacao = prod_cli->faturacao;
        g_hash_table_insert(resultado, prod_cli->prodID, produto_faturacao);
    }
}

int produtos_cliente_comparator(void const* prod_1, void const* prod_2) {
    ProdutoFaturacao p1 = *((ProdutoFaturacao*) prod_1);
    ProdutoFaturacao p2 = *((ProdutoFaturacao*) prod_2);
    double faturacao_p1 = p1->faturacao;
    double faturacao_p2 = p2->faturacao;
    if (faturacao_p2 > faturacao_p1) {
        return 1;
    } else if (faturacao_p2 < faturacao_p1) {
        return -1;
    }
    return 0;
}

void set_info_produtos_cliente(void* value, void* user_data) {
    ProdutoFaturacao produto = (ProdutoFaturacao) value;
    GPtrArray* resultado = (GPtrArray*) user_data;
    g_ptr_array_add(resultado, produto->prodID);
}

ProdutoFaturacao get_maior(GList* lista) {
    ProdutoFaturacao p_f = malloc(sizeof(struct produto_faturacao));
    p_f->prodID = "";
    p_f->faturacao = -1;
    for (int i = 0; i < g_list_length(lista); ++i) {
        ProdutoFaturacao produto = g_list_nth_data(lista, i);
        if (produto->faturacao > p_f->faturacao) {
            char* id = p_f->prodID;
            double faturacao = p_f->faturacao;
            p_f->prodID = produto->prodID;
            p_f->faturacao = produto->faturacao;
            produto->prodID = id;
            produto->faturacao = faturacao;
        }
    }
    return p_f;
}
