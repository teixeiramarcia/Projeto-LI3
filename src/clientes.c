#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "util.h"
#include "clientes.h"

typedef struct vendas_mes {
    GPtrArray* vendas;
} VendasMes;

VendasMes make_vendas_mes(){
    GPtrArray* v = g_ptr_array_new();
    return (VendasMes) {.vendas = v};
}

void destroy_vendas_mes(VendasMes v){
    g_ptr_array_free(v.vendas, TRUE);
}

typedef struct meses {
    VendasMes meses[12];
} Meses;

Meses make_meses(){
    Meses m;
    for(int i=0; i<12; i++){
        m.meses[i] = make_vendas_mes();
    }
    return m;
}

void destroy_meses(Meses m){
    for(int i=0; i<12; i++){
        destroy_vendas_mes(m.meses[i]);
    }
}

typedef struct filiais {
    Meses filiais[3];
} Filiais;

Filiais make_filiais(){
    Filiais f;
    for(int i=0; i<3; i++){
        f.filiais[i] = make_meses();
    }
    return f;
}

void destroy_filiais(Filiais f){
    for(int i=0; i<3; i++){
        destroy_meses(f.filiais[i]);
    }
}

typedef struct cliente {
    char* clienteID;
    Filiais historico;
} Cliente;

Cliente* make_cliente(char* c){
    Cliente* cliente = malloc(sizeof(Cliente));
    cliente->clienteID = strdup(c);
    Filiais h = make_filiais();
    cliente->historico = h;
    return cliente;
}

void destroy_cliente(void* c){
    Cliente* cli = (Cliente*) c;
    free(cli->clienteID);
    destroy_filiais(cli->historico);
    free(cli);
}

//Struct Clientes

Clientes make_clientes(){
    GHashTable* clientes = g_hash_table_new_full(g_str_hash, str_compare, free, destroy_cliente);
    return (Clientes) {.clientes = clientes};
}

void destroy_clientes(Clientes cs){
    g_hash_table_destroy(cs.clientes);
}

bool valida_cliente (char *l) {
    if (isupper(l[0])) {
        return valida_codigo(l+1) && (atoi(l+1) >= 1000 && atoi(l+1) <= 5000);
    }
    return false;
}

bool adiciona_cliente (Clientes c, char* cliente){
    if(valida_cliente(cliente) && !g_hash_table_contains(c.clientes, cliente)){
        Cliente* cl = make_cliente(cliente);
        return g_hash_table_insert(c.clientes, strdup(cliente), cl);
    }
    return false;
}

bool existe_cliente(Clientes c, char *cliente) {
    return g_hash_table_contains(c.clientes, cliente);
}

