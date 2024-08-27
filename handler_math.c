/**
 * @file Handlers - Funções que processam alguns comandos, neste caso, sobre funções matematicas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "handler_math.h"
#include "itemfunctions.h"
#include "utils.h"


/** @brief Função que adiciona 1 ao item se este for um número.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_m_Incr(Stack* stack, char cmd)
{
    if (cmd != ')')
        return 0;
    return ifunc_Increment(stack_Peek(stack));
}

/** @brief Função que remove 1 ao item se este for um número.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_m_Decr(Stack* stack, char cmd)
{
    if (cmd != '(')
        return 0;
    return ifunc_Decrement(stack_Peek(stack));
}


/** @brief Função que calcula a soma de dois items números.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_m_Add(Stack* stack, char cmd)
{
    if (cmd != '+')
        return 0;
    Item* iB = stack_Pop(stack);
    Item* iA = stack_Pop(stack);
    if (ifunc_Add(iA, iB))
    {
        stack_Push(stack, iB); item_Dispose(iA);
        return 1;
    }
    stack_Push(stack, iA);
    stack_Push(stack, iB);
    return 0;
}

/** @brief Função que calcula a subtração de dois items números.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_m_Sub(Stack* stack, char cmd)
{
    if (cmd != '-')
        return 0;
    Item* iB = stack_Pop(stack);
    Item* iA = stack_Pop(stack);
    if (ifunc_Subtract(iA, iB))
    {
        stack_Push(stack, iB); item_Dispose(iA);
        return 1;
    }
    stack_Push(stack, iA);
    stack_Push(stack, iB);
    return 0;
}

/** @brief Função que calcula a multiplicação de dois items números.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_m_Mult(Stack* stack, char cmd)
{
    if (cmd != '*')
        return 0;
    Item* iB = stack_Pop(stack);
    Item* iA = stack_Pop(stack);
    if (ifunc_Multiply(iA, iB))
    {
        stack_Push(stack, iB); item_Dispose(iA);
        return 1;
    }
    stack_Push(stack, iA);
    stack_Push(stack, iB);
    return 0;
}

/** @brief Função que calcula a divisão de dois items números.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_m_Div(Stack* stack, char cmd)
{
    if (cmd != '/')
        return 0;
    Item* iB = stack_Pop(stack);
    Item* iA = stack_Pop(stack);
    if (ifunc_Divide(iA, iB))
    {
        stack_Push(stack, iB); item_Dispose(iA);
        return 1;
    }
    stack_Push(stack, iA);
    stack_Push(stack, iB);
    return 0;
}


/** @brief Função que calcula o resto da divisão de dois items números.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_m_Mod(Stack* stack, char cmd)
{
    if (cmd != '%')
        return 0;
    Item* iB = stack_Pop(stack);
    Item* iA = stack_Pop(stack);
    if (ifunc_Mod(iA, iB))
    {
        stack_Push(stack, iB); item_Dispose(iA);
        return 1;
    }
    stack_Push(stack, iA);
    stack_Push(stack, iB);
    return 0;
}

/** @brief Função que calcula um item elevado a outro (os dois números).
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_m_Pow(Stack* stack, char cmd)
{
    if (cmd != '#')
        return 0;
    Item* iB = stack_Pop(stack);
    Item* iA = stack_Pop(stack);
    if (ifunc_Pow(iA, iB))
    {
        stack_Push(stack, iB); item_Dispose(iA);
        return 1;
    }
    stack_Push(stack, iA);
    stack_Push(stack, iB);
    return 0;
}


/** @brief Função que calcula itemA & itemB.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_m_And(Stack* stack, char cmd)
{
    if (cmd != '&')
        return 0;
    Item* iB = stack_Pop(stack);
    Item* iA = stack_Pop(stack);
    if (ifunc_And(iA, iB))
    {
        stack_Push(stack, iB); item_Dispose(iA);
        return 1;
    }
    stack_Push(stack, iA);
    stack_Push(stack, iB);
    return 0;
}

/** @brief Função que calcula itemA | itemB.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_m_Or(Stack* stack, char cmd)
{
    if (cmd != '|')
        return 0;
    Item* iB = stack_Pop(stack);
    Item* iA = stack_Pop(stack);
    if (ifunc_Or(iA, iB))
    {
        stack_Push(stack, iB); item_Dispose(iA);
        return 1;
    }
    stack_Push(stack, iA);
    stack_Push(stack, iB);
    return 0;
}

/** @brief Função que calcula itemA ^ itemB.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_m_Xor(Stack* stack, char cmd)
{
    if (cmd != '^')
        return 0;
    Item* iB = stack_Pop(stack);
    Item* iA = stack_Pop(stack);
    if (ifunc_Xor(iA, iB))
    {
        stack_Push(stack, iB); item_Dispose(iA);
        return 1;
    }
    stack_Push(stack, iA);
    stack_Push(stack, iB);
    return 0;
}

/** @brief Função que calcula ~item.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_m_Not(Stack* stack, char cmd)
{
    if (cmd != '~')
        return 0;
    return ifunc_Not(stack_Peek(stack));
}



/** @brief Esta função é um hub para todas as outras funções que resolvem a entrada.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int hHub_Math(Stack* stack, char cmd)
{
    return h_m_Incr(stack, cmd) || h_m_Decr(stack, cmd) || 
    h_m_Add(stack, cmd) || h_m_Sub(stack, cmd) || 
    h_m_Mult(stack, cmd) || h_m_Div(stack, cmd) ||
    h_m_Mod(stack, cmd) || h_m_Pow(stack, cmd) ||
    h_m_And(stack, cmd) || h_m_Or(stack, cmd) ||
    h_m_Xor(stack, cmd) || h_m_Not(stack, cmd);;
}


