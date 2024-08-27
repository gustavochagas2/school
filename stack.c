/**
 * @file Stack é uma estrutura de dados em que o primeiro item a entrar é o ultimo a sair
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "utils.h"


/** @brief Verifica se o stack tem espaço para mais um item.
 * 
 * @param stack Apontador para o stack
 */
void stack_AssureCapacity(Stack* stack)
{
    if (stack->pointer + 2 >= stack->capacity)
        stack_IncreaseSize(stack, stack->capacity);
}


/** @brief Cria um stack.
 * 
 * @warning O novo stack é criado com o "malloc", logo tem que ser libertado depois usando a função 'stack_Dispose'.
 * @param initialSize Tamanho do stack (Se <= 0, o tamanho passa para 100)
 * @returns Novo stack
 */
Stack* stack_Create(int initialSize)
{
    if (initialSize <= 0)
        initialSize = DefaultStringBufferSize;
    Stack* stack = malloc(sizeof(Stack));
    stack->array = calloc(initialSize, sizeof(Item*));
    stack->capacity = initialSize;
    stack->pointer = -1;
    return stack;
}

/** @brief Aumenta o tamanho do stack.
 * 
 * @param stack Apontador para o stack
 * @param increase Tamanho a acrescentar ao stack
 */
void stack_IncreaseSize(Stack* stack, int increase)
{
    int size = stack->capacity + increase;
    Item** new = calloc(size, sizeof(Item*));
    memcpy(new, stack->array, (stack->pointer + 1) * sizeof(Item*));
    free(stack->array);
    stack->array = new;
    stack->capacity = size;
}

/** @brief Limpa os items no stack.
 * 
 * @param stack Apontador para o stack
 */
void stack_Clear(Stack* stack)
{
    Item** array = stack->array;
    for (int i = 0; i < stack->capacity; i++)
        if (array[i] != NULL)
        {
            item_Dispose(array[i]);
            array[i] = NULL;
        }
}

/** @brief Limpa o stack e os items no stack.
 * 
 * @param stack Apontador para o stack
 */
void stack_Dispose(Stack* stack)
{
    stack_Clear(stack);
    free(stack->array);
    free(stack);
}

/** @brief Verifica se o stack está vazio.
 * 
 * @param stack Apontador para o stack
 * @returns 1 se o stack estiver vazio, 0 se não
 */
int stack_IsEmpty(Stack* stack)
{ return stack->pointer <= -1; }

/** @brief Calcula o número de items no stack.
 * 
 * @param stack Apontador para o stack
 * @returns Quantidade de items no stack
 */
int stack_Count(Stack* stack)
{ return stack->pointer + 1; }



/** @brief Guarda um item na stack.
 * 
 * @param stack Apontador para o stack
 * @param item Apontador para o item
 */
void stack_Push(Stack* stack, Item* item)
{
    stack_AssureCapacity(stack);
    stack->pointer++;
    stack->array[stack->pointer] = item;
}

/** @brief Retira um item da stack.
 * 
 * @param stack Apontador para o stack
 * @returns Item removido
 */
Item* stack_Pop(Stack* stack)
{
    if (stack_IsEmpty(stack))
        return NULL;
    Item* item = stack->array[stack->pointer];
    stack->array[stack->pointer] = NULL;
    stack->pointer--;
    return item;
}

/** @brief Retorna o item no topo da stack sem o remover.
 * 
 * @param stack Apontador para o stack
 * @returns Item
 */
Item* stack_Peek(Stack* stack)
{
    if (stack_IsEmpty(stack))
        return NULL;
    return stack->array[stack->pointer];
}


/** @brief Copia um dos items na stack.
 * 
 * @param stack Apontador para o stack
 * @param n Indice do item a ser copiado, sendo 0 o topo
 * @returns Copia do item
 */
Item* stack_CopyN(Stack* stack, int n)
{
    if (n < 0 && n > stack->pointer)
        return NULL;
    return item_Copy(stack->array[stack->pointer - n]);
}

/** @brief Troca de lugar 2 items da stack.
 * 
 * @param stack Apontador para o stack
 * @param n1 Indice 1
 * @param n2 Indice 2 
 */
void stack_Switch(Stack* stack, int n1, int n2)
{
    if (n1 < 0 || n2 < 0 || n1 > stack->pointer || n2 > stack->pointer)
        return;
    Item* temp = stack->array[n1];
    stack->array[n1] = stack->array[n2];
    stack->array[n2] = temp;
}



/** @brief Converte um stack para uma lista
 * 
 * @param stack Apontador para o stack
 * @returns Lista
 */
List* stack_ToList(Stack* stack)
{
    List* list = list_Create(stack->pointer + 1);
    for (int i = 0; i <= stack->pointer; i++)
        list_Add(list, item_Copy(stack->array[i]));
    return list;
}

/** @brief Converte uma lista para um stack
 * 
 * @param stack Apontador para a lista
 * @returns Lista
 */
Stack* stack_FromList(List* list)
{
    Stack* stack = stack_Create(list->count);
    for (int i = 0; i < list->count; i++)
        stack_Push(stack, item_Copy(list->array[i]));
    return stack;
}



/** @brief Imprime o stack.
 * 
 * @param stack Apontador para o stack
 */
void stack_Print(Stack* stack)
{
    if (stack->pointer > -1)
        for (int i = 0; i <= stack->pointer; i++)
            item_Print(stack->array[i]);
}

/** @brief Imprime o stack com espaços a separar os items.
 * 
 * @param stack Apontador para o stack
 */
void stack_PrintWS(Stack* stack)
{
    if (stack->pointer > 0)
        for (int i = 0; i < stack->pointer; i++)
        {
            item_Print(stack->array[i]);
            printf(" ");
        }
    if (stack->pointer > -1)
        item_Print(stack->array[stack->pointer]);
}








