/**
 * @file Estrutura que guarda alguns tipos diferentes do C (long, double, char, string) e alguns feitos por nós (List, Block)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "utils.h"

// Funções auxiliares

/** @brief Função auxiliar para converter uma lista para uma string.
 * 
 * @param list Apontador para a lista
 * @param buf Apontador para a string
 * @param offset Indice onde se vai começar a escrever na string
 * @returns Quantidade de carateres escritos na string
 */
int list_p_ToString(List* list, char* buf, int offset)
{
    int initial = offset;
    for (int i = 0; i < list->count; i++)
        if (list->array[i] != NULL)
            offset += item_p_ToString(list->array[i], buf, offset);
        else offset += sprintf(buf + offset, "_");
    buf[offset] = '\0';
    return offset - initial;
}
/** @brief Função auxiliar para converter um item para uma string.
 * 
 * @param item Apontador para o item
 * @param buf Apontador para a string
 * @param offset Indice onde se vai começar a escrever na string
 * @returns Quantidade de carateres escritos na string
 */
int item_p_ToString(Item* item, char* buf, int offset)
{
    int initial = offset;
    if (item->type == TLong)
        offset += sprintf(buf + offset, "%ld", *(long*)item->pointer);
    else if (item->type == TDouble)
        offset += sprintf(buf + offset, "%lg", *(double*)item->pointer);
    else if (item->type == TChar)
        offset += sprintf(buf + offset, "%c", *(char*)item->pointer);
    else if (item->type == TString)
        offset += sprintf(buf + offset, "%s", (char*)item->pointer);
    else if (item->type == TBlock)
        offset += sprintf(buf + offset, "{%s}", (char*)item->pointer);
    else offset += list_p_ToString((List*)item->pointer, buf, offset);
    buf[offset] = '\0';
    return offset - initial;
}

/** @brief Imprime o item na consola.
 *
 * @param item Apontador para o item
 */
void item_Print(Item* item)
{
    char* string = i_ToString(item);
    printf("%s", string);
    free(string);
}


// Criar o item

/** @brief Cria um item com um long.
 * 
 * @warning O novo item é criado com o "malloc", logo tem que ser libertado depois usando a função 'item_Dispose'.
 * @param value Valor a guardar no item
 * @returns Item criado
 */
Item* icreate_Long(long value)
{
    long* buffer = malloc(sizeof(long));
    *buffer = value;
    Item* item = malloc(sizeof(Item));
    item->size = sizeof(long);
    item->pointer = buffer;
    item->type = TLong;
    return item;
}

/** @brief Cria um item com um double.
 * 
 * @warning O novo item é criado com o "malloc", logo tem que ser libertado depois usando a função 'item_Dispose'.
 * @param value Valor a guardar no item
 * @returns Item criado
 */
Item* icreate_Double(double value)
{
    double* buffer = malloc(sizeof(double));
    *buffer = value;
    Item* item = malloc(sizeof(Item));
    item->size = sizeof(double);
    item->pointer = buffer;
    item->type = TDouble;
    return item;
}

/** @brief Cria um item com um char.
 * 
 * @warning O novo item é criado com o "malloc", logo tem que ser libertado depois usando a função 'item_Dispose'.
 * @param value Valor a guardar no item
 * @returns Item criado
 */
Item* icreate_Char(char value)
{
    char* buffer = malloc(sizeof(char));
    *buffer = value;
    Item* item = malloc(sizeof(Item));
    item->size = sizeof(char);
    item->pointer = buffer;
    item->type = TChar;
    return item;
}

/** @brief Cria um item com uma string.
 * 
 * @warning O novo item é criado com o "malloc", logo tem que ser libertado depois usando a função 'item_Dispose'.
 * @param value Valor a guardar no item
 * @returns Item criado
 */
Item* icreate_String(char* value, int size)
{
    Item* item = malloc(sizeof(Item));
    item->size = sizeof(char) * size;
    item->pointer = value;
    item->type = TString;
    return item;
}

/** @brief Cria um item com uma lista.
 * 
 * @warning O novo item é criado com o "malloc", logo tem que ser libertado depois usando a função 'item_Dispose'.
 * @returns Item criado
 */
Item* icreate_List()
{
    List* list = list_Create(DefaultStringBufferSize);
    Item* item = malloc(sizeof(Item));
    item->size = sizeof(List);
    item->pointer = list;
    item->type = TList;
    return item;
}

/** @brief Cria um item com uma lista.
 * 
 * @warning O novo item é criado com o "malloc", logo tem que ser libertado depois usando a função 'item_Dispose'.
 * @param value Lista a guardar no item
 * @returns Item criado
 */
