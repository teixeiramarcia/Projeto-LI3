#include "sgv.h"
#include "util.h"
#include <stdio.h>
#include <ctype.h>


void query2(SGV sgv) {
    char letra[2];
    bool flagInput1 = true;
    char flagCycle[2];
    flagCycle[0] = 'a';
    printf("Indique a letra que pretende procurar:\n");
    printf("-> ");
    while (flagInput1) {
        scanf("%s", letra);
        if (isalpha(letra[0])) {
            system("clear");
            printf("----Listagem de produtos começados por uma determinada letra e respetiva contagem----\n");
            printf("\n");
            flagInput1 = false;
            Query2 q2 = getProductsStartedByLetter(sgv, toupper(letra[0]));
            g_hash_table_foreach(q2->produtos_letra, imprime_keys, NULL);
            printf("\n");
            printf("Total: %d\n\n", g_hash_table_size(q2->produtos_letra));
            printf("Q -> voltar ao menu principal\n\n");
            printf("-> ");
            while (toupper(flagCycle[0]) != 'Q') {
                scanf("%s", flagCycle);
            }
        } else {
            printf("\n");
            printf("Input inválido.\n Indique uma letra:\n");
            printf("-> ");
        }
    }
    system("clear");
}

void query3(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    bool flagInput1 = true;
    bool flagInput2 = true;
    bool flagInput3 = true;
    char tmp[3];
    int mes;
    char codigoP[7];
    char tipo[2];
    Produtos p = sgv_get_produtos(sgv);
    printf("Insira o mês que pretende consultar:\n");
    printf("-> ");
    while (flagInput1) {
        scanf("%s", tmp);
        if (isdigit(tmp[0])) {
            mes = atoi(tmp);
            if (mes > 0 && mes < 13) {
                flagInput1 = false;
                printf("\n");
                printf("Insira o código do produto que pretende consultar:\n");
                printf("-> ");
                while (flagInput2) {
                    scanf("%s", codigoP);
                    if (valida_produto(codigoP) && existe_produto(p, codigoP)) {
                        flagInput2 = false;
                        printf("\n");
                        printf("Insira G se pretende obter resultados globais ou F se pretende obter filial a filial:\n");
                        printf("-> ");
                        while (flagInput3) {
                            scanf("%s", tipo);
                            if (toupper(tipo[0]) == 'G' || toupper(tipo[0]) == 'F') {
                                char type = tipo[0];
                                system("clear");
                                printf("----Total de vendas e faturação de um produto num determinado mês----\n\n");
                                flagInput3 = false;
                                Query3 q3 = getProductSalesAndProfit(sgv, codigoP, mes);
                                if(type == 'G'){
                                    int total_vendas_normal = 0;
                                    int total_vendas_promocao = 0;
                                    double faturacao_normal = 0;
                                    double faturacao_promocao = 0;
                                    for (int filial = 0; filial < N_FILIAIS; ++filial) {
                                        total_vendas_normal += q3->vendas_normal[filial];
                                        total_vendas_promocao += q3->vendas_promocao[filial];
                                        faturacao_normal += q3->faturacao_normal[filial];
                                        faturacao_promocao += q3->faturacao_promocao[filial];
                                    }
                                    printf("Resultados gerais para o mês %d:\n", mes);
                                    printf("  Total de vendas em modo normal: %d\n", total_vendas_normal);
                                    printf("  Total faturado em modo normal: %f\n", faturacao_normal);
                                    printf("\n");
                                    printf("  Total de vendas em modo promoção: %d\n", total_vendas_promocao);
                                    printf("  Total faturado em modo promoção: %f\n\n", faturacao_promocao);
                                } else {
                                    printf("Resultados filial a filial para o mês %d:\n", mes);
                                    printf("\n");
                                    for (int filial = 0; filial < N_FILIAIS; ++filial) {
                                        printf("  Filial %d:\n", filial+1);
                                        printf("\n");
                                        printf("    Total de vendas em modo normal: %d\n", q3->vendas_normal[filial]);
                                        printf("    Total faturado em modo normal: %f\n", q3->faturacao_normal[filial]);
                                        printf("\n");
                                        printf("    Total de vendas em modo promoção: %d\n", q3->vendas_promocao[filial]);
                                        printf("    Total faturado em modo promoção: %f\n\n", q3->faturacao_promocao[filial]);
                                    }
                                    printf("\n");
                                }
                                printf("Q -> voltar ao menu principal\n\n");
                                printf("-> ");
                                while (toupper(flagCycle[0]) != 'Q') {
                                    scanf("%s", flagCycle);
                                }
                            } else {
                                printf("\n");
                                printf("Insira uma letra válida:\n");
                                printf("-> ");
                            }
                        }
                    } else {
                        printf("\n");
                        printf("Insira um código (que exista no sistema), sendo este composto por duas maiúsculas e quatro dígitos:\n");
                        printf("-> ");
                    }
                }
            } else {
                printf("\n");
                printf("Insira um mês válido:\n");
                printf("-> ");
            }
        } else {
            printf("\n");
            printf("Insira um dígito válido:\n");
            printf("-> ");
        }
    }
    system("clear");
}

