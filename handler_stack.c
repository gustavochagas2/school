/**
 * @file Handlers - Funções que processam alguns comandos, neste caso, sobre funções que manipulão o stack
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "handler_stack.h"
#include "itemfunctions.h"
#include "stack.h"
#include "utils.h"


/** @brief Função que converte o item no topo da stack.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_s_ToLong(Stack* stack, char cmd)
{
    if (cmd != 'i')
        return 0;
    return ifunc_ConvertToLong(stack_Peek(stack));
}

/** @brief Função que converte o item no topo da stack.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_s_ToDouble(Stack* stack, char cmd)
{
    if (cmd != 'f')
        return 0;
    return ifunc_ConvertToDouble(stack_Peek(stack));
}

/** @brief Função que converte o item no topo da stack.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_s_ToChar(Stack* stack, char cmd)
{
    if (cmd != 'c')
        return 0;
    return ifunc_ConvertToChar(stack_Peek(stack));
}

/** @brief Função que converte o item no topo da stack.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_s_ToString(Stack* stack, char cmd)
{
    if (cmd != 's')
        return 0;
    Item* item = stack_Pop(stack);
    char* string = i_ToString(item);
    item_Dispose(item);
    Item* new = icreate_String(string, strlen(string));
    stack_Push(stack, new);
    return 1;
}


/** @brief Duplica o item no topo da stack.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se o comando foi processado
 */
int h_s_Duplicate(Stack* stack, char cmd)
{
    if (cmd != '_')
        return 0;
    Item* item = item_Copy(stack_Peek(stack));
    stack_Push(stack, item);
    return 1;
}

/** @brief Remove o item no topo da stack.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se o comando foi processado
 */
int h_s_Pop(Stack* stack, char cmd)
{
    if (cmd != ';')
        return 0;
    item_Dispose(stack_Pop(stack));
    return 1;
}

/** @brief Troca de posição os 2 items no topo da stack.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se o comando foi processado
 */
int h_s_Switch(Stack* stack, char cmd)
{
    if (cmd != '\\')
        return 0;
    Item* b = stack_Pop(stack);
    Item* a = stack_Pop(stack);
    stack_Push(stack, b);
    stack_Push(stack, a);
    return 1;
}

/** @brief Troca de posição os 3 items no topo da stack.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se o comando foi processado
 */
int h_s_Switch3(Stack* stack, char cmd)
{
    if (cmd != '@')
        return 0;
    Item* c = stack_Pop(stack);
    Item* b = stack_Pop(stack);
    Item* a = stack_Pop(stack);
    stack_Push(stack, b);
    stack_Push(stack, c);
    stack_Push(stack, a);
    return 1;
}

/** @brief Copia um item da stack (0 é o topo).
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se o comando foi processado
 */
int h_s_CapyN(Stack* stack, char cmd)
{
    if (cmd != '$')
        return 0;
    Item* itemIndex = stack_Pop(stack);
    if (!item_IsType(itemIndex, IT_Num))
    {
        stack_Push(stack, itemIndex);
        return 0;
    }
    long i = i_ToLong(itemIndex);
    stack_Push(stack, stack_CopyN(stack, i));
    return 1;
}

/** @brief Guarda uma linha da consola na stack.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se o comando foi processado
 */
int h_s_GetLine(Stack* stack, char cmd)
{
    if (cmd != 'l')
        return 0;
    int size; char* line = utils_GetLine(&size);
    stack_Push(stack, icreate_String(line, size));
    return 1;
}

/** @brief Guarda várias linhas da consola na stack.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se o comando foi processado
 */
int h_s_GetAllLines(Stack* stack, char cmd)
{
    if (cmd != 't')
        return 0;
    int size; char* line = utils_GetAllLines(&size);
    stack_Push(stack, icreate_String(line, size));
    return 1;
}

/** @brief Imprime o item no topo da stack.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se o comando foi processado
 */
int h_s_PrintTop(Stack* stack, char cmd)
{
    if (cmd != 'p')
        return 0;
    item_Print(stack_Peek(stack));
    return 1;
}



/** @brief Esta função é um hub para todas as outras funções que resolvem a entrada.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int hHub_Stack(Stack* stack, char cmd)
{
    return h_s_Duplicate(stack, cmd) || h_s_Pop(stack, cmd) || 
    h_s_Switch(stack, cmd) || h_s_Switch3(stack, cmd) || 
    h_s_CapyN(stack, cmd) || h_s_GetLine(stack, cmd) ||
    h_s_GetAllLines(stack, cmd) || h_s_PrintTop(stack, cmd) || 
    h_s_ToLong(stack, cmd) || h_s_ToDouble(stack, cmd) ||
    h_s_ToChar(stack, cmd) || h_s_ToString(stack, cmd);
}

