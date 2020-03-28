#include "sgv.h"
#include <stdio.h>
#include <ctype.h>

void query2(SGV sgv){
    char letra[2];
    printf("Escreva a letra que deseja procurar:\n");
    scanf("%s", letra);
    if(isalpha(letra[0])){
        getProductsStartedByLetter(sgv, toupper(letra[0]));
    }
    else printf("Escreva uma letra\n");
}

void query3(SGV sgv){
    char tmp[3];
    int mes;
    char codigoP[7];
    char tipo[2];
    printf("Escreva o mês que deseja procurar:\n");
    scanf("%s", tmp);
    if(isdigit(tmp[0])){
        mes = atoi(tmp);
        if(mes > 0 && mes < 13){
            printf("Escreva o codigo que deseja procurar:\n");
            scanf("%s", codigoP);

            if(valida_produto(codigoP)){
                printf("Escreva G se deja ver o resultado global ou F se quiser ver filial a filial\n");
                scanf("%s", tipo);

                if (toupper(tipo[0]) == 'G' || toupper(tipo[0]) == 'F'){
                    printf("Ainda estamos a tratar, tente mais tarde\n");
                }
                else printf("Escreva G ou F\n");
            }
            else printf("Escreva um codigo com duas letras maiusculas e quatro numeros\n");
        }
        else printf("Escreva um número entre 1 e 12\n");
    }
    else printf("Escreva um número entre 1 e 12\n");
}

void query4(SGV sgv){
    char tipo[2];
    printf("Escreva G se deja ver o resultado global ou F se quiser ver filial a filial\n");
    scanf("%s", tipo);
    if(toupper(tipo[0]) == 'G' || toupper(tipo[0]) == 'F'){
        getProductsNeverBought(sgv, 0);
    }
    else printf("Escreva G ou F\n");
}

void query7(SGV sgv){
    char codigoC[6];
    printf("Escreva o codigo do cliente\n");
    scanf("%s", codigoC);
    if(valida_cliente(codigoC)){
        getProductsBoughtByClient(sgv, codigoC);
    }
    else printf("Escreva um codigo com uma letra maiuscula e quatro numeros\n");
}

void query8(SGV sgv){
    char tmp[3];
    int pmes;
    int umes;
    printf("Escreva o primeiro mes\n");
    scanf("%s", tmp);
    if(isdigit(tmp[0])){
        pmes = atoi(tmp);
        
        if (pmes > 0 && pmes < 13){
            printf("Escreva o ultimo mes\n");
            scanf("%s", tmp);
            
            if(isdigit(tmp[0])){
                umes = atoi(tmp);
                
                if(umes >= pmes && umes < 13){
                    getSalesAndProfit(sgv, pmes, umes);
                }
                else printf("Escreva um mes entre o primeiro e 12 \n");
            }
            else printf("Escreva um mes entre o primeiro e 12 \n");
        }
        else printf("Escreva um mes entre 1 e 12 \n");
    }
    else printf("Escreva um mes entre 1 e 12 \n");
}

void query9(SGV sgv){
    char tmp[2];
    char codigoP[7];
    int filial;
    printf("Escreva o codigo do produto\n");
    scanf("%s", codigoP);
    if(valida_produto(codigoP)){
        printf("Escreva o número da filial\n");
        scanf("%s", tmp);

        if(isdigit(tmp[0])){
            filial = atoi(tmp);
            
            if(filial > 0 && filial < 4){
                getProductBuyers(sgv, codigoP, filial);
            }
            else printf("Escreva um valor entre 1 e 3\n");
        }
        else printf("Escreva um valor entre 1 e 3\n");
    }
    else printf("Escreva um codigo com duas letras maiusculas e quatro numeros\n");
}

void query10(SGV sgv){
    char tmp[3];
    char codigoC[6];
    int mes;
    printf("Escreva o codigo do cliente\n");
    scanf("%s", codigoC);
    if(valida_cliente(codigoC)){
        printf("Escreva o mês\n");
        scanf("%s", tmp);

        if (isdigit(tmp[0])){
            mes = atoi(tmp);
            
            if(mes > 0 && mes < 13){
                printf("Ainda estamos a tratar, tente mais tarde\n");
            }
            else printf("Escreva um valor entre 1 e 12\n");
        }
        else printf("Escreva um valor entre 1 e 12\n");
    }
    else printf("Escreva um codigo com uma letra maiuscula e quatro numeros\n");
}

void query11(SGV sgv){
    char tmp[3];
    int limit;
    printf("Escreva de quantos produtos quer a informação\n");
    scanf("%s", tmp);
    if(isdigit(tmp[0])){
        limit = atoi(tmp);
        
        if (limit > 0){
            getTopSoldProducts(sgv, limit);
        }
        else printf("Escreva um numero maior que 0\n");
    }
    else printf("Escreva um numero maior que 0\n");
}

void query12(SGV sgv){
    char tmp[3];
    char codigoC[6];
    int limit;
    printf("Escreva o codigo do cliente\n");
    scanf("%s", codigoC);
    if(valida_cliente(codigoC)){
        printf("Escreva de quantos produtos quer a informação\n");
        scanf("%s", tmp);
        
        if(isdigit(tmp[0])){
            limit = atoi(tmp);
        
            if (limit > 0){
                getTopSoldProducts(sgv, limit);
            }
            else printf("Escreva um numero maior que 0\n");
        }
        else printf("Escreva um numero maior que 0\n");
    }
    else printf("Escreva um codigo com uma letra maiusculas e quatro numeros\n");
}

int main(int argc, const char* argv[]) {
    if(argc < 2) {
        printf("Please Provide Data Folder\n");
        return 1;
    }
    bool flagCycle = true;
    SGV sgv = initSGV();
    loadSGVFromFiles(sgv, argv[1]);
    char tmp[2];
    int opcao;
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
        scanf("%s", tmp);
        if(isdigit(tmp[0])){
            opcao = atoi(tmp);
        }
        printf("\n");
        switch (opcao){
            case 1:
                destroySGV(sgv);
                sgv = initSGV();
                loadSGVFromFiles(sgv, argv[1]);
                break;
            case 2:
                query2(sgv);
                break;
            case 3:
                query3(sgv);
                break;
            case 4:
                query4(sgv);
                printf("\n");
                break;
            case 5:
                printf("Ainda estamos a tratar, por favor tente mais tarde\n");
                break;
            case 6:
                getClientsAndProductsNeverBoughtCount(sgv);
                printf("\n");
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
        printf("\n");
    }
    return 0;
}