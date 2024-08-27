/**
 * @file Handlers - Funções que processam alguns comandos, neste caso, sobre lógica
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "handler_logic.h"
#include "itemfunctions.h"
#include "utils.h"

/** @brief Função que verifica se 2 items sao iguais.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_l_Equals(Stack* stack, char cmd)
{
    if (cmd != '=')
        return 0;
    Item* itemB = stack_Pop(stack);
    Item* itemA = stack_Pop(stack);

    stack_Push(stack, icreate_Long(item_Equals(itemA, itemB)));
    item_Dispose(itemA); item_Dispose(itemB);
    return 1;
}

/** @brief Função que verifica se um item e menor que outro.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_l_Less(Stack* stack, char cmd)
{
    if (cmd != '<')
        return 0;
    Item* itemB = stack_Pop(stack);
    Item* itemA = stack_Pop(stack);
    if ((!item_IsType(itemA, IT_Num) && itemA->type != TString) || (!item_IsType(itemB, IT_Num) && itemB->type != TString))
    {
        stack_Push(stack, itemA);
        stack_Push(stack, itemB);
        return 0;
    }
    if (itemA->type == itemB->type && itemA->type == TString)
    {
        char* a = (char*)itemA->pointer, *b = (char*)itemB->pointer;
        stack_Push(stack, icreate_Long((utils_StringCompare(a, b) == -1)));
        return 1;
    }
    double a = i_ToDouble(itemA), b = i_ToDouble(itemB);
    stack_Push(stack, icreate_Long(a < b));
    return 1;
}

/** @brief Função que verifica se um item e maior que outro.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_l_More(Stack* stack, char cmd)
{
    if (cmd != '>')
        return 0;
    Item* itemB = stack_Pop(stack);
    Item* itemA = stack_Pop(stack);
    if ((!item_IsType(itemA, IT_Num) && itemA->type != TString) || (!item_IsType(itemB, IT_Num) && itemB->type != TString))
    {
        stack_Push(stack, itemA);
        stack_Push(stack, itemB);
        return 0;
    }
    if (itemA->type == itemB->type && itemA->type == TString)
    {
        char* a = (char*)itemA->pointer, *b = (char*)itemB->pointer;
        stack_Push(stack, icreate_Long((utils_StringCompare(a, b) == 1)));
        return 1;
    }
    double a = i_ToDouble(itemA), b = i_ToDouble(itemB);
    stack_Push(stack, icreate_Long(a > b));
    return 1;
}

/** @brief Função que troca um 0 por 1 e 1 por 0.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_l_Not(Stack* stack, char cmd)
{
    if (cmd != '!')
        return 0;
    Item* item = stack_Peek(stack);
    if (!item_IsType(item, IT_Num))
        return 0;
    ifunc_ConvertToLong(item);
    *(long*)item->pointer = (*(long*)item->pointer != 0) ? 0 : 1;
    return 1;
}

/** @brief Guarda itemA se a condição for verdadeira e B se não.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_l_IfElse(Stack* stack, char cmd)
{
    if (cmd != '?')
        return 0;
    Item* itemB = stack_Pop(stack);
    Item* itemA = stack_Pop(stack);
    Item* itemCond = stack_Pop(stack);
    long v;
    if (item_IsType(itemCond, IT_Arr))
        v = (itemCond->type == TString) ? itemCond->size : ((List*)itemCond->pointer)->count;
    else v = i_ToLong(itemCond);
    item_Dispose(itemCond);
    if (v != 0)
    {
        stack_Push(stack, itemA);
        item_Dispose(itemB);
    }
    else
    {
        stack_Push(stack, itemB);
        item_Dispose(itemA);
    }
    return 1;
}


/** @brief Se os 2 items forem diferentes de 0, guarda o segundo.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_el_And(Stack* stack, char cmd)
{
    if (cmd != '&')
        return 0;
    Item* iB = stack_Pop(stack);
    Item* iA = stack_Pop(stack);
    long a = i_ToLong(iA), b = i_ToLong(iB);
    if (a != 0 && b != 0)
    {
        stack_Push(stack, iB);
        item_Dispose(iA);
        return 1;
    }
    item_Dispose(iA); item_Dispose(iB);
    stack_Push(stack, icreate_Long(0));
    return 1;
}

/** @brief Se um dos 2 items forem diferentes de 0, guarda o primeiro diferente de 0.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_el_Or(Stack* stack, char cmd)
{
    if (cmd != '|')
        return 0;
    Item* iB = stack_Pop(stack);
    Item* iA = stack_Pop(stack);
    long a = i_ToLong(iA), b = i_ToLong(iB);
    if (a != 0)
    {
        stack_Push(stack, iA);
        item_Dispose(iB);
        return 1;
    }
    if (b != 0)
    {
        stack_Push(stack, iB);
        item_Dispose(iA);
        return 1;
    }
    item_Dispose(iA); item_Dispose(iB);
    stack_Push(stack, icreate_Long(0));
    return 1;
}

/** @brief Guarda o item menor.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_el_Less(Stack* stack, char cmd)
{
    if (cmd != '<')
        return 0;
    Item* iB = stack_Pop(stack);
    Item* iA = stack_Pop(stack);
    int result = 0;
    if (iA->type == iB->type && iB->type == TString)
    {
        char* a = (char*)iA->pointer, *b = (char*)iB->pointer;
        result = utils_StringCompare(a, b) == -1;
    }
    else 
    {
        double a = i_ToDouble(iA), b = i_ToDouble(iB);
        result = a < b;
    }
    if (result)
    {
        stack_Push(stack, iA);
        item_Dispose(iB);
    }
    else 
    {
        stack_Push(stack, iB);
        item_Dispose(iA);
    }
    return 1;
}

/** @brief Guarda o item maior.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_el_More(Stack* stack, char cmd)
{
    if (cmd != '>')
        return 0;
    Item* iB = stack_Pop(stack);
    Item* iA = stack_Pop(stack);
    int result = 0;
    if (iA->type == iB->type && iB->type == TString)
    {
        char* a = (char*)iA->pointer, *b = (char*)iB->pointer;
        result = utils_StringCompare(a, b) == 1;
    }
    else 
    {
        double a = i_ToDouble(iA), b = i_ToDouble(iB);
        result = a > b;
    }
    if (result)
    {
        stack_Push(stack, iA);
        item_Dispose(iB);
    }
    else 
    {
        stack_Push(stack, iB);
        item_Dispose(iA);
    }
    return 1;
}



/** @brief Esta função é um hub para todas as outras funções que resolvem a entrada.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @param line Linha da entrada
 * @param linePos Posição na linha
 * @returns 1 se tiver sucesso
 */
int hHub_Logic(Stack* stack, char cmd, char* line, int* linePos)
{
    if (cmd != 'e')
        return h_l_Equals(stack, cmd) || h_l_Less(stack, cmd) ||
        h_l_More(stack, cmd) || h_l_Not(stack, cmd) || h_l_IfElse(stack, cmd);
    cmd = line[*linePos];
    *linePos += 1;
    return h_el_And(stack, cmd) || h_el_Or(stack, cmd) ||
    h_el_Less(stack, cmd) || h_el_More(stack, cmd);
}




