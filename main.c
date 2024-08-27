/**
 * @file Ponto de entrada do programa
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vars.h"
#include "stack.h"
#include "utils.h"
#include "parser.h"

/**
 * Ponto de entrada do programa
 */
int main()
{
    Item** vars = vars_CreateArray();
    Stack* stack = stack_Create(StackInitialSize);

    int size; char* line = utils_GetLine(&size);
    if (line[0] == 'z')
        parser_DebugProcess(vars, stack, line + 1, size);
    else parser_Process(vars, stack, line, size);

    stack_Print(stack);
    printf("\n");

    vars_Dispose(vars);
    stack_Dispose(stack);
    return 0;
}

