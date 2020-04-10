#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgv.h"
#include "util.h"
#include "colors.h"

#define CODE_SIZE 1024

void destroy_query2(Query2 q2) {
    g_hash_table_destroy(q2->produtos_letra);
    free(q2);
}

void destroy_query3(Query3 q3) {
    free(q3);
}

void destroy_query4(Query4 q4) {
    if (q4->e_global) {
        g_ptr_array_free(q4->produtos_nunca_comprados_global, TRUE);
    } else {
        for (int i = 0; i < N_FILIAIS; ++i) {
            g_ptr_array_free(q4->produtos_nunca_comprados[i], TRUE);
        }
    }
    free(q4);
}

void destroy_query5(Query5 q5) {
    g_ptr_array_free(q5->clientes, TRUE);
    free(q5);
}

void destroy_query6(Query6 q6) {
    free(q6);
}

void destroy_query7(Query7 q7) {
    free(q7);
}

void destroy_query8(Query8 q8) {
    free(q8);
}

void destroy_query9(Query9 q9) {
    g_hash_table_destroy(q9->clientes_que_compraram_produto_N_filial);
    g_hash_table_destroy(q9->clientes_que_compraram_produto_P_filial);
    free(q9);
}

void destroy_query10(Query10 q10) {
    g_ptr_array_free(q10->produtos_por_quantidade, TRUE);
    free(q10);
}

void destroy_query11(Query11 q11) {
    g_ptr_array_free(q11->top_n, TRUE);
    free(q11);
}

void destroy_query12(Query12 q12) {
    g_ptr_array_free(q12->top_n, TRUE);
    free(q12);
}

typedef struct sgv {
    Clientes clientes;
    Produtos produtos;
    Query13 q13;
} * SGV;

Produtos sgv_get_produtos(SGV sgv) {
    return sgv->produtos;
}

Clientes sgv_get_clientes(SGV sgv) {
    return sgv->clientes;
}

Query13 sgv_get_query_13(SGV sgv) {
    return sgv->q13;
}

void read_clientes_with_fgets(FILE* file, Clientes c, Query13 q13) {
    char code[CODE_SIZE];
    int validos = 0;
    int linhas = 0;
    while (fgets(code, CODE_SIZE, file)) {
        char* b = strtok(code, "\r\n");
        adiciona_cliente(c, b, &validos);
        linhas++;
    }
    printf("\n\n");
    printf(BLUE "  Foi lido o ficheiro \"Clientes.txt\":\n" RESET);
    printf(YELLOW "    Linhas lidas:" RESET " %d\n", linhas);
    printf(YELLOW "    Clientes válidos:" RESET " %d\n\n", validos);
    q13->linhas_lidas_clientes = linhas;
    q13->linhas_validas_clientes = validos;
}

void read_produtos_with_fgets(FILE* file, Produtos p, Query13 q13) {
    char code[CODE_SIZE];
    int validos = 0;
    int linhas = 0;
    while (fgets(code, CODE_SIZE, file)) {
        char* c = strtok(code, "\r\n");
        adiciona_produto(p, c, &validos);
        linhas++;
    }
    printf(BLUE "  Foi lido o ficheiro \"Produtos.txt\":\n" RESET);
    printf(YELLOW "    Linhas lidas:" RESET " %d\n", linhas);
    printf(YELLOW "    Produtos válidos:" RESET " %d\n\n", validos);
    q13->linhas_lidas_produtos = linhas;
    q13->linhas_validas_produtos = validos;
}

void read_vendas_with_fgets(FILE* file, SGV sgv, Query13 q13) {
    char code[CODE_SIZE];
    int validos = 0;
    int linhas = 0;
    while (fgets(code, CODE_SIZE, file)) {
        char* c = strtok(code, "\r\n");
        Venda venda = valida_venda(sgv->produtos, sgv->clientes, c);
        if (venda) {
            update_produtos(sgv->produtos, venda);
            update_clientes(sgv->clientes, venda);
            validos++;
        }
        linhas++;
    }
    printf(BLUE "  Foi lido o ficheiro \"Vendas.txt\":\n" RESET);
    printf(YELLOW "    Linhas lidas:" RESET " %d\n", linhas);
    printf(YELLOW "    Vendas válidas:" RESET " %d\n\n", validos);
    q13->linhas_lidas_vendas = linhas;
    q13->linhas_validas_vendas = validos;
}

