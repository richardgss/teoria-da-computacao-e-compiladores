//
// Created by Richard on 28/09/2023.
//

#ifndef D_ARRAY_H
#define D_ARRAY_H

#include <stdio.h>
#include <malloc.h>
#include "dstring.h"
#include <stdlib.h>

typedef struct d_arr_int {
  int length;
  int* data;
} arr_int;

/**
 * Adiciona um valor inteiro a uma lista de valores inteiros
 * @param arr    Array
 * @param value  Valor a ser adicionado
 * @return 0=Sucesso na alocacao, 1=Falha na alocação
 */
int arr_int_add(arr_int* arr, int value) {
  int* tmp;
  int prev_length = arr->length;
  if (arr->data == NULL) {
    // Alloca inicialmente o vetor
    arr->length = 1;
    tmp = (int*) malloc(arr->length * sizeof(int));
  } else {
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
 * Le um valor da lista na posicao especificada
 * @param arr  Lista
 * @param pos  Posicao a receber o valor
 * @return
 */
int arr_int_get(arr_int arr, int pos) {
  if (pos < arr.length && pos >= 0) {
    return arr.data[pos];
  }
  return 0;
}

/**
 * Libera a alocacao de memoria da lista
 * @param arr
 */
void arr_clear(arr_int* arr) {
  if (arr->data != NULL) {
    free(arr->data);
    arr->length = 0;
    arr->data = NULL;
  }
}

/**
 * Converte o vetor para uma string dinamica
 * Vale lembrar que essa string precisa ser desalocada
 * @param arr Lista a ser convertida para string
 */
__THROW __attribute_warn_unused_result__
string arr_int_to_string(arr_int arr) {
  string str = {};
  const int length = 50;
  char buffer[length];

  sprintf(buffer, "{ ");
  string_append(&str, buffer);
  for (int i=0; i<arr.length; i++) {
    sprintf(buffer, "%d%s", arr_int_get(arr, i), i == arr.length - 1 ? "" : ", ");
    string_append(&str, buffer);
  }
  sprintf(buffer, " }");
  string_append(&str, buffer);

  return str;
}

/**
 * Converte o vetor para uma string dinamica separada por virgula
 * Em que o primeiro numero é o tamanho da lista e os demais os valores
 * Vale lembrar que essa string precisa ser desalocada
 * @param arr Lista a ser convertida para string
 */
__THROW __attribute_warn_unused_result__
string arr_int_to_csv_string(arr_int arr) {
  string str = {};
  const int length = 50;
  char buffer[length];

  sprintf(buffer, "%d", arr.length);
  string_append(&str, buffer);
  sprintf(buffer, ", ");
  string_append(&str, buffer);
  for (int i=0; i<arr.length; i++) {
    sprintf(buffer, "%d%s", arr_int_get(arr, i), i == arr.length - 1 ? "" : ", ");
    string_append(&str, buffer);
  }

  return str;
}

/**
 * Convert a string dinamica separada por virgula para um vetor
 * Em que o primeiro numero é o tamanho da lista e os demais os valores
 * @param arr Lista que irá receber os dados
 * @param str Dados do csv
 */
void arr_int_from_csv_string(arr_int *arr, string str) {
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
      arr_int_add(arr, value);
    }

    // Get the next token
    token = strtok(NULL, ",");

    offset++;
  }
}

/**
 * Imprime o conteudo da lista de inteiros na tela
 * @param arr Lista a ser impresso o conteudo
 */
void arr_int_print(arr_int arr) {
  string str = arr_int_to_string(arr);
  printf("%s", str.buffer);
  string_clear(&str);
}

/**
 * Salva a em um arquivo binario
 * @param arr    Lista a ser salva
 * @param f_name Nome do arquivo
 * @return 0=Sucesso, 1=Falha na abertura do arquivo
 */
int arr_int_save_file_bin(arr_int arr, const char* f_name) {
  FILE *arq;

  // Abre arquivo para escrita no modo binario
  arq = fopen(f_name, "wb");

  if (arq == NULL) {
    // Falha na abertura do arquivo
    return 1;
  }

  // Salva o tamanho da lista no arquivo
  fwrite(&arr.length, sizeof(int), 1, arq);
  for (int i=0; i<arr.length; i++) {
    // Salva os itens da lista no arquivo
    fwrite(&arr.data[i], sizeof(int), 1, arq);
  }

  // Fecha o arquivo
  fclose(arq);

  return 0;
}

