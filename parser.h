/**
 * @file Conversor que pega numa linha e executa-a
 */

#pragma once


/** @brief Processa uma linha
 * 
 * @param vars Apontador para o array de variáveis
 * @param stack Apontador para o stack
 * @param line Linha da entrada
 * @param linePos Posição na linha
 * @returns O resultado do processo do ultimo char, não tem grande uso
 */
int parser_Process(Item** vars, Stack* stack, char* line, int lineSize);

/** @brief Processa uma linha imprimindo detalhes sobre cada passo
 * 
 * @param vars Apontador para o array de variáveis
 * @param stack Apontador para o stack
 * @param line Linha da entrada
 * @param linePos Posição na linha
 * @returns O resultado do processo do ultimo char, não tem grande uso
 */
int parser_DebugProcess(Item** vars, Stack* stack, char* line, int lineSize);