Item* icreate_FromList(List* list)
{
    Item* item = malloc(sizeof(Item));
    item->size = sizeof(List);
    item->pointer = list;
    item->type = TList;
    return item;
}

/** @brief Cria um item com um bloco.
 * 
 * @warning O novo item é criado com o "malloc", logo tem que ser libertado depois usando a função 'item_Dispose'.
 * @param value Valor a guardar no item
 * @returns Item criado
 */
Item* icreate_Block(char* value, int size)
{
    Item* item = malloc(sizeof(Item));
    // Precisa-se do +1 por causa do '\\0' no final
    item->size = sizeof(char) * (size + 1);
    item->pointer = value;
    item->type = TBlock;
    return item;
}


// Converter Items para tipos

/** @brief Pega no conteudo do item e converte-o para um long.
 * 
 * @param item Apontador para o item
 * @returns Long
 */
long i_ToLong(Item* item)
{
    ItemType type = item->type;
    if (type == TLong)
        return *(long*)item->pointer;
    else if (type == TChar)
        return (long)*(char*)item->pointer;
    else if (type == TDouble)
        return (long)*(double*)item->pointer;
    else if (type == TString)
        return utils_LongFromString((char*)item->pointer);
    return 0;
}

/** @brief Pega no conteudo do item e converte-o para um double.
 * 
 * @param item Apontador para o item
 * @returns Double
 */
double i_ToDouble(Item* item)
{
    ItemType type = item->type;
    if (type == TDouble)
        return *(double*)item->pointer;
    else if (type == TLong)
        return (double)*(long*)item->pointer;
    else if (type == TChar)
        return (double)*(char*)item->pointer; 
    else if (type == TString)
        return utils_DoubleFromString((char*)item->pointer);
    return 0.0;
}

/** @brief Pega no conteudo do item e converte-o para um char.
 * 
 * @param item Apontador para o item
 * @returns Char
 */
char i_ToChar(Item* item)
{
    ItemType type = item->type;
    if (type == TChar)
        return *(char*)item->pointer;
    else if (type == TDouble)
        return (char)*(double*)item->pointer;
    else if (type == TLong)
        return (char)*(long*)item->pointer;  
    else if (type == TString)
        return utils_CharFromString((char*)item->pointer);
    return ' ';
}

/** @brief Pega no conteudo do item e converte-o para uma string.
 * 
 * @param item Apontador para o item
 * @returns String
 */
char* i_ToString(Item* item)
{
    char* buffer = calloc(DefaultStringBufferSize, sizeof(char));
    int size = item_p_ToString(item, buffer, 0);
    char* s = utils_Substring(buffer, size);
    free(buffer);
    return s;
}

/** @brief Pega no conteudo do item e converte-o para uma lista.
 * 
 * @param item Apontador para o item
 * @returns List
 */
List* i_ToList(Item* item)
{
    if (item->type == TList)
        return list_Copy((List*)item->pointer);
    List* list = list_Create(ListInitialSize);
    if (item->type != TString)
        list_Add(list, item);
    else
    {
        char* string = (char*)item->pointer;
        for (int i = 0; i < item->size; i++)
            list_Add(list, icreate_Char(string[i]));
    }
    return list;
}



// Items

/** @brief Função auxiliar para mais facilmente verificar o tipo de um item.
 * 
 * @param item Apontador para o item
 * @param mask Mascara usada para verificar o tipo (IT_Int, IT_Num, IT_Arr)
 * @returns 1 se o item for do tipo da mascara, 0 se não
 */
int item_IsType(Item* item, int mask) 
{ return (item->type & mask) != 0; }

/** @brief Cria uma cópia do item.
 * 
 * @param item Item
 * @returns Cópia do item
 */
Item* item_Copy(Item* item)
{
    Item* new = malloc(sizeof(Item));
    new->type = item->type;
    new->size = item->size;
    if (item->type != TList)
    {
        int size = (item->type == TString) ? item->size + 1 : item->size;
        void* buffer = malloc(size);
        memcpy(buffer, item->pointer, size);
        new->pointer = buffer;
        return new;
    }
    new->pointer = list_Copy(item->pointer);
    return new;
}

/** @brief Liberta a memória ocupada pelo item e o seu conteudo.
 * 
 * @param item Item
 */
void item_Dispose(Item* item)
{
    if (item->type != TList)
        free(item->pointer);
    else list_Dispose(item->pointer);
    free(item);
}

/** @brief Liberta a memória ocupada pelo item (apenas o struct).
 * 
 * @param item Item
 */
void item_Free(Item* item)
{  free(item); }

/** @brief Verifica se dois items sao iguais.
 * 
 * @param itemA Lista 
 * @param itemB Lista 
 * @returns 1 ou 0
 */
