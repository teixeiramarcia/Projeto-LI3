/**
@file faturacaoMes.h
\brief Módulo de tratamento da faturação mensal dentro de uma determinada filial.
*/
#ifndef FATURACAOMES_H
#define FATURACAOMES_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "venda.h"
#include "types.h"

/**
@brief Estrutura FaturacaoMes.
*/
typedef struct faturacaoMes* FaturacaoMes;

/**
@brief Aloca memória e inicializa a estrutura de dados FaturacaoMes.

@return estrutura de dados FaturacaoMes
*/
FaturacaoMes make_faturacao_mes();

/**
@brief Atualiza a faturação mensal com uma nova venda.
 *
 * @param fmes FaturacaoMes a ser atualizada
 * @param venda Venda a ser colocada na estrutura
*/
void update_faturacao_mes(FaturacaoMes fmes, Venda venda);

/**
@brief Obter a faturação mensal em modo promoção.
 *
 * @param fmes FaturacaoMes a ser consultada
 *
@return faturação mensal em modo promoção
*/
double faturacao_mes_get_faturacao_promocao(FaturacaoMes fmes);

/**
@brief Obter o total de vendas mensal em modo promoção.
 *
 * @param fmes FaturacaoMes a ser consultada
 *
@return total de vendas mensal em modo promoção
*/
int faturacao_mes_get_total_promocao(FaturacaoMes fmes);

/**
@brief Obter a faturação mensal em modo normal.
 *
 * @param fmes FaturacaoMes a ser consultada
 *
@return faturação mensal em modo normal
*/
double faturacao_mes_get_faturacao_normal(FaturacaoMes fmes);

/**
@brief Obter o total de vendas mensal em modo normal.
 *
 * @param fmes FaturacaoMes a ser consultada
 *
@return total de vendas mensal em modo normal
*/
int faturacao_mes_get_total_normal(FaturacaoMes fmes);

/**
@brief Obter as vendas mensais em modo normal.
 *
 * @param fmes FaturacaoMes a ser consultada
 *
@return GPtrArray* de vendas mensais em modo normal
*/
GPtrArray* faturacao_mes_get_vendas_normal(FaturacaoMes fmes);

/**
@brief Obter as vendas mensais em modo promoção.
 *
 * @param fmes FaturacaoMes a ser consultada
 *
@return GPtrArray* de vendas mensais em modo promoção
*/
GPtrArray* faturacao_mes_get_vendas_promocao(FaturacaoMes fmes);

/**
@brief Verificar se um produto faturou ou não num determinado mês.
 *
 * @param fmes FaturacaoMes a ser consultada
 *
@return true se não tiver havido faturação, false no caso contrário
*/
bool faturacao_nao_faturou(FaturacaoMes fmes);

/**
@brief Liberta a memória alocada para a estrutura FaturacaoMes.
 *
 * @param fmes FaturacaoMes a libertar
*/
void destroy_faturacao_mes(FaturacaoMes fmes);

#endif