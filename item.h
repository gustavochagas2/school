/**
 * @file Estrutura que guarda alguns tipos diferentes do C (long, double, char, string) e alguns feitos por nós (List, Block)
 */

#pragma once

/** Tamanho inicial de uma lista */
#define ListInitialSize 25
/** Tamanho extra adicionado a uma lista quando esta precisa de ser expandida */
#define ListResizeSize 25

/**
 * Enum que representa o tipo de um item
 */
typedef enum ItemValueType
{
    TLong   = 1,    /*!< Longs são números inteiros */
    TDouble = 2,    /*!< Doubles são números com casas decimais */
    TChar   = 4,    /*!< Chars são números inteiros que representão caracteres */
    TString = 8,    /*!< Strings são arrays de chars */
    TList   = 16,   /*!< Lista é um tipo criado por nós que guarda qualquer outro tipo neste enum */
    TBlock  = 32,   /*!< Block é apenas uma string, mas tem que ser diferenciada para saber se é executável ou não */
} ItemType;


/** Tipos que são inteiros */
#define IT_Int (TChar | TLong)
/** Tipos que são números */
#define IT_Num (IT_Int | TDouble)
/** Tipos que são números ou convertidos */
#define IT_Num2 (IT_Int | TDouble | TString)
/** Tipos que são texto */
#define IT_Txt (TChar | TString)
/** Tipos que são 'arrays' */
#define IT_Arr (TString | TList)


/**
 * Struct usado para guardar vários tipos numa lista / stack / etc
 */
typedef struct ItemContainer
{
    void* pointer;  /*!< Apontador para o pedaço de memória onde está guardado o tipo */
    ItemType type;  /*!< Tipo do que está guardado no apontador */
    int size;       /*!< Tamanho do item que está guardado (util para blocos e strings) */
} Item;

/**
 * Lista é uma array que facilita a adição e remoção de items
 */
typedef struct ItemList
{
    Item** array;   /*!< Apontador para array de items */
    int capacity;   /*!< Quantidade de items que a lista pode guardar */
    int count;      /*!< Quantidade de items que a lista tem */
} List;


// Criar o item

/** @brief Cria um item com um long.
 * 
 * @warning O novo item é criado com o "malloc", logo tem que ser libertado depois usando a função 'item_Dispose'.
 * @param value Valor a guardar no item
 * @returns Item criado
 */
Item* icreate_Long(long value);

/** @brief Cria um item com um double.
 * 
 * @warning O novo item é criado com o "malloc", logo tem que ser libertado depois usando a função 'item_Dispose'.
 * @param value Valor a guardar no item
 * @returns Item criado
 */
Item* icreate_Double(double value);

/** @brief Cria um item com um char.
 * 
 * @warning O novo item é criado com o "malloc", logo tem que ser libertado depois usando a função 'item_Dispose'.
 * @param value Valor a guardar no item
 * @returns Item criado
 */
Item* icreate_Char(char value);

/** @brief Cria um item com uma string.
 * 
 * @warning O novo item é criado com o "malloc", logo tem que ser libertado depois usando a função 'item_Dispose'.
 * @param value Valor a guardar no item
 * @returns Item criado
 */
Item* icreate_String(char* value, int size);

/** @brief Cria um item com uma lista.
 * 
 * @warning O novo item é criado com o "malloc", logo tem que ser libertado depois usando a função 'item_Dispose'.
 * @returns Item criado
 */
Item* icreate_List();

/** @brief Cria um item com uma lista.
 * 
 * @warning O novo item é criado com o "malloc", logo tem que ser libertado depois usando a função 'item_Dispose'.
 * @param value Lista a guardar no item
 * @returns Item criado
 */
Item* icreate_FromList(List* list);

/** @brief Cria um item com um bloco.
 * 
 * @warning O novo item é criado com o "malloc", logo tem que ser libertado depois usando a função 'item_Dispose'.
 * @param value Valor a guardar no item
 * @returns Item criado
 */
Item* icreate_Block(char* value, int size);



// Converter Items para tipos

/** @brief Pega no conteudo do item e converte-o para um long
 * 
 * @param item Apontador para o item
 * @returns Long
 */
long i_ToLong(Item* item);

/** @brief Pega no conteudo do item e converte-o para um double
 * 
 * @param item Apontador para o item
 * @returns Double
 */
double i_ToDouble(Item* item);

/** @brief Pega no conteudo do item e converte-o para um char
 * 
 * @param item Apontador para o item
 * @returns Char
 */
char i_ToChar(Item* item);

/** @brief Pega no conteudo do item e converte-o para uma string
 * 
 * @param item Apontador para o item
 * @returns String
 */
char* i_ToString(Item* item);

/** @brief Pega no conteudo do item e converte-o para uma lista
 * 
 * @param item Apontador para o item
 * @returns List
 */
List* i_ToList(Item* item);



// Funções auxiliares

/** @brief Função auxiliar para converter uma lista para uma string
 * 
 * @param list Apontador para a lista
 * @param buf Apontador para a string
 * @param offset Indice onde se vai começar a escrever na string
 * @returns Quantidade de carateres escritos na string
 */
int list_p_ToString(List* list, char* buf, int offset);
/** @brief Função auxiliar para converter um item para uma string
 * 
 * @param item Apontador para o item
 * @param buf Apontador para a string
 * @param offset Indice onde se vai começar a escrever na string
 * @returns Quantidade de carateres escritos na string
 */
