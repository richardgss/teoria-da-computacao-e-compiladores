//
// Created by Richard on 28/09/2023.
//

#ifndef D_TUPLE_H
#define D_TUPLE_H

#include <stdio.h>
#include <malloc.h>
#include "dstring.h"
#include <stdlib.h>

typedef struct d_tuple_int {
  int length;
  int* data;
} tuple_int;

/**
 * Adiciona um valor inteiro a uma tupla de valores inteiros
 * @param arr    Tupla
 * @param value  Valor a ser adicionado
 * @return 0=Sucesso na alocacao, 1=Falha na alocação, 2=Valor ja existe na tupla
 */
int tuple_int_add(tuple_int* arr, int value) {
  int* tmp;
  int prev_length = arr->length;
  if (arr->data == NULL) {
    // Alloca inicialmente o vetor
    arr->length = 1;
    tmp = (int*) malloc(arr->length * sizeof(int));
  } else {
    // Ignora o valor caso ja exista na Tupla
    for (int i=0; i<arr->length; i++) {
      if (arr->data[i] == value) {
          // Valor ja existe na tupla
          return 2;
      }
    }
      
    // Realoca dinamicamente o vetor incrementando 1 no tamanho anterior
    arr->length += 1;
    tmp = (int*) realloc(arr->data, arr->length * sizeof(int));
  }

  if (tmp != NULL) {
    // Alocacao funcionou salva a nova lista
    arr->data = tmp;
    arr->data[arr->length - 1] = value;
    return 0;
  } else {
    // Restaura o tamanho original da lista
    arr->length = prev_length;
    return 1;
  }
}

/**
 * Le um valor da tupla na posicao especificada
 * @param arr  Tupla
 * @param pos  Posicao a receber o valor
 * @return
 */
int tuple_int_get(tuple_int arr, int pos) {
  if (pos < arr.length && pos >= 0) {
    return arr.data[pos];
  }
  return 0;
}

/**
 * Libera a alocacao de memoria da tupla
 * @param arr Ponteiro da tupla
 */
void tuple_clear(tuple_int* arr) {
  if (arr->data != NULL) {
    free(arr->data);
    arr->length = 0;
    arr->data = NULL;
  }
}

/**
 * Converte a tupla para uma string dinamica
 * Vale lembrar que essa string precisa ser desalocada
 * @param arr Tupla a ser convertida para string
 */
__THROW __attribute_warn_unused_result__
string tuple_int_to_string(tuple_int arr) {
  string str = {};
  const int length = 50;
  char buffer[length];

  sprintf(buffer, "{ ");
  string_append(&str, buffer);
  for (int i=0; i<arr.length; i++) {
    sprintf(buffer, "%d%s", tuple_int_get(arr, i), i == arr.length - 1 ? "" : ", ");
    string_append(&str, buffer);
  }
  sprintf(buffer, " }");
  string_append(&str, buffer);

  return str;
}

/**
 * Convert a string dinamica separada por virgula para uma tupla
 * Em que o primeiro numero é o tamanho da tupla e os demais os valores
 * @param arr Tupla que irá receber os dados
 * @param str Dados do csv
 */
void tuple_int_from_csv_string(tuple_int *arr, string str) {
  int offset = 0;
  int value;

  // Tokenizing the string
  char *token = strtok(str.buffer, ",");

  // Loop through the tokens
  while (token != NULL) {
    // Converte o valor para inteiro
    value = atoi(token); // NOLINT(cert-err34-c)

    if (offset != 0) {
      // Ignora a posicao zero pois nao precisamos do tamanho da lista
      tuple_int_add(arr, value);
    }

    // Get the next token
    token = strtok(NULL, ",");

    offset++;
  }
}

/**
 * Imprime o conteudo da tupla de inteiros na tela
 * @param arr Tupla a ser impresso o conteudo
 */
void tuple_int_print(tuple_int arr) {
  string str = tuple_int_to_string(arr);
  printf("%s", str.buffer);
  string_clear(&str);
}

/**
 * Salva a tupla em um arquivo binario
 * @param arr    Tupla a ser salva
 * @param f_name Nome do arquivo
 * @return 0=Sucesso, 1=Falha na abertura do arquivo
 */
int tuple_int_save_file_bin(tuple_int arr, const char* f_name) {
  FILE *arq;

  // Abre arquivo para escrita no modo binario
  arq = fopen(f_name, "wb");

  if (arq == NULL) {
    // Falha na abertura do arquivo
    return 1;
  }

  // Salva o tamanho da tupla no arquivo
  fwrite(&arr.length, sizeof(int), 1, arq);
  for (int i=0; i<arr.length; i++) {
    // Salva os itens da tupla no arquivo
    fwrite(&arr.data[i], sizeof(int), 1, arq);
  }

  // Fecha o arquivo
  fclose(arq);

  return 0;
}

/**
 * Converte a lista de inteiros para uma tupla
 * @param arr Lista a ter o conteudo convertido
 */
void tuple_from_arr_int(tuple_int* tup, arr_int arr) {
  for (int i=0; i<arr.length; i++) {
    tuple_int_add(tup, arr_int_get(arr, i));
  }
}


#endif //D_TUPLE_H
