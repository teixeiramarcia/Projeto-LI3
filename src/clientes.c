#include <ctype.h>
#include <stdlib.h>
#include "util.h"
#include "clientes.h"

Clientes make_clientes() {
    Clientes clientes = (Clientes) malloc(sizeof(struct clientes));
    clientes->clientes = g_hash_table_new_full(g_str_hash, str_compare, free, NULL);
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
                cliente->filiaisCli[j]->produtos[i] = g_hash_table_new_full(g_str_hash, str_compare, free, NULL);
            }
        }
        return g_hash_table_insert(clis->clientes, cliente->clienteID, cliente);
    }
    return false;
}