int item_Equals(Item* itemA, Item* itemB)
{
    if (item_IsType(itemA, IT_Num2) && item_IsType(itemB, IT_Num2) && !(itemA->type == itemB->type && itemA->type == TString))
    {
        double a = i_ToDouble(itemA), b = i_ToDouble(itemB);
        return utils_DoubleEquals(a, b);
    }
    if (itemA->type == itemB->type && (itemA->type == TString || itemA->type == TBlock))
    {
        char* a = (char*)itemA->pointer, *b = (char*)itemB->pointer;
        return utils_StringEquals(a, b);
    }
    if (itemA->type == itemB->type && itemA->type == TList)
    {
        List* a = (List*)itemA->pointer, *b = (List*)itemB->pointer;
        return list_Equals(a, b);
    }
    return 0;
}




/** @brief Troca o conteudo de dois items.
 * 
 * @param ia Primeiro item
 * @param ib Segundo item
 */
void item_Swap(Item* ia, Item* ib)
{
    void* p = ia->pointer;
    int s = ia->size;
    ItemType t = ia->type;
    ia->pointer = ib->pointer;
    ia->size = ib->size;
    ia->type = ib->type;
    ib->pointer = p;
    ib->size = s;
    ib->type = t;
}



// Listas

/** @brief Cria uma lista.
 * 
 * @warning A nova lista é criada com o "malloc", logo tem que ser libertada depois usando a função 'list_Dispose'.
 * @param initialSize Tamanho da lista (Se <= 0, o tamanho passa para 25)
 * @returns Nova lista
 */
List* list_Create(int initialSize)
{
    if (initialSize <= 0)
        initialSize = ListInitialSize;
    List* list = malloc(sizeof(List));
    Item** array = calloc(initialSize, sizeof(Item*));
    list->array = array;
    list->capacity = initialSize;
    list->count = 0;
    return list;
}

/** @brief Cria uma lista com um 'range'.
 * 
 * @warning A nova lista é criada com o "malloc", logo tem que ser libertada depois usando a função 'list_Dispose'.
 * @param n Tamanho da lista (Se <= 0, o tamanho passa para 25)
 * @returns Nova lista
 */
List* list_CreateRange(int n)
{
    if (n <= 0)
        n = ListInitialSize;
    List* list = malloc(sizeof(List));
    Item** array = calloc(n, sizeof(Item*));
    list->array = array;
    list->capacity = n;
    list->count = 0;
    for (int i = 0; i < n; i++)
        list_Add(list, icreate_Long(i));
    return list;
}

/** @brief Aumenta a capacidade de uma lista.
 * 
 * @param list Apontador para a lista
 * @param extraSize Tamanho a adicionar à lista
 */
void list_IncreaseSize(List* list, int extraSize)
{
    Item** oldarray = list->array;
    Item** newarray = calloc(list->capacity + extraSize, sizeof(Item*));
    list->array = newarray;
    for (int i = 0; i < list->count; i++)
        newarray[i] = oldarray[i];
    list->capacity += extraSize;
    free(oldarray);
}

/** @brief Cria uma cópia de uma lista.
 * 
 * @warning A nova lista é criada com o "malloc", logo tem que ser libertada depois usando a função 'list_Dispose'.
 * @param list Lista original
 * @returns Cópia da lista
 */
List* list_Copy(List* list)
{
    List* new = list_Create(list->capacity);
    for (int i = 0; i < list->count; i++)
        new->array[i] = item_Copy(list->array[i]);
    new->count = list->count;
    return new;
}

/** @brief Liberta a memória ocupada pela lista e os seus items.
 * 
 * @param list Lista
 */
void list_Dispose(List* list)
{
    for (int i = 0; i < list->count; i++)
        if (list->array[i] != NULL)
            item_Dispose(list->array[i]);
    free(list->array);
    free(list);
}

/** @brief Liberta a memória ocupada pela lista.
 * 
 * @param list Lista
 */
void list_Free(List* list)
{
    free(list->array);
    free(list);
}

/** @brief Verifica se duas listas sao iguais.
 * 
 * @param listA Lista 
 * @param listB Lista 
 * @returns 1 ou 0
 */
int list_Equals(List* listA, List* listB)
{
    if (listA->count != listB->count)
        return 0;
    for (int i = 0; i < listA->count; i++)
        if (!item_Equals(listA->array[i], listB->array[i]))
            return 0;
    return 1;
}


/** @brief Verifica se a lista tem espaço para N elementos extra, e aumenta o tamanho se esta não tiver.
 * 
 * @param list Apontador para a lista
 * @param n Tamanho a verificar
 */
void list_p_AssureSizeN(List* list, int n)
{
    if (list->count + n > list->capacity)
        list_IncreaseSize(list, n + ListResizeSize);
}
/** @brief Verifica se a lista tem espaço para um elemento extra, e aumenta o tamanho se esta não tiver.
 * 
 * @param list Apontador para a lista
 */
