#include <ctype.h>
#include <stdlib.h>
#include "util.h"
#include "clientes.h"

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
        for (int j = 0; j < 3; ++j) {
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

void destroy_clientes(Clientes clientes) {
    g_hash_table_destroy(clientes->clientes);
    free(clientes);
}

void destroy_cliente(Cliente cliente) {
    for (int i = 0; i < 3; ++i) {
        destroy_filiais_cli(cliente->filiaisCli[i]);
    }
    free(cliente);
}

void destroy_filiais_cli(FiliaisCli fcli) {
    for (int i = 0; i < 12; ++i) {
        g_hash_table_destroy(fcli->produtos[i]);
    }
    free(fcli);
}
