/**
 * @file Handlers - Funções que processam alguns comandos, neste caso, sobre as variáveis
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "handler_vars.h"
#include "utils.h"


/** @brief Função que guarda no topo da stack o item numa das variáveis
 * 
 * @param vars Apontador para o array de variáveis
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @param line Linha da entrada
 * @param linePos Posição na linha
 * @returns 1 se tiver sucesso
 */
int h_v_GetValue(Item** vars, Stack* stack, char cmd)
{
    if (cmd < 'A' || cmd > 'Z')
        return 0;
    int index = cmd - 65;
    Item* var = vars[index];
    Item* copy = item_Copy(var);
    stack_Push(stack, copy);
    return 1;
}

/** @brief Função que guarda o item no topo da stack numa das variáveis
 * 
 * @param vars Apontador para o array de variáveis
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @param line Linha da entrada
 * @param linePos Posição na linha
 * @returns 1 se tiver sucesso
 */
int h_v_SetValue(Item** vars, Stack* stack, char cmd, char* line, int* linePos)
{
    if (cmd != ':')
        return 0;
    char cv = line[*linePos];
    if (cv < 'A' || cv > 'Z')
        return 0;
    *linePos += 1;
    int index = cv - 65;
    item_Dispose(vars[index]);
    vars[index] = item_Copy(stack_Peek(stack));
    return 1;
}

/** @brief Esta função é um hub para todas as outras funções que resolvem a entrada
 * 
 * @param vars Apontador para o array de variáveis
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @param line Linha da entrada
 * @param linePos Posição na linha
 * @returns 1 se tiver sucesso
 */
int hHub_Vars(Item** vars, Stack* stack, char cmd, char* line, int* linePos)
{
    return h_v_GetValue(vars, stack, cmd) || h_v_SetValue(vars, stack, cmd, line, linePos);
}


