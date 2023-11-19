//
// Created by Richard on 28/09/2023.
//

#ifndef D_STRING_H
#define D_STRING_H

#include <ctype.h>
#include "string.h"
#include <stdlib.h>

typedef struct d_string {
  int length;
  char* buffer;
} string;

/**
 * Adiciona texto a uma string
 * @param str    Instancia da string
 * @param a_str  Texto a ser adicionado
 * @return 0=Sucesso, 1=Erro
 */
int string_append(string* str, const char* a_str) {
  char* tmp;
  int prev_length = str->length;
  size_t len = strlen(a_str);

  if (str->buffer == NULL) {
    // Alloca inicialmente o buffer
    str->length = (int) len;
    tmp = (char*) malloc(str->length * sizeof(char) + 1);
    // Inicializa o buffer como vazio
    tmp[0] = '\0';
  } else {
    // Realoca o buffer para caber mais texto
    str->length += (int) len;
    tmp = (char*) realloc(str->buffer, str->length * sizeof(char) + 1);
  }

  if (tmp != NULL) {
    // Adiciona o texto no final do buffer
    str->buffer = tmp;
    strcat(str->buffer, a_str);
    // Adiciona terminacao da string no buffer
    tmp[str->length] = '\0';
    return 0;
  } else {
    // Restaura o tamanho original do buffer
    str->length = prev_length;
    return 1;
  }
}

/**
 * Diminui o tamanho da string na quantia informada
 * @param str     String a ser diminuida
 * @param length  Tamanho a ser diminuido
 * @return 0=Sucesso, 1=Erro
 */
int string_decrease(string* str, int length) {
  char* tmp;
  int prev_length = str->length;

  if (length <= 0) {
    // Tamanho a ser diminuido deve ser maior que zero
    return 1;
  }

  if (str->buffer != NULL) {
    // Verifica se o tamanho a ser diminuido ficara menor que zero
    if (length < str->length) {
      str->length -= length;
    } else {
      str->length = 0;
    }

    // Realoca a memoria para um tamanho menor
    tmp = realloc(str->buffer, str->length + 1);
  }

  if (tmp != NULL) {
    // Sucesso na reducao do tamanho do buffer
    str->buffer = tmp;
    // Adiciona caracter nulo no final do buffer
    str->buffer[str->length] = '\0';
  } else {
    // Falha na reducao do tamanho do buffer volta o tamanho anterior
    str->length = prev_length;
  }

  return 0;
}

/**
 * Limpa e libera a alocacao de memoria da string
 * @param str String a ser limpa
 */
void string_clear(string* str) {
  if (str->buffer != NULL) {
    str->length = 0;
    free(str->buffer);
  }
}

/**
 * Remove espacamentos removidos a esquerda e a direta do conteudo
 * @param str  String que ira ter os espacos removidos
 */
void string_trim(string* str) {
  int start_trim = 0;
  int end_trim = 0;

  if (str->length == 0 || str->buffer == NULL) {
    // String nao alocada
    return;
  }

  // Recebe a quantidade de espacos no inicio da string
  while (start_trim < str->length && isspace(str->buffer[start_trim])) {
    start_trim++;
  }

  // Recebe a quantidade de espacos no fim da string
  while (end_trim < str->length && isspace(str->buffer[str->length - 1 - end_trim])) {
    end_trim++;
  }

  // Move conteudo da string para o inicio da string
  memmove(str->buffer, str->buffer + start_trim, str->length - end_trim);

  // Diminui o tamanho da string para o tamanho que foi removido em espacamentos
  string_decrease(str, end_trim + start_trim);
}

#endif //D_STRING_H