SGV initSGV() {
    SGV sgv = malloc(sizeof(struct sgv));
    sgv->clientes = make_clientes();
    sgv->produtos = make_produtos();
    return sgv;
}

void destroySGV(SGV sgv) {
    destroy_clientes(sgv->clientes);
    destroy_produtos(sgv->produtos);
    free(sgv->q13);
    free(sgv);
}

SGV loadSGVFromFiles(SGV sgv, char const* filesFolderPath) {
    printf(BLUE);
    printf("\n------------------------------------------- Carregamento de dados e resultados da verificação -------------------------------------------\n");
    printf(RESET);
    Query13 q13 = malloc(sizeof(struct query_13));
    char* result = malloc(strlen(filesFolderPath) + strlen("/Clientes.txt") + 1);
    strcpy(result, filesFolderPath);
    strcat(result, "/Clientes.txt");
    FILE* clientes_file = fopen(result, "r");
    read_clientes_with_fgets(clientes_file, sgv->clientes, q13);
    free(result);
    fclose(clientes_file);

    result = malloc(strlen(filesFolderPath) + strlen("/Produtos.txt") + 1);
    strcpy(result, filesFolderPath);
    strcat(result, "/Produtos.txt");
    FILE* produtos_file = fopen(result, "r");
    read_produtos_with_fgets(produtos_file, sgv->produtos, q13);
    free(result);
    fclose(produtos_file);

    result = malloc(strlen(filesFolderPath) + strlen("/Vendas_1M.txt") + 1);
    strcpy(result, filesFolderPath);
    strcat(result, "/Vendas_1M.txt");
    FILE* vendas_file = fopen(result, "r");
    read_vendas_with_fgets(vendas_file, sgv, q13);
    free(result);
    fclose(vendas_file);

    sgv->q13 = q13;

    return sgv;
}

//query 2
Query2 getProductsStartedByLetter(SGV sgv, char letter) {
    Query2 q2 = malloc(sizeof(struct query_2));
    q2->produtos_letra = g_hash_table_new(g_str_hash, str_compare);
    produtos_foreach_started_by(sgv->produtos, letter, add_product_id, q2->produtos_letra);
    return q2;
}

//query 3
Query3 getProductSalesAndProfit(SGV sgv, char* productID, int month) {
    Query3 q3 = malloc(sizeof(struct query_3));
    for (int filial = 0; filial < N_FILIAIS; filial++) {
        q3->faturacao_normal[filial] = 0;
        q3->vendas_normal[filial] = 0;
        q3->faturacao_promocao[filial] = 0;
        q3->vendas_promocao[filial] = 0;
    }
    Produtos prods = sgv->produtos;
    char letra = productID[0];
    GHashTable* produtos = produtos_get_produtos_letra(prods, (letra - 'A'));
    Produto produto = g_hash_table_lookup(produtos, productID);
    for (int i = 0; i < N_FILIAIS; i++) {
        Filial filial = produto_get_filial(produto, i);
        FaturacaoMes fmes = filial_get_faturacao_mes(filial, INT_2_MONTH(month));
        q3->faturacao_normal[i] += faturacao_mes_get_faturacao_normal(fmes);
        q3->vendas_normal[i] += faturacao_mes_get_vendas_normal(fmes)->len;
        q3->faturacao_promocao[i] += faturacao_mes_get_faturacao_promocao(fmes);
        q3->vendas_promocao[i] += faturacao_mes_get_vendas_promocao(fmes)->len;
    }
    return q3;
}

