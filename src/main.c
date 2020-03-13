#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "clientes.h"
#include "produtos.h"
#include "vendas.h"

char* strdup(char const*);

#define CODE_SIZE 1024

Clientes read_clientes_with_fgets(FILE* file){
    char code[CODE_SIZE];
    Clientes c = make_clientes();
    while (fgets(code, CODE_SIZE, file)) {
        char *b = strtok(code, "\r\n");
        adiciona_cliente(c, b);
    }

    return c;
}

Produtos read_produtos_with_fgets(FILE* file){
    char code[CODE_SIZE];
    Produtos p = make_produtos();
    while (fgets(code, CODE_SIZE, file)) {
        char *c = strtok(code, "\r\n");
        adiciona_produto(p, c);
    }
    return p;
}

Vendas read_vendas_with_fgets(FILE* file, Produtos p, Clientes cl){
    char code[CODE_SIZE];
    int validos = 0;
    char** vendasValidas = NULL;
    while (fgets(code, CODE_SIZE, file)) {
        char *c = strtok(code, "\r\n");
        if (valida_venda(c, p, cl)){
            vendasValidas = (char**) realloc(vendasValidas, (validos+1)*sizeof(char*));
            vendasValidas[validos] = strdup(c);
            validos++;
        }
    }
    return (Vendas) {.validos = vendasValidas, .num = validos};
}

int main (){
    FILE* clientes_file = fopen("Dados/Clientes.txt", "r");
    Clientes clientes = read_clientes_with_fgets(clientes_file);
    fclose(clientes_file);

    FILE* produtos_file = fopen("Dados/Produtos.txt", "r");
    Produtos produtos = read_produtos_with_fgets(produtos_file);
    fclose(produtos_file);

    FILE* vendas_file = fopen("Dados/Vendas_1M.txt", "r");
    read_vendas_with_fgets(vendas_file, produtos, clientes);
    fclose(vendas_file);
    return 0;
}
