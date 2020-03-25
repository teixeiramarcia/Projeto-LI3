#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

char* strtok(char* restrict str, const char* restrict sep);

char* strtok_r(char* restrict str, const char* restrict sep, char** restrict lasts);

char* strdup(char const* a);

int str_compare(void const* a, void const* b);

bool valida_codigo(char* codigo);

void imprime_keys(void* key, void* value, void* user_data);

#endif