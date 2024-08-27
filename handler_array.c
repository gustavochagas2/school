/**
 * @file Handlers - Funções que processam alguns comandos, neste caso, sobre funções de arrays
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "handler_array.h"
#include "itemfunctions.h"
#include "parser.h"
#include "utils.h"

// ""
/** @brief Função que gera uma string, da entrada.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @param line Linha de entrada
 * @param linePos Posição de leitura na linha
 * @returns 1 se tiver sucesso
 */
int h_a_CreateString(Stack* stack, char cmd, char* line, int* linePos)
{
    if (cmd != '\"')
        return 0;
    int end = utils_NextChar(line, *linePos, '\"');
    char* string = utils_Substring(line + *linePos, end - *linePos);
    Item* item = icreate_String(string, end - *linePos);
    stack_Push(stack, item);
    *linePos = end + 1;
    return 1;
}

// ~
/** @brief Função que gera uma string, da entrada.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_a_Split(Stack* stack, char cmd)
{
    if (cmd != '~')
        return 0;
    Item* item = stack_Peek(stack);
    if (!item_IsType(item, IT_Arr))
        return 0;
    stack_Pop(stack);
    if (item->type == TString)
    {
        char* s = (char*)item->pointer;
        for (int i = 0; i < item->size; i++)
            stack_Push(stack, icreate_Char(s[i]));
        item_Dispose(item);
    }
    else
    {
        List* l = (List*)item->pointer;
        for (int i = 0; i < l->count; i++)
            stack_Push(stack, l->array[i]);
        list_Free(l); item_Free(item);
    }
    return 1;
}


// +
/** @brief Função que junta strings.
 * 
 * @param ia Item A
 * @param ib Item B
 * @param result Apontador para o resultado
 * @returns 1 se tiver sucesso
 */
int h_ah_ConcatStrings(Item* ia, Item* ib, long* result)
{
    if (!(ia->type == ib->type && ia->type == TString))
        return 0;
    char* a = (char*)ia->pointer, *b = (char*)ib->pointer;
    char* s = utils_ConcatString(a, b);
    *result = (long)icreate_String(s, strlen(s));
    item_Dispose(ia); item_Dispose(ib);
    return 1;
}
/** @brief Função que junta string e char.
 * 
 * @param ia Item A
 * @param ib Item B
 * @param result Apontador para o resultado
 * @returns 1 se tiver sucesso
 */
int h_ah_ConcatStringChar(Item* ia, Item* ib, long* result)
{
    if (!(ia->type == TString && ib->type == TChar))
        return 0;
    char* a = (char*)ia->pointer;
    char* b = calloc(2, sizeof(char));
    b[0] =  *(char*)ib->pointer;
    char* s = utils_ConcatString(a, b);
    *result = (long)icreate_String(s, strlen(s));
    item_Dispose(ia); item_Dispose(ib);
    return 1;
}
/** @brief Função que junta string e char.
 * 
 * @param ia Item A
 * @param ib Item B
 * @param result Apontador para o resultado
 * @returns 1 se tiver sucesso
 */
int h_ah_ConcatCharString(Item* ia, Item* ib, long* result)
{
    if (!(ia->type == TChar && ib->type == TString))
        return 0;
    char* b = (char*)ia->pointer;
    char* a = calloc(2, sizeof(char));
    a[0] =  *(char*)ib->pointer;
    char* s = utils_ConcatString(a, b);
    *result = (long)icreate_String(s, strlen(s));
    item_Dispose(ia); item_Dispose(ib);
    return 1;
}

/** @brief Função que junta listas.
 * 
 * @param ia Item A
 * @param ib Item B
 * @param result Apontador para o resultado
 * @returns 1 se tiver sucesso
 */
int h_ah_ConcatLists(Item* ia, Item* ib, long* result)
{
    if (!(ia->type == ib->type && ia->type == TList))
        return 0;
    List* a = (List*)ia->pointer, *b = (List*)ib->pointer;
    list_AddCopyRange(a, b);
    *result = (long)icreate_FromList(a);
    item_Free(ia); item_Dispose(ib);
    return 1;
}

