#include "sgv.h"
#include <stdio.h>

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("provide Data folder\n");
        return 1;
    }
    SGV sgv = initSGV();
    loadSGVFromFiles(sgv, argv[1]);

    //getProductsStartedByLetter(sgv, 'A'); //query 2

    //getProductSalesAndProfit(sgv, productID, month); //query 3 FIXME testar

    //getProductsNeverBought(sgv, 0); //query 4

    //getClientsAndProductsNeverBoughtCount(sgv); //query 6

    //getProductsBoughtByClient(sgv, "A3984"); //query 7

    //getSalesAndProfit(sgv, 1, 12); //query 8

    //getProductBuyers(sgv, "NR1091", 3); //query 9

    //getTopSoldProducts(sgv, 1); //query 11


    destroySGV(sgv);
    return 0;
}


