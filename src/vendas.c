#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "vendas.h"
#include "util.h"

bool is_number (char *s) {
    for (int i=0; s[i]!='\0' && s[i]!='\n' && s[i]!='\r'; i++) {
        if(!isdigit(s[i]))
            return false;
    }
    return true;
}

bool is_price (char *s) {
    char * rest = s;

    bool res = is_number(strtok_r(rest, ".", &rest));
    res &= is_number(strtok_r(rest, ".", &rest));
    res &= (strtok_r(rest, ".", &rest) == NULL);
    return res;
}

bool valida_venda (char *l, Produtos p, Clientes c) {
    int res = 0;
    l = strdup(l);
    char *token = strtok(l, " ");
    for (int i=0; token!=NULL; i++){
        switch (i) {
            case 0:
                if (valida_produto(token) && existe_produto(p, token)) {
                    res++;
                }
                break;
            case 1:
                if (is_price(token)) {
                    res++;
                }
                break;
            case 2:
                if (is_number(token) && (atoi(token) >= 1 && atoi(token) <=200)) {
                    res++;
                }
                break;
            case 3:
                if (token[0] == 'P' || token[0] == 'N') {
                    res++;
                }
                break;
            case 4:
                if (valida_cliente(token) && existe_cliente(c, token)) {
                    res++;
                }
                break;
            case 5:
                if (is_number(token) && (atoi(token) >= 1 && atoi(token) <= 12)) {
                    res++;
                }
                break;
            case 6:
                if (is_number(token) && (atoi(token) >= 1 && atoi(token) <= 3)) {
                    res++;
                }
                break;
            default: return false;
        }
        token = strtok(NULL, " ");
    }
    if (res!=7) return false;
    else return true;
}


