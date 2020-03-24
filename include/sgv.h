#ifndef SGV_H
#define SGV_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "clientes.h"
#include "produtos.h"
#include "vendas.h"
#include "types.h"

typedef struct sgv* SGV;

void sgv_adiciona_venda(SGV sgv, Venda venda);

SGV initSGV();

SGV loadSGVFromFiles(SGV sgv, char const* filesFolderPath);

void destroySGV(SGV sgv);

//queries

void getProductsNeverBought(SGV sgv, int branchID); //query 4

void getClientsAndProductsNeverBoughtCount(SGV sgv); //query 6

void getProductBuyers(SGV sgv, char* prodID, int branchID); //query 9

#endif