void list_p_AssureSize(List* list)
{ list_p_AssureSizeN(list, 1); }


/** @brief Adiciona um item a uma lista.
 * 
 * @param list Lista
 * @param item Item a adicionar
 */
void list_Add(List* list, Item* item)
{
    list_p_AssureSize(list);
    list->array[list->count] = item;
    list->count += 1;
}

/** @brief Adiciona um item a uma lista.
 * 
 * @param list Lista
 * @param item Item a adicionar
 * @param index Indice onde se vai inserir o item
 */
void list_AddAt(List* list, Item* item, int index)
{
    if (index >= list->count)
    {
        list_Add(list, item);
        return;
    }
    if (index < 0)
        index = 0;
    list_ShiftRight(list, index);
    list->array[index] = item;
}

/** @brief Adiciona uma lista a uma lista.
 * 
 * @param list Lista
 * @param range Lista a adicionar
 */
void list_AddRange(List* list, List* range)
{
    list_p_AssureSizeN(list, range->count);
    Item** array = list->array;
    int offset = list->count;
    for (int i = 0; i < range->count; i++)
        array[offset + i] = range->array[i];
    list->count += range->count;
}

/** @brief Adiciona uma lista a uma lista, copiando os valores.
 * 
 * @param list Lista
 * @param range Lista a adicionar
 */
void list_AddCopyRange(List* list, List* range)
{
    list_p_AssureSizeN(list, range->count);
    Item** array = list->array;
    int offset = list->count;
    for (int i = 0; i < range->count; i++)
        array[offset + i] = item_Copy(range->array[i]);
    list->count += range->count;
}


/** @brief Desloca a lista, a partir de um indice, para a esquerda.
 * 
 * @param list Lista
 * @param index Indice do inicio
 */
void list_ShiftLeft(List* list, int index)
{ list_ShiftLeftN(list, index, 1); }

/** @brief Desloca a lista, a partir de um indice, para a esquerda.
 * 
 * @param list Lista
 * @param i Indice do inicio
 * @param n Quantidade a deslocar
 */
void list_ShiftLeftN(List* list, int index, int n)
{
    if (list->count <= 0)
        return;
    Item** array = list->array;
    for (int i = index; i < list->count - n; i++)
        array[i] = array[i + n];
    for (int i = 0; i < n; i++)
        array[list->count - n + i] = NULL;
    list->count -= n;
}

/** @brief Desloca a lista, a partir de um indice, para a direita.
 * 
 * @param list Lista
 * @param index Indice do inicio
 */
void list_ShiftRight(List* list, int index)
{ list_ShiftRightN(list, index, 1); }

/** @brief Desloca a lista, a partir de um indice, para a direita.
 * 
 * @param list Lista
 * @param index Indice do inicio
 * @param n Quantidade a deslocar
 */
void list_ShiftRightN(List* list, int index, int n)
{
    if (list->count <= 0)
        return;
    list_p_AssureSizeN(list, n);
    Item** array = list->array;
    for (int i = list->count - 1 + n; i > index + n; i--)
        array[i] = array[i - n];
    for (int i = index; i < n; i++)
        array[i] = NULL;
    list->count += n;
}


/** @brief Remove um item de uma lista.
 * 
 * @param list Lista
 * @returns Item removido
 */
Item* list_Remove(List* list)
{
    if (list->count <= 0)
        return NULL;
    list->count -= 1;
    Item* item = list->array[list->count];
    list->array[list->count] = NULL;
    return item;
}

/** @brief Remove um item de uma lista.
 * 
 * @param list Lista
 * @param i Indice do item a ser removido
 * @returns Item removido
 */
Item* list_RemoveAt(List* list, int i)
{
    if (list->count <= 0 || i < 0 || i >= list->count)
        return NULL;
    Item** array = list->array;
    Item* item = array[i];
    list_ShiftLeft(list, i);
    return item;
}

/** @brief Troca a ordem dos items da lista
 * 
 * @param list Lista
 * @returns Lista reversa
 */
List* list_Reverse(List* list)
{
    List* newlist = list_Create(list->capacity);
    int n = list->count;
    for (int i = 0; i < n; i++)
        list_Add(newlist, list_Remove(list));
    list_Free(list);
    return newlist;
}


/** @brief Cria uma lista com todos os chars da string
 * 
 * @param string Apontador para a string
 * @param size Tamanho da string
 * @returns Apontador para a Lista
 */
List* list_FromString(char* string, int size)
{
    List* list = list_Create(size);
    for (int i = 0; i < size; i++)
        list_Add(list, icreate_Char(string[i]));
    return list;
}





