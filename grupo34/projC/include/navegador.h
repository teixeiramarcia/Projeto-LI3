#ifndef LI3_NAVEGADOR_H
#define LI3_NAVEGADOR_H
#include "sgv.h"

void imprime_10 (void* value, void* user_data);

void imprime_10_hash_table (void* key, void* value, void* user_data);

void imprime_info_produto_quantidade (void* value, void* user_data);

void imprime_informacao_produto (void* value, void* user_data);

void print_q2_with_navegador (Query2 q2);

void print_q4_with_navegador (Query4 q4, int option);

void print_q5_with_navegador(Query5 q5);

void print_q10_with_navegador(Query10 q10);

void print_q11_with_navegador(Query11 q11);

void print_q12_with_navegador(Query12 q12);


#endif //LI3_NAVEGADOR_H
