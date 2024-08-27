/**
 * @file Funções relativas a items, como operações matemáticas e conversões
 */

#pragma once

#include "item.h"


// Conversões

/** @brief Converte o tipo no item para um Long.
 * 
 * @warning Esta função apenas funciona com chars, longs, doubles e strings.
 * @param item Apontador para o item
 * @returns 1 se o item poder ser convertido
 */
int ifunc_ConvertToLong(Item* item);

/** @brief Converte o tipo no item para um Double.
 * 
 * @warning Esta função apenas funciona com chars, longs, doubles e strings.
 * @param item Apontador para o item
 * @returns 1 se o item poder ser convertido
 */
int ifunc_ConvertToDouble(Item* item);

/** @brief Converte o tipo no item para um Char.
 * 
 * @warning Esta função apenas funciona com chars, longs, doubles e strings.
 * @param item Apontador para o item
 * @returns 1 se o item poder ser convertido
 */
int ifunc_ConvertToChar(Item* item);

/** @brief Converte o tipo no item para um String.
 * 
 * @warning Esta função apenas funciona com chars, longs, doubles e strings.
 * @param item Apontador para o item
 * @returns 1 se o item poder ser convertido
 */
int ifunc_ConvertToString(Item* item);

/** @brief Converte o tipo no item para uma lista.
 * 
 * @warning Esta função apenas funciona com chars, longs, doubles, strings e listas.
 * @param item Apontador para o item
 * @returns 1 se o item puder ser convertido
 */
int ifunc_ConvertToList(Item* item);



// Math

/** @brief Adiciona 1 ao número guardado no item (mantém o tipo).
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles.
 * @param item Apontador para o item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Increment(Item* item);

/** @brief Remove 1 ao número guardado no item (mantém o tipo).
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles.
 * @param item Apontador para o item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Decrement(Item* item);


/** @brief Calcula a soma dos dois items, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Add(Item* itemA, Item* itemB);

/** @brief Calcula a subtração de dois items, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Subtract(Item* itemA, Item* itemB);

/** @brief Calcula a multiplicação de dois items, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Multiply(Item* itemA, Item* itemB);

/** @brief Calcula a divisão de dois items, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Divide(Item* itemA, Item* itemB);


/** @brief Calcula o resto da divisão de dois items, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Mod(Item* itemA, Item* itemB);

/** @brief Calcula o itemA elevado a itemB, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Pow(Item* itemA, Item* itemB);


/** @brief Calcula itemA & itemB, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_And(Item* itemA, Item* itemB);

/** @brief Calcula itemA | itemB, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Or(Item* itemA, Item* itemB);

/** @brief Calcula itemA ^ itemB, e coloca o resultado no itemB.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param itemA Apontador para um item
 * @param itemB Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Xor(Item* itemA, Item* itemB);

/** @brief Calcula ~item.
 * 
 * @warning Esta função apenas funciona com chars, longs e doubles e troca o tipo do itemB.
 * @param item Apontador para um item
 * @returns 1 se a operação puder ser efetuada
 */
int ifunc_Not(Item* item);