void query4(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    bool flagInput1 = true;
    char tmp[2];
    int tipo;
    printf("Resultados globais - Insira 0:\n");
    printf("Resultados segregados por filiais - Insira 3:\n");
    printf("\n");
    printf("-> ");
    while (flagInput1) {
        scanf("%s", tmp);
        if (isdigit(tmp[0])) {
            tipo = atoi(tmp);
            if (tipo == 0 || tipo == 3) {
                flagInput1 = false;
                system("clear");
                printf("----Listagem e total de produtos que nunca foram comprados----\n");
                printf("\n");
                Query4 q4 = getProductsNeverBought(sgv, tipo);
                if (tipo == 0) {
                    printf("Produtos nunca comprados em nenhuma das filiais:\n");
                    g_ptr_array_foreach(q4->produtos_nunca_comprados_global, imprime_just_keys_produtos, NULL);
                    printf("\n");
                    printf("Total: %d\n\n", q4->total_produtos_nao_comprados_global);
                } else {
                    for (int filial = 0; filial < N_FILIAIS; ++filial) {
                        printf("Produtos nunca comprados na filial %d:\n", filial + 1);
                        g_ptr_array_foreach(q4->produtos_nunca_comprados[filial], imprime_just_keys_produtos, NULL);
                    }
                    for (int filial = 0; filial < N_FILIAIS; ++filial) {
                        printf("Total filial %d: %d\n\n", filial, q4->total_produtos_nao_comprados[filial]);
                    }
                }
                printf("Q -> voltar ao menu principal\n\n");
                printf("-> ");
                while (toupper(flagCycle[0]) != 'Q') {
                    scanf("%s", flagCycle);
                }
            } else {
                printf("\n");
                printf("Escolha uma das opções fornecidas:\n0 - Global\n 3 - Filial a Filial\n");
                printf("-> ");
            }
        } else {
            printf("\n");
            printf("Escolha uma das opções fornecidas:\n0 - Global\n3 - Filial a Filial:\n");
            printf("-> ");
        }
    }
    system("clear");
}

void query5(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    system("clear");
    printf("----Listagem de clientes que efetuaram compras em todas as filiais----\n");
    printf("\n");
    Query5 q5 = getClientsOfAllBranches(sgv);
    g_ptr_array_foreach(q5->clientes, imprime_just_keys_clientes, NULL);
    printf("\n");
    printf("Q -> voltar ao menu principal\n\n");
    printf("-> ");
    while (toupper(flagCycle[0]) != 'Q') {
        scanf("%s", flagCycle);
    }
    system("clear");
}

void query6(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    system("clear");
    printf("----Contagem de clientes que nunca efetuaram compras e de produtos que nunca foram comprados----\n\n");
    Query6 q6 = getClientsAndProductsNeverBoughtCount(sgv);
    printf("  Total de clientes que nunca efetuaram compras: %d\n", q6->total_clientes_que_nunca_compraram);
    printf("\n");
    printf("  Total de produtos que nunca foram comprados: %d\n\n", q6->total_produtos_nunca_comprados);
    printf("Q -> voltar ao menu principal\n\n");
    printf("-> ");
    while (toupper(flagCycle[0]) != 'Q') {
        scanf("%s", flagCycle);
    }
    system("clear");
}

void query7(SGV sgv) { //FIXME fazer a tabela - ainda não imprime resultados
    char flagCycle[2];
    flagCycle[0] = 'a';
    bool flagInput1 = true;
    char codigoC[6];
    Clientes c = sgv_get_clientes(sgv);
    printf("Insira o código do cliente:\n");
    while (flagInput1) {
        scanf("%s", codigoC);
        if (valida_cliente(codigoC) && existe_cliente(c, codigoC)) {
            flagInput1 = false;
            system("clear");
            printf("----Contagem de compras efetuadas por um cliente, separadas por meses e filiais----\n");
            Query7 q7 = getProductsBoughtByClient(sgv, codigoC);
            printf("Q -> voltar ao menu principal\n\n");
            printf("-> ");
            while (toupper(flagCycle[0]) != 'Q') {
                scanf("%s", flagCycle);
            }
        } else {
            printf("\n");
            printf("Input inválido.\n Insira um código de cliente válido:\n");
            printf("-> ");
        }
    }
    system("clear");
}

