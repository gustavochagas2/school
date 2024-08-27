/**
 * @file Handlers - Funções que processam alguns comandos, neste caso, sobre as variáveis
 */

#pragma once

#include "stack.h"

/** @brief Esta função é um hub para todas as outras funções que resolvem a entrada
 * 
 * @param vars Apontador para o array de variáveis
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @param line Linha da entrada
 * @param linePos Posição na linha
 * @returns 1 se tiver sucesso
 */
int hHub_Vars(Item** vars, Stack* stack, char cmd, char* line, int* linePos);