//query 4
Query4 getProductsNeverBought(SGV sgv, int branchID) {
    Produtos prods = sgv->produtos;
    Query4 q4 = malloc(sizeof(struct query_4));
    ProdutosNuncaVendidos p_n_v = make_produtos_nunca_vendidos();
    set_de_e_ate_filial_p_n_v(p_n_v, INT_2_FILIAL(1), INT_2_FILIAL(3));
    if (branchID == 1) {
        for (int filial = 0; filial < N_FILIAIS; ++filial) {
            q4->total_produtos_nao_comprados[filial] = 0;
            q4->produtos_nunca_comprados[filial] = g_ptr_array_new();
        }
        for (int letra = 0; letra < ('Z' - 'A') + 1; ++letra) {
            GHashTable* produtos_letra = produtos_get_produtos_letra(prods, letra);
            g_hash_table_foreach(produtos_letra, guarda_se_nao_foi_vendido, p_n_v);
        }
        GHashTable* produtos_nao_vendidos_filial[N_FILIAIS];
        int total[3];
        for (int filial = 0; filial < N_FILIAIS; ++filial) {
            produtos_nao_vendidos_filial[filial] = p_n_v_get_produtos_n_vendidos(p_n_v, filial);
            total[filial] = g_hash_table_size(produtos_nao_vendidos_filial[filial]);
            g_hash_table_foreach(produtos_nao_vendidos_filial[filial], to_ptr_array_productID,
                                 q4->produtos_nunca_comprados[filial]);
            g_ptr_array_sort(q4->produtos_nunca_comprados[filial], produtos_comparator_id);
            q4->total_produtos_nao_comprados[filial] = total[filial];
        }
        q4->e_global = false;
    } else {
        q4->produtos_nunca_comprados_global = g_ptr_array_new();
        for (int letra = 0; letra < ('Z' - 'A') + 1; ++letra) {
            GHashTable* produtos_letra = produtos_get_produtos_letra(prods, letra);
            g_hash_table_foreach(produtos_letra, guarda_se_nao_foi_vendido_global, p_n_v);
        }
        GHashTable* produtos_nunca_vendidos = p_n_v_get_produtos_n_vendidos_global(p_n_v);
        g_hash_table_foreach(produtos_nunca_vendidos, to_ptr_array_productID, q4->produtos_nunca_comprados_global);
        g_ptr_array_sort(q4->produtos_nunca_comprados_global, produtos_comparator_id);
        q4->total_produtos_nao_comprados_global = g_hash_table_size(produtos_nunca_vendidos);
        q4->e_global = true;
    }
    destroy_produtos_nunca_vendidos(p_n_v);
    return q4;
}

//query 5
Query5 getClientsOfAllBranches(SGV sgv) {
    Query5 q5 = malloc(sizeof(struct query_5));
    q5->clientes = g_ptr_array_new();
    GHashTable* clis = clientes_get_clientes(sgv->clientes);
    g_hash_table_foreach(clis, cliente_fez_compras_todas_filiais, q5->clientes);
    g_ptr_array_sort(q5->clientes, clientes_comparator);
    return q5;
}

//query 6
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
    q6->total_produtos_nunca_comprados = g_hash_table_size(p_n_v_get_produtos_n_vendidos_global(p_n_v));
    destroy_produtos_nunca_vendidos(p_n_v);
    return q6;
}

//query 7
Query7 getProductsBoughtByClient(SGV sgv, char* clientID) {
    Query7 q7 = malloc(sizeof(struct query_7));
    Cliente c = clientes_get_cliente(clientes_get_clientes(sgv->clientes), clientID);
    ProdutosCompradosCliente p_c_c = make_produtos_comprados_cliente();
    for (int filial = 0; filial < N_FILIAIS; filial++) {
        for (int mes = 0; mes < N_MONTHS; ++mes) {
            FilialCli fcli = cliente_get_filial(c, filial);
            GHashTable* mes_ = filiais_cli_get_mes(fcli, mes);
            int result = get_total_compras(mes_);
            *p_c_c_get_n_produtos_comprados(p_c_c, filial, mes) = result;
        }
    }
    for (int i = 0; i < N_FILIAIS; ++i) {
        for (int j = 0; j < N_MONTHS; ++j) {
            q7->n_produtos_comprados[i][j] = *p_c_c_get_n_produtos_comprados(p_c_c, i, j);
        }
    }
    free(p_c_c);
    return q7;
}