void query8(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    char tmp[3];
    int pmes;
    int umes;
    bool flagInput1 = true;
    bool flagInput2 = true;
    printf("Insira o mês que pretende que seja o limite inferior:\n");
    printf("-> ");
    while (flagInput1) {
        scanf("%s", tmp);
        if (isdigit(tmp[0])) {
            pmes = atoi(tmp);
            if (pmes > 0 && pmes < 13) {
                flagInput1 = false;
                printf("\n");
                printf("Insira o mês que pretende que seja o limite superior:\n");
                printf("-> ");
                while (flagInput2) {
                    scanf("%s", tmp);
                    if (isdigit(tmp[0])) {
                        umes = atoi(tmp);
                        if (umes >= pmes && umes < 13) {
                            flagInput2 = false;
                            system("clear");
                            printf("----Contagem de vendas e faturação total do SGV num intervalo de meses----\n\n");
                            Query8 q8 = getSalesAndProfit(sgv, pmes, umes);
                            printf("  Total de vendas no intervalo de meses indicado: %d\n", q8->total_vendas_meses);
                            printf("  Faturação total no intervalo de meses indicado: %f\n\n", q8->total_faturado_meses);
                            printf("Q -> voltar ao menu principal\n\n");
                            printf("-> ");
                            while (toupper(flagCycle[0]) != 'Q') {
                                scanf("%s", flagCycle);
                            }
                        } else {
                            printf("\n");
                            printf("Insira um mês posterior ao que definiu como limite inferior:\n");
                            printf("-> ");
                        }
                    } else {
                        printf("\n");
                        printf("Insira um dígito compreendido entre 1 e 12:\n");
                        printf("-> ");
                    }
                }
            } else {
                printf("\n");
                printf("Insira um mês válido:\n");
                printf("-> ");
            }
        } else {
            printf("\n");
            printf("Insira um dígito compreendido entre 1 e 12:\n");
            printf("-> ");
        }
    }
    system("clear");
}

void query9(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    bool flagInput1 = true;
    bool flagInput2 = true;
    char tmp[2];
    char codigoP[7];
    int filial;
    Produtos p = sgv_get_produtos(sgv);
    printf("Insira o código do produto que pretende consultar:\n");
    printf("-> ");
    while (flagInput1) {
        scanf("%s", codigoP);
        if (valida_produto(codigoP) && existe_produto(p, codigoP)) {
            flagInput1 = false;
            printf("\n");
            printf("Insira o número da filial:\n");
            printf("-> ");
            while (flagInput2) {
                scanf("%s", tmp);
                if (isdigit(tmp[0])) {
                    filial = atoi(tmp);
                    if (filial > 0 && filial < 4) {
                        flagInput2 = false;
                        system("clear");
                        printf("----Total de clientes que compraram um determinado produto numa determinada filial----\n");
                        Query9 q9 = getProductBuyers(sgv, codigoP, filial);
                        printf("  Na filial %d\n", filial);
                        printf("    Em modo normal:\n");
                        printf("Clientes que efetuaram compras em modo normal:\n");
                        g_hash_table_foreach(q9->clientes_que_compraram_produto_N_filial, imprime_keys, NULL);
                        printf("\n");
                        printf("Número total de clientes envolvidos: %d\n\n", q9->total_clientes_N);
                        printf("  Em modo promoção:\n");
                        printf("Clientes que efetuaram compras em modo promoção:\n");
                        g_hash_table_foreach(q9->clientes_que_compraram_produto_P_filial, imprime_keys, NULL);
                        printf("\n");
                        printf("Número total de clientes envolvidos: %d\n\n", q9->total_clientes_P);
                        printf("Q -> voltar ao menu principal\n\n");
                        printf("-> ");
                        while (toupper(flagCycle[0]) != 'Q') {
                            scanf("%s", flagCycle);
                        }
                    } else {
                        printf("\n");
                        printf("Indique uma filial entre 1 e 3:\n");
                        printf("-> ");
                    }
                } else {
                    printf("\n");
                    printf("Insira uma filial válida:\n");
                    printf("-> ");
                }
            }
        } else {
            printf("\n");
            printf("Insira um código (que exista no sistema), sendo este composto por duas maiúsculas e quatro dígitos:\n");
            printf("-> ");
        }
    }
    system("clear");
}