/** @brief Função que junta items.
 * 
 * @param ia Item A
 * @param ib Item B
 * @param result Apontador para o resultado
 * @returns 1 se tiver sucesso
 */
int h_ah_ConcatItemList(Item* ia, Item* ib, long* result)
{
    List* l = list_Create(2);
    list_Add(l, ia); list_Add(l, ib);
    *result = (long)icreate_FromList(l);
    return 1;
}


/** @brief Função que junta strings, arrays e elementos.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_a_Concat(Stack* stack, char cmd)
{
    if (cmd != '+')
        return 0;
    Item* ib = stack_Pop(stack);
    Item* ia = stack_Pop(stack);
    if (!item_IsType(ia, IT_Arr) && !item_IsType(ib, IT_Arr))
    {
        stack_Push(stack, ia);
        stack_Push(stack, ib);
        return 0;
    }
    long resultPointer = 0;
    if (!(h_ah_ConcatStrings(ia, ib, &resultPointer) || h_ah_ConcatLists(ia, ib, &resultPointer) ||
    h_ah_ConcatItemList(ia, ib, &resultPointer)))
    {
        stack_Push(stack, ia);
        stack_Push(stack, ib);
        return 0;
    }

    Item* result = (Item*)resultPointer;
    stack_Push(stack, result);
    return 1;
}


// *
/** @brief Função que repete strings ou arrays X vezes.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_a_ConcatX(Stack* stack, char cmd)
{
    if (cmd != '*')
        return 0;
    Item* in = stack_Pop(stack);
    Item* ia = stack_Pop(stack);
    if (!item_IsType(ia, IT_Arr) || !item_IsType(in, IT_Num))
    {
        stack_Push(stack, ia);
        stack_Push(stack, in);
        return 0;
    }
    long n = i_ToLong(in);
    Item* result;
    if (ia->type == TString)
    {
        char* s = utils_RepeatString((char*)ia->pointer, ia->size, n);
        result = icreate_String(s, ia->size * n);
    }
    else
    {
        List* l = (List*)ia->pointer;
        List* newl = list_Create(l->count * n);
        for (int i = 0; i < n; i++)
            list_AddCopyRange(newl, l);
        result = icreate_FromList(newl);
    }
    item_Dispose(ia);
    item_Dispose(in);
    stack_Push(stack, result);
    return 1;
}

// ,
/** @brief Função que dá o tamanho de uma string ou lista, ou cria uma lista com X elementos.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_a_RangeSize(Stack* stack, char cmd)
{
    if (cmd != ',')
        return 0;
    Item* ia = stack_Pop(stack);
    if (item_IsType(ia, IT_Num))
    {
        List* l = list_CreateRange(i_ToLong(ia));
        stack_Push(stack, icreate_FromList(l));
        item_Dispose(ia);
        return 1;
    }
    else if (ia->type == TString)
    {
        stack_Push(stack, icreate_Long(ia->size));
        item_Dispose(ia);
        return 1;
    }
    else if (ia->type == TList)
    {
        List* l = (List*)ia->pointer;
        stack_Push(stack, icreate_Long(l->count));
        item_Dispose(ia);
        return 1;
    }
    stack_Push(stack, ia);
    return 0;
}

// =
/** @brief Função que retira um elemento duma lista.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_a_ByIndex(Stack* stack, char cmd)
{
    if (cmd != '=')
        return 0;
    Item* in = stack_Pop(stack);
    Item* ia = stack_Pop(stack);
    if (!item_IsType(in, IT_Num) || !item_IsType(ia, IT_Arr))
    {
        stack_Push(stack, ia);
        stack_Push(stack, in);
        return 0;
    }
    int n = i_ToLong(in);
    if (ia->type == TList)
    {
        List* l = (List*)ia->pointer;
        Item* i = list_RemoveAt(l, n);
        if (i == NULL)
            stack_Push(stack, icreate_Long(0));
        else stack_Push(stack, i);
    }
    else
    {
        char c = ((char*)ia->pointer)[n];
        stack_Push(stack, icreate_Char(c));
    }
    item_Dispose(ia); item_Dispose(in);
    return 1;
}

// #
/** @brief Função que procura uma string num string maior.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_a_FindSub(Stack* stack, char cmd)
{
    if (cmd != '#')
        return 0;
    Item* is = stack_Pop(stack);
    Item* ia = stack_Pop(stack);
    if (ia->type != is->type || ia->type != TString)
    {
        stack_Push(stack, ia);
        stack_Push(stack, is);
        return 0;
    }
    char* a = (char*)ia->pointer, *b = (char*)is->pointer;
    char* c = strstr(a, b);
    if (c != NULL)
        stack_Push(stack, icreate_Long(c - a));
    else stack_Push(stack, icreate_Long(-1));
    item_Dispose(ia); item_Dispose(is);
    return 1;
}


// []
/** @brief Função que procura o final do array.
 * 
 * @param line Linha da entrada
 * @param linePos Posição na linha
 * @returns Posição do final
 */
