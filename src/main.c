#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendas.h"
#include "sgv.h"

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


void read_vendas_with_fgets(FILE* file, SGV sgv){
   char code[CODE_SIZE];
   while (fgets(code, CODE_SIZE, file)) {
       char *c = strtok(code, "\r\n");
       adiciona_venda(c, sgv);
   }
}

SGV initSGV(){
    SGV sgv = (SGV) malloc(sizeof(struct sgv));
    return sgv;
}

SGV loadSGVFromFiles (SGV sgv, char* filesFolderPath) {
    char *result = malloc(strlen(filesFolderPath) + strlen("/Clientes.txt") + 1);
    strcpy(result, filesFolderPath);
    strcat(result, "/Clientes.txt");
    FILE* clientes_file = fopen(result, "r");
    sgv->clientes = read_clientes_with_fgets(clientes_file);
    fclose(clientes_file);

    result = malloc(strlen(filesFolderPath) + strlen("/Produtos.txt") + 1);
    strcpy(result, filesFolderPath);
    strcat(result, "/Produtos.txt");
    FILE* produtos_file = fopen(result, "r");
    sgv->produtos = read_produtos_with_fgets(produtos_file);
    fclose(produtos_file);

    result = malloc(strlen(filesFolderPath) + strlen("/Vendas_1M.txt") + 1);
    strcpy(result, filesFolderPath);
    strcat(result, "/Vendas_1M.txt");
    FILE* vendas_file = fopen(result, "r");
    read_vendas_with_fgets(vendas_file, sgv);
    fclose(vendas_file);

    return sgv;
}

int main(int argc, const char* argv[]) {
    SGV sgv = initSGV();

    loadSGVFromFiles(sgv, (char*) argv[1]);

    Cliente c = g_hash_table_lookup(sgv->clientes->clientes, "A2652");

    printf("%s %d %d %d\n", c->clienteID, c->filiaisCli[0]->quantidade, c->filiaisCli[1]->quantidade, c->filiaisCli[2]->quantidade);

    return 0;
}
