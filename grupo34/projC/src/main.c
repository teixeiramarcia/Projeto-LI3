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
    while (flagInput1) {
        scanf("%s", letra);
        if (isalpha(letra[0])) {
            system("clear");
            printf("----Listagem de produtos começados por uma determinada letra e respetiva contagem----\n");
            flagInput1 = false;
            Query2 q2 = getProductsStartedByLetter(sgv, toupper(letra[0]));
            g_hash_table_foreach(q2->produtos_letra, imprime_keys, NULL);
            printf("Total: %d\n\n", g_hash_table_size(q2->produtos_letra));
            printf("Q -> voltar ao menu principal\n");
            while (toupper(flagCycle[0]) != 'Q') {
                scanf("%s", flagCycle);
            }
        } else printf("Input inválido.\n Indique uma letra:\n");
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
    printf("Escreva o mês que deseja procurar:\n");
    while (flagInput1) {
        scanf("%s", tmp);
        if (isdigit(tmp[0])) {
            mes = atoi(tmp);

            if (mes > 0 && mes < 13) {
                flagInput1 = false;
                printf("Escreva o codigo do produto que deseja procurar:\n");
                while (flagInput2) {
                    scanf("%s", codigoP);

                    if (valida_produto(codigoP) && existe_produto(p, codigoP)) {
                        flagInput2 = false;
                        printf("Escreva G se deja ver o resultado global ou F se quiser ver filial a filial\n");

                        while (flagInput3) {
                            scanf("%s", tipo);
                            if (toupper(tipo[0]) == 'G' || toupper(tipo[0]) == 'F') {
                                system("clear");
                                flagInput3 = false;
                                getProductSalesAndProfit(sgv, codigoP, mes);

                                printf("Prima Q para voltar ao Menu Principal\n");
                                while (toupper(flagCycle[0]) != 'Q') {
                                    scanf("%s", flagCycle);
                                }
                            } else printf("Escreva G ou F\n");
                        }

                    } else
                        printf("Escreva um codigo com duas letras maiusculas e quatro numeros que exista no sistema\n");
                }
            } else printf("Escreva um número entre 1 e 12\n");
        } else printf("Escreva um número entre 1 e 12\n");
    }
    system("clear");
}

void query4(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    bool flagInput1 = true;
    char tmp[2];
    int tipo;
    printf("Opções:\n");
    printf("Resultados globais - insira 0\n");
    printf("Resultados segregados por filiais - insira 3\n");
    while (flagInput1) {
        scanf("%s", tmp);
        if (isdigit(tmp[0])) {
            tipo = atoi(tmp);
            if (tipo == 0 || tipo == 3) {
                flagInput1 = false;
                system("clear");
                printf("----Listagem e total de produtos que nunca foram comprados----\n");
                Query4 q4 = getProductsNeverBought(sgv, tipo);
                if (tipo == 0) {
                    printf("Produtos nunca comprados:\n");
                    g_hash_table_foreach(q4->produtos_nunca_comprados_global, imprime_keys, NULL);
                    printf("Total: %d\n\n", q4->total_produtos_nao_comprados_global);
                } else {
                    for (int filial = 0; filial < N_FILIAIS; ++filial) {
                        printf("Produtos nunca comprados na filial %d\n", filial + 1);
                        g_hash_table_foreach(q4->produtos_nunca_comprados[filial], imprime_keys, NULL);
                        printf("Total: %d\n\n", q4->total_produtos_nao_comprados[filial]);
                    }
                }
                printf("Q -> voltar ao menu principal\n");
                while (toupper(flagCycle[0]) != 'Q') {
                    scanf("%s", flagCycle);
                }
            } else printf("Escolha uma das opções fornecidas: 0 - Global ou 3 - Filial a Filial\n");
        } else printf("Escolha uma das opções fornecidas: 0 - Global ou 3 - Filial a Filial\n");
    }
    system("clear");
}

void query5(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    system("clear");
    printf("----Listagem de clientes que efetuaram compras em todas as filiais----\n");
    Query5 q5 = getClientsOfAllBranches(sgv);
    g_ptr_array_foreach(q5->clientes, imprime_just_keys_clientes, NULL);
    printf("\n");
    printf("Q -> voltar ao menu principal\n");
    while (toupper(flagCycle[0]) != 'Q') {
        scanf("%s", flagCycle);
    }
    system("clear");
}

