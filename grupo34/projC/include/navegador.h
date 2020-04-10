/**
@file navegador.h
\brief Módulo de tratamento e implementação de um catálogo navegável.
*/
#ifndef LI3_NAVEGADOR_H
#define LI3_NAVEGADOR_H

#include "sgv.h"

/**
@brief Guarda num Navegador os identificadores de 10 estruturas (capacidade de uma página do catálogo) existentes.
 *
 * @param value void* identificador a ser imprimido
 * @param user_data Navegador que vai guardar a informação acerca da impressão em modo catálogo
*/
void imprime_10(void* value, void* user_data);

/**
@brief Função auxiliar da imprime_10 que permite a generalização desta para aceitar GHashTables* e GPtrArrays*.
 *
 * @param value void* identificador a ser imprimido
 * @param value void* não utilizado mas presente na estrutura obrigatória existente na glib
 * @param user_data Navegador que vai guardar a informação acerca da impressão em modo catálogo
*/
void imprime_10_hash_table(void* key, void* value, void* user_data);

/**
@brief Guarda num Navegador os identificadores de 10 ProdutoQuantidade (capacidade de uma página do catálogo) existentes.
 *
 * @param value void* identificador a ser imprimido
 * @param user_data Navegador que vai guardar a informação acerca da impressão em modo catálogo
*/
void imprime_info_produto_quantidade(void* value, void* user_data);

/**
@brief Guarda num Navegador os identificadores de 10 InformacaoProduto (capacidade de uma página do catálogo) existentes.
 *
 * @param value void* identificador a ser imprimido
 * @param user_data Navegador que vai guardar a informação acerca da impressão em modo catálogo
*/
void imprime_informacao_produto(void* value, void* user_data);

/**
@brief Função que executa a auxiliar na main.
 *
 * @param q2 Query2 a ser consultada
*/
void print_q2_with_navegador(Query2 q2);

/**
@brief Função que executa a auxiliar na main.
 *
 * @param q4 Query4 a ser consultada
*/
void print_q4_with_navegador(Query4 q4, int option);

/**
@brief Função que executa a auxiliar na main.
 *
 * @param q5 Query5 a ser consultada
*/
void print_q5_with_navegador(Query5 q5);

/**
@brief Função que executa a auxiliar na main.
 *
 * @param q10 Query10 a ser consultada
*/
void print_q10_with_navegador(Query10 q10);

/**
@brief Função que executa a auxiliar na main.
 *
 * @param q11 Query11 a ser consultada
*/
void print_q11_with_navegador(Query11 q11);

/**
@brief Função que executa a auxiliar na main.
 *
 * @param q12 Query12 a ser consultada
*/
void print_q12_with_navegador(Query12 q12);


#endif //LI3_NAVEGADOR_H
