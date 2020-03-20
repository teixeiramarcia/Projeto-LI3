#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sgv.h"
#include "util.h"

#define CODE_SIZE 1024

typedef struct sgv {
    Clientes clientes;
    Produtos produtos;
} *SGV;

Clientes read_clientes_with_fgets(FILE *file) {
    char code[CODE_SIZE];
    Clientes c = make_clientes();
    while (fgets(code, CODE_SIZE, file)) {
        char *b = strtok(code, "\r\n");
        adiciona_cliente(c, b);
    }
    return c;
}

Produtos read_produtos_with_fgets(FILE *file) {
    char code[CODE_SIZE];
    Produtos p = make_produtos();
    while (fgets(code, CODE_SIZE, file)) {
        char *c = strtok(code, "\r\n");
        adiciona_produto(p, c);
    }
    return p;
}


void read_vendas_with_fgets(FILE *file, SGV sgv) {
    char code[CODE_SIZE];
    while (fgets(code, CODE_SIZE, file)) {
        char *c = strtok(code, "\r\n");
        Venda venda = valida_venda(sgv->produtos, sgv->clientes, c);
        sgv_adiciona_venda(sgv, venda);
    }
}

void sgv_adiciona_venda(SGV sgv, Venda v) {
    if (v == NULL) {
        return;
    }
    update_produtos(sgv->produtos, v);
    update_clientes(sgv->clientes, v);
}

SGV initSGV() {
    SGV sgv = malloc(sizeof(struct sgv));
    Clientes c = make_clientes();
    Produtos p = make_produtos();
    sgv->clientes = c;
    sgv->produtos = p;
    return sgv;
}

void destroySGV(SGV sgv) {
    destroy_clientes(sgv->clientes);
    destroy_produtos(sgv->produtos);
    free(sgv);
}

SGV loadSGVFromFiles(SGV sgv, char const* filesFolderPath) {
    char *result = malloc(strlen(filesFolderPath) + strlen("/Clientes.txt") + 1);
    strcpy(result, filesFolderPath);
    strcat(result, "/Clientes.txt");
    FILE *clientes_file = fopen(result, "r");
    sgv->clientes = read_clientes_with_fgets(clientes_file);
    fclose(clientes_file);

    result = malloc(strlen(filesFolderPath) + strlen("/Produtos.txt") + 1);
    strcpy(result, filesFolderPath);
    strcat(result, "/Produtos.txt");
    FILE *produtos_file = fopen(result, "r");
    sgv->produtos = read_produtos_with_fgets(produtos_file);
    fclose(produtos_file);

    result = malloc(strlen(filesFolderPath) + strlen("/Vendas_1M.txt") + 1);
    strcpy(result, filesFolderPath);
    strcat(result, "/Vendas_1M.txt");
    FILE *vendas_file = fopen(result, "r");
    read_vendas_with_fgets(vendas_file, sgv);
    fclose(vendas_file);

    return sgv;
}

//query 2 - WORKING
void getProductsStartedByLetter(SGV sgv, char letter){
    printf("Produtos começados pela letra %c\n", letter);
    produtos_foreach_started_by(sgv->produtos, letter, imprime_keys, NULL);
}

//query 4
void getProductsNeverBought(SGV sgv, int branchID){ //FIXME
    assert(branchID >= 0 && branchID < 4);
    FilialID branch = INT_2_FILIAL(branchID);
    if(branch == filial_todas){
        ProdutosETotaisHelper p_e_t = produtos_foreach_never_bought_t(sgv->produtos);
        printf("Produtos nunca comprados em todas as filiais:\n");
        g_ptr_array_foreach(produtos_e_totais_helper_get_produtos(p_e_t), (GFunc) imprime_keys, NULL);
        int total = produtos_e_totais_get_total(produtos_e_totais_helper_get_produtos_e_totais(p_e_t));
        printf("Total de produtos nunca vendidos em todas as filiais: %d\n", total);
    } else {
        ProdutosETotais1Filial p_e_t_1f = produtos_foreach_never_bought_1f(sgv->produtos, branch);
        printf("Produtos nunca comprados na filial %d:\n", branchID);
        g_hash_table_foreach(produtos_e_totais_1filial_get_produtos(p_e_t_1f), imprime_keys, NULL);
        printf("Total de produtos nunca comprados na filial %d: %d\n", branchID, produtos_e_totais_1filial_get_total(p_e_t_1f));
    }
}

//query 6
void getClientsandProductsNeverBoughtCount(SGV sgv){
    int resCli = 0;
    g_hash_table_foreach(clientes_get_clientes(sgv->clientes), clientes_procurarCli, &resCli);
    ProdutosETotaisHelper p_e_t_h = produtos_foreach_never_bought_t(sgv->produtos);
    printf("Clientes que nunca fizeram compras: %d\n", resCli);
    int total_produtos = produtos_e_totais_get_total(produtos_e_totais_helper_get_produtos_e_totais(p_e_t_h));
    printf("Produtos nunca comprados: %d\n", total_produtos);

}

//query 9 - FIXME
void guarda_cliente(Venda venda, GHashTable* vendas_n){
    g_hash_table_add(vendas_n, venda_get_codigo_cliente(venda));
}

void getProductBuyers(SGV sgv, char* prodID, int branchID){
    GHashTable* vendas_n = g_hash_table_new(g_str_hash, str_compare);
    GHashTable* vendas_p = g_hash_table_new(g_str_hash, str_compare);
    for(size_t month = 0; month < sizeof(MONTHS); month++){
        Filial filial = produtos_get_filial(sgv->produtos, prodID, branchID);
        FaturacaoMes fmes = filial_get_faturacao_mes(filial, MONTHS[month]);
        GPtrArray* vendas_normal = faturacao_mes_get_vendas_normal(fmes);
        GPtrArray* vendas_promocao = faturacao_mes_get_vendas_promocao(fmes);
        g_ptr_array_foreach(vendas_normal, (GFunc) guarda_cliente, vendas_n);
        g_ptr_array_foreach(vendas_promocao, (GFunc) guarda_cliente, vendas_p);
    }
    printf("Clientes que compraram o produto %s na filial %d:\n", prodID, branchID);
    printf("Em época normal:\n");
    g_hash_table_foreach(vendas_n, imprime_keys, NULL);
    printf("Número total de clientes: %d\n", g_hash_table_size(vendas_n));
    printf("Em época promocional:\n");
    g_hash_table_foreach(vendas_p, imprime_keys, NULL);
    printf("Número total de clientes: %d\n", g_hash_table_size(vendas_p));

}