void query6(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    system("clear");
    printf("----Contagem de clientes que nunca efetuaram compras e de produtos que nunca foram comprados----\n");
    Query6 q6 = getClientsAndProductsNeverBoughtCount(sgv);
    printf("Total de clientes que nunca efetuaram compras: %d\n", q6->total_clientes_que_nunca_compraram);
    printf("Total de produtos que nunca foram comprados: %d\n", q6->total_produtos_nunca_comprados);
    printf("\n");
    printf("Q -> voltar ao menu principal\n");
    while (toupper(flagCycle[0]) != 'Q') {
        scanf("%s", flagCycle);
    }
    system("clear");
}

void query7(SGV sgv) {
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
            //FIXME falta fazer os prints
            printf("Q -> voltar ao menu principal\n");
            while (toupper(flagCycle[0]) != 'Q') {
                scanf("%s", flagCycle);
            }
        } else printf("Input inválido.\n Insira um código de cliente válido:\n");
    }
    system("clear");
}

void query8(SGV sgv) { //FIXME texto dos else's
    char flagCycle[2];
    flagCycle[0] = 'a';
    char tmp[3];
    int pmes;
    int umes;
    bool flagInput1 = true;
    bool flagInput2 = true;
    printf("Insira o mês que pretende que seja o limite inferior:\n");
    while (flagInput1) {
        scanf("%s", tmp);
        if (isdigit(tmp[0])) {
            pmes = atoi(tmp);
            if (pmes > 0 && pmes < 13) {
                flagInput1 = false;
                printf("Escreva o ultimo mes\n");
                while (flagInput2) {
                    scanf("%s", tmp);
                    if (isdigit(tmp[0])) {
                        umes = atoi(tmp);
                        if (umes >= pmes && umes < 13) {
                            flagInput2 = false;
                            system("clear");
                            printf("----Contagem de vendas e faturação total do SGV num intervalo de meses----\n");
                            Query8 q8 = getSalesAndProfit(sgv, pmes, umes);
                            //FIXME falta fazer os prints
                            printf("Q -> voltar ao menu principal\n");
                            while (toupper(flagCycle[0]) != 'Q') {
                                scanf("%s", flagCycle);
                            }
                        } else printf("Escreva um mes entre o primeiro e 12 \n");
                    } else printf("Escreva um mes entre o primeiro e 12 \n");
                }
            } else printf("Escreva um mes entre 1 e 12 \n");
        } else printf("Escreva um mes entre 1 e 12 \n");
    }
    system("clear");
}

void query9(SGV sgv) { //FIXME texto dos else's
    char flagCycle[2];
    flagCycle[0] = 'a';
    bool flagInput1 = true;
    bool flagInput2 = true;
    char tmp[2];
    char codigoP[7];
    int filial;
    Produtos p = sgv_get_produtos(sgv);
    printf("Insira o código do produto:\n");
    while (flagInput1) {
        scanf("%s", codigoP);
        if (valida_produto(codigoP) && existe_produto(p, codigoP)) {
            flagInput1 = false;
            printf("Insira o número da filial:\n");
            while (flagInput2) {
                scanf("%s", tmp);
                if (isdigit(tmp[0])) {
                    filial = atoi(tmp);
                    if (filial > 0 && filial < 4) {
                        flagInput2 = false;
                        system("clear");
                        printf("----Total de clientes que compraram um determinado produto numa determinada filial----\n");
                        Query9 q9 = getProductBuyers(sgv, codigoP, filial);
                        //FIXME falta fazer os prints
                        printf("Q -> voltar ao menu principal\n");
                        while (toupper(flagCycle[0]) != 'Q') {
                            scanf("%s", flagCycle);
                        }
                    } else printf("Escreva um valor entre 1 e 3\n");
                } else printf("Escreva um valor entre 1 e 3\n");
            }
        } else printf("Escreva um codigo com duas letras maiusculas e quatro numeros que exista no sistema\n");
    }
    system("clear");
}

//FIXME falta rever

void query10(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    char tmp[3];
    char codigoC[6];
    int mes;
    bool flagInput1 = true;
    bool flagInput2 = true;
    Clientes c = sgv_get_clientes(sgv);
    printf("Escreva o codigo do cliente\n");
    while (flagInput1) {
        scanf("%s", codigoC);
        if (valida_cliente(codigoC) && existe_cliente(c, codigoC)) {
            flagInput1 = false;
            printf("Escreva o mês\n");
            while (flagInput2) {
                scanf("%s", tmp);

                if (isdigit(tmp[0])) {
                    mes = atoi(tmp);

                    if (mes > 0 && mes < 13) {
                        flagInput2 = false;
                        system("clear");
                        printf("Ainda estamos a tratar, tente mais tarde\n");

                        printf("Prima Q para voltar ao Menu Principal\n");
                        while (toupper(flagCycle[0]) != 'Q') {
                            scanf("%s", flagCycle);
                        }
                    } else printf("Escreva um valor entre 1 e 12\n");
                } else printf("Escreva um valor entre 1 e 12\n");
            }
        } else printf("Escreva um codigo com uma letra maiuscula e quatro numeros que exista no sistema\n");
    }
    system("clear");
}

