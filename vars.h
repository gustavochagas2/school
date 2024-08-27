/**
 * @file Funções e handlers para a parte das Variáveis do Guião 3
 */

#pragma once

#include "stack.h"

/** @brief Cria um array de variáveis.
 * 
 * @warning O array das variáveis tem que ser libertado depois de utilizado com a função 'vars_Dispose'
 * @returns Array de variáveis
 */
Item** vars_CreateArray();

/** @brief Liberta um array de variáveis e os seus conteudos.
 * 
 * @param vars Array de variáveis
 */
void vars_Dispose(Item** vars);


/** @brief Imprime informações sobre as variáveis.
 * 
 * @param vars Array de variáveis
 */
void vars_DebugPrint(Item** vars);





