#include "sgv.h"
#include <stdio.h>
#include <ctype.h>


void query2(SGV sgv){
    char letra[2];
    bool flagInput1 = true;
    char flagCycle[2];
    flagCycle[0] = 'a';
    system("clear");
    printf("Escreva a letra que deseja procurar:\n");
    while(flagInput1){
        scanf("%s", letra);
        
        if(isalpha(letra[0])){
            flagInput1 = false;
            getProductsStartedByLetter(sgv, toupper(letra[0]));
            
            printf("Prima Q para voltar ao Menu Principal\n");
            while (toupper(flagCycle[0]) != 'Q'){
                scanf("%s", flagCycle);
            }
        }
        else printf("Escreva uma letra\n");
    }
    system("clear");
}

void query3(SGV sgv){
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
    system("clear");
    printf("Escreva o mês que deseja procurar:\n");
    while (flagInput1){
        scanf("%s", tmp);
        if(isdigit(tmp[0])){
            mes = atoi(tmp);
            
            if(mes > 0 && mes < 13){
                flagInput1 = false;
                printf("Escreva o codigo do produto que deseja procurar:\n");
                while (flagInput2){
                    scanf("%s", codigoP);
                    
                    if(valida_produto(codigoP) && existe_produto(p, codigoP)){
                        flagInput2 = false;
                        printf("Escreva G se deja ver o resultado global ou F se quiser ver filial a filial\n");
                        
                        while (flagInput3){
                            scanf("%s", tipo);
                            if (toupper(tipo[0]) == 'G' || toupper(tipo[0]) == 'F'){
                                flagInput3 = false;
                                getProductSalesAndProfit(sgv, codigoP, mes);
                                
                                printf("Prima Q para voltar ao Menu Principal\n");
                                while (toupper(flagCycle[0]) != 'Q'){
                                    scanf("%s", flagCycle);
                                }
                            }
                            else printf("Escreva G ou F\n");
                        }
                
                    }
                    else printf("Escreva um codigo com duas letras maiusculas e quatro numeros que exista no sistema\n");
                }
            }
            else printf("Escreva um número entre 1 e 12\n");
        }
        else printf("Escreva um número entre 1 e 12\n");
    }
    system("clear");
}

void query4(SGV sgv){
    char flagCycle[2];
    flagCycle[0] = 'a';
    bool flagInput1 = true;
    char tmp[2];
    int tipo;
    system("clear");
    printf("Escreva o numero da filial que deja ver ou 0 se quer ver todas as filiais\n");
    while (flagInput1){
        scanf("%s", tmp);
        if(isdigit(tmp[0])){
            tipo = atoi(tmp);
            if(tipo >= 0 && tipo < 4){
                flagInput1 = false;
                getProductsNeverBought(sgv, tipo);
            
                printf("Prima Q para voltar ao Menu Principal\n");
                while (toupper(flagCycle[0]) != 'Q'){
                    scanf("%s", flagCycle);
                }
            }
            else printf("Escreva um numero entre 0 e 3\n");
        }
        else printf("Escreva um numero entre 0 e 3\n");
    }
    system("clear");
}

void query5(SGV sgv){
    char flagCycle[2];
    flagCycle[0] = 'a';
    system("clear");
    getClientsOfAllBranches(sgv);
    printf("Prima Q para voltar ao Menu Principal\n");
    while (toupper(flagCycle[0]) != 'Q'){
        scanf("%s", flagCycle);
    }
    system("clear");
}

void query6(SGV sgv){
    char flagCycle[2];
    flagCycle[0] = 'a';
    system("clear");
    getClientsAndProductsNeverBoughtCount(sgv);
    printf("Prima Q para voltar ao Menu Principal\n");
    while (toupper(flagCycle[0]) != 'Q'){
        scanf("%s", flagCycle);
    }
    system("clear");
}

