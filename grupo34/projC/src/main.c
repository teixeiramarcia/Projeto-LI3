#include "sgv.h"

int main(int argc, const char* argv[]) {
    SGV sgv = initSGV();

    loadSGVFromFiles(sgv, argv[1]);

    //getProductsStartedByLetter(sgv, 'A'); //query 2

    //getProductsNeverBought(sgv, 0); //query 4

    //getClientsAndProductsNeverBoughtCount(sgv); //query 6

    //getProductsBoughtByClient(sgv, "A3984"); //query 7

    //getSalesAndProfit(sgv, 1, 1); //query 8

    //getProductBuyers(sgv, "AF1184", 1); //query 9

    destroySGV(sgv);
    return 0;
}