void query10(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    char tmp[3];
    char codigoC[6];
    int mes;
    bool flagInput1 = true;
    bool flagInput2 = true;
    Clientes c = sgv_get_clientes(sgv);
    printf("Insira o código do cliente que pretende consultar:\n");
    printf("-> ");
    while (flagInput1) {
        scanf("%s", codigoC);
        if (valida_cliente(codigoC) && existe_cliente(c, codigoC)) {
            flagInput1 = false;
            printf("\n");
            printf("Insira o mês que pretende consultar:\n");
            while (flagInput2) {
                scanf("%s", tmp);
                if (isdigit(tmp[0])) {
                    mes = atoi(tmp);
                    if (mes > 0 && mes < 13) {
                        flagInput2 = false;
                        system("clear");
                        printf("----Listagem de produtos comprados por um cliente num determinado mês por ordem decrescente de quantidade----\n");
                        Query10 q10 = getClientFavoriteProducts(sgv, codigoC, mes);
                        printf("\n");
                        g_ptr_array_foreach(q10->produtos_por_quantidade, imprime_keys_for_ptr_array, NULL);
                        printf("\n");
                        printf("Q -> voltar ao menu principal\n\n");
                        printf("-> ");
                        while (toupper(flagCycle[0]) != 'Q') {
                            scanf("%s", flagCycle);
                        }
                    } else {
                        printf("\n");
                        printf("Insira um mês válido:\n");
                        printf("-> ");
                    }
                } else {
                    printf("\n");
                    printf("Insira um dígito entre 1 e 12:\n");
                    printf("-> ");
                }
            }
        } else {
            printf("\n");
            printf("Insira um código (que exista no sistema), sendo este composto por uma maiúscula e quatro dígitos:\n");
            printf("-> ");
        }
    }
    system("clear");
}

void query11(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    char tmp[3];
    int limit;
    bool flagInput1 = true;
    printf("Insira a quantidade de produtos dos quais pretende obter informação:\n");
    printf("-> ");
    while (flagInput1) {
        scanf("%s", tmp);
        if (isdigit(tmp[0])) {
            limit = atoi(tmp);
            if (limit > 0) {
                flagInput1 = false;
                system("clear");
                printf("----Listagem dos N produtos mais vendidos----\n");
                Query11 q11 = getTopSoldProducts(sgv, limit);
                printf("\n");
                g_ptr_array_foreach(q11->top_n, imprime_info, NULL);
                printf("\n");
                printf("Q -> voltar ao menu principal\n\n");
                printf("-> ");
                while (toupper(flagCycle[0]) != 'Q') {
                    scanf("%s", flagCycle);
                }
            } else {
                printf("\n");
                printf("Insira um número superior a 0\n");
                printf("-> ");
            }
        } else {
            printf("\n");
            printf("Insira um dígito válido\n");
            printf("-> ");
        }
    }
    system("clear");
}

void query12(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    char tmp[3];
    char codigoC[6];
    int limit;
    bool flagInput1 = true;
    bool flagInput2 = true;
    Clientes c = sgv_get_clientes(sgv);
    system("clear");
    printf("Insira o código do cliente que pretende consultar:\n");
    printf("-> ");
    while (flagInput1) {
        scanf("%s", codigoC);
        if (valida_cliente(codigoC) && existe_cliente(c, codigoC)) {
            flagInput1 = false;
            printf("\n");
            printf("Insira a quantidade de produtos dos quais pretende a informação:\n");
            printf("-> ");
            while (flagInput2) {
                scanf("%s", tmp);
                if (isdigit(tmp[0])) {
                    limit = atoi(tmp);
                    if (limit > 0) {
                        flagInput2 = false;
                        printf("----Lista dos N produtos em que um determinado cliente gastou mais dinheiro----\n");
                        Query12 q12 = getClientTopProfitProducts(sgv, codigoC, limit);
                        printf("\n");
                        g_ptr_array_foreach(q12->top_n, imprime_just_keys_produtos_cli, NULL);
                        printf("\n");
                        printf("Q -> voltar ao menu principal\n\n");
                        printf("-> ");
                        while (toupper(flagCycle[0]) != 'Q') {
                            scanf("%s", flagCycle);
                        }
                    } else {
                        printf("\n");
                        printf("Insira um limite válido:\n");
                        printf("-> ");
                    }
                } else {
                    printf("\n");
                    printf("Insira um dígito válido:\n");
                    printf("-> ");
                }
            }
        } else {
            printf("\n");
            printf("Insira um código (que exista no sistema), sendo este composto por uma maiúscula e quatro dígitos:\n");
            printf("-> ");
        }
    }
    system("clear");
}

