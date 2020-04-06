#include "navegador.h"
#include "types.h"
#include "clientes.h"
#include "sgv.h"
#include "colors.h"
#include <stdio.h>
#include <ctype.h>

typedef struct navegador {
    int posicao_inicio_resultados;
    int indice;
} *Navegador;

Navegador make_navegador() {
    Navegador navegador = malloc(sizeof(struct navegador));
    navegador->posicao_inicio_resultados = 0;
    navegador->indice = 0;
    return navegador;
}

void imprime_10(void* value, void* user_data) {
    char* identificador = (char*) value;
    Navegador navegador = (Navegador) user_data;
    int i = navegador->indice;
    int posicao_inicio = navegador->posicao_inicio_resultados;
    if(i >= posicao_inicio && i < posicao_inicio + 10){
        printf("%s\n", identificador);
    }
    navegador->indice++;
}

void imprime_10_hash_table(void* key, void* value, void* user_data) {
    imprime_10(key, user_data);
}

void imprime_info_produto_quantidade(void* value, void* user_data) {
    ProdutoQuantidade p_q = (ProdutoQuantidade) value;
    imprime_10(p_q_get_ID(p_q), user_data);
}

void imprime_informacao_produto_aux(InformacaoProduto i_p) {
    printf(YELLOW "Código do produto:" RESET " %s\n", i_p_get_codigo_produto(i_p));
    printf(YELLOW "Número total de clientes envolvidos:" RESET " %d\n", i_p_get_numero_compradores(i_p));
    for (int filial = 0; filial < N_FILIAIS; filial++) {
        printf(YELLOW "Número de unidades vendidas na filial %d:" RESET " %d\n", filial + 1,
               i_p_get_numero_vendido_filial(i_p, filial));
    }
}

void imprime_informacao_produto(void* value, void* user_data) {
    InformacaoProduto i_p = (InformacaoProduto) value;
    Navegador navegador = (Navegador) user_data;
    int i = navegador->indice;
    int posicao_inicio = navegador->posicao_inicio_resultados;
    if(i >= posicao_inicio && i < posicao_inicio + 10){
        imprime_informacao_produto_aux(i_p);
    }
    navegador->indice++;
}

void auxiliar(void (*funcao)(), void* query, char* titulo) {
    Navegador navegador = make_navegador();
    bool flagCycle = true;
    char tmp[3];
    int opcao = 3;
    char aux;
    int i;
    while(flagCycle) {
        printf(BLUE);
        printf(titulo);
        printf(RESET);
        printf( YELLOW "A mostrar resultados de %d até %d:\n\n" RESET, navegador->posicao_inicio_resultados, navegador->posicao_inicio_resultados + 10);
        funcao(navegador, query);
        printf( YELLOW "\n1 -> 10 resultados anteriores.\n2 -> 10 resultados seguintes.\n3 -> sair do navegador.\n" RESET);
        i = 0;
        while ((aux = fgetc(stdin)) != '\n'){
            if(i+1 < 3){
                tmp[i] = aux;
                i++;
            }
        }
        tmp[i] = '\0';
        if (isdigit(tmp[0])){
            opcao = atoi(tmp);
        }
        switch(opcao) {
            case 1:
                navegador->posicao_inicio_resultados -= 10;
                navegador->indice = 0;
                system("clear");
                break;
            case 2:
                navegador->posicao_inicio_resultados += 10;
                navegador->indice = 0;
                system("clear");
                break;
            case 3:
                flagCycle = false;
                break;
            default:
                break;
        }
    }
}

//query 2
void print_q2(Navegador navegador, void* q_2) {
    Query2 q2 = (Query2) q_2;
    printf( YELLOW "Total:" RESET "%d\n\n", g_hash_table_size(q2->produtos_letra));
    g_hash_table_foreach(q2->produtos_letra, imprime_10_hash_table, navegador);
}

void print_q2_with_navegador (Query2 q2) {
    char* titulo = "----Listagem de produtos começados por uma determinada letra e respetiva contagem----\n\n";
    auxiliar(print_q2, q2, titulo);
}

//query 4
void print_q4(Navegador navegador, void* q_4) {
    Query4 q4 = (Query4) q_4;
    printf( YELLOW "Total:" RESET "%d\n\n", q4->total_produtos_nao_comprados_global);
    g_ptr_array_foreach(q4->produtos_nunca_comprados_global, imprime_10, navegador);
}

void print_q4_2(Navegador navegador, void* array) {
    GPtrArray* produtos_nunca_comprados = (GPtrArray*) array;
    g_ptr_array_foreach(produtos_nunca_comprados, imprime_10, navegador);
}

void print_q4_with_navegador(Query4 q4, int option) {
    if(option == 0) {
        char* titulo = BLUE "----Listagem e total de produtos que nunca foram comprados----\n\n"
                        "Produtos nunca comprados em nenhuma filial:\n" RESET;
        auxiliar(print_q4, q4, titulo );
        return;
    }
    char* titulo = BLUE "----Listagem e total de produtos que nunca foram comprados----\n\n";
    for (int filial = 0; filial < N_FILIAIS; ++filial) {
        printf( BLUE "\n\n ------------------------------------------\n\n" RESET);
        printf( YELLOW "Produtos nunca comprados na filial %d:\n" RESET, filial + 1);
        printf( YELLOW "Total:" RESET "%d\n\n", q4->total_produtos_nao_comprados[filial]);
        auxiliar(print_q4_2, q4->produtos_nunca_comprados[filial], titulo);
    }
}

//query 5
void print_q5(Navegador navegador, void* q_5) {
    Query5 q5 = (Query5) q_5;
    g_ptr_array_foreach(q5->clientes, imprime_10, navegador);
}

void print_q5_with_navegador(Query5 q5) {
    char* titulo = "----Listagem de clientes que efetuaram compras em todas as filiais----\n\n";
    auxiliar(print_q5, q5, titulo);
}

//query 10
void print_q10(Navegador navegador, void* q_10) {
    Query10 q10 = (Query10) q_10;
    g_ptr_array_foreach(q10->produtos_por_quantidade, imprime_info_produto_quantidade, navegador);
}

void print_q10_with_navegador(Query10 q10) {
    char* titulo = "\n----Listagem de produtos comprados por um cliente num determinado mês por ordem decrescente de quantidade----\n\n";
    auxiliar(print_q10, q10, titulo);
}

//query 11
void print_q11(Navegador navegador, void* q_11) {
    Query11 q11 = (Query11) q_11;
    g_ptr_array_foreach(q11->top_n, imprime_informacao_produto, navegador);
}

void print_q11_with_navegador(Query11 q11) {
    char* titulo = "----Listagem dos N produtos mais vendidos----\n\n";
    auxiliar(print_q11, q11, titulo);
}

//query 12
void print_q12(Navegador navegador, void* q_12) {
    Query12 q12 = (Query12) q_12;
    g_ptr_array_foreach(q12->top_n, imprime_10, navegador);
}

void print_q12_with_navegador(Query12 q12) {
    char* titulo = "\n----Lista dos N produtos em que um determinado cliente gastou mais dinheiro----\n\n";
    auxiliar(print_q12, q12, titulo);
}