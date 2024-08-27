/**
 * @file Varias funções uteis
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/** @brief Copia parte de uma string para outra.
 * 
 * @warning A nova string é criada com o "calloc", logo tem que ser libertada depois.
 * @param original Apontador para a string original
 * @param size Tamanho da nova string
 * @returns Nova string que é copiada da original
 */
char* utils_Substring(char* original, int size)
{
    // O +1 é importante porque a string tem que acabar com '\0'
    char* new = calloc(size + 1, sizeof(char));
    memcpy(new, original, size);
    new[size] = '\0';
    return new;
}

/** @brief Cria uma string com uma string várias vezes repetida.
 * 
 * @warning A nova string é criada com o "calloc", logo tem que ser libertada depois.
 * @param original Apontador para a string original
 * @param size Tamanho da nova string
 * @param times Número de vezes a ser repetida
 * @returns Nova string
 */
char* utils_RepeatString(char* original, int size, int times)
{
    // O +1 é importante porque a string tem que acabar com '\0'
    char* new = calloc((size * times) + 1, sizeof(char));
    for (int i = 0; i < times; i++)
        memcpy(new + (i * size), original, size);
    new[size * times] = '\0';
    return new;
}

/** @brief Cria uma cópia de uma string.
 * 
 * @warning A nova string é criada com o "calloc", logo tem que ser libertada depois.
 * @param string Apontador para a string original
 * @returns Nova string
 */
char* utils_CopyString(char* string)
{
    int size = strlen(string);
    return utils_Substring(string, size);
}

/** @brief Cria uma string que é a junção de duas.
 * 
 * @warning A nova string é criada com o "calloc", logo tem que ser libertada depois.
 * @param s1 Apontador para a primeira string
 * @param s2 Apontador para a segunda string
 * @returns Junção das duas strings
 */
char* utils_ConcatString(char* s1, char* s2)
{
    int l1 = strlen(s1), l2 = strlen(s2);
    char* new = calloc(l1 + l2 + 1, sizeof(char));
    memcpy(new, s1, l1);
    memcpy(new + l1, s2, l2);
    new[l1 + l2] = '\0';
    return new;
}

/** @brief Cria uma string que se substitui 'sub' por 'rep'.
 * 
 * @warning A nova string é criada com o "calloc", logo tem que ser libertada depois.
 * @param str Apontador para a primeira string
 * @param sub Apontador para a segunda string
 * @param rep Apontador para a terceira string
 * @returns Junção das duas strings
 */
char* utils_StringReplace(char* str, char* sub, char* rep)
{
    int sstr = strlen(str), ssub = strlen(sub), srep = strlen(rep); 
    int subcount = 0;
    char* strPtr, *subPtr;
    for (strPtr = str; (subPtr = strstr(strPtr, sub)); strPtr = subPtr + ssub)
        subcount++;
    int newLen = sstr + subcount * (srep - ssub);
    char* newBuffer = calloc(newLen + 1, sizeof(char));
    char* repPtr = newBuffer;
    for (strPtr = str; (subPtr = strstr(strPtr, sub)); strPtr = subPtr + ssub)
    {
        int sklen = subPtr - strPtr;
        memcpy(repPtr, strPtr, sklen);
        repPtr += sklen;
        memcpy(repPtr, rep, srep);
        repPtr += srep;
    }
    memcpy(repPtr, strPtr, strlen(strPtr));
    return newBuffer;
}


/** @brief Obtém uma linha da 'stdin'.
 * 
 * @param size Out: O tamanho da string
 * @returns NULL ou a linha
 */
char* utils_GetLine(int* size)
{
    char* buffer = calloc(DefaultStringBufferSize, sizeof(char));
    if (fgets(buffer, DefaultStringBufferSize, stdin) != NULL)
    {
        *size = strlen(buffer);
        // Remove o '\n' no final
        if (buffer[*size - 1] == '\n')
            *size = *size - 1;
        // A função 'utils_Substring' remove o espaço desperdiçado e adiciona o '\0' no final
        char* string = utils_Substring(buffer, *size);
        free(buffer); // liberta o buffer original
        return string;
    }
    *size = 0;
    free(buffer);
    return NULL;
}

/** @brief Obtém uma linha da 'stdin'.
 * 
 * @warning Esta função utiliza um buffer externo para evitar 'calloc's e 'free's desnecessários
 * @param size Out: O tamanho da string
 * @returns NULL ou a linha
 */
char* utils_GetLine_NC(int* size, char* tempBuffer, int tempBufferSize)
{
    if (fgets(tempBuffer, tempBufferSize, stdin) != NULL)
    {
        *size = strlen(tempBuffer);
        // Remove o '\n' no final
        if (tempBuffer[*size - 1] == '\n')
            *size = *size - 1;
        // A função 'utils_Substring' remove o espaço desperdiçado e adiciona o '\0' no final
        char* string = utils_Substring(tempBuffer, *size);
        return string;
    }
    *size = 0;
    return NULL;
}

/** @brief Obtém várias linhas da 'stdin'.
 * 
 * @param size Out: O tamanho da string
 * @returns NULL ou a linha
 */
