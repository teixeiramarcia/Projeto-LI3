#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "util.h"
#include "clientes.h"

bool valida_cliente (char *l) {
    if (isupper(l[0])) {
        return valida_codigo(l+1) && (atoi(l+1) >= 1000 && atoi(l+1) <= 5000);
    }
    return false;
}

bool existe_cliente(Clientes c, char *cliente) {
    for(size_t i=0; i<c.num; i++){
        if(strcmp(cliente, c.validos[i]) == 0) return true;
    }
    return false;
}


