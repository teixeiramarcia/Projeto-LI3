#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>

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
    FiliaisCli filiaisCli[3];
} *Cliente;

typedef struct clientes {
    GHashTable *clientes;
} *Clientes;

Clientes make_clientes();

bool adiciona_cliente(Clientes c, char *cliente);

bool existe_cliente(Clientes c, char *cliente);

bool valida_cliente(char *l);

void destroy_clientes(Clientes clientes);

void destroy_cliente(Cliente cliente);

void destroy_filiais_cli(FiliaisCli fcli);

#endif
