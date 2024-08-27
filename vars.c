/**
 * @file Funções e handlers para a parte das Variáveis do Guião 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vars.h"
#include "utils.h"


/** Macro simples para usar letras de A a Z como indices de 0 a 26 */
#define I(c) c - 65
/** Macro simples para usar indices de 0 a 26 como letras de A a Z */
#define II(c) c + 65

/** @brief Cria um array de variáveis.
 * 
 * @warning O array das variáveis tem que ser libertado depois de utilizado com a função 'vars_Dispose'
 * @returns Array de variáveis
 */
Item** vars_CreateArray()
{
    Item** array = calloc(26, sizeof(Item*));
    array[I('A')] = icreate_Long(10);
    array[I('B')] = icreate_Long(11);
    array[I('C')] = icreate_Long(12);
    array[I('D')] = icreate_Long(13);
    array[I('E')] = icreate_Long(14);
    array[I('F')] = icreate_Long(15);
    array[I('N')] = icreate_Char('\n');
    array[I('S')] = icreate_Char(' ');
    array[I('X')] = icreate_Long(0);
    array[I('Y')] = icreate_Long(1);
    array[I('Z')] = icreate_Long(2);
    for (int i = I('G'); i < I('X'); i++)
        if (i != I('N') && i != I('S'))
            array[i] = icreate_Long(0);
    return array;
}

/** @brief Liberta um array de variáveis e os seus conteudos.
 * 
 * @param vars Array de variáveis
 */
void vars_Dispose(Item** vars)
{
    for (int i = 0; i < 26; i++)
        item_Dispose(vars[i]);
    free(vars);
}


/** @brief Imprime informações sobre as variáveis.
 * 
 * @param vars Array de variáveis
 */
void vars_DebugPrint(Item** vars)
{
    printf("Vars:\n");
    for (int i = 0; i < 25; i++)
    {
        if (i == 13)
            printf("\n");
        printf("%c: '", II(i));
        item_Print(vars[i]);
        printf("' ");
    }
    printf("%c: '", II(25));
    item_Print(vars[25]);
    printf("' ");
    printf("\n");
}



