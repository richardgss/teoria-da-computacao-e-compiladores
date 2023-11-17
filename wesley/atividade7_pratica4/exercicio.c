//
// Created by Richard on 15/11/2023.
//
#include <stdio.h>
#include "dstring.h"

int read_txt_file(string *str, const char* f_name, const char* modes) {
  FILE *arq;
  int line_pos = 0;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  // Abre arquivo para escrita no modo binario
  arq = fopen(f_name, modes);

  if (arq == NULL) {
    // Falha na abertura do arquivo
    return 1;
  }

  // Recebe as linhas do arquivo
  while ((read = getline(&line, &len, arq)) != -1) {
    string_append(str, line);
  }

  fclose(arq);

  return 0;
}

int append_txt_file(string *str, const char* f_name) {
  FILE *arq;

  // Abre arquivo para escrita no modo binario
  arq = fopen(f_name, "a");

  if (arq == NULL) {
    // Falha na abertura do arquivo
    return 1;
  }

  // Adiciona quebra de linha no arquivo
  fwrite("\n", 1 * sizeof(char), 1, arq);

  // Adiciona linha no arquivo
  fwrite(str->buffer, str->length * sizeof(char), 1, arq);

  fclose(arq);

  return 0;
}

int tamanho_r(string str, int pos) {
  if (str.buffer[pos] != 0) {
    return tamanho_r(str, pos + 1);
  }

  return pos;
}

void reverse_r(string *str_in, string *str_out, int pos) {
  if (pos == 0) {
    string_append(str_out, str_in->buffer);
  }

  if (str_in->length - pos > 0) {
    str_out->buffer[pos] = str_in->buffer[str_in->length - pos - 1];
    reverse_r(str_in, str_out, pos + 1);
  }
}

int main() {
  const char* f_name = "texto.txt";
  string str = {};
  string str_r = {};
  string str_len = {};
  read_txt_file(&str, f_name, "r");

  printf("texto: %s\n", str.buffer);

  int tamanho = tamanho_r(str, 0);
  printf("tamanho: %d\n", tamanho);

  reverse_r(&str, &str_r, 0);
  printf("reverso: %s\n", str_r.buffer);

  string_append(&str_len, "Tamanho: ");
  char strLen[40] = {0};
  sprintf(strLen, "%d", tamanho);
  string_append(&str_len, strLen);

  append_txt_file(&str_r, f_name);
  append_txt_file(&str_len, f_name);

  string_clear(&str);
  string_clear(&str_r);

  return 0;
}
