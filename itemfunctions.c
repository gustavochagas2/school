/**
 * @file Funções relativas a items, como operações matemáticas e conversões
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "itemfunctions.h"
#include "utils.h"


// Conversões

/** @brief Converte o tipo no item para um Long.
 * 
 * @warning Esta função apenas funciona com chars, longs, doubles e strings.
 * @param item Apontador para o item
 * @returns 1 se o item puder ser convertido
 */
int ifunc_ConvertToLong(Item* item)
{
    if (!item_IsType(item, IT_Num) && item->type != TString)
        return 0;
    if (item->type == TLong)
        return 1;
    long* buffer = malloc(sizeof(long));
    *buffer = i_ToLong(item);
    free(item->pointer);
    item->size = sizeof(long);
    item->pointer = buffer;
    item->type = TLong;
    return 1;
}

/** @brief Converte o tipo no item para um Double.
 * 
 * @warning Esta função apenas funciona com chars, longs, doubles e strings.
 * @param item Apontador para o item
 * @returns 1 se o item puder ser convertido
 */
int ifunc_ConvertToDouble(Item* item)
{
    if (!item_IsType(item, IT_Num) && item->type != TString)
        return 0;
    if (item->type == TDouble)
        return 1;
    double* buffer = malloc(sizeof(double));
    *buffer = i_ToDouble(item);
    free(item->pointer);
    item->size = sizeof(double);
    item->pointer = buffer;
    item->type = TDouble;
    return 1;
}

/** @brief Converte o tipo no item para um Char.
 * 
 * @warning Esta função apenas funciona com chars, longs, doubles e strings.
 * @param item Apontador para o item
 * @returns 1 se o item puder ser convertido
 */
int ifunc_ConvertToChar(Item* item)
{
    if (!item_IsType(item, IT_Num) && item->type != TString)
        return 0;
    if (item->type == TChar)
        return 1;
    char* buffer = malloc(sizeof(char));
    *buffer = i_ToChar(item);
    free(item->pointer);
    item->size = sizeof(char);
    item->pointer = buffer;
    item->type = TChar;
    return 1;
}

/** @brief Converte o tipo no item para um String.
 * 
 * @warning Esta função apenas funciona com chars, longs, doubles e strings.
 * @param item Apontador para o item
 * @returns 1 se o item puder ser convertido
 */
int ifunc_ConvertToString(Item* item)
{
    if (!item_IsType(item, IT_Num) && item->type != TString)
        return 0;
    if (item->type == TString)
        return 1;
    char* buffer = i_ToString(item);
    free(item->pointer);
    item->size = strlen(buffer) * sizeof(char);
    item->pointer = buffer;
    item->type = TString;
    return 1;
}

/** @brief Converte o tipo no item para uma lista.
 * 
 * @warning Esta função apenas funciona com chars, longs, doubles, strings e listas.
 * @param item Apontador para o item
 * @returns 1 se o item puder ser convertido
 */
int ifunc_ConvertToList(Item* item)
{
    if (!item_IsType(item, IT_Num) && !item_IsType(item, IT_Arr))
        return 0;
    if (item->type == TList)
        return 1;
    List* list;
    if (item->type != TString)
    {
        list = list_FromString((char*)item->pointer, item->size);
        free(item->pointer);
    }
    else
    {
        list = list_Create(1);
        list_Add(list, item_Copy(item));
        free(item->pointer);
    }
    item->pointer = list;
    item->size = sizeof(List);
    item->type = TList;
    return 1;
}



// Math