int item_p_ToString(Item* item, char* buf, int offset);

/** @brief Imprime o item na consola.
 *
 * @param item Apontador para o item
 */
void item_Print(Item* item);



// Items

/** @brief Função auxiliar para mais facilmente verificar o tipo de um item
 * 
 * @param item Apontador para o item
 * @param mask Mascara usada para verificar o tipo (IT_Int, IT_Num, IT_Arr)
 * @returns 1 se o item for do tipo da mascara, 0 se não
 */
int item_IsType(Item* item, int mask);

/** @brief Cria uma cópia do item.
 * 
 * @param item Item
 * @returns Cópia do item
 */
Item* item_Copy(Item* item);

/** @brief Liberta a memória ocupada pelo item e o seu conteudo.
 * 
 * @param item Item
 */
void item_Dispose(Item* item);

/** @brief Liberta a memória ocupada pelo item (apenas o struct).
 * 
 * @param item Item
 */
void item_Free(Item* item);

/** @brief Verifica se dois items sao iguais.
 * 
 * @param itemA Lista 
 * @param itemB Lista 
 * @returns 1 ou 0
 */
int item_Equals(Item* itemA, Item* itemB);

/** @brief Troca o conteudo de dois items.
 * 
 * @param ia Primeiro item
 * @param ib Segundo item
 */
void item_Swap(Item* ia, Item* ib);



// Listas

/** @brief Cria uma lista.
 * 
 * @warning A nova lista é criada com o "malloc", logo tem que ser libertada depois usando a função 'list_Dispose'.
 * @param initialSize Tamanho da lista (Se <= 0, o tamanho passa para 25)
 * @returns Nova lista
 */
List* list_Create(int initialSize);

/** @brief Cria uma lista com um 'range'.
 * 
 * @warning A nova lista é criada com o "malloc", logo tem que ser libertada depois usando a função 'list_Dispose'.
 * @param n Tamanho da lista (Se <= 0, o tamanho passa para 25)
 * @returns Nova lista
 */
List* list_CreateRange(int n);

/** @brief Aumenta a capacidade de uma lista
 * 
 * @param list Apontador para a lista
 * @param extraSize Tamanho a adicionar à lista
 */
void list_IncreaseSize(List* list, int extraSize);

/** @brief Cria uma cópia de uma lista.
 * 
 * @warning A nova lista é criada com o "malloc", logo tem que ser libertada depois usando a função 'list_Dispose'.
 * @param list Lista original
 * @returns Cópia da lista
 */
List* list_Copy(List* list);

/** @brief Liberta a memória ocupada pela lista e os seus items
 * 
 * @param list Lista
 */
void list_Dispose(List* list);

/** @brief Liberta a memória ocupada pela lista.
 * 
 * @param list Lista
 */
void list_Free(List* list);

/** @brief Verifica se duas listas sao iguais.
 * 
 * @param listA Lista 
 * @param listB Lista 
 * @returns 1 ou 0
 */
int list_Equals(List* listA, List* listB);


/** @brief Adiciona um item a uma lista.
 * 
 * @param list Lista
 * @param item Item a adicionar
 */
void list_Add(List* list, Item* item);

/** @brief Adiciona um item a uma lista.
 * 
 * @param list Lista
 * @param item Item a adicionar
 * @param index Indice onde se vai inserir o item
 */
void list_AddAt(List* list, Item* item, int index);

/** @brief Adiciona uma lista a uma lista.
 * 
 * @param list Lista
 * @param range Lista a adicionar
 */
void list_AddRange(List* list, List* range);

/** @brief Adiciona uma lista a uma lista, copiando os valores.
 * 
 * @param list Lista
 * @param range Lista a adicionar
 */
void list_AddCopyRange(List* list, List* range);


/** @brief Desloca a lista, a partir de um indice, para a esquerda.
 * 
 * @param list Lista
 * @param index Indice do inicio
 */
void list_ShiftLeft(List* list, int index);

/** @brief Desloca a lista, a partir de um indice, para a esquerda.
 * 
 * @param list Lista
 * @param i Indice do inicio
 * @param n Quantidade a deslocar
 */
void list_ShiftLeftN(List* list, int i, int n);

/** @brief Desloca a lista, a partir de um indice, para a direita.
 * 
 * @param list Lista
 * @param index Indice do inicio
 */
void list_ShiftRight(List* list, int index);

/** @brief Desloca a lista, a partir de um indice, para a direita.
 * 
 * @param list Lista
 * @param index Indice do inicio
 * @param n Quantidade a deslocar
 */
void list_ShiftRightN(List* list, int index, int n);


/** @brief Remove um item de uma lista.
 * 
 * @param list Lista
 * @returns Item removido
 */
Item* list_Remove(List* list);

/** @brief Remove um item de uma lista.
 * 
 * @param list Lista
 * @param i Indice do item a ser removido
 * @returns Item removido
 */
Item* list_RemoveAt(List* list, int i);

/** @brief Troca a ordem dos items da lista
 * 
 * @param list Lista
 * @returns Lista reversa
 */
List* list_Reverse(List* list);


/** @brief Cria uma lista com todos os chars da string
 * 
 * @param string Apontador para a string
 * @param size Tamanho da string
 * @returns Apontador para a Lista
 */
List* list_FromString(char* string, int size);



