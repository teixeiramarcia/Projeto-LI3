#include "sgv.h"

int main(int argc, const char* argv[]) {
    SGV sgv = initSGV();

    loadSGVFromFiles(sgv, argv[1]);

    //getProductsStartedByLetter(sgv, 'A'); //query 2

    getProductsNeverBought(sgv, 0); //query 4 FIXME - doesnt work

    //getClientsAndProductsNeverBoughtCount(SGV sgv); //query 6 FIXME - dependente da query 4

    //getProductBuyers(sgv, "AF1184", 1); //query 9

    destroySGV(sgv);
    return 0;
}