//query 8
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
    free(t_v_f);
    return q8;
}

//query 9
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
    g_hash_table_foreach(vendas_n, add_client_id, q9->clientes_que_compraram_produto_N_filial);
    q9->total_clientes_N = g_hash_table_size(vendas_n);
    g_hash_table_foreach(vendas_n, add_client_id, q9->clientes_que_compraram_produto_P_filial);
    q9->total_clientes_P = g_hash_table_size(vendas_n);
    g_hash_table_destroy(vendas_n);
    g_hash_table_destroy(vendas_p);
    return q9;
}

//query10
Query10 getClientFavoriteProducts(SGV sgv, char* clientID, int month) {
    Query10 q10 = malloc(sizeof(struct query_10));
    Cliente c = clientes_get_cliente(clientes_get_clientes(sgv->clientes), clientID);
    GHashTable* produtos_resultado = g_hash_table_new(g_str_hash, str_compare);
    for (int filial = 0; filial < N_FILIAIS; filial++) {
        FilialCli filial_cli = cliente_get_filial(c, filial);
        GHashTable* produtos_mes = filiais_cli_get_mes(filial_cli, INT_2_MONTH(month));
        g_hash_table_foreach(produtos_mes, get_produto_quantidade, produtos_resultado);
    }
    q10->produtos_por_quantidade = g_ptr_array_new_with_free_func(free);
    g_hash_table_foreach(produtos_resultado, adiciona_produto_quantidade, q10->produtos_por_quantidade);
    g_ptr_array_sort(q10->produtos_por_quantidade, produtos_cli_comparator);
    g_hash_table_destroy(produtos_resultado);
    return q10;
}

//query 11
Query11 getTopSoldProducts(SGV sgv, int limit) {
    Query11 q11 = malloc(sizeof(struct query_11));
    TopProdutos top_produtos = make_top_produtos(limit);
    Produtos produtos = sgv->produtos;
    for (int letra = 0; letra < ('Z' - 'A') + 1; ++letra) {
        g_hash_table_foreach(produtos_get_produtos_letra(produtos, letra), adiciona_produtos, top_produtos);
    }
    GPtrArray* prods = top_produtos_get_produtos(top_produtos);
    g_ptr_array_sort(prods, produtos_comparator);
    GPtrArray* produtos_resultado = g_ptr_array_new_with_free_func(destroy_informacao_produto);
    g_ptr_array_foreach(prods, set_info_produtos, produtos_resultado);
    q11->top_n = produtos_resultado;
    destroy_top_produtos(top_produtos);
    return q11;
}

//query12
Query12 getClientTopProfitProducts(SGV sgv, char* clientID, int limit) {
    Query12 q12 = malloc(sizeof(struct query_12));
    Cliente c = clientes_get_cliente(clientes_get_clientes(sgv->clientes), clientID);
    GHashTable* produtos = g_hash_table_new_full(g_str_hash, str_compare, NULL, free);
    for (int filial = 0; filial < N_FILIAIS; filial++) {
        for (int mes = 0; mes < N_MONTHS; mes++) {
            FilialCli filial_cli = cliente_get_filial(c, filial);
            GHashTable* produtos_mes = filiais_cli_get_mes(filial_cli, mes);
            g_hash_table_foreach(produtos_mes, adiciona_produtos_q12, produtos);
        }
    }
    GList* por_ordenar = g_hash_table_get_values(produtos);
    GPtrArray* resultado = g_ptr_array_new();
    for (int i = 0; i < limit; ++i) {
        ProdutoFaturacao produto_faturacao = get_maior(&por_ordenar);
        if (produto_faturacao) {
            set_info_produtos_cliente(produto_faturacao, resultado);
        } else {
            break;
        }
    }
    g_list_free(por_ordenar);
    g_hash_table_destroy(produtos);
    q12->top_n = resultado;
    return q12;
}