int h_ah_FindEndOfArray(char* line, int* linePos)
{
    int score = 1;
    int size = strlen(line);
    int pos = *linePos;
    while (score > 0 && pos < size)
    {
        if (line[pos] == '[')
            score++;
        else if (line[pos] == ']')
            score--;
        pos++;
    }
    return pos - 1;
}

/** @brief Função que procura uma string num string maior.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_a_Array(Item** vars, Stack* stack, char cmd, char* line, int* linePos)
{
    if (cmd != '[')
        return 0;
    int end = h_ah_FindEndOfArray(line, linePos);
    char* arrayString = utils_Substring(line + *linePos, end - *linePos);
    Stack* newStack = stack_Create(StackInitialSize);
    parser_Process(vars, newStack, arrayString, end - *linePos);
    Item* result = icreate_FromList(stack_ToList(newStack));
    stack_Push(stack, result);
    stack_Dispose(newStack);
    *linePos = end + 1;
    return 1;
}


// (
/** @brief Função que retira o primeiro elemento de uma string ou array.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_a_First(Stack* stack, char cmd)
{
    if (cmd != '(')
        return 0;
    Item* ia = stack_Peek(stack);
    if (!item_IsType(ia, IT_Arr))
        return 0;
    if (ia->type == TString)
    {
        stack_Push(stack, icreate_Char(((char*)ia->pointer)[0]));
        char* s = utils_Substring((char*)ia->pointer + 1, ia->size - 1);
        free(ia->pointer);
        ia->pointer = s;
        ia->size -= 1;
    }
    else
    {
        Item* i = list_RemoveAt((List*)ia->pointer, 0);
        stack_Push(stack, i);
    }
    return 1;
}

// )
/** @brief Função que retira o ultimo elemento de uma string ou array.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_a_Last(Stack* stack, char cmd)
{
    if (cmd != ')')
        return 0;
    Item* ia = stack_Peek(stack);
    if (!item_IsType(ia, IT_Arr))
        return 0;
    if (ia->type == TString)
    {
        stack_Push(stack, icreate_Char(((char*)ia->pointer)[ia->size - 1]));
        char* s = utils_Substring((char*)ia->pointer, ia->size - 1);
        free(ia->pointer);
        ia->pointer = s;
        ia->size -= 1;
    }
    else
    {
        Item* i = list_Remove((List*)ia->pointer);
        stack_Push(stack, i);
    }
    return 1;
}

// <
/** @brief Função que retira X elemento do inicio de uma string ou array.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_a_FirstX(Stack* stack, char cmd)
{
    if (cmd != '<')
        return 0;
    Item* in = stack_Pop(stack);
    Item* ia = stack_Pop(stack);
    if (!item_IsType(ia, IT_Arr) || !item_IsType(in, IT_Num))
    {
        stack_Push(stack, ia);
        stack_Push(stack, in);
        return 0;
    }
    int n = i_ToLong(in);
    if (ia->type == TString)
    {
        if (n > ia->size) n = ia->size;
        char* s = utils_Substring(ia->pointer, n);
        stack_Push(stack, icreate_String(s, n));
    }
    else
    {
        List* list = ia->pointer;
        if (n > list->count) n = list->count;
        List* newL = list_Create(n);
        for (int i = 0; i < n; i++)
            list_Add(newL, item_Copy(list->array[i]));
        stack_Push(stack, icreate_FromList(newL));
    }
    item_Dispose(ia);
    item_Dispose(in);   
    return 1;
}

/** @brief Função que retira X elemento do fim de uma string ou array.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_a_LastX(Stack* stack, char cmd)
{
    if (cmd != '>')
        return 0;
    Item* in = stack_Pop(stack);
    Item* ia = stack_Pop(stack);
    if (!item_IsType(ia, IT_Arr) || !item_IsType(in, IT_Num))
    {
        stack_Push(stack, ia);
        stack_Push(stack, in);
        return 0;
    }
    int n = i_ToLong(in);
    if (ia->type == TString)
    {
        if (n > ia->size) n = ia->size;
        char* s = utils_Substring((char*)ia->pointer + ia->size - n, n);
        stack_Push(stack, icreate_String(s, n));
    }
    else
    {
        List* list = ia->pointer;
        if (n > list->count) n = list->count;
        List* newL = list_Create(n);
        for (int i = list->count - n; i < list->count; i++)
            list_Add(newL, item_Copy(list->array[i]));
        stack_Push(stack, icreate_FromList(newL));
    }
    item_Dispose(ia);
    item_Dispose(in);   
    return 1;
}


// /
/** @brief Função que divide uma string usando outra como separador.
 * 
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @returns 1 se tiver sucesso
 */
