#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

int str_compare(void const* a, void const* b) {
    char const* _a = (char const*) a;
    char const* _b = (char const*) b;
    return strcmp(_a, _b) == 0;
}

bool valida_codigo(char* codigo) {
    int i;
    for (i = 0; codigo[i] != '\0'; i++) {
        if (!isdigit(codigo[i])) {
            return false;
        }
    }
    if (i != 4) {
        return false;
    }
    return true;
}

void imprime_keys(void* key, void* value, void* user_data) {
    printf("%s\n", (char*) key);
}

