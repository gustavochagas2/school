/**
 * @file Stack é uma estrutura de dados em que o primeiro item a entrar é o ultimo a sair
 */

#pragma once

#include "item.h"

/** Tamanho inicial de um stack */
#define StackInitialSize 100

/**
 * Struct que representa um Stack
 */
typedef struct StackT
{
    Item** array;   /*!< Array de apontadores para os items na stack */
    int pointer;    /*!< Indice do item no topo da stack */
    int capacity;   /*!< Capacidade da stack */
} Stack;



/** @brief Cria um stack.
 * 
 * @warning O novo stack é criado com o "malloc", logo tem que ser libertado depois usando a função 'stack_Dispose'.
 * @param initialSize Tamanho do stack (Se <= 0, o tamanho passa para 100)
 * @returns Novo stack
 */
Stack* stack_Create(int initialSize);

/** @brief Aumenta o tamanho do stack.
 * 
 * @param stack Apontador para o stack
 * @param increase Tamanho a acrescentar ao stack
 */
void stack_IncreaseSize(Stack* stack, int increase);

/** @brief Limpa os items no stack.
 * 
 * @param stack Apontador para o stack
 */
void stack_Clear(Stack* stack);

/** @brief Limpa o stack e os items no stack.
 * 
 * @param stack Apontador para o stack
 */
void stack_Dispose(Stack* stack);

/** @brief Verifica se o stack está vazio.
 * 
 * @param stack Apontador para o stack
 * @returns 1 se o stack estiver vazio, 0 se não
 */
int stack_IsEmpty(Stack* stack);

/** @brief Calcula o número de items no stack.
 * 
 * @param stack Apontador para o stack
 * @returns Quantidade de items no stack
 */
int stack_Count(Stack* stack);


/** @brief Guarda um item na stack.
 * 
 * @param stack Apontador para o stack
 * @param item Apontador para o item
 */
void stack_Push(Stack* stack, Item* item);

/** @brief Retira um item da stack.
 * 
 * @param stack Apontador para o stack
 * @returns Item removido
 */
Item* stack_Pop(Stack* stack);

/** @brief Retorna o item no topo da stack sem o remover.
 * 
 * @param stack Apontador para o stack
 * @returns Item
 */
Item* stack_Peek(Stack* stack);


/** @brief Copia um dos items na stack.
 * 
 * @param stack Apontador para o stack
 * @param n Indice do item a ser copiado, sendo 0 o topo
 * @returns Copia do item
 */
Item* stack_CopyN(Stack* stack, int n);

/** @brief Troca de lugar 2 items da stack.
 * 
 * @param stack Apontador para o stack
 * @param n1 Indice 1
 * @param n2 Indice 2 
 */
void stack_Switch(Stack* stack, int n1, int n2);



/** @brief Converte um stack para uma lista
 * 
 * @param stack Apontador para o stack
 * @returns Lista
 */
List* stack_ToList(Stack* stack);

/** @brief Converte uma lista para um stack
 * 
 * @param stack Apontador para a lista
 * @returns Lista
 */
Stack* stack_FromList(List* list);



/** @brief Imprime o stack.
 * 
 * @param stack Apontador para o stack
 */
void stack_Print(Stack* stack);

/** @brief Imprime o stack com espaços a separar os items.
 * 
 * @param stack Apontador para o stack
 */
void stack_PrintWS(Stack* stack);