void query13(SGV sgv) { //FIXME por a funcionar como as outras (só imprime o menu outra vez se se carregar em Q)
    printf("----Leitura  e verificação dos ficheiros de dados----\n\n");
    Query13 q13 = sgv_get_query_13(sgv);
    printf("  Foi lido o ficheiro \"Clientes.txt\":\n");
    printf("    Linhas lidas: %d\n", q13->linhas_lidas_clientes);
    printf("    Clientes válidos: %d\n\n", q13->linhas_validas_clientes);
    printf("\n");
    printf("  Foi lido o ficheiro \"Produtos.txt\":\n");
    printf("    Linhas lidas: %d\n", q13->linhas_lidas_produtos);
    printf("    Clientes válidos: %d\n\n", q13->linhas_validas_produtos);
    printf("\n");
    printf("  Foi lido o ficheiro \"Vendas.txt\":\n");
    printf("    Linhas lidas: %d\n", q13->linhas_lidas_vendas);
    printf("    Clientes válidos: %d\n\n", q13->linhas_validas_vendas);
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("\nForneça a pasta que contém os ficheiros de carregamento de dados.\n");
        printf("->    ./build/prog ../Dados\n");
        return 1;
    }
    bool flagCycle = true;
    SGV sgv = initSGV();
    loadSGVFromFiles(sgv, argv[1]);
    char opcaoQ1[2];
    opcaoQ1[0] = 'a';
    char tmp[2];
    int opcao = 14;
    while (flagCycle) {
        printf("\n------------------------------------------------------ Sistema de Gestão de Vendas ------------------------------------------------------\n\n");
        printf("Escolha uma opção:\n\n");
        printf("1 - Carregamento de dados para o sistema\n");
        printf("2 - Listagem de produtos começados por uma determinada letra e respetiva contagem\n");
        printf("3 - Total de vendas e faturação de um produto num determinado mês\n");
        printf("4 - Listagem e total de produtos que nunca foram comprados\n");
        printf("5 - Listagem de clientes que efetuaram compras em todas as filiais\n");
        printf("6 - Contagem de clientes que nunca efetuaram compras e produtos que nunca foram comprados\n");
        printf("7 - Contagem de compras efetuadas por um cliente, separadas por meses e filiais\n");
        printf("8 - Contagem de vendas e faturação total do SGV num intervalo de meses\n");
        printf("9 - Total de clientes que compraram um determinado produto numa determinada filial\n");
        printf("10 - Listagem de produtos comprados por um cliente num determinado mês por ordem decrescente de quantidade\n");
        printf("11 - Listagem dos N produtos mais vendidos\n");
        printf("12 - Lista dos N produtos em que um determinado cliente gastou mais dinheiro\n");
        printf("13 - Leitura  e verificação dos ficheiros de dados\n\n");
        printf("0 - Sair do programa\n");
        printf("\n\n\n");
        printf("Input -->  ");
        scanf("%s", tmp);
        if (isdigit(tmp[0])) {
            opcao = atoi(tmp);
        }
        printf("\n");
        switch (opcao) {
            case 1:
                system("clear");
                destroySGV(sgv);
                sgv = initSGV();
                loadSGVFromFiles(sgv, argv[1]);
                printf("\n");
                printf("Q -> voltar ao menu principal\n\n");
                printf("-> ");
                while (toupper(opcaoQ1[0]) != 'Q') {
                    scanf("%s", opcaoQ1);
                }
                system("clear");
                break;
            case 2:
                query2(sgv);
                break;
            case 3:
                query3(sgv);
                break;
            case 4:
                query4(sgv);
                break;
            case 5:
                query5(sgv);
                break;
            case 6:
                query6(sgv);
                break;
            case 7:
                query7(sgv);
                break;
            case 8:
                query8(sgv);
                break;
            case 9:
                query9(sgv);
                break;
            case 10:
                query10(sgv);
                break;
            case 11:
                query11(sgv);
                break;
            case 12:
                query12(sgv);
                break;
            case 13:
                query13(sgv);
                break;
            case 0:
                flagCycle = false;
                break;
            default:
                printf("Por favor escolha um numero entre 0 e 13:\n\n");
                printf("-> ");
                break;
        }
    }
    destroySGV(sgv);
    return 0;
}