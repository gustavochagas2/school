/**
 * @file Handlers - Funções que processam alguns comandos, neste caso, sobre funções que manipulão o stack
 */

#pragma once

#include "stack.h"

/** @brief Esta função é um hub para todas as outras funções que resolvem a entrada.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int hHub_Stack(Stack* stack, char cmd);