char* utils_GetAllLines(int* size)
{
    char* buffer = calloc(DefaultStringBufferSize, sizeof(char));
    int offset = 0;
    while (fgets(buffer + offset, DefaultStringBufferSize, stdin) != NULL)
    {
        offset += strlen(buffer + offset);
    }
    *size = offset;
    buffer[offset] = '\0';
    if (offset == 0)
    {
        free(buffer);
        return NULL;
    }
    char* s = calloc(offset + 1, sizeof(char));
    memcpy(s, buffer, offset + 1);
    free(buffer);
    return s;
}



/** @brief Tenta encontrar um char numa string.
 * 
 * @param string A string onde se vai procurar o char
 * @param c Char
 * @returns -1 se a string não tiver o char ou o indice da primeira vez onde aparece o char
 */
int utils_FindChar(char* string, char c)
{
    int i = 0;
    while(string[i] != '\0')
    {
        if (string[i] == c)
            return i;
        i++;
    }
    return -1;
}

/** @brief Tenta encontrar um char numa string.
 * 
 * @param string A string onde se vai procurar o char
 * @param size Tamanho máximo onde pode estar o char
 * @param c Char
 * @returns -1 se a string não tiver o char ou o indice da primeira vez onde aparece o char
 */
int utils_FindCharSub(char* string, int size, char c)
{
    int i = 0;
    while(string[i] != '\0' && i < size)
    {
        if (string[i] == c)
            return i;
        i++;
    }
    return -1;
}

/** @brief Tenta encontrar um char numa string.
 * 
 * @param string A string onde se vai procurar o char
 * @param i Indice do inicio
 * @param c Char
 * @returns O indice da primeira vez onde aparece o char, ou o fim da string
 */
int utils_NextChar(char* string, int i, char c)
{
    while(string[i] != '\0')
    {
        if (string[i] == c)
            return i;
        i++;
    }
    return i;
}



/** @brief Cria uma cópia de um char.
 * 
 * @warning O novo char é criado com o "calloc", logo tem que ser libertado depois.
 * @param c Char
 * @returns Novo char
 */
char* utils_CopyChar(char c)
{
    char* new = calloc(1, sizeof(char));
    *new = c;
    return new;
}

/** @brief Cria uma cópia de um long ou double.
 * 
 * @warning O novo número é criado com o "calloc", logo tem que ser libertado depois.
 * Esta função funciona tanto para doubles como longs, pois estes tem o mesmo tamanho.
 * 
 * @param original Número original
 * @returns Novo número
 */
void* utils_CopyNumber(void* original)
{
    void* new = calloc(1, sizeof(long));
    memcpy(new, original, sizeof(long));
    return new;
}



/** @brief Converte uma string para um long
 * 
 * @warning Esta função retorna 0 se a string não for válida para ter sempre algum long.
 * @param buf String
 * @returns Long convertido da string
 */
long utils_LongFromString(char* buf)
{
    long out;
    if (sscanf(buf, "%ld", &out) != 1)
        return 1;
    return out;
}

/** @brief Converte uma string para um double
 * 
 * @warning Esta função retorna 0 se a string não for válida para ter sempre algum double.
 * @param buf String
 * @returns Double convertido da string
 */
double utils_DoubleFromString(char* buf)
{
    double out;
    if (sscanf(buf, "%lg", &out) != 1)
        return 1.0;
    return out;
}

/** @brief "Converte" uma string para um char
 * 
 * @param buf String
 * @returns Primeiro char da string
 */
char utils_CharFromString(char* buf)
{ return buf[0]; }

/** @brief Compara 2 strings.
 *  
 * @param s1 String 1
 * @param s2 String 2
 * @returns 1 ou 0
 */
int utils_StringEquals(char* s1, char* s2)
{
    int i = 0;
    while (s1[i] == s2[i])
    {
        if (s1[i] == '\0')
            return 1;
        i++;
    }
    return 0;
}

/** @brief Compara 2 strings.
 *  
 * @param s1 String 1
 * @param s2 String 2
 * @returns -1, 0 ou 1
 */
int utils_StringCompare(char* a, char* b)
{
    int i = 0;
    if (a[0] < b[0])
        return -1;
    if (a[0] > b[0])
        return 1;
    while (a[i] == b[i] && a[i] != '\0')
    {
        if (a[i] < b[i])
            return -1;
        if (a[i] > b[i])
            return 1;
        i++;
    }
    return 0;
}


/** @brief Compara 2 doubles.
 *  
 * @param a Double 1
 * @param a Double 2
 * @returns 1 ou 0
 */
int utils_DoubleEquals(double a, double b)
{
    if (fabs(a - b) < 4.9E-64)
        return 1;
    return 0;
}


/** @brief Imprime a string na consola, mas pelo número do char separado por vírgulas.
 * 
 * @warning A string não imprime um '\\n' no final.
 * @param string String
 */
void debug_PrintString(char* string)
{
    int size = strlen(string);
    if (size <= 0)
        return;
    if (size > 1)
        for (int i = 0; i < size - 1; i++)
            printf("%d, ", string[i]);
    printf("%d", string[size - 1]);
}