/**
 * Recebe a lista de um arquivo binario
 * @param arr    Lista a ser recebida
 * @param f_name Nome do arquivo
 * @return 0=Sucesso, 1=Falha na abertura do arquivo
 */
int arr_int_read_file_bin(arr_int *arr, const char* f_name) {
  int length;
  int value;
  FILE *arq;

  // Abre arquivo para escrita no modo binario
  arq = fopen(f_name, "rb");

  if (arq == NULL) {
    // Falha na abertura do arquivo
    return 1;
  }

  // Le o tamanho da lista no arquivo
  fread(&length, sizeof(int), 1, arq);
  for (int i=0; i<length; i++) {
    // Le os itens da lista no arquivo
    fread(&value, sizeof(int), 1, arq);
    // Adiciona item lido na lista
    arr_int_add(arr, value);
  }

  // Fecha o arquivo
  fclose(arq);

  return 0;
}

/**
 * Salva a lista em um arquivo no modo texto separado por virgulas
 * @param arr
 * @param f_name
 * @return
 */
int arr_int_save_file_txt(arr_int arr, const char* f_name) {
  FILE *arq;

  // Abre arquivo para escrita no modo binario
  arq = fopen(f_name, "w");

  if (arq == NULL) {
    // Falha na abertura do arquivo
    return 1;
  }

  // Converte o vetor para uma string csv
  string csv = arr_int_to_csv_string(arr);

  // Escreve conteudo no arquivo
  fwrite(csv.buffer, csv.length * sizeof(char), 1, arq);

  // Fecha o arquivo
  fclose(arq);

  // Libera memoria allocada para o csv
  string_clear(&csv);

  return 0;
}

/**
 * Adiciona uma matriz de listas de inteiro em um arquivo no modo texto separado por virgulas
 * em que cada linha denota uma lista da matriz
 * @param arr    arr_int[] Contendo as listas de inteiros
 * @param length Tamanho da matriz de listas a serem escritas no arquivo
 * @param f_name Nome do arquivo
 * @return 0=Sucesso, 1=Erro ao abrir arquivo
 */
int arr_int_list_save_file_txt(arr_int* arr, int length, const char* f_name) {
  FILE *arq;

  // Abre arquivo para escrita no modo binario
  arq = fopen(f_name, "w");

  if (arq == NULL) {
    // Falha na abertura do arquivo
    return 1;
  }

  for (int i=0; i<length; i++) {
    // Converte o vetor para uma string csv
    string csv = arr_int_to_csv_string(arr[i]);
    // Escreve conteudo no arquivo
    fwrite(csv.buffer, csv.length * sizeof(char), 1, arq);
    // Libera memoria alocada para o csv
    string_clear(&csv);

    if (i < length - 1) {
      // Adiciona quebra de linha no arquivo
      fwrite("\n", 1 * sizeof(char), 1, arq);
    }
  }

  // Fecha o arquivo
  fclose(arq);

  return 0;
}

/**
 * Recebe uma matriz de listas de inteiro de um arquivo no modo texto separado por virgulas
 * em que cada linha denota uma lista da matriz
 * @param arr    arr_int[] Contendo as listas de inteiros
 * @param length Tamanho da matriz de listas a serem escritas no arquivo
 * @param f_name Nome do arquivo
 * @param r_len  Quantidade de listas da matriz lidas do arquivo
 * @return 0=Sucesso, 1=Erro ao abrir arquivo
 */
int arr_int_list_read_file_txt(arr_int* arr, int length, const char* f_name, int* r_len) {
  FILE *arq;

  int line_pos = 0;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  // Zera a quantidade de listas lidas
  *r_len = 0;

  // Abre arquivo para escrita no modo binario
  arq = fopen(f_name, "r");

  if (arq == NULL) {
    // Falha na abertura do arquivo
    return 1;
  }

  // Recebe as linhas do arquivo
  while ((read = getline(&line, &len, arq)) != -1) {
    // Converte a linha recebida para uma string dinamica
    string csv = {(int) read, line};

    if (line_pos < length) {
      // Se o tamanho do buffer couber o conteudo recebido adiciona,
      // caso contrario ignora
      arr_int_from_csv_string(&arr[line_pos], csv);

      // Incrementa a quantidade de listas lidas
      *r_len += 1;
    }

    line_pos++;
  }

  if (line_pos > length) {
    printf("O tamanho do buffer não coube o total de listas %d presente no arquivo.", line_pos);
  }

  // Libera alocacao dinamica do buffer
  free(line);
  line = NULL;
  len = 0;

  // Fecha o arquivo
  fclose(arq);

  return 0;
}

#endif //D_ARRAY_H
