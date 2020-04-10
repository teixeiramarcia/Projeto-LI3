/**
@file filial.h
\brief Módulo de tratamento de uma filial.
*/
#ifndef FILIAIS_H
#define FILIAIS_H

#include <stdbool.h>
#include <stddef.h>
#include <glib.h>
#include "faturacaoMes.h"
#include "venda.h"
#include "types.h"
#include "month.h"

/**
@brief Estrutura Filial.
*/
typedef struct filial* Filial;

/**
@brief Aloca memória e inicializa a estrutura de dados Filial.
 *
@return estrutura de dados Filial
*/
Filial make_filial();

/**
@brief Atualiza a estrutura Filial com uma nova venda.
 *
 * @param filial Filial a ser alterada
 * @param venda Venda a ser adicionada
*/
void update_filial(Filial filial, Venda venda);

/**
@brief Obter a faturação numa determinada filial num determinado mês.
 *
 * @param filial Filial a ser consultada
 * @param month Month a ser consultado
*/
FaturacaoMes filial_get_faturacao_mes(Filial filial, Month month);

/**
@brief Libertar a memória alocada para a estrutura Filial.
 *
 * @param filial Filial a ser libertada
*/
void destroy_filial(Filial filial);

#endif