int h_a_SplitString(Stack* stack, char cmd)
{
    if (cmd != '/')
        return 0;
    Item* is = stack_Pop(stack);
    Item* ia = stack_Pop(stack);
    if (!item_IsType(is, IT_Txt) || ia->type != TString)
    {
        stack_Push(stack, ia);
        stack_Push(stack, is);
        return 0;
    }
    char* string = (char*)ia->pointer, *sub;
    if (is->type == TString) sub = (char*)is->pointer;
    else
    {
        sub = calloc(2, sizeof(char));
        sub[0] = *(char*)is->pointer;
    }
    char* testStr = utils_StringReplace(string, "\n", sub);
    int testStrLen = strlen(testStr);
    List* parts = list_Create(10);
    char* token = strtok(testStr, sub);
    while (token != NULL && token - testStr < testStrLen + 1)
    {
        int partLen = strlen(token);
        Item* i = icreate_String(utils_Substring(token, partLen), partLen);
        list_Add(parts, i);
        token = strtok(NULL, sub);
    }
    if (is->type == TChar)
        free(sub);
    stack_Push(stack, icreate_FromList(parts));
    item_Dispose(ia); item_Dispose(is);
    return 1;
}



/** @brief Esta função é um hub para todas as outras funções que resolvem a entrada.
 * 
 * @param vars Apontador para o array de variáveis
 * @param stack Apontador para o stack
 * @param cmd Char do comando
 * @param line Linha da entrada
 * @param linePos Posição na linha
 * @returns 1 se tiver sucesso
 */
int hHub_Array(Item** vars, Stack* stack, char cmd, char* line, int* linePos)
{
    return h_a_CreateString(stack, cmd, line, linePos) || h_a_Array(vars, stack, cmd, line, linePos) || 
    h_a_Split(stack, cmd) || h_a_Concat(stack, cmd) || h_a_ConcatX(stack, cmd) || 
    h_a_RangeSize(stack, cmd) || h_a_ByIndex(stack, cmd) || h_a_FindSub(stack, cmd) ||
    h_a_First(stack, cmd) || h_a_Last(stack, cmd) || h_a_FirstX(stack, cmd) ||
    h_a_LastX(stack, cmd) || h_a_SplitString(stack, cmd);
}
