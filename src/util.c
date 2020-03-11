#include <ctype.h>
#include "util.h"

bool valida_codigo (char *codigo) {
    int i;
    for (i=0; codigo[i]!='\0'; i++) {
        if (!isdigit(codigo[i])) {
            return false;
        }
    }
    if (i!=4) {
        return false;
    }
    return true;
}


