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
 * @param unsafe 0=Nao permite valores repetidos, 1=Permite valores repetidos
 * @return 0=Sucesso na alocacao, 1=Falha na alocação, 2=Valor ja existe na tupla
 */
int tuple_int_add_internal(tuple_int* arr, int value, int unsafe) {
  int* tmp;
  int prev_length = arr->length;
  if (arr->data == NULL) {
    // Alloca inicialmente o vetor
    arr->length = 1;
    tmp = (int*) malloc(arr->length * sizeof(int));
  } else {
    if (unsafe == 0) {
      // Ignora o valor caso ja exista na Tupla
      for (int i = 0; i < arr->length; i++) {
        if (arr->data[i] == value) {
          // Valor ja existe na tupla
          return 2;
        }
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
 * Adiciona um valor inteiro a uma tupla de valores inteiros
 * @param arr    Tupla
 * @param value  Valor a ser adicionado
 * @return 0=Sucesso na alocacao, 1=Falha na alocação, 2=Valor ja existe na tupla
 */
int tuple_int_add(tuple_int* arr, int value) {
  return tuple_int_add_internal(arr, value, 0);
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
 * Libera a alocacao de memoria de uma lista de tupla
 * @param arr Ponteiro da lista de tupla
 * @param length Quantidade de items na lista
 */
void tuple_list_clear(tuple_int* arr, int length) {
  if (arr == NULL) {
    return;
  }

  for (int i=0; i<length; i++) {
    tuple_clear(&arr[i]);
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
 * Converte a tupla para uma string dinamica separada por virgula
 * Em que o primeiro numero é o tamanho da tupla e os demais os valores
 * Vale lembrar que essa string precisa ser desalocada
 * @param arr Tupla a ser convertida para string
 */
__THROW __attribute_warn_unused_result__
string tuple_int_to_csv_string(tuple_int arr) {
  string str = {};
  const int length = 50;
  char buffer[length];

  sprintf(buffer, "%d", arr.length);
  string_append(&str, buffer);
  sprintf(buffer, ", ");
  string_append(&str, buffer);
  for (int i=0; i<arr.length; i++) {
    sprintf(buffer, "%d%s", tuple_int_get(arr, i), i == arr.length - 1 ? "" : ", ");
    string_append(&str, buffer);
  }

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
 * Recebe a tupla de um arquivo binario
 * @param arr    Tupla a ser recebida
 * @param f_name Nome do arquivo
 * @return 0=Sucesso, 1=Falha na abertura do arquivo
 */
int tuple_int_read_file_bin(tuple_int *arr, const char* f_name) {
  int length;
  int value;
  FILE *arq;

  // Abre arquivo para escrita no modo binario
  arq = fopen(f_name, "rb");

  if (arq == NULL) {
    // Falha na abertura do arquivo
    return 1;
  }

  // Le o tamanho da tupla no arquivo
  fread(&length, sizeof(int), 1, arq);
  for (int i=0; i<length; i++) {
    // Le os itens da tupla no arquivo
    fread(&value, sizeof(int), 1, arq);
    // Adiciona item lido na tupla
    tuple_int_add(arr, value);
  }

  // Fecha o arquivo
  fclose(arq);

  return 0;
}

/**
 * Salva a tupla em um arquivo no modo texto separado por virgulas
 * @param arr
 * @param f_name
 * @return
 */
int tuple_int_save_file_txt(tuple_int arr, const char* f_name) {
  FILE *arq;

  // Abre arquivo para escrita no modo binario
  arq = fopen(f_name, "w");

  if (arq == NULL) {
    // Falha na abertura do arquivo
    return 1;
  }

  // Converte o vetor para uma string csv
  string csv = tuple_int_to_csv_string(arr);

  // Escreve conteudo no arquivo
  fwrite(csv.buffer, csv.length * sizeof(char), 1, arq);

  // Fecha o arquivo
  fclose(arq);

  // Libera memoria allocada para o csv
  string_clear(&csv);

  return 0;
}

/**
 * Adiciona uma matriz de tupla de inteiro em um arquivo no modo texto separado por virgulas
 * em que cada linha denota uma tupla da matriz
 * @param arr    tuple_int[] Contendo as tupla de inteiros
 * @param length Tamanho da lista de tupla a serem escritas no arquivo
 * @param f_name Nome do arquivo
 * @param modes  Modo de escrita no arquivo    w -> Escrita substitui, a -> Escrita adiciona conteudo no arquivo
 * @param add_break Quantidade de quebras de linha a serem adicionados no final do arquivo
 * @return 0=Sucesso, 1=Erro ao abrir arquivo
 */
int tuple_int_list_save_file_txt(tuple_int* arr, int length, const char* f_name, const char* modes, int add_break) {
  FILE *arq;

  // Abre arquivo para escrita no modo binario
  arq = fopen(f_name, modes);

  if (arq == NULL) {
    // Falha na abertura do arquivo
    return 1;
  }

  for (int i=0; i<length; i++) {
    // Converte o vetor para uma string csv
    string csv = tuple_int_to_csv_string(arr[i]);
    // Escreve conteudo no arquivo
    fwrite(csv.buffer, csv.length * sizeof(char), 1, arq);
    // Libera memoria alocada para o csv
    string_clear(&csv);

    if (i < length - 1) {
      // Adiciona quebra de linha no arquivo
      fwrite("\n", 1 * sizeof(char), 1, arq);
    }

    if (i == length - 1) {
      // Ultima linha do arquivo
      while(add_break-- >= 0) {
        // Adiciona quebra de linha adicional no arquivo
        fwrite("\n", 1 * sizeof(char), 1, arq);
      }
    }
  }

  // Fecha o arquivo
  fclose(arq);

  return 0;
}

/**
 * Recebe uma matriz de listas de inteiro de um arquivo no modo texto separado por virgulas
 * em que cada linha denota uma lista da matriz
 * @param arr    tuple_int[] Contendo as listas de inteiros
 * @param length Tamanho do buffer tuple_int[]
 * @param f_name Nome do arquivo
 * @param r_len  Quantidade de tupla lidas do arquivo
 * @return 0=Sucesso, 1=Erro ao abrir arquivo
 */
int tuple_int_list_read_file_txt(tuple_int* arr, int length, const char* f_name, int* r_len) {
  FILE *arq;

  int line_pos = 0;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  // Zera a quantidade de tupla lidas
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
      tuple_int_from_csv_string(&arr[line_pos], csv);

      // Incrementa a quantidade de tupla lidas
      *r_len += 1;
    }

    line_pos++;
  }

  if (line_pos > length) {
    printf("O tamanho do buffer não coube o total de tupla %d presente no arquivo.", line_pos);
  }

  // Libera alocacao dinamica do buffer
  free(line);
  line = NULL;
  len = 0;

  // Fecha o arquivo
  fclose(arq);

  return 0;
}

/**
 * Gerador de subconjuntos recursivo
 * @param p_tuple     Buffer da lista de conjuntos que irá armazenar todos os subconjuntos potencia
 * @param length      Tamanho do buffer da lista de conjuntos
 * @param cur_length  Tamanho atual da quantidade de conjuntos no buffer
 * @param add_offset  Offset de onde continuar a adicao de novos itens na lista
 * @param arr         Conjunto ao qual será utilizado para gerar os subconjuntos potencia
 * @param data        Vetor de inteiros temporarios que armazena o subconjunto da combinação corrente
 * @param r           Posição atual da iteração acerca do conjunto utilizado para gerar os subconjuntos. Usado para delimitar o fim da recursão do subconjunto que está sendo gerado.
 * @param index       Indice utilizado para incluir ou excluir o elemento atual ao gerar as combinações
 * @param i           Posição do valor do subconjunto utilizado para gerar os subconjuntos potencia que será salvo no subconjunto atual data[]
 * @return Quantidade de subconjuntos encontrados
 */
int tuple_int_power_sets_part(tuple_int* p_tuple, int length, int cur_length, int add_offset, tuple_int arr, int* data, int r, int index, int i) { // NOLINT(misc-no-recursion)
  if (index == r) {
    printf("{");
    // Exibe a combinacao
    for (int x = 0; x < r; x++) {
      printf("%d%s", data[x], (x == r - 1 ? "" : ","));

      // Posicao no buffer onde inserir os valores do subconjunto atual
      int p_tuple_pos = add_offset + cur_length;
      if (p_tuple != NULL && p_tuple_pos < length) {
        // Salva o conjunto potencia na lista de conjuntos potencia
        tuple_int_add(&p_tuple[p_tuple_pos], data[x]);
      }
    }
    printf("}");
    printf(" ");
    return cur_length + 1;
  }

  // Quando não houver mais elementos para colocar no vetor de subconjuntos atual -> data[]
  if (i >= arr.length) {
    return cur_length;
  }

  // Inclui o elemento atual e gera combinações de forma recursiva
  data[index] = tuple_int_get(arr, i);
  cur_length = tuple_int_power_sets_part(p_tuple, length, cur_length, add_offset, arr, data, r, index + 1, i + 1);

  // Exclui o elemento atual e gera combinações sem ele
  cur_length = tuple_int_power_sets_part(p_tuple, length, cur_length, add_offset, arr, data, r, index, i + 1);
  return cur_length;
}

/**
 * Gera todas os subconjuntos de forma recursiva
 * @param p_tuple     Buffer da lista de conjuntos que irá armazenar todos os subconjuntos potencia
 * @param length      Tamanho do buffer da lista de conjuntos
 * @param cur_length  Tamanho atual da quantidade de conjuntos no buffer
 * @param add_offset  Offset de onde continuar a adicao de novos itens na lista
 * @param arr         Conjunto ao qual será utilizado para gerar os subconjuntos potencia
 * @param r           Posição atual da iteração acerca do conjunto utilizado para gerar os subconjuntos. Usado para delimitar o fim da recursão do subconjunto que está sendo gerado.
 * @return            Quantidade de subconjuntos encontrados
 */
int tuple_int_power_sets_all(tuple_int* p_tuple, int length, int cur_length, int add_offset, tuple_int arr, int r) {
  int data[arr.length];
  return tuple_int_power_sets_part(p_tuple, length, cur_length, add_offset, arr, data, r, 0, 0);
}

/**
 * Recebe os conjuntos potencia de um conjunto e armazena em uma matriz de conjuntos
 * @param p_tuple     Buffer da matriz que irá armazenar os conjuntos potência
 * @param length      Tamanho do buffer da matriz que irá armazenar os conjuntos potência
 * @param add_offset  Offset de onde continuar a adicao de novos itens na lista
 * @param tuple_int   Conjunto a ter os conjuntos potencia extraidos
 * @param proper_sets 0=Gera conjuntos potencia, 1=Gera conjuntos próprios
 * return             Quantidade de subconjuntos encontrados
 */
int tuple_int_power_sets(tuple_int* p_tuple, int length, int add_offset, tuple_int arr, int proper_sets) {
  int cur_length = 0;
  int iter_length = arr.length;
  if (proper_sets == 1) {
    iter_length -= 1;
  }
  printf("{} ");
  for (int i=1; i<=iter_length; i++) {
    cur_length = tuple_int_power_sets_all(p_tuple, length, cur_length, add_offset, arr, i);
  }

  printf("-> %d subconjuntos %s encontrados\n", cur_length, proper_sets == 1 ? "proprios" : "potencia");

  return cur_length;
}

/**
 * Uniao de dois conjuntos
 *
 * @param u_tuple Conjunto que ira armazenar a uniao de A e B
 * @param tup1  Conjunto A
 * @param tup2  Conjunto B
 */
void tuple_int_union(tuple_int* u_tuple, tuple_int tup1, tuple_int tup2) {
  // OBS: A adicao de elementos já é um metodo de uniao pois somente adiciona valores unicos na tupla
  // Adiciona elementos do conjunto A
  for (int i=0; i<tup1.length; i++) {
    tuple_int_add(u_tuple, tuple_int_get(tup1, i));
  }
  // Adiciona elementos do conjunto B
  for (int i=0; i<tup2.length; i++) {
    tuple_int_add(u_tuple, tuple_int_get(tup2, i));
  }
}

/**
 * Calcula a interseção de dois conjuntos e armazena no conjunto intersection
 * @param intersection  Intersecao dos conjuntos
 * @param tup1          Conjunto A
 * @param tup2          Conjunto B
 * @param int_inverted   0=Intersecao de A com B, 1=Intersecao de B com A
 */
void tuple_int_intersection_internal(tuple_int* intersection, tuple_int tup1, tuple_int tup2, int int_inverted) { // NOLINT(misc-no-recursion)
  int pertence;
  for (int i=0; i<tup1.length; i++) {
    pertence = 0;
    for (int x=0; x<tup2.length; x++) {
      if (tuple_int_get(tup1, i) == tuple_int_get(tup2, x)) {
        // Valor do conjunto A pertence ao conjunto B
        pertence = 1;
      }
    }
    if (pertence == 1) {
      tuple_int_add(intersection, tuple_int_get(tup1, i));
    }
  }

  // Calcula a intersecao de B com A
  if (int_inverted == 0) {
    tuple_int_intersection_internal(intersection, tup1, tup2, 1);
  }
}

/**
 * Calcula a interseção de dois conjuntos e armazena no conjunto intersection
 * @param intersection  Intersecao dos conjuntos
 * @param tup1          Conjunto A
 * @param tup2          Conjunto B
 */
void tuple_int_intersection(tuple_int* intersection, tuple_int tup1, tuple_int tup2) {
  tuple_int_intersection_internal(intersection, tup1, tup2, 0);
}

/**
 * Calcula a diferenca entre dois conjuntos A - B.
 * A diferença entre dois conjuntos é caracterizada pelos elementos que pertencem somente ao primeiro conjunto (Conjunto A)
 * @param diff Diferenca dos conjuntos
 * @param tup1 Conjunto A
 * @param tup2 Conjunto B
 */
void tuple_int_diff(tuple_int* diff, tuple_int tup1, tuple_int tup2) {
  int pertence;
  for (int i=0; i<tup1.length; i++) {
    pertence = 0;
    for (int x=0; x<tup2.length; x++) {
      if (tuple_int_get(tup1, i) == tuple_int_get(tup2, x)) {
        // Valor do conjunto A pertence ao conjunto B
        pertence = 1;
      }
    }
    if (pertence == 0) {
      tuple_int_add(diff, tuple_int_get(tup1, i));
    }
  }
}

/**
 * Calcula o produto cartesiano entre dois conjuntos A * B
 * @param prod Buffer do produto cartesiano dos conjuntos. É uma matriz contendo vários subconjuntos
 * @param length Tamanho do buffer do produto cartesiano
 * @param tup1 Conjunto A
 * @param tup2 Conjunto B
 * @return Quantidade de subconjuntos do produto cartesiano
 */
int tuple_int_cartesian_product(tuple_int* prod, int length, tuple_int tup1, tuple_int tup2) {
  int r_length = 0;
  for (int i=0; i<tup1.length; i++) {
    for (int x=0; x<tup2.length; x++) {
      tuple_int_add_internal(&prod[r_length], tuple_int_get(tup1, i), 1);
      tuple_int_add_internal(&prod[r_length], tuple_int_get(tup2, x), 1);
      r_length++;
    }
  }
  return r_length;
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
