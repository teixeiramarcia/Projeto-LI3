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
} * SGV;

Clientes read_clientes_with_fgets(FILE* file) {
    char code[CODE_SIZE];
    Clientes c = make_clientes();
    while (fgets(code, CODE_SIZE, file)) {
        char* b = strtok(code, "\r\n");
        adiciona_cliente(c, b);
    }
    return c;
}

Produtos read_produtos_with_fgets(FILE* file) {
    char code[CODE_SIZE];
    Produtos p = make_produtos();
    while (fgets(code, CODE_SIZE, file)) {
        char* c = strtok(code, "\r\n");
        adiciona_produto(p, c);
    }
    return p;
}


void read_vendas_with_fgets(FILE* file, SGV sgv) {
    char code[CODE_SIZE];
    while (fgets(code, CODE_SIZE, file)) {
        char* c = strtok(code, "\r\n");
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
    char* result = malloc(strlen(filesFolderPath) + strlen("/Clientes.txt") + 1);
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

//query 2 - WORKING
Query2 getProductsStartedByLetter(SGV sgv, char letter) {
    Query2 q2 = malloc(sizeof(struct query_2));
    q2->produtos_letra = g_hash_table_new(g_str_hash, str_compare);
    produtos_foreach_started_by(sgv->produtos, letter, add_product_id, q2->produtos_letra);
    printf("Produtos começados pela letra %c\n", letter);
    produtos_foreach_started_by(sgv->produtos, letter, imprime_keys, NULL);
    return q2;
}

//query 3
Query3 getProductSalesAndProfit(SGV sgv, char* productID, int month){ //FIXME fazer ifs do utilizador
    Query3 q3 = malloc(sizeof(struct query_3));    
    Produtos prods = sgv->produtos;
    char letra = productID[0];
    GHashTable* produtos = produtos_get_produtos_letra(prods, (letra - 'A'));
    Produto produto = g_hash_table_lookup(produtos, productID);
    for(int i=0; i<N_FILIAIS; i++){
        Filial filial = produto_get_filial(produto, i);
        FaturacaoMes fmes = filial_get_faturacao_mes(filial, INT_2_MONTH(month));
        q3->faturacao_normal[i] = faturacao_mes_get_faturacao_normal(fmes);
        q3->vendas_normal[i] = faturacao_mes_get_total_normal(fmes);
        q3->faturacao_promocao[i] = faturacao_mes_get_faturacao_promocao(fmes);
        q3->vendas_promocao[i] = faturacao_mes_get_total_promocao(fmes);
    }
    printf("Faturação e Vendas do produto %s:\n", productID);
    if(/*cliente quiser resultados filial*/productID == productID){
        for(int i=0; i<N_FILIAIS; i++){
            printf("Para a filial %d\n", i+1);
            printf("Faturação em modo normal: %f\n", q3->faturacao_normal[i]);
            printf("Vendas em modo normal: %d\n", q3->vendas_normal[i]);
            printf("Faturação em modo promoção: %f\n", q3->faturacao_promocao[i]);
            printf("Vendas em modo promoção: %d\n", q3->vendas_promocao[i]);
        }
    }else{
        double faturacao_total_normal = 0;
        int vendas_total_normal = 0;
        double faturacao_total_promocao = 0;
        int vendas_total_promocao = 0;
        for(int j=0; j<N_FILIAIS; j++){
            faturacao_total_normal += q3->faturacao_normal[j];
            vendas_total_normal += q3->vendas_normal[j];
            faturacao_total_promocao += q3->faturacao_normal[j];
            vendas_total_promocao += q3->vendas_normal[j];
        }
        printf("Valores totais:\n");
        printf("Faturação total em modo normal: %f\n", faturacao_total_normal);
        printf("Vendas totais em modo normal: %d\n", vendas_total_normal);
        printf("Faturação total em modo promoção: %f\n", faturacao_total_promocao);
        printf("Vendas totais em modo promoção: %d\n", vendas_total_promocao);
    }
    return q3;
} 

//query 4 - WORKING
Query4 getProductsNeverBought(SGV sgv, int branchID) {
    assert(branchID >= 0 && branchID < 4);
    Query4 q4 = malloc(sizeof(struct query_4));
    q4->total_produtos_nao_comprados = 0;
    Produtos prods = sgv->produtos;
    q4->produtos_nunca_comprados = g_hash_table_new(g_str_hash, str_compare);
    ProdutosNuncaVendidos p_n_v = make_produtos_nunca_vendidos();
    if (branchID == 0) {
        printf("Produtos que nunca foram comprados em nenhuma filial:\n");
        set_de_e_ate_filial_p_n_v(p_n_v, INT_2_FILIAL(1), INT_2_FILIAL(3));
    } else {
        printf("Produtos que nunca foram comprados na filial %d:\n", branchID);
        set_de_e_ate_filial_p_n_v(p_n_v, INT_2_FILIAL(branchID), INT_2_FILIAL(branchID));
    }
    for (int i = 0; i < ('Z' - 'A') + 1; i++) {
        GHashTable* produtos_letra = produtos_get_produtos_letra(prods, i);
        g_hash_table_foreach(produtos_letra, guarda_se_nao_foi_vendido, p_n_v);
    }
    GHashTable* produtos_nao_vendidos = p_n_v_get_produtos_n_vendidos(p_n_v);
    int total = g_hash_table_size(p_n_v_get_produtos_n_vendidos(p_n_v));
    g_hash_table_foreach(produtos_nao_vendidos, add_product_id, q4->produtos_nunca_comprados);
    q4->total_produtos_nao_comprados = total;
    g_hash_table_foreach(produtos_nao_vendidos, imprime_keys, NULL);
    printf("Número total: %d", total);
    return q4;
}

//query 5
Query5 getClientsOfAllBranches(SGV sgv){
    Query5 q5 = malloc(sizeof(struct query_5));
    q5->clientes = g_hash_table_new(g_str_hash, str_compare);
    GHashTable* clis = clientes_get_clientes(sgv->clientes);
    g_hash_table_foreach(clis, cliente_fez_compras_todas_filiais, q5->clientes);
    g_hash_table_foreach(q5->clientes, imprime_keys, NULL);
    return q5;
}

//query 6 - WORKING
Query6 getClientsAndProductsNeverBoughtCount(SGV sgv) {
    Query6 q6 = malloc(sizeof(struct query_6));
    int resCli = 0;
    g_hash_table_foreach(clientes_get_clientes(sgv->clientes), clientes_procurarCli, &resCli);
    ProdutosNuncaVendidos p_n_v = make_produtos_nunca_vendidos();
    set_de_e_ate_filial_p_n_v(p_n_v, INT_2_FILIAL(1), INT_2_FILIAL(3));
    for (int i = 0; i < ('Z' - 'A') + 1; i++) {
        GHashTable* produtos_letra = produtos_get_produtos_letra(sgv->produtos, i);
        g_hash_table_foreach(produtos_letra, guarda_se_nao_foi_vendido, p_n_v);
    }

    q6->total_clientes_que_nunca_compraram = resCli;
    q6->total_produtos_nunca_comprados = g_hash_table_size(p_n_v_get_produtos_n_vendidos(p_n_v));
    printf("Clientes que nunca fizeram compras: %d\n", resCli);
    printf("Produtos nunca comprados: %d", g_hash_table_size(p_n_v_get_produtos_n_vendidos(p_n_v)));
    return q6;
}

//query 7 - WORKING
void getProductsBoughtByClient(SGV sgv, char* clientID) {
    Cliente c = clientes_get_cliente(clientes_get_clientes(sgv->clientes), clientID);
    if (c != NULL) {
        ProdutosCompradosCliente p_c_c = make_produtos_comprados_cliente();
        for (int filial = 0; filial < N_FILIAIS; filial++) {
            for (int mes = 0; mes < N_MONTHS; ++mes) {
                FiliaisCli fcli = cliente_get_filial(c, filial);
                GHashTable* mes_ = filiais_cli_get_mes(fcli, mes);
                int result = get_total_compras(mes_);
                *p_c_c_get_n_produtos_comprados(p_c_c, filial, mes) = result;
            }
        }
        for (int i = 0; i < N_FILIAIS; ++i) {
            printf("Total de compras que o cliente fez na filial %d:\n", i + 1);
            for (int j = 0; j < N_MONTHS; ++j) {
                printf("No mês %d\n", j + 1);
                int compras = *p_c_c_get_n_produtos_comprados(p_c_c, i, j);
                printf("%d\n", compras);
            }
        }
    } else {
        printf("O cliente %s não existe no sistema.\n", clientID);
    }
}

//query 8 - WORKING
Query8 getSalesAndProfit(SGV sgv, int minMonth, int maxMonth) {
    Query8 q8 = malloc(sizeof(struct query_8));
    Produtos produtos = sgv->produtos;
    TotaisVendasFaturacao t_v_f = make_totais_vendas_faturacao();
    t_v_f_set_limites(t_v_f, minMonth, maxMonth);

    for (int letra = 0; letra < ('Z' - 'A') + 1; letra++) {
        GHashTable* produtos_letra = produtos_get_produtos_letra(produtos, letra);
        g_hash_table_foreach(produtos_letra, get_totais, t_v_f);
    }
    q8->total_vendas_meses = t_v_f_get_total_vendas(t_v_f);
    q8->total_faturado_meses = t_v_f_get_total_faturacao(t_v_f);
    printf("Total de vendas no intervalo de meses indicados: %d\n", t_v_f_get_total_vendas(t_v_f));
    printf("Total faturado no intervalo de meses indicados: %f\n", t_v_f_get_total_faturacao(t_v_f));
    return q8;
}

//query 9 - WORKING
Query9 getProductBuyers(SGV sgv, char* prodID, int branchID) {
    Query9 q9 = malloc(sizeof(struct query_9));
    GHashTable* vendas_n = g_hash_table_new(g_str_hash, str_compare);
    GHashTable* vendas_p = g_hash_table_new(g_str_hash, str_compare);
    for (size_t month = 0; month < N_MONTHS; month++) {
        Filial filial = produtos_get_filial(sgv->produtos, prodID, INT_2_FILIAL(branchID));
        FaturacaoMes fmes = filial_get_faturacao_mes(filial, MONTHS[month]);
        GPtrArray* vendas_normal = faturacao_mes_get_vendas_normal(fmes);
        GPtrArray* vendas_promocao = faturacao_mes_get_vendas_promocao(fmes);
        g_ptr_array_foreach(vendas_normal, (GFunc) guarda_cliente, vendas_n);
        g_ptr_array_foreach(vendas_promocao, (GFunc) guarda_cliente, vendas_p);
    }
    q9->clientes_que_compraram_produto_N_filial = g_hash_table_new(g_str_hash, str_compare);
    q9->clientes_que_compraram_produto_P_filial = g_hash_table_new(g_str_hash, str_compare);
    printf("Clientes que compraram o produto %s na filial %d:\n", prodID, branchID);
    printf("Em época normal:\n");
    g_hash_table_foreach(vendas_n, imprime_keys, NULL);
    g_hash_table_foreach(vendas_n, add_client_id, q9->clientes_que_compraram_produto_N_filial);
    printf("Número total de clientes: %d\n", g_hash_table_size(vendas_n));
    q9->total_clientes_N = g_hash_table_size(vendas_n);
    printf("Em época promocional:\n");
    g_hash_table_foreach(vendas_p, imprime_keys, NULL);
    g_hash_table_foreach(vendas_n, add_client_id, q9->clientes_que_compraram_produto_P_filial);
    printf("Número total de clientes: %d\n", g_hash_table_size(vendas_p));
    q9->total_clientes_P = g_hash_table_size(vendas_n);
    return q9;
}

//query 11 - WORKING
Query11 getTopSoldProducts(SGV sgv, int limit) {
    Query11 q11 = malloc(sizeof(struct query_11));
    TopProdutos top_produtos = make_top_produtos(limit);
    Produtos produtos = sgv->produtos;
    for (int letra = 0; letra < ('Z' - 'A') + 1; ++letra) {
        g_hash_table_foreach(produtos_get_produtos_letra(produtos, letra), adiciona_produtos, top_produtos);
    }
    GPtrArray* prods = top_produtos_get_produtos(top_produtos);

    g_ptr_array_sort(prods, produtos_comparator);
    printf("Top %d produtos vendidos:\n", limit);
    g_ptr_array_foreach(prods, imprime_keys_for_ptr_array, NULL);
    return q11;
}