void query11(SGV sgv) {
    char flagCycle[2];
    flagCycle[0] = 'a';
    char tmp[3];
    int limit;
    bool flagInput1 = true;
    printf("Escreva de quantos produtos quer a informação\n");
    while (flagInput1) {
        scanf("%s", tmp);
        if (isdigit(tmp[0])) {
            limit = atoi(tmp);

            if (limit > 0) {
                flagInput1 = false;
                system("clear");
                getTopSoldProducts(sgv, limit);

                printf("Prima Q para voltar ao Menu Principal\n");
                while (toupper(flagCycle[0]) != 'Q') {
                    scanf("%s", flagCycle);
                }
            } else printf("Escreva um numero maior que 0\n");
        } else printf("Escreva um numero maior que 0\n");
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
    printf("Escreva o codigo do cliente\n");
    while (flagInput1) {
        scanf("%s", codigoC);
        if (valida_cliente(codigoC) && existe_cliente(c, codigoC)) {
            flagInput1 = false;
            printf("Escreva de quantos produtos quer a informação\n");
            while (flagInput2) {
                scanf("%s", tmp);

                if (isdigit(tmp[0])) {
                    limit = atoi(tmp);

                    if (limit > 0) {
                        flagInput2 = false;
                        printf("Ainda estamos a tratar, tente mais tarde\n");

                        printf("Prima Q para voltar ao Menu Principal\n");
                        while (toupper(flagCycle[0]) != 'Q') {
                            scanf("%s", flagCycle);
                        }
                    } else printf("Escreva um numero maior que 0\n");
                } else printf("Escreva um numero maior que 0\n");
            }
        } else printf("Escreva um codigo com uma letra maiusculas e quatro numeros que exista no sistema\n");
    }
    system("clear");
}

//FIXME até aqui

void query13(SGV sgv) {
    printf("----Leitura  e verificação dos ficheiros de dados----\n\n");
    Query13 q13 = sgv_get_query_13(sgv);
    printf("Foi lido o ficheiro \"Clientes.txt\":\n");
    printf("Linhas lidas: %d\n", q13->linhas_lidas_clientes);
    printf("Clientes válidos: %d\n\n", q13->linhas_validas_clientes);
    printf("Foi lido o ficheiro \"Produtos.txt\":\n");
    printf("Linhas lidas: %d\n", q13->linhas_lidas_produtos);
    printf("Clientes válidos: %d\n\n", q13->linhas_validas_produtos);
    printf("Foi lido o ficheiro \"Vendas.txt\":\n");
    printf("Linhas lidas: %d\n", q13->linhas_lidas_vendas);
    printf("Clientes válidos: %d\n\n", q13->linhas_validas_vendas);
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("Please Provide Data Folder\n");
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
        printf("\n------------------------------------------------------ Sistema de Gestão de Vendas ------------------------------------------------------\n");
        printf("Escolha uma opção:\n");
        printf("1 - Carregamento de dados para o sistema\n");
        printf("2 - Listagem de produtos começados por uma determinada letra e respetiva contagem\n");
        printf("3 - Total de vendas e faturação de um produto num determinado mês\n");
        printf("4 - Listagem e total de produtos que nunca foram comprados\n");
        printf("5 - Listagem de clientes que efetuaram compras em todas as filiais\n");
        printf("6 - Contagem de clientes que nunca efetuaram compras e produtos que nunca foram comprados\n");
        printf("7 - Contagem de compras efetuadas por um cliente, separadas por meses e filiais\n");
        printf("8 - Contagem de vendas e faturação total do SGV num intervalo de meses\n");
        printf("9 - Total de clientes que compraram um determinado produto numa determinada filial\n");
        printf("10 - Listagem de produtos comprados por um cliente num determinado mês por ordem decerscente de quantidade\n");
        printf("11 - Listagem dos N produtos mais vendidos\n");
        printf("12 - Lista dos N produtos em que um determinado cliente gastou mais dinheiro\n");
        printf("13 - Leitura  e verificação dos ficheiros de dados\n\n");
        printf("0 - Sair do programa\n");
        printf("\n\n\n");
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
                printf("Prima Q para voltar ao Menu Principal\n");
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
                printf("Por favor escolha um numero entre 0 e 12\n");
                break;
        }
    }
    destroySGV(sgv);
    return 0;
}
