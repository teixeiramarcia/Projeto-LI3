#include "sgv.h"
#include "util.h"
#include "navegador.h"
#include "colors.h"
#include <stdio.h>
#include <ctype.h>

void query2(SGV sgv) {
    char letra[2];
    bool flagInput1 = true;
    char flagCycle[2];
    flagCycle[0] = 'a';
    char aux;
    int i;
    printf(YELLOW "Indique a letra que pretende procurar:\n");
    printf("-> " RESET);
    while (flagInput1) {
        i = 0;
        while ((aux = fgetc(stdin)) != '\n') {
            if ((i + 1) < 2) {
                letra[i] = aux;
                i++;
            }
        }
        letra[i] = '\0';
        if (isalpha(letra[0])) {
            system("clear");
            printf("\n");
            flagInput1 = false;
            Query2 q2 = getProductsStartedByLetter(sgv, toupper(letra[0]));
            print_q2_with_navegador(q2);
            printf(BLUE "\nQ -> voltar ao menu principal\n\n");
            printf("-> " RESET);
            while (toupper(flagCycle[0]) != 'Q') {
                i = 0;
                while ((aux = fgetc(stdin)) != '\n') {
                    if ((i + 1) < 2) {
                        flagCycle[i] = aux;
                        i++;
                    }
                }
                flagCycle[i] = '\0';
            }
        } else {
            printf(RED "\nInput inválido.\n Indique uma letra:\n");
            printf("-> ");
            printf(RESET);
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
    char aux;
    char tipo[2];
    int i;
    Produtos p = sgv_get_produtos(sgv);
    printf(YELLOW "Insira o mês que pretende consultar:\n");
    printf("-> " RESET);
    while (flagInput1) {
        i = 0;
        while ((aux = fgetc(stdin)) != '\n') {
            if ((i + 1) < 3) {
                tmp[i] = aux;
                i++;
            }
        }
        tmp[i] = '\0';
        if (isdigit(tmp[0])) {
            mes = atoi(tmp);
            if (mes > 0 && mes < 13) {
                flagInput1 = false;
                printf(YELLOW "\nInsira o código do produto que pretende consultar:\n");
                printf("-> " RESET);
                while (flagInput2) {
                    i = 0;
                    while ((aux = fgetc(stdin)) != '\n') {
                        if ((i + 1) < 7) {
                            codigoP[i] = aux;
                            i++;
                        }
                    }
                    codigoP[i] = '\0';
                    if (valida_produto(codigoP) && existe_produto(p, codigoP)) {
                        flagInput2 = false;
                        printf(YELLOW "\nInsira G se pretende obter resultados globais ou F se pretende obter filial a filial:\n");
                        printf("-> " RESET);
                        while (flagInput3) {
                            i = 0;
                            while ((aux = fgetc(stdin)) != '\n') {
                                if ((i + 1) < 2) {
                                    tipo[i] = aux;
                                    i++;
                                }
                            }
                            tipo[i] = '\0';
                            if (toupper(tipo[0]) == 'G' || toupper(tipo[0]) == 'F') {
                                char type = tipo[0];
                                system("clear");
                                printf(BLUE "----Total de vendas e faturação de um produto num determinado mês----\n\n" RESET);
                                flagInput3 = false;
                                Query3 q3 = getProductSalesAndProfit(sgv, codigoP, mes);
                                if (type == 'G') {
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
                                    printf(YELLOW "Resultados gerais para o mês %d:\n\n", mes);
                                    printf("  Total de vendas em modo normal:" RESET "%d\n", total_vendas_normal);
                                    printf(YELLOW "  Total faturado em modo normal:" RESET "%f\n\n", faturacao_normal);
                                    printf(YELLOW "  Total de vendas em modo promoção:" RESET "%d\n",
                                           total_vendas_promocao);
                                    printf(YELLOW "  Total faturado em modo promoção:" RESET "%f\n\n",
                                           faturacao_promocao);
                                } else {
                                    printf(YELLOW "Resultados filial a filial para o mês %d:\n\n" RESET, mes);
                                    for (int filial = 0; filial < N_FILIAIS; ++filial) {
                                        printf(YELLOW "  Filial %d:\n\n" RESET, filial + 1);
                                        printf(YELLOW "    Total de vendas em modo normal:" RESET "%d\n",
                                               q3->vendas_normal[filial]);
                                        printf(YELLOW "    Total faturado em modo normal:" RESET "%f\n\n",
                                               q3->faturacao_normal[filial]);
                                        printf(YELLOW "    Total de vendas em modo promoção:" RESET "%d\n",
                                               q3->vendas_promocao[filial]);
                                        printf(YELLOW "    Total faturado em modo promoção:" RESET "%f\n\n",
                                               q3->faturacao_promocao[filial]);
                                    }
                                    printf("\n");
                                }
                                printf(BLUE "Q -> voltar ao menu principal\n\n");
                                printf("-> " RESET);
                                while (toupper(flagCycle[0]) != 'Q') {
                                    i = 0;
                                    while ((aux = fgetc(stdin)) != '\n') {
                                        if ((i + 1) < 2) {
                                            flagCycle[i] = aux;
                                            i++;
                                        }
                                    }
                                    flagCycle[i] = '\0';
                                }
                            } else {

                                printf(RED "\nInsira uma letra válida:\n");
                                printf("-> " RESET);
                            }
                        }
                    } else {

                        printf(RED "\nInsira um código (que exista no sistema), sendo este composto por duas maiúsculas e quatro dígitos:\n");
                        printf("-> " RESET);
                    }
                }
            } else {
                printf(RED "\nInsira um mês válido:\n");
                printf("-> " RESET);
            }
        } else {
            printf(RED "\nInsira um dígito válido:\n");
            printf("-> " RESET);
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
    char aux;
    int i;
    printf(YELLOW "Resultados globais - Insira 0:\n");
    printf("Resultados segregados por filiais - Insira 3:\n\n");
    printf("-> " RESET);
    while (flagInput1) {
        i = 0;
        while ((aux = fgetc(stdin)) != '\n') {
            if ((i + 1) < 2) {
                tmp[i] = aux;
                i++;
            }
        }
        tmp[i] = '\0';
        if (isdigit(tmp[0])) {
            tipo = atoi(tmp);
            if (tipo == 0 || tipo == 3) {
                flagInput1 = false;
                system("clear");
                printf("\n");
                Query4 q4 = getProductsNeverBought(sgv, tipo);
                print_q4_with_navegador(q4, tipo);
                printf(BLUE "\nQ -> voltar ao menu principal\n\n");
                printf("-> " RESET);
                while (toupper(flagCycle[0]) != 'Q') {
                    i = 0;
                    while ((aux = fgetc(stdin)) != '\n') {
                        if ((i + 1) < 2) {
                            flagCycle[i] = aux;
                            i++;
                        }
                    }
                    flagCycle[i] = '\0';
                }
            } else {
                printf(RED "\nEscolha uma das opções fornecidas:\n0 - Global\n 3 - Filial a Filial\n");
                printf("-> " RESET);
            }
        } else {
            printf(RED "\nEscolha uma das opções fornecidas:\n0 - Global\n3 - Filial a Filial:\n");
            printf("-> " RESET);
        }
    }
    system("clear");
}

void query5(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    char aux;
    int i;
    system("clear");
    printf("\n");
    Query5 q5 = getClientsOfAllBranches(sgv);
    print_q5_with_navegador(q5);
    printf(BLUE "\nQ -> voltar ao menu principal\n\n");
    printf("-> " RESET);
    while (toupper(flagCycle[0]) != 'Q') {
        i = 0;
        while ((aux = fgetc(stdin)) != '\n') {
            if ((i + 1) < 2) {
                flagCycle[i] = aux;
                i++;
            }
        }
        flagCycle[i] = '\0';
    }
    system("clear");
}

void query6(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    char aux;
    int i;
    system("clear");
    printf(BLUE "----Contagem de clientes que nunca efetuaram compras e de produtos que nunca foram comprados----\n\n");
    Query6 q6 = getClientsAndProductsNeverBoughtCount(sgv);
    printf("  Total de clientes que nunca efetuaram compras:" RESET " %d\n", q6->total_clientes_que_nunca_compraram);
    printf("\n");
    printf(YELLOW "  Total de produtos que nunca foram comprados:" RESET " %d\n\n", q6->total_produtos_nunca_comprados);
    printf(BLUE "Q -> voltar ao menu principal\n\n");
    printf("-> " RESET);
    while (toupper(flagCycle[0]) != 'Q') {
        i = 0;
        while ((aux = fgetc(stdin)) != '\n') {
            if ((i + 1) < 2) {
                flagCycle[i] = aux;
                i++;
            }
        }
        flagCycle[i] = '\0';
    }
    system("clear");
}

void query7(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    bool flagInput1 = true;
    char codigoC[6];
    char aux;
    int i;
    Clientes c = sgv_get_clientes(sgv);
    printf(YELLOW "Insira o código do cliente:\n");
    printf("-> " RESET);
    while (flagInput1) {
        i = 0;
        while ((aux = fgetc(stdin)) != '\n') {
            if ((i + 1) < 6) {
                codigoC[i] = aux;
                i++;
            }
        }
        codigoC[i] = '\0';
        if (valida_cliente(codigoC) && existe_cliente(c, codigoC)) {
            flagInput1 = false;
            system("clear");
            printf(BLUE "----Contagem de compras efetuadas por um cliente, separadas por meses e filiais----\n\n" RESET);
            Query7 q7 = getProductsBoughtByClient(sgv, codigoC);
            printf(YELLOW "%10s \uFF5C", "Filiais");
            for (int filial = 0; filial < N_FILIAIS; ++filial) {
                printf("%10d ", filial + 1);
            }
            printf("\n");
            for (int tracinho = 0; tracinho < 11 * (N_FILIAIS + 1) + 6; ++tracinho) {
                printf("—");
            }
            printf("\n" RESET);
            for (int mes = 0; mes < N_MONTHS; mes++) {
                printf(YELLOW "%10s \uFF5C" RESET, mes_to_string(MONTHS[mes]));
                for (int filial = 0; filial < N_FILIAIS; filial++) {
                    printf("%10d ", q7->n_produtos_comprados[filial][mes]);
                }
                printf("\n");
            }
            printf("\n\n");
            printf(BLUE "Q -> voltar ao menu principal\n\n");
            printf("-> " RESET);
            while (toupper(flagCycle[0]) != 'Q') {
                i = 0;
                while ((aux = fgetc(stdin)) != '\n') {
                    if ((i + 1) < 2) {
                        flagCycle[i] = aux;
                        i++;
                    }
                }
                flagCycle[i] = '\0';
            }
        } else {
            printf(RED "Input inválido.\n Insira um código de cliente válido:\n");
            printf("-> " RESET);
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
    char aux;
    int i;
    printf(YELLOW "Insira o mês que pretende que seja o limite inferior:\n");
    printf("-> " RESET);
    while (flagInput1) {
        i = 0;
        while ((aux = fgetc(stdin)) != '\n') {
            if ((i + 1) < 3) {
                tmp[i] = aux;
                i++;
            }
        }
        tmp[i] = '\0';
        if (isdigit(tmp[0])) {
            pmes = atoi(tmp);
            if (pmes > 0 && pmes < 13) {
                flagInput1 = false;
                printf(YELLOW "\nInsira o mês que pretende que seja o limite superior:\n");
                printf("-> " RESET);
                while (flagInput2) {
                    i = 0;
                    while ((aux = fgetc(stdin)) != '\n' && (i + 1) < 3) {
                        if ((i + 1) < 3) {
                            tmp[i] = aux;
                            i++;
                        }
                    }
                    tmp[i] = '\0';
                    if (isdigit(tmp[0])) {
                        umes = atoi(tmp);
                        if (umes >= pmes && umes < 13) {
                            flagInput2 = false;
                            system("clear");
                            printf(BLUE "----Contagem de vendas e faturação total do SGV num intervalo de meses----\n\n");
                            Query8 q8 = getSalesAndProfit(sgv, pmes, umes);
                            printf("  Total de vendas no intervalo de meses indicado:" RESET " %d\n",
                                   q8->total_vendas_meses);
                            printf(YELLOW "  Faturação total no intervalo de meses indicado:" RESET " %f\n\n",
                                   q8->total_faturado_meses);
                            printf(BLUE "Q -> voltar ao menu principal\n\n");
                            printf("-> " RESET);
                            while (toupper(flagCycle[0]) != 'Q') {
                                i = 0;
                                while ((aux = fgetc(stdin)) != '\n') {
                                    if ((i + 1) < 2) {
                                        flagCycle[i] = aux;
                                        i++;
                                    }
                                }
                                flagCycle[i] = '\0';
                            }
                        } else {
                            printf(RED "\nInsira um mês posterior ao que definiu como limite inferior:\n");
                            printf("-> " RESET);
                        }
                    } else {
                        printf(RED "\nInsira um dígito compreendido entre 1 e 12:\n");
                        printf("-> " RESET);
                    }
                }
            } else {
                printf(RED "\nInsira um mês válido:\n");
                printf("-> " RESET);
            }
        } else {
            printf(RED "\nInsira um dígito compreendido entre 1 e 12:\n");
            printf("-> " RESET);
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
    char aux;
    int i;
    Produtos p = sgv_get_produtos(sgv);
    printf(YELLOW "\nInsira o código do produto que pretende consultar:\n");
    printf("-> " RESET);
    while (flagInput1) {
        i = 0;
        while ((aux = fgetc(stdin)) != '\n') {
            if ((i + 1) < 7) {
                codigoP[i] = aux;
                i++;
            }
        }
        codigoP[i] = '\0';
        if (valida_produto(codigoP) && existe_produto(p, codigoP)) {
            flagInput1 = false;
            printf(YELLOW "\nInsira o número da filial:\n");
            printf("-> " RESET);
            while (flagInput2) {
                i = 0;
                while ((aux = fgetc(stdin)) != '\n') {
                    if ((i + 1) < 2) {
                        tmp[i] = aux;
                        i++;
                    }
                }
                tmp[i] = '\0';
                if (isdigit(tmp[0])) {
                    filial = atoi(tmp);
                    if (filial > 0 && filial < 4) {
                        flagInput2 = false;
                        system("clear");
                        printf(BLUE "----Total de clientes que compraram um determinado produto numa determinada filial----\n" RESET);
                        Query9 q9 = getProductBuyers(sgv, codigoP, filial);
                        printf(YELLOW "  Na filial %d\n", filial);
                        printf("Em modo normal:\n");
                        printf("Clientes que efetuaram compras em modo normal:\n" RESET);
                        g_hash_table_foreach(q9->clientes_que_compraram_produto_N_filial, imprime_keys, NULL);
                        printf(YELLOW "\nNúmero total de clientes envolvidos:" RESET " %d\n\n", q9->total_clientes_N);
                        printf(YELLOW "Em modo promoção:\n");
                        printf("Clientes que efetuaram compras em modo promoção:\n" RESET);
                        g_hash_table_foreach(q9->clientes_que_compraram_produto_P_filial, imprime_keys, NULL);
                        printf(YELLOW "\nNúmero total de clientes envolvidos:" RESET " %d\n\n", q9->total_clientes_P);
                        printf(BLUE "Q -> voltar ao menu principal\n\n");
                        printf("-> " RESET);
                        while (toupper(flagCycle[0]) != 'Q') {
                            i = 0;
                            while ((aux = fgetc(stdin)) != '\n') {
                                if ((i + 1) < 2) {
                                    flagCycle[i] = aux;
                                    i++;
                                }
                            }
                            flagCycle[i] = '\0';
                        }
                    } else {
                        printf(RED "\nIndique uma filial entre 1 e 3:\n");
                        printf("-> " RESET);
                    }
                } else {
                    printf(RED "\nInsira uma filial válida:\n");
                    printf("-> " RESET);
                }
            }
        } else {
            printf(RED "\nInsira um código (que exista no sistema), sendo este composto por duas maiúsculas e quatro dígitos:\n");
            printf("-> " RESET);
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
    char aux;
    int i;
    Clientes c = sgv_get_clientes(sgv);
    printf(YELLOW "Insira o código do cliente que pretende consultar:\n");
    printf("-> " RESET);
    while (flagInput1) {
        i = 0;
        while ((aux = fgetc(stdin)) != '\n') {
            if ((i + 1) < 6) {
                codigoC[i] = aux;
                i++;
            }
        }
        codigoC[i] = '\0';
        if (valida_cliente(codigoC) && existe_cliente(c, codigoC)) {
            flagInput1 = false;
            printf(YELLOW "\nInsira o mês que pretende consultar:\n");
            printf("-> " RESET);
            while (flagInput2) {
                i = 0;
                while ((aux = fgetc(stdin)) != '\n') {
                    if ((i + 1) < 3) {
                        tmp[i] = aux;
                        i++;
                    }
                }
                tmp[i] = '\0';
                if (isdigit(tmp[0])) {
                    mes = atoi(tmp);
                    if (mes > 0 && mes < 13) {
                        flagInput2 = false;
                        system("clear");
                        Query10 q10 = getClientFavoriteProducts(sgv, codigoC, mes);
                        print_q10_with_navegador(q10);
                        printf(BLUE "\nQ -> voltar ao menu principal\n\n");
                        printf("-> " RESET);
                        while (toupper(flagCycle[0]) != 'Q') {
                            i = 0;
                            while ((aux = fgetc(stdin)) != '\n') {
                                if ((i + 1) < 2) {
                                    flagCycle[i] = aux;
                                    i++;
                                }
                            }
                            flagCycle[i] = '\0';
                        }
                    } else {
                        printf(RED "\nInsira um mês válido:\n");
                        printf("-> " RESET);
                    }
                } else {
                    printf(RED "\nInsira um dígito entre 1 e 12:\n");
                    printf("-> " RESET);
                }
            }
        } else {
            printf(RED "\nInsira um código (que exista no sistema), sendo este composto por uma maiúscula e quatro dígitos:\n");
            printf("-> " RESET);
        }
    }
    system("clear");
}

void query11(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    char tmp[6];
    int limit;
    bool flagInput1 = true;
    char aux;
    int i;
    printf(YELLOW "Insira a quantidade de produtos dos quais pretende obter informação:\n");
    printf("-> " RESET);
    while (flagInput1) {
        i = 0;
        while ((aux = fgetc(stdin)) != '\n') {
            if ((i + 1) < 6) {
                tmp[i] = aux;
                i++;
            }
        }
        tmp[i] = '\0';
        if (isdigit(tmp[0])) {
            limit = atoi(tmp);
            if (limit > 0) {
                flagInput1 = false;
                system("clear");
                Query11 q11 = getTopSoldProducts(sgv, limit);
                print_q11_with_navegador(q11);
                printf(BLUE "\nQ -> voltar ao menu principal\n\n");
                printf("-> " RESET);
                while (toupper(flagCycle[0]) != 'Q') {
                    i = 0;
                    while ((aux = fgetc(stdin)) != '\n') {
                        if ((i + 1) < 2) {
                            flagCycle[i] = aux;
                            i++;
                        }
                    }
                    flagCycle[i] = '\0';
                }
            } else {
                printf(RED "\nInsira um número superior a 0\n");
                printf("-> " RESET);
            }
        } else {
            printf(RED "\nInsira um dígito válido\n");
            printf("-> " RESET);
        }
    }
    system("clear");
}

void query12(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    char tmp[6];
    char codigoC[6];
    int limit;
    bool flagInput1 = true;
    bool flagInput2 = true;
    char aux;
    int i;
    Clientes c = sgv_get_clientes(sgv);
    system("clear");
    printf(YELLOW "Insira o código do cliente que pretende consultar:\n");
    printf("-> " RESET);
    while (flagInput1) {
        i = 0;
        while ((aux = fgetc(stdin)) != '\n') {
            if ((i + 1) < 6) {
                codigoC[i] = aux;
                i++;
            }
        }
        codigoC[i] = '\0';
        if (valida_cliente(codigoC) && existe_cliente(c, codigoC)) {
            flagInput1 = false;
            printf(YELLOW "\nInsira a quantidade de produtos dos quais pretende a informação:\n");
            printf("-> " RESET);
            while (flagInput2) {
                i = 0;
                while ((aux = fgetc(stdin)) != '\n') {
                    if ((i + 1) < 6) {
                        tmp[i] = aux;
                        i++;
                    }
                }
                tmp[i] = '\0';
                if (isdigit(tmp[0])) {
                    limit = atoi(tmp);
                    if (limit > 0) {
                        flagInput2 = false;
                        system("clear");
                        Query12 q12 = getClientTopProfitProducts(sgv, codigoC, limit);
                        print_q12_with_navegador(q12);
                        printf(BLUE "\nQ -> voltar ao menu principal\n\n");
                        printf("-> " RESET);
                        while (toupper(flagCycle[0]) != 'Q') {
                            i = 0;
                            while ((aux = fgetc(stdin)) != '\n') {
                                if ((i + 1) < 2) {
                                    flagCycle[i] = aux;
                                    i++;
                                }
                            }
                            flagCycle[i] = '\0';
                        }
                    } else {
                        printf(RED "\nInsira um limite válido:\n");
                        printf("-> " RESET);
                    }
                } else {
                    printf(RED "\nInsira um dígito válido:\n");
                    printf("-> " RESET);
                }
            }
        } else {
            printf(RED "\nInsira um código (que exista no sistema), sendo este composto por uma maiúscula e quatro dígitos:\n");
            printf("-> " RESET);
        }
    }
    system("clear");
}

void query13(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    char aux;
    int i;
    printf(BLUE "----Leitura  e verificação dos ficheiros de dados----\n\n");
    Query13 q13 = sgv_get_query_13(sgv);
    printf("  Foi lido o ficheiro \"Clientes.txt\":\n" RESET);
    printf(YELLOW "    Linhas lidas:" RESET " %d\n", q13->linhas_lidas_clientes);
    printf(YELLOW "    Clientes válidos:" RESET " %d\n\n", q13->linhas_validas_clientes);
    printf(BLUE "\n  Foi lido o ficheiro \"Produtos.txt\":\n" RESET);
    printf(YELLOW "    Linhas lidas:" RESET " %d\n", q13->linhas_lidas_produtos);
    printf(YELLOW "    Clientes válidos:" RESET " %d\n\n", q13->linhas_validas_produtos);
    printf(BLUE "\n  Foi lido o ficheiro \"Vendas.txt\":\n" RESET);
    printf(YELLOW "    Linhas lidas:" RESET " %d\n", q13->linhas_lidas_vendas);
    printf(YELLOW "    Clientes válidos:" RESET " %d\n\n", q13->linhas_validas_vendas);
    printf(BLUE"Q -> voltar ao menu principal\n\n");
    printf("-> " RESET);
    while (toupper(flagCycle[0]) != 'Q') {
        i = 0;
        while ((aux = fgetc(stdin)) != '\n') {
            if ((i + 1) < 2) {
                flagCycle[i] = aux;
                i++;
            }
        }
        flagCycle[i] = '\0';
    }
    system("clear");
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf(RED);
        printf("\nForneça a pasta que contém os ficheiros de carregamento de dados.\n");
        printf("->    ./build/prog ../Dados\n");
        printf(RESET);
        return 1;
    }
    bool flagCycle = true;
    system("clear");
    SGV sgv = initSGV();
    loadSGVFromFiles(sgv, argv[1]);
    char opcaoQ1[2];
    opcaoQ1[0] = 'a';
    char tmp[3];
    int opcao = 14;
    char aux;
    int i;
    bool no_errors = true;
    while (flagCycle) {
        if (no_errors) {
            printf(BLUE);
            printf("\n------------------------------------------------------ SISTEMA DE GESTÃO DE VENDAS ------------------------------------------------------\n\n");
            printf(RESET);
            printf(YELLOW);
            printf("Escolha uma opção:\n\n");
            printf(RESET);
            printf(YELLOW " 1 -> " RESET "Carregamento de dados para o sistema\n");
            printf(YELLOW " 2 -> " RESET "Listagem de produtos começados por uma determinada letra e respetiva contagem\n");
            printf(YELLOW " 3 -> " RESET "Total de vendas e faturação de um produto num determinado mês\n");
            printf(YELLOW " 4 -> " RESET "Listagem e total de produtos que nunca foram comprados\n");
            printf(YELLOW " 5 -> " RESET "Listagem de clientes que efetuaram compras em todas as filiais\n");
            printf(YELLOW " 6 -> " RESET "Contagem de clientes que nunca efetuaram compras e produtos que nunca foram comprados\n");
            printf(YELLOW " 7 -> " RESET "Contagem de compras efetuadas por um cliente, separadas por meses e filiais\n");
            printf(YELLOW " 8 -> " RESET "Contagem de vendas e faturação total do SGV num intervalo de meses\n");
            printf(YELLOW " 9 -> " RESET "Total de clientes que compraram um determinado produto numa determinada filial\n");
            printf(YELLOW "10 -> " RESET "Listagem de produtos comprados por um cliente num determinado mês por ordem decrescente de quantidade\n");
            printf(YELLOW "11 -> " RESET "Listagem dos N produtos mais vendidos\n");
            printf(YELLOW "12 -> " RESET "Lista dos N produtos em que um determinado cliente gastou mais dinheiro\n");
            printf(YELLOW "13 -> " RESET "Leitura  e verificação dos ficheiros de dados\n\n");
            printf(YELLOW " 0 -> " RESET "Sair do programa\n");
            printf("\n\n\n");
            strcpy(tmp, "a");
            printf(BLUE);
            printf("Input -->  ");
            printf(RESET);
        } else {
            printf("\033[1;31m");
            printf("Input inválido.\nIndique um dígito entre 0 e 13\n");
            printf("Input -->  ");
            printf("\033[0m");
            no_errors = true;
        }
        i = 0;
        while ((aux = fgetc(stdin)) != '\n') {
            if (i + 1 < 3) {
                tmp[i] = aux;
                i++;
            }
        }
        tmp[i] = '\0';
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
                strcpy(opcaoQ1, "a");
                while (toupper(opcaoQ1[0]) != 'Q') {
                    i = 0;
                    while ((aux = fgetc(stdin)) != '\n') {
                        if ((i + 1) < 2) {
                            opcaoQ1[i] = aux;
                            i++;
                        }
                    }
                    opcaoQ1[i] = '\0';
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
                no_errors = false;
                break;
        }
    }
    destroySGV(sgv);
    return 0;
}