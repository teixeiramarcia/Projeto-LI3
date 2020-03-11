#include <string.h>
#include <ctype.h>
#include "util.h"
#include "produtos.h"

bool existe_produto (Produtos p, char *produto) {
    for(size_t i=0; i<p.num ; i++){
        if(strcmp(produto, p.validos[i]) == 0) return true;
    }
    return false;
}

bool valida_produto (char *l) {
    if (isupper(l[0]) && isupper(l[1])) {
        return valida_codigo(l+2);
    }
    return false;
}


