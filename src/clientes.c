#include <ctype.h>
#include <stdlib.h>
#include "util.h"
#include "clientes.h"
#include "vendas.h"

typedef struct produtoCli {
    char *prodID;
    int quantidade;
    double faturacao;
} *ProdutoCli;

typedef struct filiaisCli {
    int quantidade;
    GHashTable *produtos[12];
} *FiliaisCli;

typedef struct cliente {
    char *clienteID;
    FiliaisCli filiaisCli[sizeof(FILIAIS)];
} *Cliente;

typedef struct clientes {
    GHashTable *clientes;
} *Clientes;

Clientes make_clientes() {
    Clientes clientes = (Clientes) malloc(sizeof(struct clientes));
    clientes->clientes = g_hash_table_new_full(g_str_hash, str_compare, free, (GDestroyNotify) destroy_cliente);
    return clientes;
}

bool valida_cliente(char *l) {
    if (isupper(l[0])) {
        return valida_codigo(l + 1) && (atoi(l + 1) >= 1000 && atoi(l + 1) <= 5000);
    }
    return false;
}

bool existe_cliente(Clientes c, char *cliente) {
    return g_hash_table_contains(c->clientes, cliente);
}

bool adiciona_cliente(Clientes clis, char *cliID) {
    if (valida_cliente(cliID) && !existe_cliente(clis, cliID)) {
        Cliente cliente = (Cliente) malloc(sizeof(struct cliente));
        cliente->clienteID = strdup(cliID);
        for (int j = 0; j < sizeof(FILIAIS); ++j) {
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

GHashTable* clientes_get_clientes(Clientes clientes);

GHashTable *clientes_get_clientes(Clientes clientes) {
    return clientes->clientes;
}

void clientes_procurarCli(void* cliente, void *clienteID, void* resCli) {
    (void) clienteID;
    Cliente cliente_ = (Cliente) cliente;
    int* resCli_ = (int*) resCli;
    int count = 0;
    int i;
    for (i = 0; i< sizeof(FILIAIS); i++){
        if(cliente_->filiaisCli[i]->quantidade == 0) count++;
    }
    if(count== sizeof(FILIAIS)) (*resCli_)++;
}

void update_clientes(Clientes clientes, Venda venda){
    char* codigo_cliente = venda_get_codigo_cliente(venda);
    Cliente cliente = g_hash_table_lookup(clientes->clientes, codigo_cliente);
    ProdutoCli pcli = g_hash_table_lookup(cliente->filiaisCli[venda_get_filial(venda)]->produtos[venda_get_mes(venda)], venda_get_codigo_produto(venda));
    if(pcli == NULL){
        pcli = (ProdutoCli) malloc(sizeof(struct produtoCli));
        pcli->prodID = venda_get_codigo_produto(venda);
        pcli->quantidade = venda_get_unidades(venda);
        pcli->faturacao = venda_get_preco_unitario(venda) * venda_get_unidades(venda);
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
    for (int i = 0; i < sizeof(FILIAIS); ++i) {
        destroy_filiais_cli(cliente->filiaisCli[i]);
    }
    free(cliente);
}