/** @brief Adiciona 1 ao número guardado no item (mantém o tipo).
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles.
 * @param item Apontador para o item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Increment(Item* item)
{
    if (!item_IsType(item, IT_Num))
        return 0;
    ItemType type = item->type;
    if (type == TLong)
        *(long*)item->pointer += 1;
    else if (type == TDouble)
        *(double*)item->pointer += 1;
    else *(char*)item->pointer += 1;
    return 1;
}

/** @brief Remove 1 ao número guardado no item (mantém o tipo).
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles.
 * @param item Apontador para o item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Decrement(Item* item)
{
    if (!item_IsType(item, IT_Num))
        return 0;
    ItemType type = item->type;
    if (type == TLong)
        *(long*)item->pointer -= 1;
    else if (type == TDouble)
        *(double*)item->pointer -= 1;
    else *(char*)item->pointer -= 1;
    return 1;
}


/** @brief Calcula a soma dos dois items, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Add(Item* itemA, Item* itemB)
{
    if (!item_IsType(itemA, IT_Num) || !item_IsType(itemB, IT_Num))
        return 0;
    ItemType tA = itemA->type, tB = itemB->type;
    if (tA == TDouble || tB == TDouble) // 1 double e 1 double, long ou char
    {
        ifunc_ConvertToDouble(itemB);
        *(double*)itemB->pointer += i_ToDouble(itemA);
    }
    else if (tA == TLong || tB == TLong) // 1 long e 1 long ou char
    {
        ifunc_ConvertToLong(itemB);
        *(long*)itemB->pointer += i_ToLong(itemA);
    }
    else *(char*)itemB->pointer += *(char*)itemA->pointer; // 2 chars
    return 1;
}

/** @brief Calcula a subtração de dois items, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Subtract(Item* itemA, Item* itemB)
{
    if (!item_IsType(itemA, IT_Num) || !item_IsType(itemB, IT_Num))
        return 0;
    ItemType tA = itemA->type, tB = itemB->type;
    if (tA == TDouble || tB == TDouble) // 1 double e 1 double, long ou char
    {
        ifunc_ConvertToDouble(itemB);
        *(double*)itemB->pointer = i_ToDouble(itemA) - *(double*)itemB->pointer;
    }
    else if (tA == TLong || tB == TLong) // 1 long e 1 long ou char
    {
        ifunc_ConvertToLong(itemB);
        *(long*)itemB->pointer = i_ToLong(itemA) - *(long*)itemB->pointer;
    }
    else *(char*)itemB->pointer = *(char*)itemA->pointer - *(char*)itemB->pointer;// 2 chars
    return 1;
}

/** @brief Calcula a multiplicação de dois items, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Multiply(Item* itemA, Item* itemB)
{
    if (!item_IsType(itemA, IT_Num) || !item_IsType(itemB, IT_Num))
        return 0;
    ItemType tA = itemA->type, tB = itemB->type;
    if (tA == TDouble || tB == TDouble) // 1 double e 1 double, long ou char
    {
        ifunc_ConvertToDouble(itemB);
        *(double*)itemB->pointer = i_ToDouble(itemA) * *(double*)itemB->pointer;
    }
    else if (tA == TLong || tB == TLong) // 1 long e 1 long ou char
    {
        ifunc_ConvertToLong(itemB);
        *(long*)itemB->pointer = i_ToLong(itemA) * *(long*)itemB->pointer;
    }
    else *(char*)itemB->pointer = *(char*)itemA->pointer * *(char*)itemB->pointer;// 2 chars
    return 1;
}

/** @brief Calcula a divisão de dois items, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Divide(Item* itemA, Item* itemB)
{
    if (!item_IsType(itemA, IT_Num) || !item_IsType(itemB, IT_Num))
        return 0;
    ItemType tA = itemA->type, tB = itemB->type;
    if (tA == TDouble || tB == TDouble) // 1 double e 1 double, long ou char
    {
        ifunc_ConvertToDouble(itemB);
        *(double*)itemB->pointer = i_ToDouble(itemA) / *(double*)itemB->pointer;
    }
    else if (tA == TLong || tB == TLong) // 1 long e 1 long ou char
    {
        ifunc_ConvertToLong(itemB);
        *(long*)itemB->pointer = i_ToLong(itemA) / *(long*)itemB->pointer;
    }
    else *(char*)itemB->pointer = *(char*)itemA->pointer / *(char*)itemB->pointer;// 2 chars
    return 1;
}


/** @brief Calcula o resto da divisão de dois items, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Mod(Item* itemA, Item* itemB)
{
    if (!item_IsType(itemA, IT_Num) || !item_IsType(itemB, IT_Num))
        return 0;
    ItemType tA = itemA->type, tB = itemB->type;
    if (tA == TDouble || tB == TDouble) // 1 double e 1 double, long ou char
    {
        ifunc_ConvertToDouble(itemB);
        *(double*)itemB->pointer = (double)(i_ToLong(itemA) % i_ToLong(itemB));
    }
    else if (tA == TLong || tB == TLong) // 1 long e 1 long ou char
    {
        ifunc_ConvertToLong(itemB);
        *(long*)itemB->pointer = i_ToLong(itemA) % *(long*)itemB->pointer;
    }
    else *(char*)itemB->pointer = *(char*)itemA->pointer % *(char*)itemB->pointer;// 2 chars
    return 1;
}

/** @brief Calcula o itemA elevado a itemB, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Pow(Item* itemA, Item* itemB)
{
    if (!item_IsType(itemA, IT_Num) || !item_IsType(itemB, IT_Num))
        return 0;
    ItemType tA = itemA->type, tB = itemB->type;
    if (tA == TDouble || tB == TDouble) // 1 double e 1 double, long ou char
    {
        ifunc_ConvertToDouble(itemB);
        *(double*)itemB->pointer = pow(i_ToDouble(itemA), *(double*)itemB->pointer);
    }
    else if (tA == TLong || tB == TLong) // 1 long e 1 long ou char
    {
        ifunc_ConvertToLong(itemB);
        *(long*)itemB->pointer = (long)pow(i_ToLong(itemA), *(long*)itemB->pointer);
    }
    else *(char*)itemB->pointer = (char)pow(*(char*)itemA->pointer, *(char*)itemB->pointer);// 2 chars
    return 1;
}


/** @brief Calcula itemA & itemB, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_And(Item* itemA, Item* itemB)
{
    if (!item_IsType(itemA, IT_Num) || !item_IsType(itemB, IT_Num))
        return 0;
    ifunc_ConvertToLong(itemB);
    *(long*)itemB->pointer = i_ToLong(itemA) & *(long*)itemB->pointer;
    return 1;
}

/** @brief Calcula itemA | itemB, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Or(Item* itemA, Item* itemB)
{
    if (!item_IsType(itemA, IT_Num) || !item_IsType(itemB, IT_Num))
        return 0;
    ifunc_ConvertToLong(itemB);
    *(long*)itemB->pointer = i_ToLong(itemA) | *(long*)itemB->pointer;
    return 1;
}

/** @brief Calcula itemA ^ itemB, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Xor(Item* itemA, Item* itemB)
{
    if (!item_IsType(itemA, IT_Num) || !item_IsType(itemB, IT_Num))
        return 0;
    ifunc_ConvertToLong(itemB);
    *(long*)itemB->pointer = i_ToLong(itemA) ^ *(long*)itemB->pointer;
    return 1;
}

/** @brief Calcula ~item.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param item Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Not(Item* item)
{
    if (!item_IsType(item, IT_Num))
        return 0;
    ifunc_ConvertToLong(item);
    *(long*)item->pointer = ~ *(long*)item->pointer;
    return 1;
}














