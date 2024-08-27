/**
 * @file Conversor que pega numa linha e executa-a
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "utils.h"
#include "parser.h"

#include "handler_vars.h"
#include "handler_math.h"
#include "handler_array.h"
#include "handler_stack.h"
#include "handler_logic.h"


/** @brief Esta função é um hub para todas as outras funções que resolvem a entrada
 * 
 * @param vars Apontador para o array de variáveis
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @param line Linha da entrada
 * @param linePos Posição na linha
 * @returns 1 se tiver sucesso
 */
int handler_Handle(Item** vars, Stack* stack, char cmd, char* line, int* linePos)
{
    return hHub_Vars(vars, stack, cmd, line, linePos) || hHub_Math(stack, cmd) ||
    hHub_Stack(stack, cmd) || hHub_Array(vars, stack, cmd, line, linePos) ||
    hHub_Logic(stack, cmd, line, linePos);
}


/** @brief Verifica se a entrada tem um número (double ou long) e guarda-o no stack
 * 
 * @param stack Apontador para o stack
 * @param line Linha da entrada
 * @param linePos Posição na linha
 * @param outN Variável de saida, usada apenas para testes
 * @returns 1 se tiver sucesso
 */
int parser_InputNumber(Stack* stack, char* line, int* linePos, double* outN)
{
    double input = 0; int pos = *linePos, offset = 0;
    if (sscanf(line + pos, "%lg%n", &input, &offset) != 1)
        return 0;
    // Se existir um '.' no espaço, quer dizer que o número é um double
    if (utils_FindCharSub(line + pos, offset, '.') != -1)
         stack_Push(stack, icreate_Double(input));
    else stack_Push(stack, icreate_Long(input));
    *outN = input;
    *linePos += offset;
    return 1;
}

/** @brief Verifica se a entrada tem um char de um comando e executa-o
 * 
 * @param vars Apontador para o array de variáveis
 * @param stack Apontador para o stack
 * @param line Linha da entrada
 * @param linePos Posição na linha
 * @param outN Variável de saida, usada apenas para testes
 * @returns 1 se tiver sucesso
 */
int parser_InputCmd(Item** vars, Stack* stack, char* line, int* linePos, char* outN)
{
    char input = 0; int pos = *linePos, offset = 0;
    if (sscanf(line + pos, "%c%n", &input, &offset) != 1)
        return 0;
    *linePos += offset;
    if (input == ' ' || input == '\n')
        return 1;
    *outN = input;
    if (!handler_Handle(vars, stack, input, line, linePos))
    {
        // debug
        if (input > 10)
            printf("Can't handle command '%d'\n", input);
        return 0;
    }
    return 1;
}



/** @brief Processa uma linha
 * 
 * @param vars Apontador para o array de variáveis
 * @param stack Apontador para o stack
 * @param line Linha da entrada
 * @param linePos Posição na linha
 * @returns O resultado do processo do ultimo char, não tem grande uso
 */
int parser_Process(Item** vars, Stack* stack, char* line, int lineSize)
{
    int linePos = 0, r = 0; double discardD; char discardC;
    while (linePos < lineSize)
    {
        if (line[linePos] != ' ' && line[linePos] > 31)
            r = parser_InputNumber(stack, line, &linePos, &discardD) ||
                parser_InputCmd(vars, stack, line, &linePos, &discardC);
        else linePos++;
    }
    return r;
}

/** @brief Processa uma linha imprimindo detalhes sobre cada passo
 * 
 * @param vars Apontador para o array de variáveis
 * @param stack Apontador para o stack
 * @param line Linha da entrada
 * @param linePos Posição na linha
 * @returns O resultado do processo do ultimo char, não tem grande uso
 */
int parser_DebugProcess(Item** vars, Stack* stack, char* line, int lineSize)
{
    int linePos = 0, r = 0; double inpD; char inpC;
    printf("\nLine Size: %d\n\n", lineSize);
    while (linePos < lineSize)
    {
        if (line[linePos] != ' ' && line[linePos] > 31)
        {
            if (parser_InputNumber(stack, line, &linePos, &inpD))
                printf("N: '%lg'\n", inpD);
            else if (parser_InputCmd(vars, stack, line, &linePos, &inpC))
            {
                char* is = i_ToString(stack_Peek(stack));
                printf("C: '%c': '%s'\n", inpC, is);
                free(is);
            }
            stack_PrintWS(stack);
            printf("\n\n");
        }
        else linePos++;
    }
    printf("\nResult:\n");
    return r;
}
