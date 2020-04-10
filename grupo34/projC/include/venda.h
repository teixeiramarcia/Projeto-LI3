/**
@file clientes.h
\brief Módulo de tratamento de uma venda.
*/
#ifndef VENDAS_H
#define VENDAS_H

#include "produtos.h"
#include "types.h"
#include "month.h"
#include "filialID.h"

/**
@brief Liberta a memória alocada para a estrutura Venda.
 *
 * @param venda void* a libertar
*/
void destroy_venda(void* venda);

/**
@brief Obter o código do produto presente numa venda.
 *
 * @param venda Venda a consultar
 *
@return código do produto presente numa venda
*/
char* venda_get_codigo_produto(Venda venda);

/**
@brief Obter o o preço unitário de um produto presente numa venda.
 *
 * @param venda Venda a consultar
 *
@return preço unitário de um produto presente numa venda
*/
double venda_get_preco_unitario(Venda venda);

/**
@brief Obter as unidades vendidas.
 *
 * @param venda Venda a consultar
 *
@return unidades vendidas
*/
int venda_get_unidades(Venda venda);

/**
@brief Obter o tipo de venda.
 *
 * @param venda Venda a consultar
 *
@return tipo de venda
*/
char venda_get_tipo_compra(Venda venda);

/**
@brief Obter o código do cliente que efetuou a compra.
 *
 * @param venda Venda a consultar
 *
@return código do cliente que efetuou a compra
*/
char* venda_get_codigo_cliente(Venda venda);

/**
@brief Obter o mês em que a venda foi efetuada.
 *
 * @param venda Venda a consultar
 *
@return mês em que a venda foi efetuada
*/
Month venda_get_mes(Venda venda);

/**
@brief Função auxiliar da Query 9.
 *
 * @param venda Venda de onde vai ser retirado o código do cliente
 * @param vendas GHashTable* onde vai ser guardado o código do cliente
*/
void guarda_cliente(Venda venda, GHashTable* vendas);

/**
@brief Obter a filial em que a venda foi efetuada.
 *
 * @param venda Venda a consultar
 *
@return filial em que a venda foi efetuada
*/
FilialID venda_get_filial(Venda venda);

/**
@brief Verificar se uma venda é válida e se ainda não existe no sistema.
 *
 * @param prods Produtos estrutura da qual é extraido o código do produto para verificar se este existe no sistema
 * @param clientes Clientes estrutura da qual é extraido o código do cliente para verificar se este existe no sistema
 * @param l char* venda a validar
 *
@return a venda caso seja válida, NULL no caso contrário
*/
Venda valida_venda(Produtos prods, Clientes clientes, char* l);

#endif