void query7(SGV sgv){
    char flagCycle[2];
    flagCycle[0] = 'a';
    bool flagInput1 = true;
    char codigoC[6];
    Clientes c = sgv_get_clientes(sgv);
    system("clear");
    printf("Escreva o codigo do cliente\n");
    while(flagInput1){
        scanf("%s", codigoC);
        if(valida_cliente(codigoC) && existe_cliente(c, codigoC)){
            flagInput1 = false;
            getProductsBoughtByClient(sgv, codigoC);

            printf("Prima Q para voltar ao Menu Principal\n");
            while (toupper(flagCycle[0]) != 'Q'){
                scanf("%s", flagCycle);
            }
        }
        else printf("Escreva um codigo com uma letra maiuscula e quatro numeros que exista no sistema\n");
    }
    system("clear");
}

void query8(SGV sgv){
    char flagCycle[2];
    flagCycle[0] = 'a';
    char tmp[3];
    int pmes;
    int umes;
    bool flagInput1 = true;
    bool flagInput2 = true;
    system("clear");
    printf("Escreva o primeiro mes\n");
    while(flagInput1){
        scanf("%s", tmp);
        if(isdigit(tmp[0])){
            pmes = atoi(tmp);
            
            if (pmes > 0 && pmes < 13){
                flagInput1 = false;
                printf("Escreva o ultimo mes\n");
                while(flagInput2){
                    scanf("%s", tmp);
                    
                    if(isdigit(tmp[0])){
                        umes = atoi(tmp);
                        
                        if(umes >= pmes && umes < 13){
                            flagInput2 = false;
                            getSalesAndProfit(sgv, pmes, umes);
                            
                            printf("Prima Q para voltar ao Menu Principal\n");
                            while (toupper(flagCycle[0]) != 'Q'){
                                scanf("%s", flagCycle);
                            }
                        }
                        else printf("Escreva um mes entre o primeiro e 12 \n");
                    }
                    else printf("Escreva um mes entre o primeiro e 12 \n");
                }
            }
            else printf("Escreva um mes entre 1 e 12 \n");
        }
        else printf("Escreva um mes entre 1 e 12 \n");
    }
    system("clear");
}

void query9(SGV sgv){
    char flagCycle[2];
    flagCycle[0] = 'a';
    bool flagInput1 = true;
    bool flagInput2 = true;
    char tmp[2];
    char codigoP[7];
    int filial;
    Produtos p = sgv_get_produtos(sgv);
    system("clear");
    printf("Escreva o codigo do produto\n");
    while(flagInput1){
        scanf("%s", codigoP);
        
        if(valida_produto(codigoP) && existe_produto(p, codigoP)){
            flagInput1 = false;
            printf("Escreva o número da filial\n");
            while(flagInput2){
                scanf("%s", tmp);

                if(isdigit(tmp[0])){
                    filial = atoi(tmp);
                    
                    if(filial > 0 && filial < 4){
                        flagInput2 = false;
                        getProductBuyers(sgv, codigoP, filial);

                        printf("Prima Q para voltar ao Menu Principal\n");
                        while (toupper(flagCycle[0]) != 'Q'){
                            scanf("%s", flagCycle);
                        }
                    }
                    else printf("Escreva um valor entre 1 e 3\n");
                }
                else printf("Escreva um valor entre 1 e 3\n");
            }
        }
        else printf("Escreva um codigo com duas letras maiusculas e quatro numeros que exista no sistema\n");
    }
    system("clear");
}

void query10(SGV sgv){
    char flagCycle[2];
    flagCycle[0] = 'a';
    char tmp[3];
    char codigoC[6];
    int mes;
    bool flagInput1 = true;
    bool flagInput2 = true;
    Clientes c = sgv_get_clientes(sgv);
    system("clear");
    printf("Escreva o codigo do cliente\n");
    while(flagInput1){
        scanf("%s", codigoC);
        if(valida_cliente(codigoC) && existe_cliente(c, codigoC)){
            flagInput1 = false;
            printf("Escreva o mês\n");
            while(flagInput2){
                scanf("%s", tmp);

                if (isdigit(tmp[0])){
                    mes = atoi(tmp);
                    
                    if(mes > 0 && mes < 13){
                        flagInput2 = false;
                        printf("Ainda estamos a tratar, tente mais tarde\n");

                        printf("Prima Q para voltar ao Menu Principal\n");
                        while (toupper(flagCycle[0]) != 'Q'){
                            scanf("%s", flagCycle);
                        }
                    }
                    else printf("Escreva um valor entre 1 e 12\n");
                }
                else printf("Escreva um valor entre 1 e 12\n");
            }
        }
        else printf("Escreva um codigo com uma letra maiuscula e quatro numeros que exista no sistema\n");
    }
    system("clear");
}

