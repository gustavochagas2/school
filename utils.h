/**
 * @file Varias funções uteis
 */

#pragma once

/** Tamanho padrão de uma string grande */
#define DefaultStringBufferSize 20000


/** @brief Copia parte de uma string para outra.
 * 
 * @warning A nova string é criada com o "calloc", logo tem que ser libertada depois.
 * @param original Apontador para a string original
 * @param size Tamanho da nova string
 * @returns Nova string que copiada da original
 */
char* utils_Substring(char* original, int size);

/** @brief Cria uma string com uma string várias vezes repetida.
 * 
 * @warning A nova string é criada com o "calloc", logo tem que ser libertada depois.
 * @param original Apontador para a string original
 * @param size Tamanho da nova string
 * @param times Número de vezes a ser repetida
 * @returns Nova string
 */
char* utils_RepeatString(char* original, int size, int times);

/** @brief Cria uma cópia de uma string.
 * 
 * @warning A nova string é criada com o "calloc", logo tem que ser libertada depois.
 * @param string Apontador para a string original
 * @returns Nova string
 */
char* utils_CopyString(char* string);

/** @brief Cria uma string que é a junção de duas.
 * 
 * @warning A nova string é criada com o "calloc", logo tem que ser libertada depois.
 * @param s1 Apontador para a primeira string
 * @param s2 Apontador para a segunda string
 * @returns Junção das duas strings
 */
char* utils_ConcatString(char* s1, char* s2);

/** @brief Cria uma string que se substitui 'sub' por 'rep'.
 * 
 * @warning A nova string é criada com o "calloc", logo tem que ser libertada depois.
 * @param str Apontador para a primeira string
 * @param sub Apontador para a segunda string
 * @param rep Apontador para a terceira string
 * @returns Junção das duas strings
 */
char* utils_StringReplace(char* str, char* sub, char* rep);



/** @brief Obtém uma linha da 'stdin'.
 * 
 * @param size Out: O tamanho da string
 * @returns NULL ou a linha
 */
char* utils_GetLine(int* size);

/** @brief Obtém uma linha da 'stdin'.
 * 
 * @warning Esta função utiliza um buffer externo para evitar 'calloc's e 'free's desnecessários
 * @param size Out: O tamanho da string
 * @returns NULL ou a linha
 */
char* utils_GetLine_NC(int* size, char* tempBuffer, int tempBufferSize);

/** @brief Obtém várias linhas da 'stdin'.
 * 
 * @param size Out: O tamanho da string
 * @returns NULL ou a linha
 */
char* utils_GetAllLines(int* size);



/** @brief Tenta encontrar um char numa string.
 * 
 * @param string A string onde se vai procurar o char
 * @param c Char
 * @returns -1 se a string não tiver o char ou o indice da primeira vez onde aparece o char
 */
int utils_FindChar(char* string, char c);

/** @brief Tenta encontrar um char numa string.
 * 
 * @param string A string onde se vai procurar o char
 * @param size Tamanho máximo onde pode estar o char
 * @param c Char
 * @returns -1 se a string não tiver o char ou o indice da primeira vez onde aparece o char
 */
int utils_FindCharSub(char* string, int size, char c);

/** @brief Tenta encontrar um char numa string.
 * 
 * @param string A string onde se vai procurar o char
 * @param i Indice do inicio
 * @param c Char
 * @returns O indice da primeira vez onde aparece o char, ou o fim da string
 */
int utils_NextChar(char* string, int i, char c);



/** @brief Cria uma cópia de um char.
 * 
 * @warning O novo char é criado com o "calloc", logo tem que ser libertado depois.
 * @param c Char
 * @returns Novo char
 */
char* utils_CopyChar(char c);

/** @brief Cria uma cópia de um long ou double.
 * 
 * @warning O novo número é criado com o "calloc", logo tem que ser libertado depois.
 * Esta função funciona tanto para doubles como longs, pois estes tem o mesmo tamanho.
 * 
 * @param original Número original
 * @returns Novo número
 */
void* utils_CopyNumber(void* original);



/** @brief Converte uma string para um long
 * 
 * @warning Esta função retorna 0 se a string não for válida para ter sempre algum long.
 * @param buf String
 * @returns Long convertido da string
 */
long utils_LongFromString(char* buf);

/** @brief Converte uma string para um double
 * 
 * @warning Esta função retorna 0 se a string não for válida para ter sempre algum double.
 * @param buf String
 * @returns Double convertido da string
 */
double utils_DoubleFromString(char* buf);

/** @brief "Converte" uma string para um char
 * 
 * @param buf String
 * @returns Primeiro char da string
 */
char utils_CharFromString(char* buf);

/** @brief Compara 2 strings.
 *  
 * @param s1 String 1
 * @param s2 String 2
 * @returns 1 ou 0
 */
int utils_StringEquals(char* s1, char* s2);

/** @brief Compara 2 strings.
 *  
 * @param s1 String 1
 * @param s2 String 2
 * @returns -1, 0 ou 1
 */
int utils_StringCompare(char* s1, char* s2);

/** @brief Compara 2 doubles.
 *  
 * @param a Double 1
 * @param a Double 2
 * @returns 1 ou 0
 */
int utils_DoubleEquals(double a, double b);




/** @brief Imprime a string na consola, mas pelo número do char separado por vírgulas.
 * 
 * @warning A string não imprime um '\\n' no final.
 * @param string String
 */
void debug_PrintString(char* string);