void query11(SGV sgv){
    char flagCycle[2];
    flagCycle[0] = 'a';
    char tmp[3];
    int limit;
    bool flagInput1 = true;
    system("clear");
    printf("Escreva de quantos produtos quer a informação\n");
    while(flagInput1){
        scanf("%s", tmp);
        if(isdigit(tmp[0])){
            limit = atoi(tmp);
            
            if (limit > 0){
                flagInput1 = false;
                getTopSoldProducts(sgv, limit);

                printf("Prima Q para voltar ao Menu Principal\n");
                while (toupper(flagCycle[0]) != 'Q'){
                    scanf("%s", flagCycle);
                }
            }
            else printf("Escreva um numero maior que 0\n");
        }
        else printf("Escreva um numero maior que 0\n");
    }
    system("clear");
}

void query12(SGV sgv){
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
    while(flagInput1){
        scanf("%s", codigoC);
        if(valida_cliente(codigoC) && existe_cliente(c, codigoC)){
            flagInput1 = false;
            printf("Escreva de quantos produtos quer a informação\n");
            while(flagInput2){
                scanf("%s", tmp);
                
                if(isdigit(tmp[0])){
                    limit = atoi(tmp);
                
                    if (limit > 0){
                        flagInput2 = false;
                        printf("Ainda estamos a tratar, tente mais tarde\n");

                        printf("Prima Q para voltar ao Menu Principal\n");
                        while (toupper(flagCycle[0]) != 'Q'){
                            scanf("%s", flagCycle);
                        }
                    }
                    else printf("Escreva um numero maior que 0\n");
                }
                else printf("Escreva um numero maior que 0\n");
            }
        }
        else printf("Escreva um codigo com uma letra maiusculas e quatro numeros que exista no sistema\n");
    }
    system("clear");
}

int main(int argc, const char* argv[]) {
    if(argc < 2) {
        printf("Please Provide Data Folder\n");
        return 1;
    }
    bool flagCycle = true;
    SGV sgv = initSGV();
    loadSGVFromFiles(sgv, argv[1]);
    char opcaoQ1[2];
    opcaoQ1[0] = 'a';
    char tmp[2];
    int opcao = 13;
    while(flagCycle){
        printf("\n------------------------------------------------------ Menu Principal ------------------------------------------------------\n");
        printf("Escolha uma opção:\n");
        printf("1 - Ler os ficheiros e carregar a SGV\n");
        printf("2 - Lista e número de produtos começados por uma letra a escolha\n");
        printf("3 - Número total de vendas e o total faturado por um produto num certo mês\n");
        printf("4 - Lista e quantidade de produtos que ninguem comprou\n");
        printf("5 - Lista de clientes que compraram em todas as filiais\n");
        printf("6 - Numero de clientes e produtos que nunca foram comprados\n");
        printf("7 - Tabela das compras de um cliente\n");
        printf("8 - Total de vendas e total faturado num intervalo de meses\n");
        printf("9 - Total de clientes que compraram um certo produto numa certa filial\n");
        printf("10 - Lista de produtos comprados por um cliente num determinado mês por ordem decerscente de quantidade\n");
        printf("11 - Lista de produtos dos n produtos mais vendidos\n");
        printf("12 - Lista de n produtos em que um cliente gastou mais dinheiro\n");
        printf("0 - Sair do programa\n");
        printf("\n\n\n\n\n");
        scanf("%s", tmp);
        if(isdigit(tmp[0])){
            opcao = atoi(tmp);
        }
        printf("\n");
        switch (opcao){
            case 1:
                system("clear");
                destroySGV(sgv);
                sgv = initSGV();
                loadSGVFromFiles(sgv, argv[1]);
                printf("Prima Q para voltar ao Menu Principal\n");
                while (toupper(opcaoQ1[0]) != 'Q'){
                    scanf("%s",opcaoQ1);
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